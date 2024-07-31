/*
 *
 * 23K256-I/SN (256 kbit SRAM component) Driver
 *
 * Author: Christian V.
 * Created: 17 November 2023
 *
 */

// Preprocessor directives and Import for HAL Abstraction
#ifndef BYTE_SRAM_23K256_H
#define BYTE_SRAM_23K256_H
#include "stm32l4xx_hal.h"

// Modes (Status) of Operation
#define BYTE_MODE	0x00
#define PAGE_MODE	0x80
#define SEQUENTIAL_MODE	0x40
#define CLEAR_BIT_7_6 0x3F

// Instructions and Status for Read and Write
#define READ_INSTRUCTION	0x03
#define WRITE_INSTRUCTION	0x02
#define READ_STATUS 0x05
#define WRITE_STATUS 0x01

// Size of Transmission and Reception in Bytes
#define NUM_BYTES  0x01

// Read and Write Instruction Methods
uint8_t BYTE_readData(SPI_HandleTypeDef* hspi, uint8_t data, uint16_t* address);
HAL_StatusTypeDef BYTE_writeData(SPI_HandleTypeDef* hspi, uint8_t data, uint16_t* address);

// Read and Change Mode Methods
uint8_t MODE_read(SPI_HandleTypeDef* hspi);
HAL_StatusTypeDef MODE_write(SPI_HandleTypeDef* hspi, uint8_t mode);
HAL_StatusTypeDef BYTE_mode(SPI_HandleTypeDef* hspi);
HAL_StatusTypeDef PAGE_mode(SPI_HandleTypeDef* hspi);
HAL_StatusTypeDef SEQUENTIAL_mode(SPI_HandleTypeDef* hspi);

#endif
