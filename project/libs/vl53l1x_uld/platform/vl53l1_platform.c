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

// ChibiOS includes
#include "ch.h"
#include "hal.h"



int8_t VL53L1_WriteMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count) {
	// TODO
    // TODO: Pointers?!
    return 0; // to be implemented
}

int8_t VL53L1_ReadMulti(uint16_t dev, uint16_t index, uint8_t *pdata, uint32_t count){
    // TODO
	// TODO: Pointers?!
    return 0; // to be implemented
}

int8_t VL53L1_WrByte(uint16_t dev, uint16_t index, uint8_t data) {
    // TODO: Pointers?!
    return VL53L1_WriteMulti(dev, index, data, 1U);
	//return 0; // to be implemented
}

int8_t VL53L1_WrWord(uint16_t dev, uint16_t index, uint16_t data) {
	// TODO: Pointers?!
    return VL53L1_WriteMulti(dev, index, data, 2U);
    //return 0; // to be implemented
}

int8_t VL53L1_WrDWord(uint16_t dev, uint16_t index, uint32_t data) {
    // TODO: Pointers?!
    return VL53L1_WriteMulti(dev, index, data, 4U);
	//return 0; // to be implemented
}

int8_t VL53L1_RdByte(uint16_t dev, uint16_t index, uint8_t *data) {
    // TODO: Pointers?!
    return VL53L1_ReadMulti(dev, index, data, 1U);
	//return 0; // to be implemented
}

int8_t VL53L1_RdWord(uint16_t dev, uint16_t index, uint16_t *data) {
    // TODO: Pointers?!
    return VL53L1_ReadMulti(dev, index, data, 2U);
	//return 0; // to be implemented
}

int8_t VL53L1_RdDWord(uint16_t dev, uint16_t index, uint32_t *data) {
    // TODO: Pointers?!
    return VL53L1_ReadMulti(dev, index, data, 4U);
	//return 0; // to be implemented
}

int8_t VL53L1_WaitMs(uint16_t dev, int32_t wait_ms){
    // TODO
    // TODO: Pointers?!
	return 0; // to be implemented
}

