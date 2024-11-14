#include "pcb_config.h"
#include "APP_Web.h"

struct PCB_Config pcb_config;

void SetPCB_Config()
{

	const int magic_define_version = MAGIC;

	// Set the default config parameters
	pcb_config.MagicNumber[0] = 0xDD;
	pcb_config.MagicNumber[1] = 0x55;
	pcb_config.MagicNumber[2] = magic_define_version;
	pcb_config.MagicNumber[3] = 0x11;

	//	pcb_config.sSetIR[0] = '2';
	//	pcb_config.sSetIR[1] = '0';
	//	pcb_config.sSetIR[2] = 'D';
	//	pcb_config.sSetIR[3] = 'F';
	//	pcb_config.sSetIR[4] = '2';
	//	pcb_config.sSetIR[5] = '3';
	//	pcb_config.sSetIR[6] = 'D';
	//	pcb_config.sSetIR[7] = 'C';
	//
	//	pcb_config.sSetIROFF[0] = '2';
	//	pcb_config.sSetIROFF[1] = '0';
	//	pcb_config.sSetIROFF[2] = 'D';
	//	pcb_config.sSetIROFF[3] = 'F';
	//	pcb_config.sSetIROFF[4] = 'A';
	//	pcb_config.sSetIROFF[5] = '3';
	//	pcb_config.sSetIROFF[6] = '5';
	//	pcb_config.sSetIROFF[7] = 'C';

	pcb_config.sSetIR[0] = 'E';
	pcb_config.sSetIR[1] = '0';
	pcb_config.sSetIR[2] = 'E';
	pcb_config.sSetIR[3] = '0';
	pcb_config.sSetIR[4] = '4';
	pcb_config.sSetIR[5] = '0';
	pcb_config.sSetIR[6] = 'B';
	pcb_config.sSetIR[7] = 'F';

	pcb_config.sSetIROFF[0] = 'E';
	pcb_config.sSetIROFF[1] = '0';
	pcb_config.sSetIROFF[2] = 'E';
	pcb_config.sSetIROFF[3] = '0';
	pcb_config.sSetIROFF[4] = '1';
	pcb_config.sSetIROFF[5] = '9';
	pcb_config.sSetIROFF[6] = 'E';
	pcb_config.sSetIROFF[7] = '6';
	//
	//	pcb_config.sSetIR[0] = 'E';
	//	pcb_config.sSetIR[1] = 'A';
	//	pcb_config.sSetIR[2] = 'C';
	//	pcb_config.sSetIR[3] = '7';
	//	pcb_config.sSetIR[0] = 'E';
	//	pcb_config.sSetIR[1] = '3';
	//	pcb_config.sSetIR[2] = '5';
	//	pcb_config.sSetIR[3] = '7';
	//	pcb_config.sSetIR[4] = 'E';
	//	pcb_config.sSetIR[5] = '8';
	//	pcb_config.sSetIR[6] = '1';
	//	pcb_config.sSetIR[7] = '7';
	//	pcb_config.sSetIROFF[0] = 'E';
	//	pcb_config.sSetIROFF[1] = '3';
	//	pcb_config.sSetIROFF[2] = '5';
	//	pcb_config.sSetIROFF[3] = '7';
	//	pcb_config.sSetIROFF[4] = 'E';
	//	pcb_config.sSetIROFF[5] = '8';
	//	pcb_config.sSetIROFF[6] = '1';
	//	pcb_config.sSetIROFF[7] = '7';

	//		pcb_config.sSetIR[0] = '2';
	//		pcb_config.sSetIR[1] = '1';
	//		pcb_config.sSetIR[2] = '7';
	//		pcb_config.sSetIR[3] = 'C';
	//		pcb_config.sSetIR[4] = '0';
	//		pcb_config.sSetIR[5] = 'C';
	//		pcb_config.sSetIR[6] = 'E';
	//		pcb_config.sSetIR[7] = 'C';
	//
	//		pcb_config.sSetIR[0] = '0';
	//				pcb_config.sSetIR[1] = '1';
	//				pcb_config.sSetIR[2] = '0';
	//				pcb_config.sSetIR[3] = '0';
	//				pcb_config.sSetIR[4] = 'B';
	//				pcb_config.sSetIR[5] = 'C';
	//				pcb_config.sSetIR[6] = '4';
	//				pcb_config.sSetIR[7] = '3';
	////
	//		pcb_config.sSetIROFF[0] = '0';
	//		pcb_config.sSetIROFF[1] = '1';
	//		pcb_config.sSetIROFF[2] = '0';
	//		pcb_config.sSetIROFF[3] = '0';
	//		pcb_config.sSetIROFF[4] = 'B';
	//		pcb_config.sSetIROFF[5] = 'C';
	//		pcb_config.sSetIROFF[6] = '4';
	//		pcb_config.sSetIROFF[7] = '3';

	pcb_config.tvtype[0] = '1'; // 0 = lg and 1 = samsung 2= panasonic

	pcb_config.sSetR2S9C[0] = 'A';
	pcb_config.sSetR2S9C[1] = 'A';
	pcb_config.sSetR2S9C[2] = '1';
	pcb_config.sSetR2S9C[3] = '1';
	pcb_config.sSetR2S9C[4] = 'F';
	pcb_config.sSetR2S9C[5] = 'E';
	pcb_config.sSetR2S9C[6] = '0';
	pcb_config.sSetR2S9C[7] = '1';
	pcb_config.sSetR2S9C[8] = '0';
	pcb_config.sSetR2S9C[9] = '1';
	pcb_config.sSetR2S9C[10] = '1';
	pcb_config.sSetR2S9C[11] = '1';
	//	pcb_config.sSetR2S9C[12] = '3';
	//	pcb_config.sSetR2S9C[13] = '0';
	//	pcb_config.sSetR2S9C[14] = '3';
	//	pcb_config.sSetR2S9C[15] = '1';
	//	pcb_config.sSetR2S9C[16] = '0';
	//	pcb_config.sSetR2S9C[17] = 'A';

	pcb_config.sSetR2S9COFF[0] = 'A';
	pcb_config.sSetR2S9COFF[1] = 'A';
	pcb_config.sSetR2S9COFF[2] = '1';
	pcb_config.sSetR2S9COFF[3] = '1';
	pcb_config.sSetR2S9COFF[4] = 'F';
	pcb_config.sSetR2S9COFF[5] = 'E';
	pcb_config.sSetR2S9COFF[6] = '0';
	pcb_config.sSetR2S9COFF[7] = '1';
	pcb_config.sSetR2S9COFF[8] = '0';
	pcb_config.sSetR2S9COFF[9] = '0';
	pcb_config.sSetR2S9COFF[10] = '1';
	pcb_config.sSetR2S9COFF[11] = '0';
	//	pcb_config.sSetR2S9COFF[12] = '3';
	//	pcb_config.sSetR2S9COFF[13] = '0';
	//	pcb_config.sSetR2S9COFF[14] = '3';
	//	pcb_config.sSetR2S9COFF[15] = '0';
	//	pcb_config.sSetR2S9COFF[16] = '0';
	//	pcb_config.sSetR2S9COFF[17] = 'A';

	pcb_config.sSetTempTreshMin[0] = '2';
	pcb_config.sSetTempTreshMin[1] = '1';
	pcb_config.sSetTempTreshMin[2] = '3';

	pcb_config.sSetTempTreshMax[0] = '4';
	pcb_config.sSetTempTreshMax[1] = '5';
	pcb_config.sSetTempTreshMax[2] = '5';

	pcb_config.sSetTempON[0] = '0';
	pcb_config.sSetPIRON[0] = '1';

	pcb_config.sPIRDelayON[0] = '0';
	pcb_config.sPIRDelayON[1] = '0';
	pcb_config.sPIRDelayON[2] = '1';
	pcb_config.sPIRDelayON[3] = '0';

	pcb_config.sPIRDelayOFF[0] = '0';
	pcb_config.sPIRDelayOFF[1] = '0';
	pcb_config.sPIRDelayOFF[2] = '5';
	pcb_config.sPIRDelayOFF[3] = '0';

	pcb_config.sSetIRON[0] = '1';
	pcb_config.sSetRS232ON[0] = '1';
	pcb_config.rs232nbcharsON[0] = 6;
	pcb_config.rs232nbcharsOFF[0] = 6;

	pcb_config.rs1[0] = '0';
	pcb_config.rs1[1] = '0';
	pcb_config.rs1[2] = '9';
	pcb_config.rs1[3] = '6';
	pcb_config.rs1[4] = '0';
	pcb_config.rs1[5] = '0';

	pcb_config.rs2[0] = '2';
	pcb_config.rs3[0] = '2';

	// todo HERE : ADD NEW INIT OF PARAMETERS. DEFAULT CONFIG WILL BE WRITTEN ON 1ST BOOT.
	pcb_config.loopoff = 2;
	pcb_config.loopon = 2;
	pcb_config.looptime = 5;
	// Mac address
	pcb_config.mac[0] = 0x00;
	pcb_config.mac[1] = 0x08;
	pcb_config.mac[2] = 0xdc;
	pcb_config.mac[3] = 0xab;
	pcb_config.mac[4] = 0xcd;
	pcb_config.mac[5] = 0xef;
	// IP address
	pcb_config.ip[0] = 192;
	pcb_config.ip[1] = 168;
	pcb_config.ip[2] = 0;
	pcb_config.ip[3] = 111;
	// Subnet mask
	pcb_config.sn[0] = 255;
	pcb_config.sn[1] = 255;
	pcb_config.sn[2] = 255;
	pcb_config.sn[3] = 0;
	// Gateway address
	pcb_config.gw[0] = 192;
	pcb_config.gw[1] = 168;
	pcb_config.gw[2] = 0;
	pcb_config.gw[3] = 1;
	// DNS server
	pcb_config.dns[0] = 8;
	pcb_config.dns[1] = 8;
	pcb_config.dns[2] = 8;
	pcb_config.dns[3] = 8;
	// DHCP enable / disable
	pcb_config.dhcp = NETINFO_STATIC;

	pcb_config.pcb_config_onSwitch = 0;
	pcb_config.pcb_config_onDateTime = 0;
	pcb_config.pcb_config_offSwitch = 0;
	pcb_config.pcb_config_offDateTime = 0;
	pcb_config.pcb_config_timezone = 15;

	for (int i = 0; i < 7; i++)
		pcb_config.pcb_config_Recursion_Alarm_ON[i] = 0;
	for (int i = 0; i < 7; i++)
		pcb_config.pcb_config_Recursion_Alarm_OFF[i] = 0;

	pcb_config.pcb_config_time_alarm_on_hh = 0;
	pcb_config.pcb_config_time_alarm_on_mm = 0;
	pcb_config.pcb_config_time_alarm_off_hh = 0;
	pcb_config.pcb_config_time_alarm_off_mm = 0;
}
