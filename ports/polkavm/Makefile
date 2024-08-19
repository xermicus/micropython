# Include the core environment definitions; this will set $(TOP).
include ../../py/mkenv.mk
include mpconfigport.mk

# qstr definitions (must come before including py.mk)
QSTR_DEFS = qstrdefsport.h

# Include py core make definitions.
include $(TOP)/py/py.mk
include $(TOP)/extmod/extmod.mk

GIT_SUBMODULES += lib/berkeley-db-1.xx

# Set CFLAGS and libraries.
CFLAGS += -I. -I$(BUILD) -I$(TOP)
LIBS += \
    /Users/cyrill/code/revive/llvm18.0/lib/unknown/libclang_rt.builtins-riscv32.a \

CC = clang
CXX = clang
LD = ld.lld

MUSL_ROOT = libs/musl-1.2.4
DLMALLOC_ROOT = libs/dlmalloc
LIBCXX_ROOT = libs/libcxx

ABI = ilp32e
ARCH ?= rv32emc
ARCH_LD ?= rv32emc
LDSCRIPT = virt.ld
AFLAGS = --target=riscv32-unknown-none-elf -mabi=$(ABI) -march=$(ARCH) \

CFLAGS += $(AFLAGS) 
CFLAGS += \
    -nostdlib \
    -nodefaultlibs \
    -static \
    -mrelax \
    -fpic \
    -fPIE \
    -ffast-math \
    -fno-exceptions \
    -fno-rtti \
    -Oz \
    -DHAVE_O_CLOEXEC \
    -D_GNU_SOURCE \
    -DHAVE_MMAP=0 \
    -DHAVE_MREMAP=0 \
    -Dmalloc_getpagesize=16384 \
    -DMORECORE_CANNOT_TRIM=1 \
    -Dconstinit="" \

CFLAGS += \
    -Iinclude \
    -I$(MUSL_ROOT)/src/include \
    -I$(MUSL_ROOT)/include \
    -I$(MUSL_ROOT)/src/internal \
    -I$(MUSL_ROOT)/src/multibyte \
    -I$(MUSL_ROOT)/arch/generic \
    #-I$(LIBCXX_ROOT)/include \

CXXFLAGS += $(CFLAGS) -std=c++20

LDFLAGS += -T $(LDSCRIPT) -EL -L $(MUSL_ROOT)/lib 

LDFLAGS += $(SPECS_FRAGMENT) -Map=$(@:.elf=.map)
LDFLAGS += --error-limit=0 --emit-relocs --no-relax --relocatable -static
LDFLAGS += 

# SRC_CXX = \
#     $(LIBCXX_ROOT)/src/new.cpp \
#     $(LIBCXX_ROOT)/src/new_helpers.cpp \
#     $(LIBCXX_ROOT)/src/new_handler.cpp \
#     $(LIBCXX_ROOT)/src/verbose_abort.cpp \
#     $(LIBCXX_ROOT)/src/string.cpp \

# Define the required source files.
SRC_C = \
	main.c \
	impl.c \
	mphalport.c \
	impl_dummy_libc.c \
	shared/runtime/stdout_helpers.c \
    $(DLMALLOC_ROOT)/malloc.c \
    $(MUSL_ROOT)/src/locale/__lctrans.c \
    $(MUSL_ROOT)/src/locale/c_locale.c \
    $(MUSL_ROOT)/src/errno/__errno_location.c \
    $(MUSL_ROOT)/src/errno/strerror.c \
    $(MUSL_ROOT)/src/exit/assert.c \
    $(MUSL_ROOT)/src/string/strspn.c \
    $(MUSL_ROOT)/src/string/strcspn.c \
    $(MUSL_ROOT)/src/string/strlen.c \
    $(MUSL_ROOT)/src/string/strcasecmp.c \
    $(MUSL_ROOT)/src/string/strchr.c \
    $(MUSL_ROOT)/src/string/strchrnul.c \
    $(MUSL_ROOT)/src/string/strcmp.c \
    $(MUSL_ROOT)/src/string/strdup.c \
    $(MUSL_ROOT)/src/string/strncasecmp.c \
    $(MUSL_ROOT)/src/string/strncmp.c \
    $(MUSL_ROOT)/src/string/strncpy.c \
    $(MUSL_ROOT)/src/string/strrchr.c \
    $(MUSL_ROOT)/src/string/strstr.c \
    $(MUSL_ROOT)/src/string/strnlen.c \
    $(MUSL_ROOT)/src/string/strlcpy.c \
    $(MUSL_ROOT)/src/string/stpncpy.c \
    $(MUSL_ROOT)/src/string/strtok_r.c \
    $(MUSL_ROOT)/src/string/memset.c \
    $(MUSL_ROOT)/src/string/memcpy.c \
    $(MUSL_ROOT)/src/string/memchr.c \
    $(MUSL_ROOT)/src/string/memrchr.c \
    $(MUSL_ROOT)/src/string/memcmp.c \
    $(MUSL_ROOT)/src/string/memmove.c \
    $(MUSL_ROOT)/src/string/wcschr.c \
    $(MUSL_ROOT)/src/string/wcslen.c \
    $(MUSL_ROOT)/src/string/wcsnlen.c \
    $(MUSL_ROOT)/src/string/wmemchr.c \
    $(MUSL_ROOT)/src/string/wmemcmp.c \
    $(MUSL_ROOT)/src/stdio/__overflow.c \
    $(MUSL_ROOT)/src/stdio/__fdopen.c \
    $(MUSL_ROOT)/src/stdio/__toread.c \
    $(MUSL_ROOT)/src/stdio/__towrite.c \
    $(MUSL_ROOT)/src/stdio/__lockfile.c \
    $(MUSL_ROOT)/src/stdio/__stdio_close.c \
    $(MUSL_ROOT)/src/stdio/__stdio_read.c \
    $(MUSL_ROOT)/src/stdio/__stdio_seek.c \
    $(MUSL_ROOT)/src/stdio/__stdio_write.c \
    $(MUSL_ROOT)/src/stdio/__stdio_exit.c \
    $(MUSL_ROOT)/src/stdio/__stdout_write.c \
    $(MUSL_ROOT)/src/stdio/__fmodeflags.c \
    $(MUSL_ROOT)/src/stdio/__uflow.c \
    $(MUSL_ROOT)/src/stdio/ftrylockfile.c \
    $(MUSL_ROOT)/src/stdio/ofl.c \
    $(MUSL_ROOT)/src/stdio/ofl_add.c \
    $(MUSL_ROOT)/src/stdio/stderr.c \
    $(MUSL_ROOT)/src/stdio/stdin.c \
    $(MUSL_ROOT)/src/stdio/stdout.c \
    $(MUSL_ROOT)/src/stdio/snprintf.c \
    $(MUSL_ROOT)/src/stdio/vsnprintf.c \
    $(MUSL_ROOT)/src/stdio/vfprintf.c \
    $(MUSL_ROOT)/src/stdio/printf.c \
    $(MUSL_ROOT)/src/stdio/sscanf.c \
    $(MUSL_ROOT)/src/stdio/ftell.c \
    $(MUSL_ROOT)/src/stdio/fwrite.c \
    $(MUSL_ROOT)/src/stdio/fseek.c \
    $(MUSL_ROOT)/src/stdio/fread.c \
    $(MUSL_ROOT)/src/stdio/fprintf.c \
    $(MUSL_ROOT)/src/stdio/fopen.c \
    $(MUSL_ROOT)/src/stdio/fflush.c \
    $(MUSL_ROOT)/src/stdio/ferror.c \
    $(MUSL_ROOT)/src/stdio/fclose.c \
    $(MUSL_ROOT)/src/stdio/vsscanf.c \
    $(MUSL_ROOT)/src/stdio/vfscanf.c \
    $(MUSL_ROOT)/src/stdio/putchar.c \
    $(MUSL_ROOT)/src/stdio/puts.c \
    $(MUSL_ROOT)/src/stdio/fputs.c \
    $(MUSL_ROOT)/src/stdio/remove.c \
    $(MUSL_ROOT)/src/stdio/rename.c \
    $(MUSL_ROOT)/src/stdio/feof.c \
    $(MUSL_ROOT)/src/stdio/fgets.c \
    $(MUSL_ROOT)/src/stdio/fputc.c \
    $(MUSL_ROOT)/src/stdio/fputwc.c \
    $(MUSL_ROOT)/src/stdio/fwide.c \
    $(MUSL_ROOT)/src/stdio/swprintf.c \
    $(MUSL_ROOT)/src/stdio/vfwprintf.c \
    $(MUSL_ROOT)/src/stdio/vswprintf.c \
    $(MUSL_ROOT)/src/stdlib/abs.c \
    $(MUSL_ROOT)/src/stdlib/atoi.c \
    $(MUSL_ROOT)/src/stdlib/atof.c \
    $(MUSL_ROOT)/src/stdlib/strtod.c \
    $(MUSL_ROOT)/src/stdlib/strtol.c \
    $(MUSL_ROOT)/src/stdlib/wcstod.c \
    $(MUSL_ROOT)/src/stdlib/wcstol.c \
    $(MUSL_ROOT)/src/stat/mkdir.c \
    $(MUSL_ROOT)/src/ctype/islower.c \
    $(MUSL_ROOT)/src/ctype/isupper.c \
    $(MUSL_ROOT)/src/ctype/isdigit.c \
    $(MUSL_ROOT)/src/ctype/toupper.c \
    $(MUSL_ROOT)/src/ctype/tolower.c \
    $(MUSL_ROOT)/src/ctype/iswspace.c \
    $(MUSL_ROOT)/src/math/__fpclassifyl.c \
    $(MUSL_ROOT)/src/math/__signbitl.c \
    $(MUSL_ROOT)/src/math/frexpl.c \
    $(MUSL_ROOT)/src/math/fmodl.c \
    $(MUSL_ROOT)/src/math/scalbn.c \
    $(MUSL_ROOT)/src/math/scalbnl.c \
    $(MUSL_ROOT)/src/math/copysignl.c \
    $(MUSL_ROOT)/src/math/sin.c \
    $(MUSL_ROOT)/src/math/ceil.c \
    $(MUSL_ROOT)/src/math/floor.c \
    $(MUSL_ROOT)/src/math/floorf.c \
    $(MUSL_ROOT)/src/math/exp.c \
    $(MUSL_ROOT)/src/math/exp2.c \
    $(MUSL_ROOT)/src/math/log.c \
    $(MUSL_ROOT)/src/math/sqrt.c \
    $(MUSL_ROOT)/src/math/round.c \
    $(MUSL_ROOT)/src/math/sqrt_data.c \
    $(MUSL_ROOT)/src/math/exp_data.c \
    $(MUSL_ROOT)/src/math/log_data.c \
    $(MUSL_ROOT)/src/math/__cos.c \
    $(MUSL_ROOT)/src/math/__sin.c \
    $(MUSL_ROOT)/src/math/__math_divzero.c \
    $(MUSL_ROOT)/src/math/__math_invalid.c \
    $(MUSL_ROOT)/src/math/__math_uflow.c \
    $(MUSL_ROOT)/src/math/__math_oflow.c \
    $(MUSL_ROOT)/src/math/__math_xflow.c \
    $(MUSL_ROOT)/src/math/__rem_pio2.c \
    $(MUSL_ROOT)/src/math/__rem_pio2_large.c \
    $(MUSL_ROOT)/src/multibyte/mbsinit.c \
    $(MUSL_ROOT)/src/multibyte/mbrtowc.c \
    $(MUSL_ROOT)/src/multibyte/wctomb.c \
    $(MUSL_ROOT)/src/multibyte/wcrtomb.c \
    $(MUSL_ROOT)/src/multibyte/internal.c \
    $(MUSL_ROOT)/src/multibyte/btowc.c \
    $(MUSL_ROOT)/src/multibyte/mbtowc.c \
    $(MUSL_ROOT)/src/unistd/lseek.c \
    $(MUSL_ROOT)/src/unistd/close.c \
    $(MUSL_ROOT)/src/thread/__lock.c \
    $(MUSL_ROOT)/src/internal/shgetc.c \
    $(MUSL_ROOT)/src/internal/floatscan.c \
    $(MUSL_ROOT)/src/internal/intscan.c \
    $(MUSL_ROOT)/src/internal/libc.c \
    $(MUSL_ROOT)/src/internal/syscall_ret.c \
	# shared/runtime/pyexec.c \
	# shared/readline/readline.c \
	# shared/runtime/gchelper_generic.c \

# Define source files containung qstrs.
# SRC_QSTR += shared/readline/readline.c shared/runtime/pyexec.c
SRC_QSTR += $(SRC_COMMON_C) $(SRC_RUN_C) $(LIB_SRC_C)

# Define the required object files.
OBJ = $(PY_CORE_O) $(addprefix $(BUILD)/, $(SRC_C:.c=.o)) 

# Define the top-level target, the main firmware.
all: $(BUILD)/firmware.elf

# Define how to build the firmware.
$(BUILD)/firmware.elf: $(OBJ)
	$(ECHO) "LINK $@"
	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
	polkatool link -o $(BUILD)/firmware.pvm $(BUILD)/firmware.elf
#	$(Q)$(LD) $(LDFLAGS) -o $@ $^ $(LIBS)
#	$(Q)$(SIZE) $@

# Include remaining core make rules.
include $(TOP)/py/mkrules.mk
