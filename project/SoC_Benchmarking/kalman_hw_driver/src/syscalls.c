/**
 * syscalls.c — bare-metal system call stubs for the Kalman HW driver project.
 *
 * Stripped from project/RVfpgaEL2_profiling/src/syscalls.c:
 *   - Removed gprof arc_table / write_gmon_out (no -pg flag in this project)
 *   - __wrap__exit halts with ebreak directly (no UART flush)
 *   - All other stubs unchanged
 *
 * Heap: bump allocator starting at _sp (top of 4 KB stack in link.lds).
 * get_bump_top() is read by GDB to measure heap usage; for the HW driver
 * with no Eigen, heap usage should remain ~0 B throughout the run.
 */

#include <sys/stat.h>
#include <stdint.h>
#include <stddef.h>

/* -------------------------------------------------------------------------
 * Heap: bump allocator — same layout as RVfpgaEL2_profiling/syscalls.c
 * ------------------------------------------------------------------------- */
extern char _sp[];
static char *bump_top = 0;

void *_sbrk(ptrdiff_t incr) {
    if (bump_top == 0) bump_top = _sp;
    char *prev = bump_top;
    bump_top += incr;
    return (void *)prev;
}

void *__wrap_malloc(size_t n) {
    if (n == 0) n = 1;
    n = (n + 15u) & ~15u;   /* 16-byte alignment */
    if (bump_top == 0) bump_top = _sp;
    char *ptr = bump_top;
    bump_top += n;
    if (bump_top > (char *)0x04000000U) { bump_top = ptr; return (void *)0; }
    return (void *)ptr;
}

void __wrap_free(void *p) { (void)p; }

/* Return current bump allocator high-water mark.
 * GDB reads kf_heap_start and kf_heap_end (set in main.cpp via this function)
 * and computes heap_bytes = kf_heap_end - kf_heap_start. */
uint32_t get_bump_top(void) {
    if (bump_top == 0) return (uint32_t)(uintptr_t)_sp;
    return (uint32_t)(uintptr_t)bump_top;
}

/* -------------------------------------------------------------------------
 * Newlib / WD-SDK retargetable stubs
 * ------------------------------------------------------------------------- */
int _write(int fd, const void *buf, size_t nbyte) {
    /* UART unreliable on this bitstream; discard all output */
    (void)fd; (void)buf;
    return (int)nbyte;
}

int _read(int fd, void *buf, size_t nbyte)  { (void)fd; (void)buf; (void)nbyte; return -1; }
int _close(int fd)                          { (void)fd; return -1; }
int _fstat(int fd, struct stat *st)         { (void)fd; (void)st; return 0; }
int _isatty(int fd)                         { (void)fd; return 1; }
off_t _lseek(int fd, off_t o, int w)       { (void)fd; (void)o; (void)w; return 0; }
int _getpid(void)                           { return 1; }
int _kill(int pid, int sig)                 { (void)pid; (void)sig; return -1; }

void __wrap__exit(int status) {
    (void)status;
    __builtin_trap();   /* ebreak — caught by GDB/OpenOCD */
}

int __wrap_write(int fd, const void *buf, size_t n)   { return _write(fd, buf, n); }
int __wrap_read(int fd, void *buf, size_t n)           { return _read(fd, buf, n); }
int __wrap_close(int fd)                               { return _close(fd); }
int __wrap_fstat(int fd, struct stat *st)              { return _fstat(fd, st); }
int __wrap_isatty(int fd)                              { return _isatty(fd); }
off_t __wrap_lseek(int fd, off_t o, int w)            { return _lseek(fd, o, w); }
int __wrap_getpid(void)                                { return _getpid(); }
int __wrap_kill(int pid, int sig)                      { return _kill(pid, sig); }
void *__wrap_sbrk(ptrdiff_t n)                        { return _sbrk(n); }

int __wrap_open(const char *p, int f, ...)  { (void)p; (void)f; return -1; }
int __wrap_stat(const char *p, struct stat *st)        { (void)p; (void)st; return -1; }
int __wrap_link(const char *o, const char *n)          { (void)o; (void)n; return -1; }
int __wrap_unlink(const char *p)                       { (void)p; return -1; }
int __wrap_fork(void)                                  { return -1; }
int __wrap_wait(int *s)                                { (void)s; return -1; }
long __wrap_times(void *buf)                           { (void)buf; return -1; }
int __wrap_execve(const char *p, char *const a[],
                  char *const e[])                     { (void)p; (void)a; (void)e; return -1; }
