/*
 * motion_detect.h
 *
 *  Created on: Apr 5, 2021
 *      Author: yanik.richard
 */

#ifndef INC_MOTION_DETECT_H_
#define INC_MOTION_DETECT_H_
#include <stdbool.h>
#include "usart.h"
bool Motion_Is_Detected();
void Motion_Detection_Process();
void Set_PIR_Delay_OFF(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
void Set_PIR_Delay_ON(uint8_t byte1, uint8_t byte2, uint8_t byte3, uint8_t byte4);
typedef enum {INITMOT, NO_MOTION, MOTION} Motion_State ;
#endif /* INC_MOTION_DETECT_H_ */
