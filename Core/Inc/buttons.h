/*
 * motion_detect.h
 *
 *  Created on: Apr 5, 2021
 *      Author: yanik.richard
 */

#ifndef INC_BUTTONS_H_
#define INC_BUTTONS_H_
#include <stdbool.h>
#include "usart.h"
bool BTN1_Is_Pressed();
void Btn1_Process();
bool BTN2_Is_Pressed();
bool BTN3_Is_Pressed();
void Btn2_Process();
void Btn3_Process();
void SetBtnPress(bool trueorfalse, int btn);
#endif /* INC_BUTTONS_H_ */
