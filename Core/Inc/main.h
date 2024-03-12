<<<<<<< HEAD
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
#include "stm32g0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Color_Sel_Pin GPIO_PIN_1
#define Color_Sel_GPIO_Port GPIOC
#define Color_Sel_EXTI_IRQn EXTI0_1_IRQn
#define Mode_Sel_Pin GPIO_PIN_2
#define Mode_Sel_GPIO_Port GPIOC
#define Mode_Sel_EXTI_IRQn EXTI2_3_IRQn
#define Batt_ADC_Pin GPIO_PIN_1
#define Batt_ADC_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_2
#define LED_1_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_3
#define LED_2_GPIO_Port GPIOA
#define LED_3_Pin GPIO_PIN_4
#define LED_3_GPIO_Port GPIOA
#define LED_4_Pin GPIO_PIN_5
#define LED_4_GPIO_Port GPIOA
#define RED_Pin GPIO_PIN_6
#define RED_GPIO_Port GPIOA
#define GREEN_Pin GPIO_PIN_7
#define GREEN_GPIO_Port GPIOA
#define BLUE_Pin GPIO_PIN_0
#define BLUE_GPIO_Port GPIOB
#define WHITE_Pin GPIO_PIN_1
#define WHITE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
=======
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
#include "stm32g0xx_hal.h"

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

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define Color_Sel_Pin GPIO_PIN_1
#define Color_Sel_GPIO_Port GPIOC
#define Color_Sel_EXTI_IRQn EXTI0_1_IRQn
#define Mode_Sel_Pin GPIO_PIN_2
#define Mode_Sel_GPIO_Port GPIOC
#define Mode_Sel_EXTI_IRQn EXTI2_3_IRQn
#define Batt_ADC_Pin GPIO_PIN_1
#define Batt_ADC_GPIO_Port GPIOA
#define LED_1_Pin GPIO_PIN_2
#define LED_1_GPIO_Port GPIOA
#define LED_2_Pin GPIO_PIN_3
#define LED_2_GPIO_Port GPIOA
#define LED_3_Pin GPIO_PIN_4
#define LED_3_GPIO_Port GPIOA
#define LED_4_Pin GPIO_PIN_5
#define LED_4_GPIO_Port GPIOA
#define RED_Pin GPIO_PIN_6
#define RED_GPIO_Port GPIOA
#define GREEN_Pin GPIO_PIN_7
#define GREEN_GPIO_Port GPIOA
#define BLUE_Pin GPIO_PIN_0
#define BLUE_GPIO_Port GPIOB
#define WHITE_Pin GPIO_PIN_1
#define WHITE_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
>>>>>>> 3eca1d0bbe1aa4dfc8139960ad98441eb06ff2c8
