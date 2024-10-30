/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
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

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

void HAL_TIM_MspPostInit(TIM_HandleTypeDef *htim);

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define heating_Pin GPIO_PIN_4
#define heating_GPIO_Port GPIOE
#define vent_Pin GPIO_PIN_6
#define vent_GPIO_Port GPIOE
#define mq135_Pin GPIO_PIN_2
#define mq135_GPIO_Port GPIOA
#define water_level_Pin GPIO_PIN_3
#define water_level_GPIO_Port GPIOA
#define phSens_Pin GPIO_PIN_6
#define phSens_GPIO_Port GPIOA
#define ds18b20_Pin GPIO_PIN_7
#define ds18b20_GPIO_Port GPIOE
#define relay1_Pin GPIO_PIN_13
#define relay1_GPIO_Port GPIOE
#define relay2_Pin GPIO_PIN_14
#define relay2_GPIO_Port GPIOE
#define dh11_Pin GPIO_PIN_10
#define dh11_GPIO_Port GPIOA

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
