/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2024 STMicroelectronics.
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
#include <stdio.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef  void (*pFunction)(void);
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
#define CS_Pin GPIO_PIN_9
#define CS_GPIO_Port GPIOB
#define LED_Pin GPIO_PIN_0
#define LED_GPIO_Port GPIOA
#define SW3_Pin GPIO_PIN_1
#define SW3_GPIO_Port GPIOA
#define DETECT_Pin GPIO_PIN_6
#define DETECT_GPIO_Port GPIOA
#define IR_IN_Pin GPIO_PIN_7
#define IR_IN_GPIO_Port GPIOA
#define BTN_1_Pin GPIO_PIN_0
#define BTN_1_GPIO_Port GPIOB
#define SW1_Pin GPIO_PIN_1
#define SW1_GPIO_Port GPIOB
#define WP_Pin GPIO_PIN_2
#define WP_GPIO_Port GPIOB
#define BTN_2_Pin GPIO_PIN_8
#define BTN_2_GPIO_Port GPIOA
#define LED2_Pin GPIO_PIN_11
#define LED2_GPIO_Port GPIOA
#define SW2_Pin GPIO_PIN_12
#define SW2_GPIO_Port GPIOA
#define RST_Pin GPIO_PIN_8
#define RST_GPIO_Port GPIOB

/* USER CODE BEGIN Private defines */
#define META_ADDRESS     (uint32_t)0x08040000
#define APPLICATION_ADDRESS     (uint32_t)0x08040800
#define NB_CHARS_RS232 64
#define VAR 126
#define EEPROM_C24_ADDR_WRITE 0xA0
#define EEPROM_C24_ADDR_READ  0xA1
#define FIRMWARE_VERSION "v989\n\r"
extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;
extern RTC_HandleTypeDef hrtc;
extern uint8_t loopon;
extern uint8_t loopoff;
extern uint8_t looptime;
extern uint8_t firmware_update;
typedef unsigned long T_u_int32; /* 32 bits unsigned */
void Error_Handler(void);
T_u_int32 reverse_bits_test(T_u_int32 inval, int bits);
void SystemClock_Config(void);
void HeartBeatLed();
void Calculate_Temperatures_Offsets();
void convert_code (uint32_t code);
void Delay_us (uint16_t us);
uint32_t receive_data (void);
void Send(uint8_t data);
uint8_t Receive(void);
void ReadAndSetConfig();
void convert_code (uint32_t code);
void Delay_us (uint16_t us);
uint32_t receive_data (void);
void MainAlgorithm();
void ButtonsAlgorithm();
void WriteToEeprom();
void ResetLoopProcess();
/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
