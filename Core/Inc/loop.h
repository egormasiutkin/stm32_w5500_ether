/*
 * loop.h
 *
 *  Created on: Mar 7, 2024
 *      Author: Camille Chevrier
 */

#ifndef INC_LOOP_H_
#define INC_LOOP_H_

void loop_process(void);
typedef enum {LOOP_INIT, NO_LOOP, LOOP_PROCESS_ON, LOOP_PROCESS_OFF} Loop_State;

#endif /* INC_LOOP_H_ */
