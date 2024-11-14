/*
 * Infrared.c
 *
 *  Created on: Aug 24, 2023
 *      Author: yanik
 */
/* USER CODE BEGIN 0 */

#include "Infrared.h"
#include <string.h>
extern TIM_HandleTypeDef htim14;
extern char tv;
uint64_t code_ON[MAX_NUMBER];
uint64_t code_OFF[MAX_NUMBER];
extern UART_HandleTypeDef huart1;
extern TIM_HandleTypeDef htim1;
extern I2C_HandleTypeDef hi2c1;
int receive_index_k = 0;
int receive_index_k_saved = 1;
uint32_t timer_tv_type_start = 0;
uint32_t timer_tv_type_end = 0;
uint32_t difference = 0;
extern struct tv_protocol tv_protocol[3];
uint8_t count;
int finish = 0;
uint32_t index_loop = 0;
uint32_t send_var = 0;
uint32_t timestamp_IR = 0;
uint32_t timestamp_IR_OFF = 0;
extern uint32_t tv_type; // 0 = lg and 1 = samsung
extern void *vptr_test;
int toggle = 0;
int toggle2 = 0;
IR_Receive_OFF_State_def IR_Receive_OFF_State = INIT2;
IR_Receive_State_def IR_Receive_State = INIT_IR;

void Delay_us(uint16_t us)
{
	__HAL_TIM_SET_COUNTER(&htim1, 0); // set the counter value a 0
	while (__HAL_TIM_GET_COUNTER(&htim1) < us)
		; // wait for the counter to reach the us input in the parameter
}

void NEC_Start()
{

	TIM14->CCR1 = VAR;
	Delay_us(tv_protocol[tv_type].start_t_on * tv_protocol[tv_type].time_Unit); // Delay_us(4500);// //Delay_us(9000);
	TIM14->CCR1 = 0;
	Delay_us(tv_protocol[tv_type].start_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(4500);
}
void NEC_Stop()
{

	TIM14->CCR1 = VAR;															// VAR;
	Delay_us(tv_protocol[tv_type].stop_t_on * tv_protocol[tv_type].time_Unit);	// Delay_us(4500);// //Delay_us(9000);
	TIM14->CCR1 = 0;															// 0;
	Delay_us(tv_protocol[tv_type].stop_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(4500);
}
void Logical_0_NEC()
{
	TIM14->CCR1 = VAR;															// 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(tv_protocol[tv_type].zero_t_on * tv_protocol[tv_type].time_Unit);	// Delay_us(560);/
	TIM14->CCR1 = 0;															// 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(tv_protocol[tv_type].zero_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(560);//
}

void Logical_1_NEC()
{
	TIM14->CCR1 = VAR;														   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);  // Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
	TIM14->CCR1 = 0;														   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit);
}
void Logical_0_RC5()
{
	TIM14->CCR1 = VAR;															// 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(tv_protocol[tv_type].zero_t_on * tv_protocol[tv_type].time_Unit);	// Delay_us(560);/
	TIM14->CCR1 = 0;															// 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(tv_protocol[tv_type].zero_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(560);//
}

void Logical_1_RC5()
{
	TIM14->CCR1 = 0;														   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);  // Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
	TIM14->CCR1 = VAR;														   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit);
}
void Logical_0_RC6()
{
	TIM14->CCR1 = 0;															// 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(tv_protocol[tv_type].zero_t_on * tv_protocol[tv_type].time_Unit);	// Delay_us(560);/
	TIM14->CCR1 = VAR;															// 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(tv_protocol[tv_type].zero_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(560);//
}

void Logical_1_RC6()
{
	TIM14->CCR1 = VAR;														   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);  // Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
	TIM14->CCR1 = 0;														   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit);
}
void Logical_0_Sharp()
{
	TIM14->CCR1 = VAR; // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(308);	   // Delay_us(312); //Delay_us(308);// Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
	TIM14->CCR1 = 0;   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(740);	   // Delay_us(735);//Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit);
}

void Logical_1_Sharp()
{
	TIM14->CCR1 = VAR; // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
	Delay_us(308);	   // Delay_us(312);// Delay_us(308);// Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
	TIM14->CCR1 = 0;   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
	Delay_us(1780);	   // Delay_us(1777);//Delay_us(1787);//Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit);
}
void Trailer_bit_0_RC6()
{
	if (toggle == 0)
	{
		toggle = 1;
		TIM14->CCR1 = VAR;															   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
		Delay_us(2 * tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);  // Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
		TIM14->CCR1 = 0;															   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
		Delay_us(2 * tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit);
	}
	else
	{
		toggle = 0;
		TIM14->CCR1 = 0;															   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_RESET);
		Delay_us(2 * tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);  // Delay_us(560); //Delay_us(tv_protocol[tv_type].one_t_on * tv_protocol[tv_type].time_Unit);
		TIM14->CCR1 = VAR;															   // 30% duty cycle 2HAL_GPIO_WritePin(GPIOA, RI_Pin, GPIO_PIN_SET);
		Delay_us(2 * tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit); // Delay_us(1680);//Delay_us(tv_protocol[tv_type].one_t_off * tv_protocol[tv_type].time_Unit)
	}
}

void NEC_Send_Byte(uint8_t value)
{
	uint8_t i;
	for (i = 0; i < 8; i++)
	{
		if (value & 0x80)
		{
			Logical_1_NEC();
		}
		else
		{
			Logical_0_NEC();
		}
		value <<= 1;
	}
}
void NEC_Send_Data(uint8_t value, uint8_t nbShift)
{
	uint8_t i;
	for (i = 0; i < nbShift; i++)
	{
		if (value & (1 << (nbShift - 1)))
		{
			Logical_1_NEC();
		}
		else
		{
			Logical_0_NEC();
		}
		value <<= 1;
	}
}
void SONY12_Send_Data(uint64_t value) // 12 bit
{
	uint8_t i;

	for (i = 0; i < 12; i++)
	{
		if ((value & 0x0800) >> 11)
		{
			Logical_1_NEC();
		}
		else
		{
			Logical_0_NEC();
		}

		value <<= 1;
	}
}
void Sharp_Send_Data(uint64_t value, int reverse) // 15 bit
{
	uint8_t i;

	if (reverse == 1)
	{
		for (i = 0; i < 5; i++)
		{
			if ((value & 0x4000) >> 14)
			{
				Logical_1_Sharp();
			}
			else
			{
				Logical_0_Sharp();
			}

			value <<= 1;
		}
		for (i = 5; i < 16; i++)
		{
			if ((value & 0x4000) >> 14)
			{
				Logical_0_Sharp();
			}
			else
			{
				Logical_1_Sharp();
			}

			value <<= 1;
		}
	}
	else
	{
		for (i = 0; i < 16; i++)
		{
			if ((value & 0x4000) >> 14)
			{
				Logical_1_Sharp();
			}
			else
			{
				Logical_0_Sharp();
			}

			value <<= 1;
		}
	}
	// Logical_0_Sharp();
}
void RC5_Send_Data(uint64_t value) // 14 bit
{
	uint8_t i;

	for (i = 0; i < 14; i++)
	{
		if ((value & 0x2000) >> 13)
		{
			Logical_1_RC5();
		}
		else
		{
			Logical_0_RC5();
		}

		value <<= 1;
	}
}
void RC6_Send_Data(uint64_t value) // 14 bit
{
	uint8_t i;

	for (i = 0; i < 16; i++)
	{
		if ((value & 0x8000) >> 15)
		{
			Logical_1_RC6();
		}
		else
		{
			Logical_0_RC6();
		}

		value <<= 1;
	}
}

void Panasonic_Send_Data(uint64_t value) // 48 bit
{
	uint8_t i;

	for (i = 0; i < 48; i++)
	{
		if ((value & 0x800000000000) >> 47)
		{
			Logical_1_NEC();
		}
		else
		{
			Logical_0_NEC();
		}

		value <<= 1;
	}
}
void BurstSony12TV(uint64_t twelve_bits_code)
{
	NEC_Start();
	SONY12_Send_Data(twelve_bits_code);
	HAL_Delay(45);
	NEC_Start();
	SONY12_Send_Data(twelve_bits_code);
	HAL_Delay(45);
	NEC_Start();
	SONY12_Send_Data(twelve_bits_code);
}
void BurstRC5TV(uint64_t fourteen_bits_code)
{
	// NEC_Start();
	RC5_Send_Data(fourteen_bits_code);
	HAL_Delay(45);
	// NEC_Start();
	RC5_Send_Data(fourteen_bits_code);
	HAL_Delay(45);
	// NEC_Start();
	RC5_Send_Data(fourteen_bits_code);
}
void RC6TV(uint64_t sixteen_bits_code)
{
	NEC_Start();					  // Leading Pulse
	Logical_1_RC6();				  // Start Bit
	Logical_0_RC6();				  // mode bit b2
	Logical_0_RC6();				  // mode bit b1
	Logical_0_RC6();				  // mode bit b0
	Trailer_bit_0_RC6();			  // Trailer bit
	RC6_Send_Data(sixteen_bits_code); // 16 bit adress + command
	TIM14->CCR1 = 0;
	HAL_Delay(2.7); // signal free time of 2.6 ms
}
void BurstRC6TV(uint64_t sixteen_bits_code)
{
	// NEC_Start();
	RC6TV(sixteen_bits_code);
	HAL_Delay(45);
	// NEC_Start();
	RC6TV(sixteen_bits_code);
	HAL_Delay(45);
	// NEC_Start();
	RC6TV(sixteen_bits_code);
}
void BurstNEC(bool trueorfalse)
{
	IRSend_NEC(trueorfalse);
	IRSend_NEC(trueorfalse);
	IRSend_NEC(trueorfalse);
}
void IRSend_NEC(bool on_off)
{
	uint8_t byte_to_send[4];

	// tv_type = 6;
	switch (tv_type)
	{
	case 0: // LG
	case 1: // Samsung
		__HAL_TIM_SET_AUTORELOAD(&htim14, 420);

		NEC_Start();

		if (on_off)
		{
			byte_to_send[0] = (uint8_t)((code_ON[0] >> 24) & 0xFF);
			byte_to_send[1] = (uint8_t)((code_ON[0] >> 16) & 0xFF);
			byte_to_send[2] = (uint8_t)((code_ON[0] >> 8) & 0xFF);
			byte_to_send[3] = (uint8_t)((code_ON[0]) & 0xFF);
		}
		else
		{
			byte_to_send[0] = (uint8_t)((code_OFF[0] >> 24) & 0xFF);
			byte_to_send[1] = (uint8_t)((code_OFF[0] >> 16) & 0xFF);
			byte_to_send[2] = (uint8_t)((code_OFF[0] >> 8) & 0xFF);
			byte_to_send[3] = (uint8_t)((code_OFF[0]) & 0xFF);
		}

		for (int i = 0; i < tv_protocol[tv_type].data_Length / 8; i++)
			NEC_Send_Data(byte_to_send[i], (tv_protocol[tv_type].data_Length / 4)); // NEC_Send_Byte(byte_to_send[i]);

		NEC_Stop();
		break;

	case 2: // PANASONIC
		// 1. interpretation: After the vendor code, the next byte is 4 bit VendorID parity and 4 bit Device and Subdevice
		//     The 5th byte is the function and the last (6.th) byte is xor of the three bytes before it.
		//     0_______ 1_______  2______ 3_______ 4_______ 5
		//     01234567 89ABCDEF  01234567 01234567 01234567 01234567
		//     01000000 00100100  Dev____  Sub_Dev_ Fun____  XOR( B2, B3, B4) - showing Panasonic vendor code 0x2002
		//  see: http://www.remotecentral.com/cgi-bin/mboard/rc-pronto/thread.cgi?26152
		//
		//  2. interpretation: LSB first, start bit + 16 VendorID + 4 VendorID parity + 4 Genre1 + 4 Genre2 + 10 Command + 2 ID + 8 Parity + stop bit
		//  see: https://www.mikrocontroller.net/articles/IRMP_-_english#KASEIKYO
		//  32 bit raw data LSB is VendorID parity.
		//
		//  We reduce it to: IRP: {37k,432}<1,-1|1,-3>(8,-4,V:16,X:4,D:4,S:8,F:8,(X^D^S^F):8,1,-173)+ {X=M:4:0^M:4:4^N:4:0^N:4:4}
		//  start bit + 16 VendorID + 4 VendorID parity + 12 Address + 8 Command + 8 Parity of VendorID parity, Address and Command + stop bit
		__HAL_TIM_SET_AUTORELOAD(&htim14, 435);
		NEC_Start();

		if (on_off)
			Panasonic_Send_Data(code_ON[0]); // Panasonic_Send_Data(0x40040100BCBD);
		else
			Panasonic_Send_Data(code_OFF[0]);
		NEC_Stop();
		HAL_Delay(100);
		NEC_Start();

		break;
	case 3: // SONY12
		__HAL_TIM_SET_AUTORELOAD(&htim14, 399);
		// BurstSony12TV(0xA90);
		if (on_off)
			BurstSony12TV(code_ON[0]);
		else
			BurstSony12TV(code_OFF[0]);
		break;

	case 4: // RC5
		__HAL_TIM_SET_AUTORELOAD(&htim14, 444);
		// BurstRC5TV(0x300C);
		if (on_off)
			BurstRC5TV(code_ON[0]);
		else
			BurstRC5TV(code_OFF[0]);
		break;

	case 5:
		__HAL_TIM_SET_AUTORELOAD(&htim14, 444);
		// BurstRC6TV(0x000C);
		if (on_off)
			BurstRC6TV(code_ON[0]);
		else
			BurstRC6TV(code_OFF[0]);
		break;

	case 6: // sharp tv
		__HAL_TIM_SET_AUTORELOAD(&htim14, 420);
		if (on_off)
		{

			Sharp_Send_Data(code_ON[0], 0);
			HAL_Delay(49.1);
			Sharp_Send_Data(code_ON[0], 1);
			HAL_Delay(46.18);
			Sharp_Send_Data(code_ON[0], 0);
			HAL_Delay(48.1);
			Sharp_Send_Data(code_ON[0], 1);
			HAL_Delay(46.18);
			Sharp_Send_Data(code_ON[0], 0);
			//			  Sharp_Send_Data(0x41A2);
			//			  HAL_Delay(49.1);
			//			  Sharp_Send_Data(0x425D);
			//			  HAL_Delay(46.18);
			//			  Sharp_Send_Data(0x41A2);
			//			  HAL_Delay(48.1);
			//			  Sharp_Send_Data(0x425D);
			//			  HAL_Delay(46.18);
			//			  Sharp_Send_Data(0x41A2);
		}
		else
		{
			Sharp_Send_Data(code_OFF[0], 0);
			HAL_Delay(49.1);
			Sharp_Send_Data(code_OFF[0], 1);
			HAL_Delay(46.18);
			Sharp_Send_Data(code_OFF[0], 0);
			HAL_Delay(48.1);
			Sharp_Send_Data(code_OFF[0], 1);
			HAL_Delay(46.18);
			Sharp_Send_Data(code_OFF[0], 0);
		}
		break;

	default:
		tv_type = 0;
		break;
	}
}
void IRSend_Var_NEC(uint64_t code_to_send)
{
	uint8_t byte_to_send[4];

	NEC_Start();

	byte_to_send[0] = (uint8_t)((code_to_send >> 24) & 0xFF);
	byte_to_send[1] = (uint8_t)((code_to_send >> 16) & 0xFF);
	byte_to_send[2] = (uint8_t)((code_to_send >> 8) & 0xFF);
	byte_to_send[3] = (uint8_t)((code_to_send) & 0xFF);

	for (int i = 0; i < tv_protocol[tv_type].data_Length / 8; i++)
		NEC_Send_Data(byte_to_send[i], (tv_protocol[tv_type].data_Length / 4));

	NEC_Stop();
}

void IRSend_Var_True()
{
	send_var = 1;
}

void IR_Receive_Process(void)
{
	switch (IR_Receive_State)
	{
	case INIT_IR:
		index_loop = 0;

		receive_index_k = 0;
		IR_Receive_State = IDLE_IR;
		finish = 0;
		count = 0;

		break;

	case IDLE_IR:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 0)
		{
			IR_Receive_State = COMMAND_START;
			timer_tv_type_start = HAL_GetTick();
		}
		Delay_us(100);
		break;
	case COMMAND_START:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 1)
		{
			IR_Receive_State = COMMAND_START2;
			difference = HAL_GetTick() - timer_tv_type_start;
			if (difference < 8 && difference > 3)
				tv_type = 1;
			else
				tv_type = 0;
		}
		Delay_us(100);
		break;
	case COMMAND_START2:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 0)
			IR_Receive_State = WAIT;
		Delay_us(100);
		timestamp_IR = HAL_GetTick();
		break;
	case WAIT:

		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 1)
			IR_Receive_State = COMMAND_LENGTH;
		// Delay_us(100);
		else // if((HAL_GetTick() - timestamp_IR) >= 10)
		{
			finish++; // finish = 1;
			// timestamp_IR = HAL_GetTick();
			if (finish >= 200)
			{
				IR_Receive_State = IDLE_IR;
				Send_Command_Data((uint32_t*)code_ON, receive_index_k, 1);

				for (int i = 0; i < 8; i++)
				{
					uint8_t temp_half_byte = (code_ON[0] >> (28 - 4 * i)) & 0x0F;
					if (temp_half_byte > 9)
						pcb_config.sSetIR[i] = temp_half_byte + '7';
					else
						pcb_config.sSetIR[i] = temp_half_byte + '0';
				}
				if (tv_type == 1)
					pcb_config.tvtype[0] = '1';
				else
					pcb_config.tvtype[0] = '0';

				// Write the default config into the eeprom
				vptr_test = &pcb_config;
				uint8_t buffer[sizeof(pcb_config)];

				memcpy(buffer, vptr_test, sizeof(pcb_config));
				//
				//					   for(int i = 0; i < sizeof(pcb_config); i++ )
				//					   {
				//						  HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, 0x20+i, 1, &buffer[i], 1, 1000);
				//						  HAL_Delay(10);
				//					   }

				HAL_Delay(10);
				receive_index_k_saved = receive_index_k;
				HAL_Delay(1000);
				index_loop = 0;
				receive_index_k = 0;
				finish = 0;
				count = 0;
				// on_receive = 0;
				// Delay_us(1000);
			}
		}

		break;

	case COMMAND_LENGTH:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 1)
		{
			count++;
			Delay_us(100);
		}
		else
		{

			if (count > 12) // if the space is more than 1.2 ms
			{
				code_ON[receive_index_k] |= (1UL << (31 - index_loop)); // write 1
			}
			else
				code_ON[receive_index_k] &= ~(1UL << (31 - index_loop)); // write 0
			finish = 0;

			// each 4 bytes, we switch to next in the table
			if (index_loop == 32 && receive_index_k != MAX_NUMBER) // if (index_loop == 32)
			{
				receive_index_k++;
				index_loop = 0;
				IR_Receive_State = WAIT;
			}
			if ((index_loop == 32 && receive_index_k == MAX_NUMBER)) // if (index_loop == 32)
			{
				IR_Receive_State = IDLE_IR;
				Send_Command_Data((uint32_t*)code_ON, receive_index_k, 1);
				receive_index_k_saved = receive_index_k;

				for (int i = 0; i < 8; i++)
				{
					uint8_t temp_half_byte = (code_ON[0] >> (28 - 4 * i)) & 0x0F;
					if (temp_half_byte > 9)
						pcb_config.sSetIR[i] = temp_half_byte + '7';
					else
						pcb_config.sSetIR[i] = temp_half_byte + '0';
				}
				if (tv_type == 1)
					pcb_config.tvtype[0] = '1';
				else
					pcb_config.tvtype[0] = '0';

				// Write the default config into the eeprom
				vptr_test = &pcb_config;
				uint8_t buffer[sizeof(pcb_config)];

				memcpy(buffer, vptr_test, sizeof(pcb_config));

				//					   for(int i = 0; i < sizeof(pcb_config); i++ )
				//					   {
				//						  HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, 0x2+i, 1, &buffer[i], 1, 1000);
				//						  HAL_Delay(10);
				//					   }

				HAL_Delay(10);
				//  HAL_Delay(1000);
				index_loop = 0;
				//  on_receive = 0;
				receive_index_k = 0;

				finish = 0;
			}
			else
			{
				index_loop++;
				IR_Receive_State = WAIT;
				count = 0;
				timestamp_IR = HAL_GetTick();
			}
		}

		break;
	}
}

void IR_Receive_Process_OFF(void)
{
	switch (IR_Receive_OFF_State)
	{
	case INIT2:
		index_loop = 0;

		receive_index_k = 0;
		IR_Receive_OFF_State = IDLE2;
		finish = 0;
		count = 0;

		break;

	case IDLE2:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 0)
		{
			IR_Receive_OFF_State = COMMAND_START3;
			timer_tv_type_start = HAL_GetTick();
		}
		Delay_us(100);
		break;
	case COMMAND_START3:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 1)
		{
			IR_Receive_OFF_State = COMMAND_START4;
			difference = HAL_GetTick() - timer_tv_type_start;
			if (difference < 8 && difference > 3)
				tv_type = 1;
			else
				tv_type = 0;
		}

		Delay_us(100);
		break;
	case COMMAND_START4:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 0)
			IR_Receive_OFF_State = WAIT2;
		Delay_us(100);
		timestamp_IR_OFF = HAL_GetTick();
		break;
	case WAIT2:

		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 1)
			IR_Receive_OFF_State = COMMAND_LENGTH2;
		// Delay_us(100);
		else // if((HAL_GetTick() - timestamp_IR_OFF) >= 10)
		{
			finish++; // finish = 1;
			// timestamp_IR_OFF = HAL_GetTick();
			if (finish >= 200)
			{
				IR_Receive_OFF_State = IDLE2;
				Send_Command_Data((uint32_t*)code_OFF, receive_index_k, 0);

				for (int i = 0; i < 8; i++)
				{
					uint8_t temp_half_byte = (code_OFF[0] >> (28 - 4 * i)) & 0x0F;
					if (temp_half_byte > 9)
						pcb_config.sSetIROFF[i] = temp_half_byte + '7';
					else
						pcb_config.sSetIROFF[i] = temp_half_byte + '0';
				}

				if (tv_type == 1)
					pcb_config.tvtype[0] = '1';
				else
					pcb_config.tvtype[0] = '0';

				// Write the default config into the eeprom
				vptr_test = &pcb_config;
				uint8_t buffer[sizeof(pcb_config)];

				memcpy(buffer, vptr_test, sizeof(pcb_config));

				//					   for(int i = 0; i < sizeof(pcb_config); i++ )
				//					   {
				//						  HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, 0x2+i, 1, &buffer[i], 1, 1000);
				//						  HAL_Delay(10);
				//					   }

				HAL_Delay(10);
				receive_index_k_saved = receive_index_k;
				HAL_Delay(1000);
				index_loop = 0;
				receive_index_k = 0;
				finish = 0;
				count = 0;
				// Delay_us(1000);
			}
		}

		break;

	case COMMAND_LENGTH2:
		if (HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin) == 1)
		{
			count++;
			Delay_us(100);
		}
		else
		{

			if (count > 12) // if the space is more than 1.2 ms
			{
				code_OFF[receive_index_k] |= (1UL << (31 - index_loop)); // write 1
			}
			else
				code_OFF[receive_index_k] &= ~(1UL << (31 - index_loop)); // write 0
			finish = 0;

			// each 4 bytes, we switch to next in the table
			if (index_loop == 32 && receive_index_k != MAX_NUMBER) // if (index_loop == 32)
			{
				receive_index_k++;
				index_loop = 0;
				IR_Receive_OFF_State = WAIT2;

				//				  }
				//				  if ((index_loop == 32 && receive_index_k == MAX_NUMBER))//if (index_loop == 32)
				//				  {
				IR_Receive_OFF_State = IDLE2;
				Send_Command_Data((uint32_t*)code_OFF, receive_index_k, 0);
				receive_index_k_saved = receive_index_k;

				for (int i = 0; i < 8; i++)
				{
					uint8_t temp_half_byte = (code_OFF[0] >> (28 - 4 * i)) & 0x0F;
					if (temp_half_byte > 9)
						pcb_config.sSetIROFF[i] = temp_half_byte + '7';
					else
						pcb_config.sSetIROFF[i] = temp_half_byte + '0';
				}

				if (tv_type == 1)
					pcb_config.tvtype[0] = '1';
				else
					pcb_config.tvtype[0] = '0';
				// Write the default config into the eeprom
				vptr_test = &pcb_config;
				uint8_t buffer[sizeof(pcb_config)];
//				uint8_t buffer2[sizeof(pcb_config)];

				memcpy(buffer, vptr_test, sizeof(pcb_config));

				//					   for(int i = 0; i < sizeof(pcb_config); i++ )
				//					   {
				//						  HAL_I2C_Mem_Write(&hi2c1, EEPROM_C24_ADDR_WRITE, 0x2+i, 1, &buffer[i], 1, 1000);
				//						  HAL_Delay(10);
				//					   }

				HAL_Delay(10);
				//  HAL_Delay(1000);
				index_loop = 0;

				receive_index_k = 0;

				finish = 0;
			}
			else
			{
				index_loop++;
				IR_Receive_OFF_State = WAIT2;
				count = 0;
				timestamp_IR_OFF = HAL_GetTick();
			}
		}

		break;
	}
}

uint32_t receive_data(void)
{
	uint32_t code = 0;

	/* The START Sequence begin here
	 * there will be a pulse of 9ms LOW and
	 * than 4.5 ms space (HIGH)
	 */
	while (!(HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin)))
		; // wait for the pin to go high.. 9ms LOW

	while ((HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin)))
		; // wait for the pin to go low.. 4.5ms HIGH

	/* START of FRAME ends here*/

	/* DATA Reception
	 * We are only going to check the SPACE after 562.5us pulse
	 * if the space is 562.5us, the bit indicates '0'
	 * if the space is around 1.6ms, the bit is '1'
	 */

	for (int i = 0; i < 32; i++)
	{
		count = 0;

		while (!(HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin)))
			; // wait for pin to go high.. this is 562.5us LOW

		while ((HAL_GPIO_ReadPin(IR_IN_GPIO_Port, IR_IN_Pin))) // count the space length while the pin is high
		{
			count++;
			Delay_us(100);
		}

		if (count > 12) // if the space is more than 1.2 ms
		{
			code |= (1UL << (31 - i)); // write 1
		}

		else
			code &= ~(1UL << (31 - i)); // write 0
	}

	return code;
}
