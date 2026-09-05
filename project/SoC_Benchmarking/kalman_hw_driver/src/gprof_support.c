/**
 * gprof_support.c — real _mcount implementation and gmon.out serialization
 * over UART for RISC-V bare-metal (rv32imac/ilp32, SweRV EL2 on Nexys A7).
 *
 * RISC-V -pg ABI:
 *   The compiler inserts a call to _mcount at the top of every instrumented
 *   function.  At the call site:
 *     a0  = frompc   (the original ra saved by the prologue = caller's PC)
 *     ra  = selfpc   (the return address back into _mcount's caller, i.e. the
 *                     instrumented function's own prologue — identifies the
 *                     callee)
 *   We retrieve selfpc with __builtin_return_address(0).
 *
 * ALL functions in this file carry __attribute__((no_instrument_function))
 * to prevent the compiler from inserting _mcount calls into _mcount itself,
 * which would cause infinite recursion.
 */

#include <stdint.h>

/* -------------------------------------------------------------------------
 * 16550-compatible UART at 0x80002000
 * -------------------------------------------------------------------------
 * Register map (each register word-aligned, 4-byte stride):
 *   Offset 0x00 (4*0) — THR  (write char, DLAB=0) / BRDL (baud divisor LSB, DLAB=1)
 *   Offset 0x04 (4*1) — IER  / BRDH (baud divisor MSB, DLAB=1)
 *   Offset 0x08 (4*2) — FCR
 *   Offset 0x0C (4*3) — LCR  (bit 7 = DLAB)
 *   Offset 0x14 (4*5) — LSR  (bit 5 = THRE = Transmitter Holding Register Empty)
 *   Offset 0x18 (4*6) — MSR
 *
 * D_CLOCK_RATE is injected by the PlatformIO wd-riscv-sdk framework builder
 * (default 13 MHz for the swervolf_nexys board).  The divisor formula matches
 * the BSP uartInit(): (D_CLOCK_RATE / BAUD_RATE) / 16.
 * ------------------------------------------------------------------------- */
#define UART_BASE   0x80002000U

#define UART_THR    (*((volatile uint32_t *)(UART_BASE + 0x00)))  /* Transmit Holding */
#define UART_BRDL   (*((volatile uint32_t *)(UART_BASE + 0x00)))  /* Baud Rate LSB    */
#define UART_IER    (*((volatile uint32_t *)(UART_BASE + 0x04)))  /* Int. Enable Reg  */
#define UART_BRDH   (*((volatile uint32_t *)(UART_BASE + 0x04)))  /* Baud Rate MSB    */
#define UART_FCR    (*((volatile uint32_t *)(UART_BASE + 0x08)))  /* FIFO Control     */
#define UART_LCR    (*((volatile uint32_t *)(UART_BASE + 0x0C)))  /* Line Control     */
#define UART_LSR    (*((volatile uint32_t *)(UART_BASE + 0x14)))  /* Line Status      */

#define UART_LCR_DLAB      0x80U  /* Divisor Latch Access Bit */
#define UART_LCR_8N1       0x03U  /* 8 data bits, no parity, 1 stop bit */
#define UART_LSR_THRE      0x20U  /* Transmitter Holding Register Empty */
/* FIFOs: enable (bit0) + clear RX (bit1) + clear TX (bit2) + 8-byte trigger (bit7) */
#define UART_FCR_ENABLE    0x87U

/* Baud-rate divisor: identical formula to the BSP uartInit().
 * D_CLOCK_RATE is defined by wd-riscv-sdk.py (-DD_CLOCK_RATE=13000000).
 * Fallback to 13 MHz if somehow not set.                                   */
#ifndef D_CLOCK_RATE
#  define D_CLOCK_RATE  13000000U
#endif
#define UART_BAUD_RATE    115200U
#define UART_BAUD_DIVISOR ((D_CLOCK_RATE / UART_BAUD_RATE) / 16U)

/* -------------------------------------------------------------------------
 * Arc table — records (caller → callee) call-graph edges
 *
 * Open-addressing hash table keyed by (from_pc, self_pc).
 * Size must be a power of 2.  Load factor ≤ 75 % keeps probing short.
 * Each _mcount call is O(1) average instead of the previous O(n) linear
 * scan, which was the dominant overhead when Eigen template code drove
 * millions of instrumented calls per run.
 * ------------------------------------------------------------------------- */
#define ARC_TABLE_SIZE 1024U          /* power-of-2 */
#define ARC_TABLE_MASK (ARC_TABLE_SIZE - 1U)

typedef struct {
    uint32_t from_pc;
    uint32_t self_pc;
    uint32_t count;   /* 0 = empty slot */
} arc_t;

static arc_t arc_table[ARC_TABLE_SIZE];
static uint32_t arc_count = 0U;        /* number of occupied slots */

/* Guard to prevent re-entrant _mcount (e.g. during UART output) */
static volatile uint32_t mcount_busy = 0U;

/* arc_table lives past _end and is NOT zeroed by the BSP BSS-init loop.
 * _mcount must not touch it until __monstartup() has explicitly zeroed
 * every slot.  Set to 1 at the end of __monstartup(). */
static volatile uint32_t arc_table_ready = 0U;

/* -------------------------------------------------------------------------
 * void *__dso_handle — identifies the DSO for __cxa_atexit.
 * On bare-metal there is no dynamic loader; NULL sentinel suffices.
 * Placed here so syscalls.c does not define it.
 * ------------------------------------------------------------------------- */
void *__dso_handle = (void *)0;

/* =========================================================================
 * UART initialisation (called once, lazily, before first character output)
 * ========================================================================= */
__attribute__((no_instrument_function))
void uart_init_16550(void)
{
    /* Enable DLAB to program baud-rate divisor (matches BSP uartInit order) */
    UART_LCR = UART_LCR_DLAB;

    /* Write divisor LSB only (MSB stays 0; divisor fits in 8 bits for ≤ 50 MHz) */
    UART_BRDL = UART_BAUD_DIVISOR & 0xFFU;

    /* 8N1, clear DLAB */
    UART_LCR = UART_LCR_8N1;

    /* Enable and clear FIFOs */
    UART_FCR = UART_FCR_ENABLE;

    /* Disable interrupts last (same order as BSP) */
    UART_IER = 0x00U;
}

/* =========================================================================
 * Output a single character via the 16550 UART.
 * '\n' is expanded to '\r\n' automatically.
 * ========================================================================= */
static int uart_initialised = 0;

__attribute__((no_instrument_function))
void gmon_uart_putchar(char c)
{
    if (!uart_initialised) {
        uart_init_16550();
        uart_initialised = 1;
    }

    if (c == '\n') {
        /* Wait for THRE, send CR first */
        while (!(UART_LSR & UART_LSR_THRE)) { }
        UART_THR = '\r';
    }

    /* Wait for THRE, then send the character */
    while (!(UART_LSR & UART_LSR_THRE)) { }
    UART_THR = (uint32_t)(unsigned char)c;
}

/* =========================================================================
 * _mcount — called by -pg instrumentation at every function entry.
 *
 * Calling convention (RISC-V -pg):
 *   a0  = frompc  (original ra = return address to the caller of the
 *                  instrumented function, saved in the prologue)
 *   ra  = selfpc  (__builtin_return_address(0) = address in _mcount's caller,
 *                  i.e. the instrumented function's prologue → identifies
 *                  the callee)
 * ========================================================================= */
__attribute__((no_instrument_function))
void _mcount(uint32_t frompc)
{
    /* arc_table is past _end and not zeroed by the BSP startup; skip
     * recording until __monstartup() has initialised the table. */
    if (!arc_table_ready) return;

    uint32_t selfpc = (uint32_t)__builtin_return_address(0);
    uint32_t h, idx, i;

    /* Prevent re-entrance */
    if (mcount_busy) {
        return;
    }
    mcount_busy = 1U;

    /* Drop calls when table is nearly full (>= 75 % load) to keep probing
     * short and avoid an O(n) degenerate case at high occupancy. */
    if (arc_count >= (ARC_TABLE_SIZE * 3U / 4U)) {
        mcount_busy = 0U;
        return;
    }

    /* Hash: mix both PCs with a Knuth multiplicative hash */
    h = ((frompc ^ (selfpc * 2654435761U)) >> 2U) & ARC_TABLE_MASK;

    /* Open-addressing linear probe — terminates quickly at low load */
    for (i = 0U; i < ARC_TABLE_SIZE; i++) {
        idx = (h + i) & ARC_TABLE_MASK;
        if (arc_table[idx].count == 0U) {
            /* Empty slot — insert new arc */
            arc_table[idx].from_pc = frompc;
            arc_table[idx].self_pc = selfpc;
            arc_table[idx].count   = 1U;
            arc_count++;
            break;
        }
        if (arc_table[idx].from_pc == frompc &&
            arc_table[idx].self_pc == selfpc) {
            arc_table[idx].count++;
            break;
        }
    }

    mcount_busy = 0U;
}

/* =========================================================================
 * __monstartup — reset arc table; may be called before main() to start
 * fresh profiling, or after a run to clear accumulated data.
 * ========================================================================= */
__attribute__((no_instrument_function))
void __monstartup(void)
{
    uint32_t i;
    for (i = 0U; i < ARC_TABLE_SIZE; i++) {
        arc_table[i].from_pc = 0U;
        arc_table[i].self_pc = 0U;
        arc_table[i].count   = 0U;
    }
    arc_count  = 0U;
    mcount_busy = 0U;
    arc_table_ready = 1U;   /* allow _mcount to record arcs from here on */
}

/* =========================================================================
 * write_gmon_out — serialise call-graph data in gmon.out binary format,
 * encoded as a continuous hex string sent over the 16550 UART.
 *
 * gmon.out format (little-endian 32-bit RISC-V):
 *   Header  (16 bytes):
 *     "gmon"             4 bytes  magic
 *     0x00000001         4 bytes  version (LE)
 *     0x00000000 × 3     12 bytes padding / spare
 *   Per arc (13 bytes each):
 *     0x01               1 byte   GMON_TAG_CG_ARC
 *     from_pc            4 bytes  LE
 *     self_pc            4 bytes  LE
 *     count              4 bytes  LE
 *
 * The hex string is written without spaces or newlines so that
 * extract_gmon.py can strip whitespace and call bytes.fromhex() directly.
 * ========================================================================= */

/* Helper: emit one byte as two uppercase hex ASCII characters */
__attribute__((no_instrument_function))
static void emit_hex_byte(uint8_t b)
{
    static const char hex_chars[] = "0123456789ABCDEF";
    gmon_uart_putchar(hex_chars[(b >> 4) & 0x0FU]);
    gmon_uart_putchar(hex_chars[b & 0x0FU]);
}

/* Helper: emit a 32-bit value in little-endian byte order as hex */
__attribute__((no_instrument_function))
static void emit_hex_u32_le(uint32_t v)
{
    emit_hex_byte((uint8_t)( v        & 0xFFU));
    emit_hex_byte((uint8_t)((v >>  8) & 0xFFU));
    emit_hex_byte((uint8_t)((v >> 16) & 0xFFU));
    emit_hex_byte((uint8_t)((v >> 24) & 0xFFU));
}

/* Helper: emit a NUL-terminated string via gmon_uart_putchar */
__attribute__((no_instrument_function))
static void emit_str(const char *s)
{
    while (*s) {
        gmon_uart_putchar(*s++);
    }
}

__attribute__((no_instrument_function))
void write_gmon_out(void)
{
    uint32_t i;

    /* Inhibit _mcount during output */
    mcount_busy = 1U;

    /* ---- Begin marker ---- */
    emit_str("\n<<<GMON_BEGIN>>>\n");

    /* ---- gmon.out header (16 bytes) ---- */
    /* Magic: "gmon" (4 bytes, ASCII) */
    emit_hex_byte('g');
    emit_hex_byte('m');
    emit_hex_byte('o');
    emit_hex_byte('n');
    /* Version: 1 (4 bytes LE) */
    emit_hex_u32_le(1U);
    /* Spare / padding: 12 zero bytes */
    emit_hex_u32_le(0U);
    emit_hex_u32_le(0U);
    emit_hex_u32_le(0U);

    /* ---- Arc records — iterate all slots, skip empty ones (hash table) ---- */
    for (i = 0U; i < ARC_TABLE_SIZE; i++) {
        if (arc_table[i].count == 0U) continue;
        /* Tag: GMON_TAG_CG_ARC = 0x01 */
        emit_hex_byte(0x01U);
        emit_hex_u32_le(arc_table[i].from_pc);
        emit_hex_u32_le(arc_table[i].self_pc);
        emit_hex_u32_le(arc_table[i].count);
    }

    /* ---- End marker ---- */
    emit_str("\n<<<GMON_END>>>\n");

    mcount_busy = 0U;
}
