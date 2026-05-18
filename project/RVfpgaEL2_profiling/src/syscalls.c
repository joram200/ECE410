/**
 * syscalls.c — bare-metal system call stubs for RVfpgaEL2 (rv32imac/ilp32).
 *
 * The WD RISC-V SDK builds with -nostdlib and wraps standard C functions via
 * -Wl,--wrap=malloc etc., requiring __wrap_* implementations from the
 * application.  Newlib also expects retargetable _write/_sbrk/... stubs.
 * This file provides both sets.
 *
 * UART output: 16550-compatible UART at 0x80002000 (same base as bsp_printf.c).
 * Heap: grows upward from _sp (top of the 4 KB stack reserved by link.lds)
 *       into the remaining 64 MB SRAM — plenty of room for Eigen matrices.
 *
 * NOTE: _mcount and __dso_handle are defined in gprof_support.c.
 *       write_gmon_out() is declared here as extern and called from
 *       __wrap__exit so that profiling data is flushed on program exit.
 */

#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

/* Defined in gprof_support.c — serialises arc table to UART as gmon.out */
extern void write_gmon_out(void);

/* -------------------------------------------------------------------------
 * UART helpers — 16550-compatible UART at 0x80002000
 *
 * Register map (word-aligned, 4-byte stride):
 *   0x00 — THR  (write char, DLAB=0) / BRDL (baud divisor LSB, DLAB=1)
 *   0x04 — IER  / BRDH (baud divisor MSB, DLAB=1)
 *   0x08 — FCR
 *   0x0C — LCR  (bit 7 = DLAB)
 *   0x14 — LSR  (bit 5 = THRE = Transmitter Holding Register Empty)
 *
 * D_CLOCK_RATE is injected by the PlatformIO wd-riscv-sdk framework builder
 * (default 13 MHz for swervolf_nexys).  Divisor formula matches BSP uartInit().
 * ------------------------------------------------------------------------- */
#define UART_BASE           0x80002000U
#define UART_THR_REG        (*((volatile uint32_t *)(UART_BASE + 0x00)))
#define UART_BRDL_REG       (*((volatile uint32_t *)(UART_BASE + 0x00)))
#define UART_IER_REG        (*((volatile uint32_t *)(UART_BASE + 0x04)))
#define UART_BRDH_REG       (*((volatile uint32_t *)(UART_BASE + 0x04)))
#define UART_FCR_REG        (*((volatile uint32_t *)(UART_BASE + 0x08)))
#define UART_LCR_REG        (*((volatile uint32_t *)(UART_BASE + 0x0C)))
#define UART_LSR_REG        (*((volatile uint32_t *)(UART_BASE + 0x14)))

#define UART_LCR_DLAB       0x80U  /* Divisor Latch Access Bit */
#define UART_LCR_8N1        0x03U  /* 8 data bits, no parity, 1 stop bit */
#define UART_LSR_THRE       0x20U  /* Transmitter Holding Register Empty */
/* FIFOs: enable (bit0) + clear RX (bit1) + clear TX (bit2) + 8-byte trigger (bit7) */
#define UART_FCR_ENABLE     0x87U

/* Baud-rate divisor: identical formula to BSP uartInit().
 * D_CLOCK_RATE is -DD_CLOCK_RATE=13000000 from wd-riscv-sdk.py.           */
#ifndef D_CLOCK_RATE
#  define D_CLOCK_RATE  13000000U
#endif
#define UART_BAUD_RATE    115200U
#define UART_BAUD_DIVISOR ((D_CLOCK_RATE / UART_BAUD_RATE) / 16U)

static int syscalls_uart_initialised = 0;

static void syscalls_uart_init(void) {
    UART_LCR_REG  = UART_LCR_DLAB;                  /* enable DLAB          */
    UART_BRDL_REG = UART_BAUD_DIVISOR & 0xFFU;      /* divisor LSB          */
    UART_LCR_REG  = UART_LCR_8N1;                   /* 8N1, clear DLAB      */
    UART_FCR_REG  = UART_FCR_ENABLE;                /* enable & clear FIFOs */
    UART_IER_REG  = 0x00U;                          /* disable interrupts   */
}

static void uart_putchar(char c) {
    if (!syscalls_uart_initialised) {
        syscalls_uart_init();
        syscalls_uart_initialised = 1;
    }
    if (c == '\n') {
        while (!(UART_LSR_REG & UART_LSR_THRE)) { }
        UART_THR_REG = '\r';
    }
    while (!(UART_LSR_REG & UART_LSR_THRE)) { }
    UART_THR_REG = (uint32_t)(unsigned char)c;
}

/* -------------------------------------------------------------------------
 * Heap: start at _sp (top of the linker-script stack section) and grow up.
 * -------------------------------------------------------------------------
 * link.lds lays out:
 *   _end   = end of BSS
 *   .stack { _heap_end = .; . += 4K; _sp = .; }
 * So _sp = _end + 4 K.  The heap lives from _sp upward in the 64 MB SRAM.
 * ------------------------------------------------------------------------- */
extern char _sp[];          /* provided by link.lds */
static char *heap_top = 0;

void *_sbrk(ptrdiff_t incr) {
    if (heap_top == 0) heap_top = _sp;
    char *prev = heap_top;
    heap_top += incr;
    return (void *)prev;
}

/* -------------------------------------------------------------------------
 * Newlib retargetable syscall stubs
 * ------------------------------------------------------------------------- */
int _write(int fd, const void *buf, size_t nbyte) {
    /* UART TX is unreliable in this bitstream (FIFO never drains).
     * Discard cout/printf output so the firmware does not hang in the
     * uart_putchar busy-wait.  Profiling data is captured via GDB memory
     * dump at the write_gmon_out breakpoint, so UART output is not needed. */
    (void)fd; (void)buf;
    return (int)nbyte;
}

int _read(int fd, void *buf, size_t nbyte) {
    (void)fd; (void)buf; (void)nbyte;
    return -1;
}

int _close(int fd)                        { (void)fd; return -1; }
int _fstat(int fd, struct stat *st)       { (void)fd; (void)st; return 0; }
int _isatty(int fd)                       { (void)fd; return 1; }
off_t _lseek(int fd, off_t off, int wh)  { (void)fd; (void)off; (void)wh; return 0; }
int _getpid(void)                         { return 1; }
int _kill(int pid, int sig)               { (void)pid; (void)sig; return -1; }

/* -------------------------------------------------------------------------
 * __wrap_malloc / __wrap_free — bump allocator
 *
 * newlib's __real_malloc (dlmalloc) silently returns NULL under --wrap=malloc
 * in this bare-metal configuration even when _sbrk has room, because the
 * dlmalloc internal state and sbrk interaction is not reliable here.
 *
 * A bump allocator is sufficient: Eigen matrices are allocated once and never
 * resized during the profiling run; free() calls are safe no-ops.
 * The heap grows upward from _sp into the 64 MB SRAM.
 * ------------------------------------------------------------------------- */
static char *bump_top = 0;

void *__wrap_malloc(size_t n) {
    if (n == 0) n = 1;
    /* 16-byte alignment so Eigen's handmade_aligned_malloc works correctly */
    n = (n + 15u) & ~15u;
    if (bump_top == 0) bump_top = _sp;
    char *ptr = bump_top;
    bump_top += n;
    /* 64 MB RAM ends at 0x04000000; return NULL only on genuine OOM */
    if (bump_top > (char *)0x04000000U) { bump_top = ptr; return (void *)0; }
    return (void *)ptr;
}

void  __wrap_free(void *p) { (void)p; /* bump allocator: no-op */ }

void __wrap__exit(int status) {
    (void)status;
    /* Flush gmon.out profiling data over UART before halting */
    write_gmon_out();
    __builtin_trap();   /* generates ebreak — GDB/OpenOCD will catch this */
}

/* All remaining wrapped POSIX calls: forward to our stubs or no-op. */
int __wrap_write(int fd, const void *buf, size_t n)        { return _write(fd, buf, n); }
int __wrap_read(int fd, void *buf, size_t n)               { return _read(fd, buf, n); }
int __wrap_close(int fd)                                   { return _close(fd); }
int __wrap_fstat(int fd, struct stat *st)                  { return _fstat(fd, st); }
int __wrap_isatty(int fd)                                  { return _isatty(fd); }
off_t __wrap_lseek(int fd, off_t off, int wh)             { return _lseek(fd, off, wh); }
int __wrap_getpid(void)                                    { return _getpid(); }
int __wrap_kill(int pid, int sig)                          { return _kill(pid, sig); }
void *__wrap_sbrk(ptrdiff_t n)                            { return _sbrk(n); }

int __wrap_open(const char *p, int f, ...)  { (void)p; (void)f; return -1; }
int __wrap_stat(const char *p, struct stat *st)            { (void)p; (void)st; return -1; }
int __wrap_link(const char *o, const char *n)              { (void)o; (void)n; return -1; }
int __wrap_unlink(const char *p)                           { (void)p; return -1; }
int __wrap_fork(void)                                      { return -1; }
int __wrap_wait(int *s)                                    { (void)s; return -1; }
long __wrap_times(void *buf)                               { (void)buf; return -1; }
int __wrap_execve(const char *p, char *const a[],
                  char *const e[])                         { (void)p; (void)a; (void)e; return -1; }
