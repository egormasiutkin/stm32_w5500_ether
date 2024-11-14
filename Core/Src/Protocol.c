/*
 * Protocol.c
 *
 *  Created on: Jul 4, 2023
 *      Author: yanik
 */

#include "Protocol.h"

struct tv_protocol tv_protocol[7];

void Set_tv_protocol()
{
	int index = 0;

	// SAMSUNG 0
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 560;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 1;
	tv_protocol[index].one_t_on = 1;
	tv_protocol[index].one_t_off = 3;
	tv_protocol[index].start_t_on = 16;
	tv_protocol[index].start_t_off = 8;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 1;
	tv_protocol[index].data_Length = 32;
	index++;

	// LG NEC1 1
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 560;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 1;
	tv_protocol[index].one_t_on = 1;
	tv_protocol[index].one_t_off = 3;
	tv_protocol[index].start_t_on = 8;
	tv_protocol[index].start_t_off = 8;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 1;
	tv_protocol[index].data_Length = 32;
	index++;

	// PANASONIC 2
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 432;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 1;
	tv_protocol[index].one_t_on = 1;
	tv_protocol[index].one_t_off = 3;
	tv_protocol[index].start_t_on = 8;
	tv_protocol[index].start_t_off = 4;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 173;
	tv_protocol[index].data_Length = 48; // = 32;
	index++;

	// SONY12 3
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 603;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 1;
	tv_protocol[index].one_t_on = 2;
	tv_protocol[index].one_t_off = 1;
	tv_protocol[index].start_t_on = 4;
	tv_protocol[index].start_t_off = 1;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 17;
	tv_protocol[index].data_Length = 16;
	index++;

	// RC5 4
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 993;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 1;
	tv_protocol[index].one_t_on = 1;
	tv_protocol[index].one_t_off = 1;
	tv_protocol[index].start_t_on = 1;
	tv_protocol[index].start_t_off = 1;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 1;
	tv_protocol[index].data_Length = 14;
	index++;

	// RC6 5
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 447;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 1;
	tv_protocol[index].one_t_on = 1;
	tv_protocol[index].one_t_off = 1;
	tv_protocol[index].start_t_on = 6;
	tv_protocol[index].start_t_off = 1;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 6;
	tv_protocol[index].data_Length = 14;
	index++;

	// SHARP 6
	tv_protocol[index].tv_type = index;
	tv_protocol[index].time_Unit = 330;
	tv_protocol[index].zero_t_on = 1;
	tv_protocol[index].zero_t_off = 2;
	tv_protocol[index].one_t_on = 1;
	tv_protocol[index].one_t_off = 5;
	tv_protocol[index].start_t_on = 1;
	tv_protocol[index].start_t_off = 1;
	tv_protocol[index].stop_t_on = 1;
	tv_protocol[index].stop_t_off = 1;
	tv_protocol[index].data_Length = 15;
	index++;
}
