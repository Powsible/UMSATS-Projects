/*
 *
 * 23K256-I/SN (256 kbit SRAM component) Driver
 *
 * Author: Christian V.
 * Created: 17 November 2023
 *
 */

// Preprocessor directives
#ifndef BYTE_SRAM_23K256_H
#define BYTE_SRAM_23K256_H

// Required for HAL abstraction
#include "stm32l4xx_hal.h"

// Modes (Have everything just in case)
#define BYTE_MODE	0x00
#define PAGE_MODE	0x40
#define BURST_MODE	0x80

// Read and write
#define READ_INSTRUCTION	0x03
#define WRITE_INSTRUCTION	0x02

#define BYTE_SRAM_23K256_SPI hspi
#define BYTE_SRAM_23K256_SPI_DELAY HAL_MAX_DELAY
#define TIME_OUT 1000000

// Byte Operation/Status Register
//#define BYTE_OPERATION_STATUS_REGISTER 0x00
//#define BYTE_OPERATION_STATUS_REG_BITS 0xC0 // Bits 7 and 6 = (0110 0000)2 = (C0)16
//#define BYTE_OPERATION_VALUE 0x00

extern SPI_HandleTypeDef hspi;
/*
 * uint#_t = #-bit positive integer
 */

// Initialize

// Use HAL_StatusTypeDef to read and write
HAL_StatusTypeDef BYTE_readRegister(uint8_t *pointer, uint16_t numBytes);
HAL_StatusTypeDef BYTE_writeRegister(uint8_t *pointer, uint16_t numBytes);

#endif
