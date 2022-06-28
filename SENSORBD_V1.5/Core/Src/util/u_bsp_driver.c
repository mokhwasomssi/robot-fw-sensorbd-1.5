/*
 * u_bsp_driver.c
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */

#include "app_sensorboard.h"
#include "u_bsp_driver.h"

void Uart_Init_Custom(UART_HandleTypeDef *huart)
{
	__HAL_UART_ENABLE_IT(huart, UART_IT_RXNE);
//	__HAL_UART_ENABLE_IT(huart, UART_IT_TC);
//	__HAL_UART_CLEAR_PEFLAG(huart);
//	__HAL_UART_CLEAR_FEFLAG(huart);
//	__HAL_UART_CLEAR_NEFLAG(huart);
//	__HAL_UART_CLEAR_OREFLAG(huart);
//	__HAL_UART_CLEAR_IDLEFLAG(huart);
}


void Uart_Reinit(UART_HandleTypeDef *huart)
{
//	UART_HandleTypeDef temp;
//	u32 baud = 0;
//
////	temp.Instance = huart->Instance;
////	temp.Init.BaudRate = huart->Init.BaudRate;
////	temp.Init.WordLength = huart->Init.WordLength;
////	temp.Init.StopBits = huart->Init.StopBits;
////	temp.Init.Parity = huart->Init.Parity;
////	temp.Init.Mode = huart->Init.Mode;
////	temp.Init.HwFlowCtl = huart->Init.HwFlowCtl;
////	temp.Init.OverSampling = huart->Init.OverSampling;
////	temp.Init.OneBitSampling = huart->Init.OneBitSampling;
////	temp.AdvancedInit.AdvFeatureInit = huart->AdvancedInit.AdvFeatureInit;
//
//	baud = temp.Init.BaudRate;
//	HAL_UART_DeInit(huart);
//	//DBG_MSG("DEINIT UART[%d]",baud);
//	baud = huart->Init.BaudRate;
//	DBG_MSG("INIT UART22[%d]",baud);
//	osDelay(100);
//	if(HAL_UART_Init(huart) != HAL_OK) Error_Handler();
//	//if(HAL_UART_Init(&temp) != HAL_OK) Error_Handler();
//	baud = huart->Init.BaudRate;
//	DBG_MSG("INIT UART33[%d]",baud);
//	osDelay(100);
}
