#ifndef __PCB_CONFIG_H__
#define __PCB_CONFIG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "main.h"
#include "usart.h"
#include "wizchip_conf.h"

#define MAGIC 0xDC

	/* USER CODE BEGIN Private defines */
	struct PCB_Config
	{
		char MagicNumber[4];			   // Magic number for eeprom saving and read
		char sSetIR[15];				   // IR ON COMMAND
		char sSetIROFF[15];				   // IR OFF COMMAND
		char sSetR2S9C[NB_CHARS_RS232];	   // RS232 COMMAND
		char sSetR2S9COFF[NB_CHARS_RS232]; // RS232 OFF COMMAND
		char sSetTempTreshMin[10];		   // TEMP Min TRESHOLD
		char sSetTempTreshMax[10];		   // TEMP Max TRESHOLD
		char sSetTempON[10];			   // TEMP ALARM = ON
		char sSetPIRON[10];				   // PIR Alarm = ON
		char sPIRDelayON[10];			   // PIR delay ON
		char sPIRDelayOFF[10];			   // PIR delay OFF
		char sSetIRON[10];				   // IR COMMAND on or OFF (default always ON)
		char sSetRS232ON[10];			   // RS232 command on or OFF (default always ON)
		char tvtype[2];					   // tv type = samsung, lg etc
		char rs232nbcharsON[2];			   // Numbers of RS232 chars configured
		char rs232nbcharsOFF[2];		   // Numbers of RS232 chars configured
		char rs1[6];					   // Baudrate setting 1
		char rs2[2];					   // Baudrate setting 2
		char rs3[2];					   // Baudrate setting 3
		uint8_t loopon;
		uint8_t loopoff;
		uint8_t looptime;
		uint8_t mac[6]; ///< Source Mac Address
		uint8_t ip[4];	///< Source IP Address
		uint8_t sn[4];	///< Subnet Mask
		uint8_t gw[4];	///< Gateway IP Address
		uint8_t dns[4]; ///< DNS server IP Address
		dhcp_mode dhcp; ///< 1 - Static, 2 - DHCP
		uint8_t pcb_config_onSwitch;
		uint32_t pcb_config_onDateTime;
		uint8_t pcb_config_offSwitch;
		uint32_t pcb_config_offDateTime;
		uint8_t pcb_config_timezone;
		int pcb_config_Recursion_Alarm_ON[7];
		int pcb_config_Recursion_Alarm_OFF[7];
		uint8_t pcb_config_time_alarm_on_hh;
		uint8_t pcb_config_time_alarm_on_mm;
		uint8_t pcb_config_time_alarm_off_hh;
		uint8_t pcb_config_time_alarm_off_mm;
	};

	void SetPCB_Config();

#ifdef __cplusplus
}
#endif

#endif /* __USART_H__ */
