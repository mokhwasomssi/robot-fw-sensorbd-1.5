/*
 * DOT_MATRIX.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Taesoo
 */

#ifndef __DOT_MATRIX2_H_
#define __DOT_MATRIX2_H_

// Replace The "#include" File Below With The CPU Relevant One For Your Board
#include "stm32f4xx.h"
#include "DOT_MATRIX0.h"

// DOT MATRIX Configuration Parameter Structure
typedef struct
{
	GPIO_TypeDef * SS_GPIO;
	/*
	 * GPIOA or GPIOB ...
	 * */
	uint16_t       SS_PIN;
	/*
	 * GPIO_PIN_0 or GPIO_PIN_1 ...
	 * */
	uint16_t       SCROLL_SPEED;
	/*
	 * Any Value [0-65535]
	 * The Bigger This Number, The Slower Scrolling Becomes
	 * */
	uint8_t        CASCADED_DEVICES;
	/*
	 * Any Number of Devices [ 1 - 255 ]
	 * */
	uint8_t        BRIGHTNESS;
	/*
	 * Any Value [ 0 -> 15 ]
	 * */
	uint8_t        SCROLL_Mode;
	/*
	 * STATIC_MODE or SCROLL_MODE
	 * */
}DOT_MATRIX_CfgType2;

/*-----[ Prototypes For All Functions ]-----*/

// Init Functions Without & With Dedicated Timer
void DOT_MATRIX2_Init(SPI_HandleTypeDef _hspi);
// STATOC MODE Functions
void MATRIX2_CLEAR(uint8_t au8_MATRIX_Instance);
void MATRIX2_Write_Char(uint8_t au8_MATRIX_Instance, uint8_t myChar);
void MATRIX2_Write_SR(uint8_t au8_MATRIX_Instance,uint8_t Row);
#endif /* DOT_MATRIX_H_ */
