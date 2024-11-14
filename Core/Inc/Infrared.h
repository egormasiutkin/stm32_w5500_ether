/*
 * Infrared.h
 *
 *  Created on: Aug 24, 2023
 *      Author: yanik
 */

#ifndef INC_INFRARED_H_
#define INC_INFRARED_H_

#include "usart.h"
#include "Protocol.h"
#include "main.h"
#include "stdbool.h"

void Delay_us(uint16_t us);
void NEC_Start();
void NEC_Stop();
void Logical_0_NEC();
void Logical_1_NEC();
void Logical_0_RC5();
void Logical_1_RC5();
void NEC_Send_Byte(uint8_t value);
void NEC_Send_Data(uint8_t value, uint8_t nbShift);
void IRSend_NEC(bool on_off);
void IRSend_Var_True();
void IRSend_Var_NEC(uint64_t code_to_send);
void IR_Receive_Process_OFF(void);
void IR_Receive_Process(void);
uint32_t receive_data(void);
void SONY12_Send_Data(uint64_t value);    // 12 bit
void RC5_Send_Data(uint64_t value);       // 12 bit
void Panasonic_Send_Data(uint64_t value); // 48 bit
void BurstSony12TV(uint64_t twelve_bits_code);
void BurstRC5TV(uint64_t fourteen_bits_code);
typedef enum
{
    INIT2,
    IDLE2,
    COMMAND_START3,
    COMMAND_START4,
    COMMAND_LENGTH2,
    WAIT2
} IR_Receive_OFF_State_def;
typedef enum
{
    INIT_IR,
    IDLE_IR,
    COMMAND_START,
    COMMAND_START2,
    COMMAND_LENGTH,
    WAIT
} IR_Receive_State_def;

void RC6_Send_Data(uint64_t value); // 14 bit
void Trailer_bit_0_RC6();
void Logical_1_RC6();
void Logical_0_RC6();
void RC6TV(uint64_t sixteen_bits_code);
void BurstRC6TV(uint64_t sixteen_bits_code);
void BurstNEC(bool trueorfalse);
void Sharp_Send_Data(uint64_t value, int reverse); // 15 bit;
void Logical_1_Sharp();
void Logical_0_Sharp();
#endif /* INC_INFRARED_H_ */
