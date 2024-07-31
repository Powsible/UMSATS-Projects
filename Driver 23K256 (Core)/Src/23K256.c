/*
 *
 * 23K256-I/SN (256 kbit SRAM component) Driver
 *
 * Author: Christian V.
 * Created: 17 November 2023
 *
 */

#include <stdio.h>
#include "23K256.h"

SPI_HandleTypeDef hspi;

// Read
HAL_StatusTypeDef BYTE_readRegister(uint8_t *pointer, uint16_t numBytes){
	return HAL_SPI_Receive(&BYTE_SRAM_23K256_SPI, pointer, numBytes, TIME_OUT);
}

// Write
HAL_StatusTypeDef BYTE_writeRegister(uint8_t *pointer, uint16_t numBytes){
	return HAL_SPI_Transmit(&BYTE_SRAM_23K256_SPI, pointer, numBytes, TIME_OUT);
}

