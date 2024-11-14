#include "w5500_init.h"
#include <stdio.h>

#include "socket.h"

extern SPI_HandleTypeDef hspi1;

/* W5500 Call Back Functions */
void wizchip_select(void)
{
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_RESET);
}

void wizchip_deselect(void)
{
	HAL_GPIO_WritePin(CS_GPIO_Port, CS_Pin, GPIO_PIN_SET);
}

uint8_t wizchip_read()
{
	uint8_t rb;
	wizchip_readburst(&rb, sizeof(rb));
	return rb;
}

void wizchip_write(uint8_t wb)
{
	wizchip_writeburst(&wb, sizeof(wb));
}

void wizchip_readburst(uint8_t *pBuf, uint16_t len)
{
	HAL_SPI_Receive(&hspi1, pBuf, len, HAL_MAX_DELAY);
}

void wizchip_writeburst(uint8_t *pBuf, uint16_t len)
{
	HAL_SPI_Transmit(&hspi1, pBuf, len, HAL_MAX_DELAY);
}

void delay_cnt(volatile unsigned int nCount)
{
	for (; nCount != 0; nCount--)
		;
}

void Display_Net_Conf()
{
	uint8_t tmpstr[6] = {
		0,
	};
	wiz_NetInfo gWIZNETINFO;

	ctlnetwork(CN_GET_NETINFO, (void *)&gWIZNETINFO);
	ctlwizchip(CW_GET_ID, (void *)tmpstr);

	// Display Network Information
	if (gWIZNETINFO.dhcp == NETINFO_DHCP)
		printf("\r\n===== %s NET CONF : DHCP =====\r\n", (char *)tmpstr);
	else
		printf("\r\n===== %s NET CONF : Static =====\r\n", (char *)tmpstr);

	printf("\r\nMAC: %02X:%02X:%02X:%02X:%02X:%02X\r\n", gWIZNETINFO.mac[0], gWIZNETINFO.mac[1], gWIZNETINFO.mac[2], gWIZNETINFO.mac[3], gWIZNETINFO.mac[4], gWIZNETINFO.mac[5]);
	printf("IP: %d.%d.%d.%d\r\n", gWIZNETINFO.ip[0], gWIZNETINFO.ip[1], gWIZNETINFO.ip[2], gWIZNETINFO.ip[3]);
	printf("GW: %d.%d.%d.%d\r\n", gWIZNETINFO.gw[0], gWIZNETINFO.gw[1], gWIZNETINFO.gw[2], gWIZNETINFO.gw[3]);
	printf("SN: %d.%d.%d.%d\r\n", gWIZNETINFO.sn[0], gWIZNETINFO.sn[1], gWIZNETINFO.sn[2], gWIZNETINFO.sn[3]);
	printf("DNS: %d.%d.%d.%d\r\n", gWIZNETINFO.dns[0], gWIZNETINFO.dns[1], gWIZNETINFO.dns[2], gWIZNETINFO.dns[3]);
}

void Net_Conf(wiz_NetInfo netinfo)
{
	// wiz_NetInfo structure declared in the main.c

	/*wiz_NetInfo gWIZNETINFO = {
		{ 0x00, 0x08, 0xDC, 0x44, 0x55, 0x66 },				// Mac address
		{ 192, 168, 1, 12},								    // IP address
		{ 255, 255, 255, 0},								// Subnet mask
		{ 192, 168, 1, 1},									// Gateway
		{ 1, 1, 1, 1},										// DNS Server
	};
*/
	ctlnetwork(CN_SET_NETINFO, (void *)&netinfo);
}

void W5500_Init()
{
	uint8_t tmp;
	uint8_t memsize[2][8] = {{2, 2, 2, 2, 2, 2, 2, 2}, {2, 2, 2, 2, 2, 2, 2, 2}};

	// reset the module
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_RESET);
	tmp = 0xff;
	while (tmp--)
		;
	HAL_GPIO_WritePin(RST_GPIO_Port, RST_Pin, GPIO_PIN_SET);

	/* Register Call back function */
	reg_wizchip_cs_cbfunc(wizchip_select, wizchip_deselect);
	reg_wizchip_spi_cbfunc(wizchip_read, wizchip_write);
	reg_wizchip_spiburst_cbfunc(wizchip_readburst, wizchip_writeburst);

	/* W5500 Chip Initialization */
	if (ctlwizchip(CW_INIT_WIZCHIP, (void *)memsize) == -1)
	{
		printf("WIZCHIP Initialized fail.\r\n");
		while (1)
			;
	}
	printf("W5500 initialized\n");
}
