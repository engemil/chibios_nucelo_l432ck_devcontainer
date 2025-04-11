#include "ch.h"
#include "hal.h"
int main(void) {
    halInit();
    chSysInit();
    while (true) {
        palToggleLine(LINE_LED_GREEN);
        chThdSleepMilliseconds(500);
    }
}
