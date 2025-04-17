/**
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */

#include "vl53l1_platform.h"
#include <string.h>
#include <time.h>
#include <math.h>

// TEST
I2CDriver *VL53L1X_I2C_DRIVER = &I2CD1; // Use I2C1 driver


int8_t VL53L1_WriteMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count) {
    // TODO
    return 0; // to be implemented
}

int8_t VL53L1_ReadMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count){
    msg_t status;
    uint8_t index_buf[2] = {(uint8_t)(index >> 8), (uint8_t)(index & 0xFF)};

    // Acquire I2C bus
    i2cAcquireBus(VL53L1X_I2C_DRIVER);

    // Send register address (2 bytes)
    status = i2cMasterTransmitTimeout(VL53L1X_I2C_DRIVER, dev, index_buf, 2, NULL, 0, TIME_MS2I(100));
    if (status != MSG_OK) {
        i2cReleaseBus(VL53L1X_I2C_DRIVER);
        return -1; // Error
    }

    // Read data
    status = i2cMasterReceiveTimeout(VL53L1X_I2C_DRIVER, dev, pdata, count, TIME_MS2I(100));
    i2cReleaseBus(VL53L1X_I2C_DRIVER);

    return (status == MSG_OK) ? 0 : -1;
}

int8_t VL53L1_WrByte(uint16_t dev, uint16_t index, uint8_t data) {
    return VL53L1_WriteMulti(dev, index, data, 1U);
	//return 0; // to be implemented
}

int8_t VL53L1_WrWord(uint16_t dev, uint16_t index, uint16_t data) {
    return VL53L1_WriteMulti(dev, index, data, 2U);
    //return 0; // to be implemented
}

int8_t VL53L1_WrDWord(uint16_t dev, uint16_t index, uint32_t data) {
    return VL53L1_WriteMulti(dev, index, data, 4U);
	//return 0; // to be implemented
}

int8_t VL53L1_RdByte(uint16_t dev, uint16_t index, uint8_t *data) {
    return VL53L1_ReadMulti(dev, index, data, 1U);
	//return 0; // to be implemented
}

int8_t VL53L1_RdWord(uint16_t dev, uint16_t index, uint16_t *data) {
    uint8_t buf[2];
    int8_t status = VL53L1_ReadMulti(dev, index, buf, 2);
    if (status == 0) {
        *data = ((uint16_t)buf[0] << 8) | buf[1]; // Combine MSB and LSB
    }
    return status;
    //return VL53L1_ReadMulti(dev, index, data, 2U);
	//return 0; // to be implemented
}

int8_t VL53L1_RdDWord(uint16_t dev, uint16_t index, uint32_t *data) {
    return VL53L1_ReadMulti(dev, index, data, 4U);
	//return 0; // to be implemented
}

int8_t VL53L1_WaitMs(uint16_t dev, int32_t wait_ms){
    // TODO
    // TODO: Pointers?!
	return 0; // to be implemented
}

