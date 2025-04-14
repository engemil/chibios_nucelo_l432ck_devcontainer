#include "ch.h"
#include "hal.h"
#include "chprintf.h"

#define SCL_LINE                LINE_ARD_D5
#define SCL_LINE_MODE           PAL_MODE_ALTERNATE(4) | \
                                PAL_STM32_OSPEED_HIGHEST | \
                                PAL_STM32_OTYPE_OPENDRAIN
#define SDA_LINE                LINE_ARD_D4
#define SDA_LINE_MODE           PAL_MODE_ALTERNATE(4) | \
                                PAL_STM32_OSPEED_HIGHEST | \
                                PAL_STM32_OTYPE_OPENDRAIN
#define INT_LINE                LINE_ARD_D9
#define XSHUT_LINE              LINE_ARD_D10
#define VL52L1X_I2C_ADDRESS     0x52 // VL52L1X/VL52L0X I2C Address

#define VIRTUAL_COM_TX_LINE         LINE_VCP_TX
// Set for USART2_TX
#define VIRTUAL_COM_TX_LINE_MODE    PAL_MODE_ALTERNATE(7) | \
                                    PAL_STM32_OSPEED_MID2 | \
                                    PAL_STM32_PUPDR_FLOATING | \
                                    PAL_STM32_OTYPE_PUSHPULL
#define VIRTUAL_COM_RX_LINE         LINE_VCP_RX
// Set for USART2_RX
#define VIRTUAL_COM_RX_LINE_MODE    PAL_MODE_ALTERNATE(3) | \
                                    PAL_STM32_OSPEED_MID2 | \
                                    PAL_STM32_PUPDR_FLOATING | \
                                    PAL_STM32_OTYPE_PUSHPULL
/* I2C Configuration (ChibiOS HAL I2Cv2)*/
static const I2CConfig i2ccfg = {
    STM32_TIMINGR_PRESC(7) | 
    STM32_TIMINGR_SCLDEL(8) | 
    STM32_TIMINGR_SDADEL(4) |
    STM32_TIMINGR_SCLH(39) |
    STM32_TIMINGR_SCLL(39), // Timing Register // System clock for STM32L432KC is 80MHz (from PLL)
    0, // CR1
    0, // CR2
};
/* t_(I2CCLK) I2C clock for the NUCLEO-L432KC board is set to system clock (80MHz)
 * t_(PRESC) = (PRESC + 1) * t_(I2CCLK)
 *
 * 
 */

/* Serial Configuration for Virtual COM Port */
static SerialConfig serial_cfg = {
    .speed  = 115200,           // Baud rate
    .cr1    = 0,                // No parity, 8-bit data (default)
    .cr2    = 0,                // No specific control settings
    .cr3    = 0                 // No hardware flow control
};


int main(void) {

    /* System initializations. */
    halInit();
    chSysInit();

    /* Configuring I2C SCL and I2C SDA related GPIOs */
    palSetLineMode(SCL_LINE, SCL_LINE_MODE);
    palSetLineMode(SDA_LINE, SDA_LINE_MODE);
    palSetLineMode(INT_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    palSetLineMode(XSHUT_LINE, PAL_MODE_OUTPUT_PUSHPULL);
    
    /* Configure Serial Driver SD2 (USART2) for Virtual COM Port */
    palSetLineMode(VIRTUAL_COM_TX_LINE, VIRTUAL_COM_TX_LINE_MODE);
    palSetLineMode(VIRTUAL_COM_RX_LINE, VIRTUAL_COM_RX_LINE_MODE);
    
    /* Start Serial Driver 2 */
    sdStart(&SD2, &serial_cfg);

    /* Print initial message */
    chprintf((BaseSequentialStream*)&SD2, "Starting VL53L1X I2C Test...\r\n");

    /* Set Interrupt pin HIGH, to keep them "inactive" */
    //palSetLine(INT_LINE);
    /* Set Shutdown pins HIGH, to Enable VL53L1X */
    palSetLine(XSHUT_LINE);


    // Start I2C
    //i2cStart(&I2CD1, &i2ccfg);



    // Main Thread
    while (true) {

        palToggleLine(LINE_LED_GREEN);
        chprintf((BaseSequentialStream*)&SD2, "Test print \r\n");

        chThdSleepMilliseconds(1000);
    }


}


