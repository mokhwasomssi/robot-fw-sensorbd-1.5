/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f4xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim4;
extern DMA_HandleTypeDef hdma_tim1_ch3;
extern DMA_HandleTypeDef hdma_tim1_ch2;
extern SPI_HandleTypeDef hspi1;

extern UART_HandleTypeDef huart4;
extern UART_HandleTypeDef huart2;
extern UART_HandleTypeDef huart3;
extern UART_HandleTypeDef huart6;

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */
void DWT_Delay_us(volatile uint32_t au32_microseconds);

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define GPIO_SPISEL1_Pin GPIO_PIN_4
#define GPIO_SPISEL1_GPIO_Port GPIOA
#define GPIO_SPISELw_Pin GPIO_PIN_6
#define GPIO_SPISELw_GPIO_Port GPIOA
#define GPIO_EYE1_EN_Pin GPIO_PIN_10
#define GPIO_EYE1_EN_GPIO_Port GPIOD
#define GPIO_EYE2_EN_Pin GPIO_PIN_11
#define GPIO_EYE2_EN_GPIO_Port GPIOD
#define GPIO_BACKLIGHT1_Pin GPIO_PIN_13
#define GPIO_BACKLIGHT1_GPIO_Port GPIOD
#define GPIO_BACKLIGHT2_Pin GPIO_PIN_14
#define GPIO_BACKLIGHT2_GPIO_Port GPIOD
#define GPIO_HWrev_0_Pin GPIO_PIN_3
#define GPIO_HWrev_0_GPIO_Port GPIOD
#define GPIO_HWrev_1_Pin GPIO_PIN_4
#define GPIO_HWrev_1_GPIO_Port GPIOD
#define GPIO_HWrev_2_Pin GPIO_PIN_5
#define GPIO_HWrev_2_GPIO_Port GPIOD
#define GPIO_HWrev_3_Pin GPIO_PIN_6
#define GPIO_HWrev_3_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
