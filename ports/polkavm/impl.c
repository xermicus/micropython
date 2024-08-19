#include <errno.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <pthread.h>
#include <math.h>
#include <fcntl.h>
#include <sys/syscall.h>

#ifdef __riscv

#include "polkavm_guest.h"

//POLKAVM_IMPORT(long, ext_stdout, long, size_t);

#endif

static void flush_stdio() {
    fflush(stdout);
    fflush(stderr);
}

__attribute__((noreturn)) void abort(void) {
    fprintf(stderr, "\nabort() called!\n");
    flush_stdio();

    POLKAVM_TRAP();
}

#define MEMORY_SIZE (16 * 1024 * 1024)

static unsigned char _MEMORY[MEMORY_SIZE];
static unsigned long _SBRK = 0;

void *sbrk(intptr_t inc) {
    if (_SBRK + inc > MEMORY_SIZE) {
        errno = ENOMEM;
        return (void*)-1;
    }

    void * p = (void *)(_MEMORY + _SBRK);
    _SBRK += inc;
    return p;
}

long __syscall_cp(long n) {
    if (n == SYS_close) {
        return 0;
    } else {
        fprintf(stderr, "WARN: unhandled syscall(0): %li\n", n);
        flush_stdio();
        return -ENOSYS;
    }
}

long __syscall1(long n, long a0) {
    switch (n) {
        case SYS_close:
        case SYS_unlink:
        {
            return 0;
        }
        default:
        {
            fprintf(stderr, "WARN: unhandled syscall(1): %li\n", n);
            flush_stdio();
            return -ENOSYS;
        }
    }
}

long __syscall2(long n, long a0, long a1) {
    switch (n) {
        case SYS_mkdir:
        case SYS_rename:
        {
            return 0;
        }
        default:
        {
            fprintf(stderr, "WARN: unhandled syscall(2): %li\n", n);
            flush_stdio();
            return -ENOSYS;
        }
    }
}

#define FD_STDOUT 1
#define FD_STDERR 2
#define FD_DUMMY 10

long __syscall3(long n, long a0, long a1, long a2) {
    switch (n) {
        /*
        case SYS_open:
        {
            const char * filename = a0;
            fprintf(stderr, "\nsys_open: '%s'\n", filename);
            flush_stdio();

            if (!strcmp(filename, "doom1.wad")) {
                fprintf(stderr, "sys_open: fetching rom size...\n");
                flush_stdio();

                ROM_SIZE = ext_rom_size();
                fprintf(stderr, "sys_open: fetched rom size: %li\n", ROM_SIZE);
                flush_stdio();

                return FD_WAD;
            } else if (!strcmp(filename, "/tmp/doom.mid")) {
                MIDI_OFFSET = 0;
                return FD_MIDI;
            } else if (!strcmp(filename, "./.savegame/temp.dsg")) {
                return FD_DUMMY;
            } else {
                return -ENOENT;
            }
        }
        case SYS_lseek:
        {
            long * offset = 0;
            long * size = 0;
            if (a0 == FD_WAD) {
                offset = &ROM_OFFSET;
                size = &ROM_SIZE;
            } else if (a0 == FD_MIDI) {
                offset = &MIDI_OFFSET;
                size = &MIDI_SIZE;
            } else if (a0 == FD_DUMMY) {
                return 0;
            } else {
                fprintf(stderr, "WARN: lseek on an unknown FD: %li\n", a0);
                flush_stdio();

                return -EBADF;
            }

            switch (a2) {
                case SEEK_SET:
                    *offset = a1;
                    break;
                case SEEK_CUR:
                    *offset += a1;
                    break;
                case SEEK_END:
                    *offset = *size + a1;
                    break;
                default:
                    return -EINVAL;
            }

            return *offset;
        }
        case SYS_ioctl:
        {
            return -ENOSYS;
        }
        case SYS_readv:
        {
            long * fd_offset = 0;
            long * fd_size = 0;
            if (a0 == FD_WAD) {
                fd_offset = &ROM_OFFSET;
                fd_size = &ROM_SIZE;
            } else if (a0 == FD_MIDI) {
                fd_offset = &MIDI_OFFSET;
                fd_size = &MIDI_SIZE;
            } else if (a0 == FD_DUMMY) {
                return 0;
            } else {
                fprintf(stderr, "WARN: read from an unknown FD: %li\n", a0);
                flush_stdio();

                return -EBADF;
            }

            const struct iovec *iov = (const struct iovec *)a1;
            long bytes_read = 0;
            for (long i = 0; i < a2; ++i) {
                long remaining = *fd_size - *fd_offset;
                long length = iov[i].iov_len;
                if (remaining < length) {
                    length = remaining;
                }
                if (length == 0) {
                    break;
                }

                if (a0 == FD_WAD) {
                    ext_rom_read(iov[i].iov_base, ROM_OFFSET, length);
                } else {
                    memcpy(iov[i].iov_base, MIDI + *fd_offset, length);
                }
                *fd_offset += length;
                bytes_read += length;
            }

            return bytes_read;
        }
        case SYS_writev:
        {
            long (*write)(long, size_t) = NULL;
            if (a0 == FD_STDOUT || a0 == FD_STDERR) {
                write = ext_stdout;
            } else if (a0 == FD_MIDI) {
                write = write_midi;
            } else if (a0 == FD_DUMMY) {
                write = write_dummy;
            } else {
                fprintf(stderr, "WARN: write into an unknown FD: %li\n", a0);
                flush_stdio();

                return -EBADF;
            }

            const struct iovec *iov = (const struct iovec *)a1;
            long bytes_written = 0;
            for (long i = 0; i < a2; ++i) {
                long result = write(iov[i].iov_base, iov[i].iov_len);
                if (result < 0) {
                    return result;
                }
                bytes_written += result;
            }

            return bytes_written;
        } */
        default:
        {
            fprintf(stderr, "WARN: unhandled syscall(3): %li\n", n);
            flush_stdio();

            return -ENOSYS;
        }
    }
}

long __syscall4(long n, long a0, long a1, long a2, long a3) {
    fprintf(stderr, "WARN: unhandled syscall(4): %li\n", n);
    flush_stdio();

    return -ENOSYS;
}

long __syscall6(long n, long a0, long a1, long a2, long a3, long a4, long a5) {
    fprintf(stderr, "WARN: unhandled syscall(6): %li\n", n);
    flush_stdio();

    return -ENOSYS;
}


// EXPORTS

extern int main(int argc, char **argv);
void ext_initialize() {
    main(0,0);
}

#ifdef __riscv

POLKAVM_EXPORT(void, ext_initialize);

#endif

extern int read(int fildes, void *buf, size_t nbyte) {
    return 0;
}

extern int open(const char *, int, ...) {

}