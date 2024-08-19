#include <unistd.h>
#include <string.h>
#include "py/mpconfig.h"

// Receive single character, blocking until one is available.
int mp_hal_stdin_rx_chr(void) {
    unsigned char c = 0;
    int r = read(STDIN_FILENO, &c, 1);
    (void)r;
    return c;
}

// Send the string of given length.
void mp_hal_stdout_tx_strn(const char *str, mp_uint_t len) {
    //int r = write(STDOUT_FILENO, str, len);
    //(void)r;
}

//void mp_hal_stdout_tx_str(const char *str) {
//    mp_hal_stdout_tx_strn(str, strlen(str));
//}
