#include <stdint.h>

// #define MICROPY_CONFIG_ROM_LEVEL                (MICROPY_CONFIG_ROM_LEVEL_MINIMUM)

// Python internal features.
#define MICROPY_PERSISTENT_CODE_LOAD            (1)
#define MICROPY_READER_POSIX                    (1)
#define MICROPY_ENABLE_COMPILER                 (1)
#define MICROPY_PY_BUILTINS_EVAL_EXEC           (1)
#define MICROPY_PY_BUILTINS_EXECFILE            (1)
#define MICROPY_MODULE_FROZEN                   (0)
#define MICROPY_HELPER_REPL                     (0)
#define MICROPY_REPL_INFO                       (0)
#define MICROPY_ENABLE_GC                       (0)
#define MICROPY_ERROR_REPORTING                 (MICROPY_ERROR_REPORTING_NONE)
#define MICROPY_FLOAT_IMPL                      (0)

// Fine control over Python builtins, classes, modules, etc.
#define MICROPY_PY_ASYNC_AWAIT                  (0)
#define MICROPY_PY_BUILTINS_SET                 (0)
#define MICROPY_PY_ATTRTUPLE                    (0)
#define MICROPY_PY_COLLECTIONS                  (0)
#define MICROPY_PY_MATH                         (0)
#define MICROPY_PY_IO                           (0)
#define MICROPY_PY_STRUCT                       (0)

// Type definitions for the specific machine.

typedef intptr_t mp_int_t; // must be pointer size
typedef uintptr_t mp_uint_t; // must be pointer size
typedef long mp_off_t;

// We need to provide a declaration/definition of alloca().
#include <alloca.h>

// Define the port's name and hardware.
#define MICROPY_HW_BOARD_NAME "polkadot"
#define MICROPY_HW_MCU_NAME   "polkavm"

#define MP_STATE_PORT MP_STATE_VM
