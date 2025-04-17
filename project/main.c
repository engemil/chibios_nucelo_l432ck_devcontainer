#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "VL53L1X_api.h"

#define SCL_LINE                LINE_ARD_D5
#define SDA_LINE                LINE_ARD_D4
#define INT_LINE                LINE_ARD_D9
#define XSHUT_LINE              LINE_ARD_D10

#define SCL_LINE_MODE           PAL_MODE_ALTERNATE(4) | \
                                PAL_STM32_OSPEED_HIGHEST | \
                                PAL_STM32_OTYPE_OPENDRAIN
#define SDA_LINE_MODE           PAL_MODE_ALTERNATE(4) | \
                                PAL_STM32_OSPEED_HIGHEST | \
                                PAL_STM32_OTYPE_OPENDRAIN

//#define VL52L1X_I2C_ADDRESS     0x52 // VL52L1X/VL52L0X I2C Address
#define VL52L1X_I2C_ADDRESS     0x29 // VL52L1X/VL52L0X I2C Address

#define VIRTUAL_COM_TX_LINE         LINE_VCP_TX
#define VIRTUAL_COM_RX_LINE         LINE_VCP_RX
#define VIRTUAL_COM_TX_LINE_MODE    PAL_MODE_ALTERNATE(7) | \
                                    PAL_STM32_OSPEED_MID2 | \
                                    PAL_STM32_PUPDR_FLOATING | \
                                    PAL_STM32_OTYPE_PUSHPULL
#define VIRTUAL_COM_RX_LINE_MODE    PAL_MODE_ALTERNATE(3) | \
                                    PAL_STM32_OSPEED_MID2 | \
                                    PAL_STM32_PUPDR_FLOATING | \
                                    PAL_STM32_OTYPE_PUSHPULL


/* I2C Configuration (ChibiOS HAL I2Cv2)*/
static const I2CConfig i2ccfg = {
    STM32_TIMINGR_PRESC(0x7U) | \
    STM32_TIMINGR_SCLDEL(0x2U) | \
    STM32_TIMINGR_SDADEL(0x4U) | \
    STM32_TIMINGR_SCLH(0x30U) | \
    STM32_TIMINGR_SCLL(0x30U), // Timing Register // System clock for STM32L432KC is 80MHz (from PLL)
    0, // CR1
    0, // CR2
};

/* Serial Configuration for Virtual COM Port */
static SerialConfig serial_cfg = {
    .speed  = 115200,           // Baud rate
    .cr1    = 0,                // No parity, 8-bit data (default)
    .cr2    = 0,                // No specific control settings
    .cr3    = 0                 // No hardware flow control
};

volatile uint16_t sensorId;
volatile VL53L1X_ERROR status;

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

    /* Set Interrupt pin LOW, to keep it active" */
    palClearLine(INT_LINE);
    /* Set Shutdown pins HIGH, to Enable VL53L1X */
    palSetLine(XSHUT_LINE);

    // Start I2C
    i2cStart(&I2CD1, &i2ccfg);


    // Main Thread
    while (true) {

        palToggleLine(LINE_LED_GREEN);
        chprintf((BaseSequentialStream*)&SD2, "Test print \r\n");

        // Get sensor ID
        status = VL53L1X_GetSensorId(VL52L1X_I2C_ADDRESS, &sensorId);
        if (status == 0) {
            // Sensor ID retrieved successfully
            // Expected sensorId for VL53L1X is typically 0xEACC
            chprintf((BaseSequentialStream*)&SD2, "Reading Successful\r\n");
            chprintf((BaseSequentialStream*)&SD2, "Value: 0x%04x\r\n", sensorId);
        } else {
            // Handle error
            chprintf((BaseSequentialStream*)&SD2, "Reading Unsuccessful\r\n");
        }

        chThdSleepMilliseconds(5000);
    }

}


