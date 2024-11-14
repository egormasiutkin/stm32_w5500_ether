/*
 * Protocol.h
 *
 *  Created on: Jul 4, 2023
 *      Author: yanik
 */

#ifndef INC_PROTOCOL_H_
#define INC_PROTOCOL_H_


struct tv_protocol
{
	int tv_type;
	int time_Unit;
	int zero_t_on;
	int zero_t_off;
	int one_t_on;
	int one_t_off;
	int start_t_on;
	int start_t_off;
	int stop_t_on;
	int stop_t_off;
	int data_Length;
};


void Set_tv_protocol();

#endif /* INC_PROTOCOL_H_ */
