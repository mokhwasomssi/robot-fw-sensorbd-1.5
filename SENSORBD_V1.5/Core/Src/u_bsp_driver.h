/*
 * u_bsp_driver.h
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */

#ifndef SRC_U_BSP_DRIVER_H_
#define SRC_U_BSP_DRIVER_H_


extern void Uart_Init_Custom(UART_HandleTypeDef *huart);
extern void Uart_Reinit(UART_HandleTypeDef *huart);

#endif /* SRC_U_BSP_DRIVER_H_ */
