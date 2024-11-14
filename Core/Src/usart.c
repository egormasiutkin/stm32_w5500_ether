/* USER CODE BEGIN Header */
/**
 ******************************************************************************
 * @file    usart.c
 * @brief   This file provides code for the configuration
 *          of the USART instances.
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
/* Includes ------------------------------------------------------------------*/

/* USER CODE BEGIN 0 */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"
#include <string.h>
#include <stdbool.h>
#include "MyApp.h"
#include "Infrared.h"
/* USER CODE BEGIN 0 */

// #ifdef __GNUC__
// #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
// #else
// #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
// #endif
// PUTCHAR_PROTOTYPE
//{
//   HAL_UART_Transmit(&huart1, (uint8_t *)&ch, 1, 0xFFFF);
//   return ch;
// }

/* USART1 init function */

char rx_Buffer[25], rx_uart[5];
uint8_t indexRxUart = 0;
bool carriage_return_flag = false;
// char RS232_command_ON[NB_CHARS_RS232] = {'k','a',' ','0','0',' ','0','1','\r'};
// char RS232_command_ON[NB_CHARS_RS232] = {0xAA, 0x11,0xFE,0x01,0x01,0x11};
// char RS232_command_OFF[NB_CHARS_RS232]= {0xAA, 0x11,0xFE,0x01,0x00,0x10};
char RS232_command_OFF[NB_CHARS_RS232];
char RS232_command_ON[NB_CHARS_RS232];

uint32_t IR_command = 0x00002023;
uint64_t IR_command_off = 0xA0DF23DC0A;
uint32_t Temp_Treshold_Min = 10;
uint32_t Temp_Treshold_Max = 40;

int PIRAlarm = 1;
int TempAlarm = 0;
int RS232Alarm = 1;
int IRAlarm = 1;
int flag_ON = 0;
/* USER CODE END 0 */

/* USER CODE BEGIN 1 */
/* Process States */
typedef enum
{
	IDLE,
	COMMAND
} Uart_State;
static Uart_State uart_state_process = IDLE;
void Uart_process(void)
{

	switch (uart_state_process)
	{
	case IDLE:

		if (Get_Carriage_Return_Flag() == true) // if we receive the end of frame
		{
			//	   		   if (getRxUartBuffer(0) == 'p' || getRxUartBuffer(0) == 'v' )
			//	   		   {
			Set_Carriage_Return_Flag(false); // Initialize at false for the next frame
			uart_state_process = COMMAND;
			//	   		   }
		}
		break;

	case COMMAND:
	{
		rx_Buffer[0] = getRxUartBuffer(0);	 // store command high
		rx_Buffer[1] = getRxUartBuffer(1);	 // store command high
		rx_Buffer[2] = getRxUartBuffer(2);	 // store command high
		rx_Buffer[3] = getRxUartBuffer(3);	 // store command high
		rx_Buffer[4] = getRxUartBuffer(4);	 // store command high
		rx_Buffer[5] = getRxUartBuffer(5);	 // store command high
		rx_Buffer[6] = getRxUartBuffer(6);	 // store command high
		rx_Buffer[7] = getRxUartBuffer(7);	 // store command high
		rx_Buffer[8] = getRxUartBuffer(8);	 // store command high
		rx_Buffer[9] = getRxUartBuffer(9);	 // store command high
		rx_Buffer[10] = getRxUartBuffer(10); // store command high
		rx_Buffer[11] = getRxUartBuffer(11); // store command high
		rx_Buffer[12] = getRxUartBuffer(12); // store command high
		rx_Buffer[13] = getRxUartBuffer(13); // store command high
		rx_Buffer[14] = getRxUartBuffer(14); // store command high
		rx_Buffer[15] = getRxUartBuffer(15); // store command high
		rx_Buffer[16] = getRxUartBuffer(16); // store command high
		rx_Buffer[17] = getRxUartBuffer(17); // store command high
		rx_Buffer[18] = getRxUartBuffer(18); // store command high
		rx_Buffer[19] = getRxUartBuffer(19); // store command high
		rx_Buffer[20] = getRxUartBuffer(20); // store command high

		if (Compare_Command("ver", sizeof("ver")))
		{
			Send_Version_Data(); // reply through uart
		}
		else if (Compare_Command("pr", sizeof("pr")))
		{
			Send_Motion_Data(); // reply through uart
		}
		else if (Compare_Command("SetIR", sizeof("SetIR")))
		{
			Set_IR_Command(getRxUartBuffer(5), getRxUartBuffer(6), getRxUartBuffer(7), getRxUartBuffer(8));
			Send_IR_Command_Debug();
		}
		else if (Compare_Command("ReadIR", sizeof("ReadIR")))
		{
			Send_IR_Command_Debug();
		}
		//			else if (Compare_Command("SetR2S", sizeof("SetR2S")))
		//			{
		//				Set_RS232_Command(getRxUartBuffer(6),getRxUartBuffer(7), getRxUartBuffer(8), getRxUartBuffer(9));
		//			    Send_RS232_Command_Debug();
		//			}
		else if (Compare_Command("SetR2S9C", sizeof("SetR2S9C")))
		{
			Set_RS232_Command();
			Send_RS232_Command_Debug();
		}
		else if (Compare_Command("ReadRS", sizeof("ReadIR")))
		{
			Send_RS232_Command_Debug();
		}
		else if (Compare_Command("SetTempTreshMin", sizeof("SetTempTreshMin")))
		{
			Set_Temp_Treshold_Min(getRxUartBuffer(15), getRxUartBuffer(16), getRxUartBuffer(17), getRxUartBuffer(18));
		}
		else if (Compare_Command("SetTempTreshMax", sizeof("SetTempTreshMax")))
		{
			Set_Temp_Treshold_Max(getRxUartBuffer(15), getRxUartBuffer(16), getRxUartBuffer(17), getRxUartBuffer(18));
		}
		else if (Compare_Command("SetTempON", sizeof("SetTempON")))
		{
			Set_Temp_On();
		}
		else if (Compare_Command("SetTempOFF", sizeof("SetTempOFF")))
		{
			Set_Temp_Off();
		}
		else if (Compare_Command("SetPIRON", sizeof("SetPIRON")))
		{
			Set_PIR_On();
		}
		else if (Compare_Command("SetPIROFF", sizeof("SetPIROFF")))
		{
			Set_PIR_Off();
		}
		else if (Compare_Command("SetIRON", sizeof("SetPIRON")))
		{
			Set_IR_On();
		}
		else if (Compare_Command("SetIROFF", sizeof("SetIROFF")))
		{
			Set_IR_Off();
		}
		else if (Compare_Command("SetRS232ON", sizeof("SetRS232ON")))
		{
			Set_RS232_On();
		}
		else if (Compare_Command("SetRS232OFF", sizeof("SetRS232OFF")))
		{
			Set_RS232_Off();
		}
		else if (Compare_Command("PIRDelayON", sizeof("PIRDelayON")))
		{
			Set_PIR_Delay_ON(getRxUartBuffer(10), getRxUartBuffer(11), getRxUartBuffer(12), getRxUartBuffer(13));
		}
		else if (Compare_Command("PIRDelayOFF", sizeof("PIRDelayOFF")))
		{
			Set_PIR_Delay_OFF(getRxUartBuffer(11), getRxUartBuffer(12), getRxUartBuffer(13), getRxUartBuffer(14));
		}

		uart_state_process = IDLE;

		break;
	}
	default:
		uart_state_process = IDLE;
	}
}

void Set_Temp_On()
{
	TempAlarm = 1;
}
void Set_Temp_Off()
{
	TempAlarm = 0;
}
void Set_PIR_On()
{
	PIRAlarm = 1;
}
void Set_PIR_Off()
{
	PIRAlarm = 0;
}
void Set_IR_On()
{
	IRAlarm = 1;
}
void Set_IR_Off()
{
	IRAlarm = 0;
}
void Set_RS232_On()
{
	RS232Alarm = 1;
}
void Set_RS232_Off()
{
	RS232Alarm = 0;
}
void Set_Temp_Treshold_Min(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	Temp_Treshold_Min = (uint32_t)(byte1 << 24) + (uint32_t)(byte2 << 16) + (uint32_t)(byte3 << 8) + byte4;
	;
}
void Set_Temp_Treshold_Max(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	Temp_Treshold_Max = (uint32_t)(byte1 << 24) + (uint32_t)(byte2 << 16) + (uint32_t)(byte3 << 8) + byte4;
	;
}

int Compare_Command(char *command, int size)
{
	char command_string[25];
	strcpy(command_string, rx_Buffer);
	if (strncmp(command_string, command, size - 1))
	{
		return 0; // reply through uart
	}
	else
	{
		return 1;
	}
}
// void Send_RS232_Command_Debug()
//{
//		char data[6]; //size of the number
//		data[3] = (uint8_t)(RS232_command & 0xFF);
//		data[2] = (uint8_t)((RS232_command >> 8) & 0xFF);
//		data[1] = (uint8_t)((RS232_command >> 16) & 0xFF);
//		data[0] = (uint8_t)((RS232_command >> 24) & 0xFF);
//		data[4] = '\n';
//		data[5] = '\r';
//
//	HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), 1000); //Send dataFrame through UART
// }
void Send_RS232_Command_Debug()
{
	char data5[NB_CHARS_RS232]; // size of the number
	// strcpy(data5, RS232_command_ON);
	memcpy(data5, RS232_command_ON, sizeof(data5));
	HAL_UART_Transmit(&huart1, (uint8_t *)data5, sizeof(data5), 1000); // Send dataFrame through UART
}
void Send_RS232_Command_ON()
{
//	char data[6]; // size of the number
	char data2[30];

	memcpy(&RS232_command_ON, &pcb_config.sSetR2S9C, NB_CHARS_RS232);
	to_hex(RS232_command_ON, 0);
	for (int i = 0; i < NB_CHARS_RS232 / 2; i++)
		RS232_command_ON[i] = RS232_command_ON[2 * i + 1];

	HAL_UART_Transmit(&huart2, (uint8_t *)RS232_command_ON, pcb_config.rs232nbcharsON[0], 1000); // Send dataFrame through UART

	strcpy(data2, "Rs232 command ON sent\n\r");
	HAL_UART_Transmit(&huart1, (uint8_t *)data2, sizeof("Rs232 command ON sent\n\r"), 1000); // Send dataFrame through UART

	LogToBufferLog(data2, sizeof("Rs232 command ON sent\n\r"));
	// HAL_UART_Transmit(&huart1, (uint8_t *)RS232_command_ON, pcb_config.rs232nbcharsON[0], 1000); //Send dataFrame through UART
	// strcpy(data2, "\r");
	// HAL_UART_Transmit(&huart1, (uint8_t *)data2, 1, 1000); //Send dataFrame through UART
}
void Send_BTN_ON(int btn1, int btn2)
{
//	char data[6]; // size of the number
//	char data2[30];
	Send_String("Function Pressed: ", sizeof("Function Pressed: "));
	char btnx = (char)(btn1) + '0';
	char btny = (char)(btn2) + '0';
	Send_String(&btnx, 2);
	Send_String(&btny, 2);
	Send_String("\n\r", sizeof("\n\r"));

	// switch (btn)
	// case 1:

	// if (btn == 1)
	// strcpy(data2, "Function %d pressed\n\r",btn);
	//	else if (btn ==2)
	//		strcpy(data2, "BTN 2 pressed\n\r");
	//	else if( btn ==3 )
	//		strcpy(data2, "BTN 3 pressed\n\r");
	//	else
	//		strcpy(data2, "BTN 4 pressed\n\r");

	// HAL_UART_Transmit(&huart1, (uint8_t *)data2, sizeof("BTN 1 pressed\n\r"), 1000); //Send dataFrame through UART
	// HAL_UART_Transmit(&huart1, (uint8_t *)RS232_command_ON, pcb_config.rs232nbcharsON[0], 1000); //Send dataFrame through UART
	// strcpy(data2, "\r");
	// HAL_UART_Transmit(&huart1, (uint8_t *)data2, 1, 1000); //Send dataFrame through UART
}
void Send_RS232_Command_OFF()
{
	char data2[30];

	memcpy(&RS232_command_OFF, &pcb_config.sSetR2S9COFF, NB_CHARS_RS232);
	to_hex(RS232_command_OFF, 0);
	for (int i = 0; i < NB_CHARS_RS232 / 2; i++)
		RS232_command_OFF[i] = RS232_command_OFF[2 * i + 1];

	HAL_UART_Transmit(&huart2, (uint8_t *)RS232_command_OFF, pcb_config.rs232nbcharsOFF[0], 1000); // Send dataFrame through UART
	memset(data2, 0, sizeof(data2));
	strcpy(data2, "Rs232 command OFF sent\n\r");
	HAL_UART_Transmit(&huart1, (uint8_t *)data2, sizeof("Rs232 command OFF sent\n\r"), 1000); // Send dataFrame through UART

	LogToBufferLog(data2, sizeof("Rs232 command OFF sent\n\r"));
	// HAL_UART_Transmit(&huart1, (uint8_t *)RS232_command_OFF, pcb_config.rs232nbcharsOFF[0], 1000); //Send dataFrame through UART
	// strcpy(data2, "\r");
	// HAL_UART_Transmit(&huart1, (uint8_t *)data2, sizeof(data2), 1000); //Send dataFrame through UART
}
void Send_IR_Command_Debug()
{
	//		char data[6]; //size of the number
	//		data[3] = (uint8_t)(IR_command & 0xFF);
	//		data[2] = (uint8_t)((IR_command >> 8) & 0xFF);
	//		data[1] = (uint8_t)((IR_command >> 16) & 0xFF);
	//		data[0] = (uint8_t)((IR_command >> 24) & 0xFF);
	//		data[4] = '\n';
	//		data[5] = '\r';

	// HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), 1000); //Send dataFrame through UART
	//IRSend_NEC(true);
}
void Send_IR_Command_Debug_OFF()
{
	//		char data[6]; //size of the number
	//		data[3] = (uint8_t)(IR_command_off & 0xFF);
	//		data[2] = (uint8_t)((IR_command_off >> 8) & 0xFF);
	//		data[1] = (uint8_t)((IR_command_off >> 16) & 0xFF);
	//		data[0] = (uint8_t)((IR_command_off >> 24) & 0xFF);
	//		data[4] = '\n';
	//		data[5] = '\r';

	// HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), 1000); //Send dataFrame through UART
	//IRSend_off_NEC();
}
void Send_IR_Command_Variable()
{
	//		char data[6]; //size of the number
	//		data[3] = (uint8_t)(IR_command & 0xFF);
	//		data[2] = (uint8_t)((IR_command >> 8) & 0xFF);
	//		data[1] = (uint8_t)((IR_command >> 16) & 0xFF);
	//		data[0] = (uint8_t)((IR_command >> 24) & 0xFF);
	//		data[4] = '\n';
	//		data[5] = '\r';

	// HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), 1000); //Send dataFrame through UART
	//IRSend_off_Var_NEC();
}
void Set_IR_Command(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
{
	IR_command = (uint32_t)(byte1 << 24) + (uint32_t)(byte2 << 16) + (uint32_t)(byte3 << 8) + byte4;
}
// void Set_RS232_Command(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4)
//{
//	RS232_command = (uint32_t)(byte1 << 24) + (uint32_t)(byte2 << 16) + (uint32_t)(byte3 << 8) + byte4;
// }

void Set_RS232_Command()
{
	for (int i = 0; i < NB_CHARS_RS232; i++)
		RS232_command_ON[i] = getRxUartBuffer(i + sizeof("SetR2S9C"));
}
void Send_Version_Data(void)
{
	char data[7];

	strcpy(data, FIRMWARE_VERSION);

	// charCount = strlen(data) + 3 ; //calcul the number of characters to send and add the 2 characters for the command + 1 character for the \r(0xOD)
	// sprintf(dataFrame, "test", charCount, GET_DATA, data); //assemble the frame to send with dataframe (7E + char count + command + data + \r(0xOD)
	HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data) - 1, 1000); // Send dataFrame through UART
	HAL_UART_Transmit(&huart2, (uint8_t *)data, sizeof(data) - 1, 1000); // Send dataFrame through UART
}
void Send_String(char *string1, int size)
{
	char data[30];

	strcpy(data, string1);

	// charCount = strlen(data) + 3 ; //calcul the number of characters to send and add the 2 characters for the command + 1 character for the \r(0xOD)
	// sprintf(dataFrame, "test", charCount, GET_DATA, data); //assemble the frame to send with dataframe (7E + char count + command + data + \r(0xOD)
	HAL_UART_Transmit(&huart1, (uint8_t *)data, size - 1, 1000); // Send dataFrame through UART
	// HAL_UART_Transmit(&huart2, (uint8_t *)data, size, 1000); //Send dataFrame through UART

	LogToBufferLog(data, size - 1);
}
void Send_Command_Data(uint32_t* command, int k, int on)
{
	uint8_t data[9 + MAX_NUMBER * 4];
	data[0] = 'I';
	data[1] = 'R';
	data[2] = 'C';
	data[3] = 'o';
	if (on)
	{
		data[4] = 'O';
		data[5] = 'N';
	}
	else
	{
		data[4] = 'O';
		data[5] = 'F';
	}
	data[6] = ':';

	for (int i = 0; i < k; i++)
	{
		data[7 + 4 * i] = (uint8_t)((command[i] >> 24) & 0xFF);
		data[8 + 4 * i] = (uint8_t)((command[i] >> 16) & 0xFF);
		data[9 + 4 * i] = (uint8_t)((command[i] >> 8) & 0xFF);
		data[10 + 4 * i] = (uint8_t)(command[i] & 0xFF);
	}

	data[9 + (k) * 4 - 2] = '\n';
	data[9 + (k) * 4 - 1] = '\r';

	HAL_UART_Transmit(&huart1, (uint8_t *)data, 9 + (k) * 4, 2000); // Send dataFrame through UART
	LogToBufferLog((char*)&data, 9 + (k) * 4);
	data[0] = 'M';
	data[1] = 'A';
	data[2] = 'X';
	data[3] = 'N';
	data[4] = 'B';
	data[5] = 'R';
	data[6] = ':';
	data[7] = k + 1 + 48;
	data[8] = '\n';
	data[9] = '\r';

	// HAL_UART_Transmit(&huart1, (uint8_t *)data, 10, 1000); //Send dataFrame through UART
}
void Send_Motion_Data(void)
{
	char data[6] = "\0";

	// Real data
	data[0] = 'p';
	data[1] = 'r';
	data[2] = '0';

	if (Motion_Is_Detected())
	{
		data[3] = '1';
	}
	else
	{
		data[3] = '0';
	}

	data[4] = '\n';

	data[5] = '\r';

	// charCount = strlen(data) + 3 ; //calcul the number of characters to send and add the 2 characters for the command + 1 character for the \r(0xOD)
	// sprintf(dataFrame, "test", charCount, GET_DATA, data); //assemble the frame to send with dataframe (7E + char count + command + data + \r(0xOD)
	HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), 1000); // Send dataFrame through UART
	HAL_UART_Transmit(&huart2, (uint8_t *)data, sizeof(data), 1000); // Send dataFrame through UART
	LogToBufferLog(data, sizeof(data));
}

void Send_Temperature_Data(float temp)
{
	char result[100];
	int dVal, dec, i;
	char data[15];
	temp += 0.005; // added after a comment from Matt McNabb, see below.

	dVal = temp;
	dec = (int)(temp * 100) % 100;

	memset(result, 0, 100);
	result[0] = (dec % 10) + '0';
	result[1] = (dec / 10) + '0';
	result[2] = '.';

	i = 3;
	while (dVal > 0)
	{
		result[i] = (dVal % 10) + '0';
		dVal /= 10;
		i++;
	}

	if (result[5] == 0)
	{
		data[0] = 'T';
		data[1] = 'e';
		data[2] = 'm';
		data[3] = 'p';
		data[4] = ':';
		data[5] = result[4];
		data[6] = result[3];
		data[7] = result[2];
		data[8] = result[1];
		data[9] = result[0];
		data[10] = ' ';
		data[11] = 'F';
		data[12] = '\n';
		data[13] = '\r';

		HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data) - 1, 1000); // Send dataFrame through UART
		HAL_UART_Transmit(&huart2, (uint8_t *)data, sizeof(data) - 1, 1000); // Send dataFrame through UART
	}
	else
	{
		data[0] = 'T';
		data[1] = 'e';
		data[2] = 'm';
		data[3] = 'p';
		data[4] = ':';
		data[5] = result[5];
		data[6] = result[4];
		data[7] = result[3];
		data[8] = result[2];
		data[9] = result[1];
		data[10] = result[0];
		data[11] = ' ';
		data[12] = 'F';
		data[13] = '\n';
		data[14] = '\r';

		HAL_UART_Transmit(&huart1, (uint8_t *)data, sizeof(data), 1000); // Send dataFrame through UART
		HAL_UART_Transmit(&huart2, (uint8_t *)data, sizeof(data), 1000); // Send dataFrame through UART
	}

	LogToBufferLog(data, sizeof(data));
}
void myPrintf(float fVal)
{
}
// Interruption Uart receive data
// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	if (indexRxUart >= BUFFER_LENGTH) //If the index reachs its maximum, reset variables
//	{
//		carriage_return_flag = false;
//		indexRxUart = 0;
//	}
//
//	rx_Buffer[indexRxUart++] =  rx_uart[0]; //store the UART datad
//
//	if (indexRxUart != 0)
//	{
//		if (rx_Buffer[indexRxUart-1] == '\n') //end of frame character (carriage return, hexa: 0x0D)
//		{
//			carriage_return_flag = true; //receive end of frame character
//			indexRxUart = 0; //initialize for the next frame
//		}
//	}
//
//
//	HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_uart, 1);  //Call again the UART interruption for the next time
//	HAL_UART_Receive_IT(&huart2, (uint8_t*)&rx_uart, 1);  //Call again the UART interruption for the next time
// }

char getRxUartBuffer(uint8_t index)
{
	return rx_Buffer[index];
}

bool Get_Carriage_Return_Flag(void)
{
	return carriage_return_flag;
}

void Set_Carriage_Return_Flag(bool new_flag)
{
	carriage_return_flag = new_flag;
}

void changeBaudRate(int baudrate, int word_length, int stop_bits)
{

	HAL_UART_Abort_IT(&huart2);
	HAL_UART_DeInit(&huart2);
	huart2.Init.BaudRate = baudrate;

	if (word_length == 1)
		huart2.Init.WordLength = UART_WORDLENGTH_7B;
	else if (word_length == 2)
		huart2.Init.WordLength = UART_WORDLENGTH_8B;
	else if (word_length == 3)
		huart2.Init.WordLength = UART_WORDLENGTH_9B;
	else
		huart2.Init.WordLength = UART_WORDLENGTH_8B;

	if (stop_bits == 1)
		huart2.Init.StopBits = UART_STOPBITS_0_5;
	else if (stop_bits == 2)
		huart2.Init.StopBits = UART_STOPBITS_1;
	else if (stop_bits == 3)
		huart2.Init.StopBits = UART_STOPBITS_1_5;
	else if (stop_bits == 4)
		huart2.Init.StopBits = UART_STOPBITS_2;
	else
		huart2.Init.StopBits = UART_STOPBITS_1;

	if (HAL_UART_Init(&huart2) != HAL_OK)
	{
		Error_Handler();
	}
	// if (HAL_UART_Receive_IT(&huart2, BUFFER, YOUR_BUFFER_SIZE) != HAL_OK) {
	//     Error_Handler();
	// }
	Send_String("Baudrate changed\r\n", sizeof("Baudrate changed\r\n"));
	char stringrer[] = "Baudrate changed\r\n";
	LogToBufferLog(stringrer, sizeof(stringrer));
}
void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{

	/* Restart DMA RX even if we encountered framing error, etc */

	// HAL_UART_Receive_IT(&huart1, (uint8_t*)&rx_uart, 1);
	// HAL_UART_Receive_IT(&huart2, (uint8_t*)&rx_uart, 1);  //Call again the UART interruption for the next time
}
/* USER CODE END 1 */
