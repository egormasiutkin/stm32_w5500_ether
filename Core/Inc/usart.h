/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    usart.h
  * @brief   This file contains all the function prototypes for
  *          the usart.c file
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
#ifndef __USART_H__
#define __USART_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* USER CODE BEGIN Includes */
#define BUFFER_LENGTH 25

//#include "stm32f0xx_hal.h"
//#include "stm32f0xx_hal_uart.h"
#include <stdbool.h>
#include "motion_detect.h"
#include "main.h"
#include "pcb_config.h"

/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;

extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

/* USER CODE BEGIN Prototypes */
#define BUFFER_LENGTH 25

#include "stm32g0xx_hal.h"
#include "stm32g0xx_hal_uart.h"
#include <stdbool.h>
#include "motion_detect.h"
#include "main.h"
#define MAX_NUMBER 1
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

extern UART_HandleTypeDef huart1;
extern UART_HandleTypeDef huart2;

/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
void Uart_process(void);
void  Send_BTN_ON(int btn1, int btn2);
void Send_Version_Data(void);
void Send_String(char * string1, int size);
void Send_Motion_Data(void);
void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart);
char getRxUartBuffer(uint8_t index);
void Set_IR_Command(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void Set_RS232_Command();
void Send_IR_Command_Debug();
void Send_RS232_Command_Debug();
void Set_Temp_Treshold_Max(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void Set_Temp_Treshold_Min(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void Set_PIR_Off();
void Set_PIR_On();
void Set_Temp_Off();
void Set_Temp_On();
void Set_PIR_Delay_OFF(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void Send_Command_Data(uint32_t* command, int k, int on);
void Set_PIR_Delay_ON(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
int Compare_Command(char * command, int size);
bool Get_Carriage_Return_Flag(void);
void Set_Carriage_Return_Flag(bool new_flag);
/* USER CODE BEGIN Prototypes */
void HAL_UART_ErrorCallback(UART_HandleTypeDef* huart);
void Send_Temperature_Data(float temp);
void Send_RS232_Command_ON();
void Set_IR_On();
void Set_IR_Off();
void Set_RS232_On();
void Set_RS232_Off();
void Send_RS232_Command_OFF();
void Send_IR_Command_Debug_OFF();
extern struct PCB_Config pcb_config;
void changeBaudRate(int baudrate, int word_length, int stop_bits);
/* USER CODE END Prototypes */

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */

