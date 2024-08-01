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

/*
 * Read Function
 */
uint8_t BYTE_readData(SPI_HandleTypeDef* hspi, uint16_t* address){
	// Turn on the chip select in active low.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

	// Activate hold.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// Get the 16-bit top and bottom address.
	uint8_t top = (*address >> 8) & 0x00FF,
			bottom = (*address) & 0x00FF,
			readInstruction = READ_INSTRUCTION, dataRead;

	// Select the read instruction.
	if (HAL_SPI_Transmit(hspi, &readInstruction, NUM_BYTES, HAL_MAX_DELAY) == HAL_OK){

		// Transmit the upper byte of the address.
		if (HAL_SPI_Transmit(hspi, &top, NUM_BYTES, HAL_MAX_DELAY) == HAL_OK){

			// Transmit the lower byte of the address.
			if (HAL_SPI_Transmit(hspi, &bottom, NUM_BYTES, HAL_MAX_DELAY) == HAL_OK){

				// Receive the data.
				HAL_SPI_Receive(hspi, &dataRead, NUM_BYTES, HAL_MAX_DELAY);
			}
		}
	}

	// Turn off the chip select.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	return dataRead;
}

/*
 * Write Function
 */
HAL_StatusTypeDef BYTE_writeData(SPI_HandleTypeDef* hspi, uint8_t data, uint16_t* address){
	// Turn on the chip select in active low.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

	// Activate hold.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// Get the 16-bit top and bottom address.
	uint8_t top = (*address >> 8) & 0x00FF,
			bottom = (*address) & 0x00FF,
			writeInstruction = WRITE_INSTRUCTION;

	// Select the write instruction.
	HAL_StatusTypeDef status = HAL_SPI_Transmit(hspi, &writeInstruction, 1, HAL_MAX_DELAY);
	if (status == HAL_OK){

		// Transmit the upper byte of the address.
		status = HAL_SPI_Transmit(hspi, &top, NUM_BYTES, HAL_MAX_DELAY);
		if (status == HAL_OK){

			// Transmit the lower byte of the address.
			status = HAL_SPI_Transmit(hspi, &bottom, NUM_BYTES, HAL_MAX_DELAY);
			if (status == HAL_OK){

				// Transmit the data.
				status = HAL_SPI_Transmit(hspi, &data, NUM_BYTES, HAL_MAX_DELAY);
			}
		}
	}

	// Turn off the chip select.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	return status;
}

/*
 * MODE read.
 */
uint8_t STATUS_read(SPI_HandleTypeDef* hspi){
	uint8_t status = -1, readStatus = READ_STATUS;

	// Turn on the chip select in active low.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

	// Activate hold.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);

	// Select the read status.
	if (HAL_SPI_Transmit(hspi, &readStatus, NUM_BYTES, HAL_MAX_DELAY) == HAL_OK){

		// Receive the status.
		HAL_SPI_Receive(hspi, &status, NUM_BYTES, HAL_MAX_DELAY);
	}

	// Turn off the chip select.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	return status;
}

/*
 * MODE write.
 */
HAL_StatusTypeDef MODE_write(SPI_HandleTypeDef* hspi, uint8_t mode){
	// Get the proper mode by clearing bits 6 and 7 and
	uint8_t writeStatus = WRITE_STATUS, newMode = STATUS_read(hspi) & CLEAR_BIT_7_6;
	newMode |= mode;

	// Activate hold.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_RESET);

	// Select the write status.
	HAL_StatusTypeDef status = HAL_SPI_Transmit(hspi, &writeStatus, 1, HAL_MAX_DELAY);
	if (status == HAL_OK){

		// Transmit the status.
		status = HAL_SPI_Transmit(hspi, &newMode, NUM_BYTES, HAL_MAX_DELAY);
	}

	// Turn off the chip select.
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_6, GPIO_PIN_SET);

	return status;
}

/*
 * BYTE status.
 */
HAL_StatusTypeDef BYTE_mode(SPI_HandleTypeDef* hspi){
	uint8_t byte = BYTE_MODE;
	return MODE_write(hspi, byte);
}

/*
 * PAGE status.
 */
HAL_StatusTypeDef PAGE_mode(SPI_HandleTypeDef* hspi){
	uint8_t page = PAGE_MODE;
	return MODE_write(hspi, page);
}

/*
 * SEQUENTIAL status.
 */
HAL_StatusTypeDef SEQUENTIAL_mode(SPI_HandleTypeDef* hspi){
	uint8_t sequential = SEQUENTIAL_MODE;
	return MODE_write(hspi, sequential);
}
