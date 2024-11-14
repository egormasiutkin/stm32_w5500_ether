/**
 @file		httpd.c
 @brief 		functions associated http processing
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "socket.h"
#include "httpParser.h"
#include "pcb_config.h"
#include "Infrared.h"
#include "MyApp.h"
#include "buttons.h"
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
// uint8_t BUFPUB[2048];
uint8_t BUFPUB[256];
char sSetIR[6];
char sSetIROFF[15];
char sSetR2S9C[NB_CHARS_RS232];
char sSetRS232OFF[NB_CHARS_RS232];
char sSetTempTreshMin[7];
char sSetTempTreshMax[7];
char sSetTempON[7];
char sSetPIRON[7];
char sPIRDelayON[10];
char sPIRDelayOFF[6];
char sSetIRON[15];
char sSetRS232ON[NB_CHARS_RS232];
char tvtype[6];
char rs232nbcharsON[6];
char rs232nbcharsOFF[6];
char rs1[7];
char rs2[7];
char rs3[7];
char tv;
char test;
char pir;
char Temp;
extern uint64_t code_ON[1];
extern uint64_t code_OFF[1];
extern I2C_HandleTypeDef hi2c1;
extern uint32_t tv_type; // 0 = lg and 1 = samsung
extern int locked;
extern int on_receive;
extern uint32_t timestamp_1min_lock;
// extern IR_Receive_State_def IR_Receive_State;
// extern IR_Receive_OFF_State_def IR_Receive_OFF_State;

/*****************************************************************************
 * Private functions
 ****************************************************************************/
static void replacetochar(uint8_t *str, uint8_t oldchar, uint8_t newchar); /* Replace old character with new character in the string */
static uint8_t C2D(uint8_t c);											   /* Convert a character to HEX */

char function[10];
char param1[10];
char param2[10];

/**
 @brief	convert escape characters(%XX) to ASCII character
 */
void unescape_http_url(
	char *url /**< pointer to be converted ( escape characters )*/
)
{
	int x, y;

	for (x = 0, y = 0; url[y]; ++x, ++y)
	{
		if ((url[x] = url[y]) == '%')
		{
			url[x] = C2D(url[y + 1]) * 0x10 + C2D(url[y + 2]);
			y += 2;
		}
	}
	url[x] = '\0';
}

/**
 @brief	make response header such as html, gif, jpeg,etc.
 */
void make_http_response_head(
	char *buf,	 /**< pointer to response header to be made */
	char type,	 /**< response type */
	uint32_t len /**< size of response header */
)
{
	char *head;
	char tmp[10];

	/*  file type*/
	if (type == PTYPE_HTML)
		head = RES_HTMLHEAD_OK;
	else if (type == PTYPE_GIF)
		head = RES_GIFHEAD_OK;
	else if (type == PTYPE_TEXT)
		head = RES_TEXTHEAD_OK;
	else if (type == PTYPE_JPEG)
		head = RES_JPEGHEAD_OK;
	else if (type == PTYPE_FLASH)
		head = RES_FLASHHEAD_OK;
	else if (type == PTYPE_XML)
		head = RES_XMLHEAD_OK;
	else if (type == PTYPE_CSS)
		head = RES_CSSHEAD_OK;
	else if (type == PTYPE_JSON)
		head = RES_JSONHEAD_OK;
	else if (type == PTYPE_JS)
		head = RES_JSHEAD_OK;
	else if (type == PTYPE_CGI)
		head = RES_CGIHEAD_OK;
	else if (type == PTYPE_PNG)
		head = RES_PNGHEAD_OK;
	else if (type == PTYPE_ICO)
		head = RES_ICOHEAD_OK;
	else if (type == PTYPE_TTF)
		head = RES_TTFHEAD_OK;
	else if (type == PTYPE_OTF)
		head = RES_OTFHEAD_OK;
	else if (type == PTYPE_WOFF)
		head = RES_WOFFHEAD_OK;
	else if (type == PTYPE_EOT)
		head = RES_EOTHEAD_OK;
	else if (type == PTYPE_SVG)
		head = RES_SVGHEAD_OK;
#ifdef _HTTPPARSER_DEBUG_
	else
	{
		head = NULL;
		printf("\r\n\r\n-MAKE HEAD UNKNOWN-\r\n");
	}
#else
	else
		head = NULL;
#endif

	sprintf(tmp, "%ld", len);
	strcpy(buf, head);
	strcat(buf, tmp);
	strcat(buf, "\r\n\r\n");
}

/**
 @brief	find MIME type of a file
 */
void find_http_uri_type(
	uint8_t *type, /**< type to be returned */
	uint8_t *buff  /**< file name */
)
{
	/* Decide type according to extension*/

	char *buf;
	buf = (char *)buff;

	if (strstr(buf, ".htm") || strstr(buf, ".html"))
		*type = PTYPE_HTML;
	else if (strstr(buf, ".gif"))
		*type = PTYPE_GIF;
	else if (strstr(buf, ".text") || strstr(buf, ".txt"))
		*type = PTYPE_TEXT;
	else if (strstr(buf, ".jpeg") || strstr(buf, ".jpg"))
		*type = PTYPE_JPEG;
	else if (strstr(buf, ".swf"))
		*type = PTYPE_FLASH;
	else if (strstr(buf, ".cgi") || strstr(buf, ".CGI"))
		*type = PTYPE_CGI;
	else if (strstr(buf, ".json") || strstr(buf, ".JSON"))
		*type = PTYPE_JSON;
	else if (strstr(buf, ".js") || strstr(buf, ".JS"))
		*type = PTYPE_JS;
	else if (strstr(buf, ".CGI") || strstr(buf, ".cgi"))
		*type = PTYPE_CGI;
	else if (strstr(buf, ".xml") || strstr(buf, ".XML"))
		*type = PTYPE_XML;
	else if (strstr(buf, ".css") || strstr(buf, ".CSS"))
		*type = PTYPE_CSS;
	else if (strstr(buf, ".png") || strstr(buf, ".PNG"))
		*type = PTYPE_PNG;
	else if (strstr(buf, ".ico") || strstr(buf, ".ICO"))
		*type = PTYPE_ICO;
	else if (strstr(buf, ".ttf") || strstr(buf, ".TTF"))
		*type = PTYPE_TTF;
	else if (strstr(buf, ".otf") || strstr(buf, ".OTF"))
		*type = PTYPE_OTF;
	else if (strstr(buf, ".woff") || strstr(buf, ".WOFF"))
		*type = PTYPE_WOFF;
	else if (strstr(buf, ".eot") || strstr(buf, ".EOT"))
		*type = PTYPE_EOT;
	else if (strstr(buf, ".svg") || strstr(buf, ".SVG"))
		*type = PTYPE_SVG;
	else if (strstr(buf, ".bin") || strstr(buf, ".SVG"))
		*type = PTYPE_SVG;
	else
		*type = PTYPE_ERR;
}

/**
 @brief	parse http request from a peer
 */
void parse_http_request(
	st_http_request *request, /**< request to be returned */
	uint8_t *buf			  /**< pointer to be parsed */
)
{
	char *nexttok;
	nexttok = strtok((char *)buf, " ");
	if (!nexttok)
	{
		request->METHOD = METHOD_ERR;
		return;
	}
	if (!strcmp(nexttok, "GET") || !strcmp(nexttok, "get"))
	{
		request->METHOD = METHOD_GET;
		nexttok = strtok(NULL, " ");
	}
	else if (!strcmp(nexttok, "HEAD") || !strcmp(nexttok, "head"))
	{
		request->METHOD = METHOD_HEAD;
		nexttok = strtok(NULL, " ");
	}
	else if (!strcmp(nexttok, "POST") || !strcmp(nexttok, "post"))
	{
		nexttok = strtok(NULL, "\0");
		request->METHOD = METHOD_POST;
	}
	else
	{
		request->METHOD = METHOD_ERR;
	}

	if (!nexttok)
	{
		request->METHOD = METHOD_ERR;
		return;
	}
	strcpy((char *)request->URI, nexttok);
}

#ifdef _OLD_
/**
 @brief	get next parameter value in the request
 */
uint8_t *get_http_param_value(
	char *uri,
	char *param_name)
{
	char tempURI[MAX_URI_SIZE];
	uint8_t *name = 0;

	if (!uri || !param_name)
		return 0;

	strcpy((char *)tempURI, uri);
	if ((name = (uint8_t *)strstr(tempURI, param_name)))
	{
		name += strlen(param_name) + 1; // strlen(para_name) + strlen("=")
		if ((name = (uint8_t *)strtok((char *)name, "& \r\n\t\0")))
		{
			unescape_http_url((char *)name);
			replacetochar(name, '+', ' ');
		}
	}
#ifdef _HTTPPARSER_DEBUG_
	printf("  %s=%s", param_name, name);
#endif

	return name;
}
#else
/**
 @brief	get next parameter value in the request
 */
uint8_t *get_http_param_value(char *uri, char *param_name)
{

	uint8_t *name = 0;
	uint8_t *ret = BUFPUB;
	uint8_t *pos2;
	uint16_t len = 0, content_len = 0;
	uint8_t tmp_buf[10] = {
		0x00,
	};

	if (!uri || !param_name)
		return 0;

	/***************/
	mid(uri, "Content-Length: ", "\r\n", (char *)tmp_buf);
	content_len = ATOI(tmp_buf, 10);
	uri = strstr(uri, "\r\n\r\n");
	uri += 4;
	uri[content_len] = 0;
	/***************/

	if ((name = (uint8_t *)strstr(uri, param_name)))
	{
		name += strlen(param_name) + 1;
		pos2 = (uint8_t *)strstr((char *)name, "&");
		if (!pos2)
		{
			pos2 = name + strlen((char *)name);
		}
		len = pos2 - name;

		if (len)
		{
			ret[len] = 0;
			strncpy((char *)ret, (char *)name, len);
			unescape_http_url((char *)ret);
			replacetochar(ret, '+', ' ');
			// ret[len] = 0;
			// ret[strlen((int8*)ret)] = 0;
			// printf("len=%d\r\n",len);
		}
		else
		{
			ret[0] = 0;
		}
	}
	else
	{
		return 0;
	}

	printf("  %s=%s\r\n", param_name, ret);

	return ret;
}
#endif

#ifdef _OLD_
uint8_t *get_http_uri_name(uint8_t *uri)
{
	char tempURI[MAX_URI_SIZE];
	uint8_t *uri_name;

	if (!uri)
		return 0;

	strcpy(tempURI, (char *)uri);

	uri_name = (uint8_t *)strtok(tempURI, " ?");

	if (strcmp((char *)uri_name, "/"))
		uri_name++;

#ifdef _HTTPPARSER_DEBUG_
	printf("  uri_name = %s\r\n", uri_name);
#endif

	return uri_name;
}
#else

uint8_t get_http_uri_name(uint8_t *uri, uint8_t *uri_buf)
{
//	wiz_NetInfo gWIZNETINFO;

	uint8_t *uri_ptr;
	uint8_t *token;
//	uint8_t *api;

//	uint8_t *ip;
//	uint8_t *sn;
	if (!uri)
		return 0;

	strcpy((char *)uri_buf, (char *)uri);
	char* pch;
	char* hn;
//	char txt[100];
	token = (uint8_t *)strtok((char *)uri_buf, " ?");
	uri_ptr = token;
	printf((char*)uri);
	printf("\n");

	//memset(pch, 0, 128);
	//memset(hn, 0, 128);
	if (strstr((char*)uri, (char*)"TEST=1") != NULL)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		printf("LED ON1\n");
		test = 1;
	}
	if (strstr((char*)uri, (char*)"read") != NULL)
	{ // READ CONFIG

		//struct PCB_Config pcb_config_read;

		//			  uint8_t buffer2[sizeof(pcb_config_read)];
		//			  // Read the config
		//			  for( int j = 0; j < sizeof(pcb_config_read); j++ )
		//			  {
		//			  	  HAL_I2C_Mem_Read (&hi2c1, EEPROM_C24_ADDR_READ, 0x0+j, 1, &buffer2[j], 1, 1000);
		//			  	  HAL_Delay(10);
		//			  }
		//			  memcpy(&pcb_config_read, &buffer2, sizeof(pcb_config_read));
		// HAL_Delay(10);

		// memcpy(sSetIR, pcb_config_read.sSetIR, 4);
		//		  memcpy(sSetIRON, pcb_config.sSetIR, 8);
		//		  memcpy(sSetIRON, pcb_config.sSetIR, 4);
		//			  for (int i = 0; i < 4; i++)
		//				  sSetIR[i] =  pcb_config_read.sSetIR[i];
		//			  for (int i = 0; i < 6; i++)
		//				  sSetIROFF[i] =  pcb_config_read.sSetIROFF[i];
		//			  for (int i = 0; i < 7; i++)
		//				  sSetR2S9C[i] =  pcb_config_read.sSetR2S9C[i];
		//			  for (int i = 0; i < 7; i++)
		//				  sSetRS232OFF[i] =  pcb_config_read.sSetR2S9COFF[i];
		//			  for (int i = 0; i < 7; i++)
		//				  sSetTempTreshMin[i] =  pcb_config_read.sSetTempTreshMin[i];
		//			  for (int i = 0; i < 7; i++)
		//				  sSetTempTreshMax[i] =  pcb_config_read.sSetTempTreshMax[i];
		//			  for (int i = 0; i < 7; i++)
		//				   sSetTempON[i] =  pcb_config_read.sSetTempON[i];
		//			  for (int i = 0; i < 7; i++)
		//				  sSetPIRON[i] =  pcb_config_read.sSetPIRON[i];
		//			  for (int i = 0; i < 10; i++)
		//				  sPIRDelayON[i] =  pcb_config_read.sPIRDelayON[i];
		//			  for (int i = 0; i < 6; i++)
		//				  sPIRDelayOFF[i] =  pcb_config_read.sPIRDelayOFF[i];
		//			  for (int i = 0; i < 6; i++)
		//				  sSetIRON[i] =  pcb_config_read.sSetIRON[i];
		//			  for (int i = 0; i < 6; i++)
		//				  sSetRS232ON[i] =  pcb_config_read.sSetRS232ON[i];
		//			  for (int i = 0; i < 6; i++)
		//				  tvtype[i] =  pcb_config_read.tvtype[i];
		//			  for (int i = 0; i < 6; i++)
		//				  rs232nbcharsON[i] =  pcb_config_read.rs232nbcharsON[i];
		//			  for (int i = 0; i < 6; i++)
		//				  rs232nbcharsOFF[i] =  pcb_config_read.rs232nbcharsOFF[i];
		//			  for (int i = 0; i < 7; i++)
		//				  rs1[i] =  pcb_config_read.rs1[i];
		//			  for (int i = 0; i < 7; i++)
		//				  rs2[i] =  pcb_config_read.rs2[i];
		//			  for (int i = 0; i < 7; i++)
		//				  rs3[i] =  pcb_config_read.rs3[i];

		//				struct PCB_Config copy_config;
		//				memcpy(&copy_config, &pcb_config_read, sizeof(pcb_config_read));
		//				to_hex(copy_config.sSetIR, 0);
		//				for (int i = 0; i < 4; i++)
		//					copy_config.sSetIR[i] = copy_config.sSetIR[2 * i + 1];
		//				to_hex(copy_config.sSetIROFF, 0);
		//				for (int i = 0; i < 4; i++)
		//					copy_config.sSetIROFF[i] = copy_config.sSetIROFF[2 * i + 1];
		//
		//				code_ON[0] = ((uint32_t) (copy_config.sSetIR[0]) << 24) + ((uint32_t) (copy_config.sSetIR[1]) << 16) + ((uint32_t) (copy_config.sSetIR[2]) << 8) + copy_config.sSetIR[3]; //full_ir_code_from_db;//
		//
		//				code_OFF[0] = ((uint32_t) (copy_config.sSetIROFF[0]) << 24) + ((uint32_t) (copy_config.sSetIROFF[1]) << 16) + ((uint32_t) (copy_config.sSetIROFF[2]) << 8) + copy_config.sSetIROFF[3];
		//				tv_type = pcb_config.tvtype[0] - '0';

		//	Calculate_Temperatures_Offsets();

		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		// printf("READ CONFIG\n");
		test = 1;
	}
	if (strstr((char*)uri, (char*)"IP") != NULL)
	{ // SAVE CONFIG
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		// printf("SAVE CONFIG\n");
		test = 1;

		//				 for (int i = 0; i < 4; i++)
		//					    pcb_config.sSetIRON[i] = sSetIR[i];
		//				  for (int i = 0; i < 8; i++)
		//					  sSetIROFF[i] =  pcb_config.sSetIROFF[i];
		//				  for (int i = 0; i < 8; i++)
		//					  sSetR2S9C[i] =  pcb_config.sSetRS232ON[i];
		//				  for (int i = 0; i < 8; i++)
		//					  sSetRS232OFF[i] =  pcb_config.sSetR2S9COFF[i];
		//				  for (int i = 0; i < 7; i++)
		//					   pcb_config.sSetTempTreshMin[i] =  sSetTempTreshMin[i];
		//				  for (int i = 0; i < 7; i++)
		//					     pcb_config.sSetTempTreshMax[i] = sSetTempTreshMax[i];
		//				  for (int i = 0; i < 7; i++)
		//					   sSetTempON[i] =  pcb_config.sSetTempON[i];
		//				  for (int i = 0; i < 7; i++)
		//					  sSetPIRON[i] =  pcb_config.sSetPIRON[i];
		//				  for (int i = 0; i < 10; i++)
		//					  sPIRDelayON[i] =  pcb_config.sPIRDelayON[i];
		//				  for (int i = 0; i < 6; i++)
		//					  sPIRDelayOFF[i] =  pcb_config.sPIRDelayOFF[i];
		//				  for (int i = 0; i < 8; i++)
		//					  sSetIRON[i] =  pcb_config.sSetIR[i];
		//				  for (int i = 0; i < 8; i++)
		//					  sSetRS232ON[i] =  pcb_config.sSetR2S9C[i];
		//				  for (int i = 0; i < 2; i++)
		//					  tvtype[i] =  pcb_config.tvtype[i];
		//				  for (int i = 0; i < 2; i++)
		//					  rs232nbcharsON[i] =  pcb_config.rs232nbcharsON[i];
		//				  for (int i = 0; i < 2; i++)
		//					  rs232nbcharsOFF[i] =  pcb_config.rs232nbcharsOFF[i];
		//				  for (int i = 0; i < 6; i++)
		//					  rs1[i] =  pcb_config.rs1[i];
		//				  for (int i = 0; i < 2; i++)
		//					  rs2[i] =  pcb_config.rs2[i];
		//				  for (int i = 0; i < 2; i++)
		//					  rs3[i] =  pcb_config.rs3[i];
	}
	if (strstr((char*)uri, (char*)"TEST=2") != NULL)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		printf("LED OFF1\n");
		test = 0;
	}
	if (strstr((char*)uri, (char*)"PIR=1") != NULL)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		printf("LED ON2\n");
		pir = 1;
		sSetPIRON[0] = '1';
	}
	if (strstr((char*)uri, (char*)"PIR=2") != NULL)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		printf("LED OFF2\n");
		pir = 0;
		sSetPIRON[0] = '0';
	}
	if (strstr((char*)uri, (char*)"TEMP=1") != NULL)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		printf("LED ON3\n");
		Temp = 1;
		sSetTempON[0] = '1';
	}
	if (strstr((char*)uri, (char*)"TEMP=2") != NULL)
	{
		HAL_GPIO_WritePin(LED_GPIO_Port, LED_Pin, SET);
		printf("LED OFF3\n");
		Temp = 0;
		sSetTempON[0] = '0';
	}

	if (strstr((char*)uri, (char*)"button=1") != NULL)
	{
		printf("button1"); // button1 pressed
		Send_BTN_ON(1, 8);
		SetBtnPress(false, 2);
		loop2();
		loop3();
		Send_String("Logging to USB\n\r", sizeof("Logging to USB\n\r"));
	}
	if (strstr((char*)uri, (char*)"button=2") != NULL)
	{
		printf("button2"); // button1 pressed
		SetBtnPress(false, 1);
		Send_BTN_ON(1, 7);

		MyApp();
		//		code_ON[0] = ((uint32_t) (pcb_config.sSetIR[0]) << 24)
		//											+ ((uint32_t) (pcb_config.sSetIR[1]) << 16)
		//											+ ((uint32_t) (pcb_config.sSetIR[2]) << 8)
		//											+ pcb_config.sSetIR[3];
		//		code_OFF[0] = ((uint32_t) (pcb_config.sSetIROFF[0]) << 24)
		//											+ ((uint32_t) (pcb_config.sSetIROFF[1]) << 16)
		//											+ ((uint32_t) (pcb_config.sSetIROFF[2]) << 8)
		//											+ pcb_config.sSetIROFF[3];
		//		tv_type = pcb_config.tvtype[0] - '0';
		ReadAndSetConfig();
		Calculate_Temperatures_Offsets();
		int baurate = ((uint32_t)(pcb_config.rs1[0] - '0') * 100000) + ((uint32_t)(pcb_config.rs1[1] - '0') * 10000) + ((uint32_t)(pcb_config.rs1[2] - '0') * 1000) + ((uint32_t)(pcb_config.rs1[3] - '0') * 100) + ((uint32_t)(pcb_config.rs1[4] - '0') * 10) + ((uint32_t)(pcb_config.rs1[5] - '0'));

		changeBaudRate(baurate, pcb_config.rs2[0] - '0',
					   pcb_config.rs3[0] - '0');

		//				switch (tv_type)
		//				{
		//
		//				case 1:
		//					tv = 1;
		//					break;
		//				case 2:
		//					tv = 0;
		//					break;
		//				case 3:
		//					tv = 2;
		//					break;
		//				case 4:
		//					tv = 3;
		//					break;
		//				case 5:
		//					tv = 4;
		//					break;
		//				case 6:
		//					tv = 5;
		//					break;
		//				case 7:
		//					tv = 6;
		//					break;
		//				default:
		//					tv = 0;
		//				}
		tv_type = tv;
		sSetTempON[0] = pcb_config.sSetTempON[0];
		sSetPIRON[0] = pcb_config.sSetPIRON[0];
	}
	if (strstr((char*)uri, (char*)"button=3") != NULL)
	{
		printf("button3"); // button1 pressed
		Send_BTN_ON(0, 9);
		SetBtnPress(false, 1);
		Send_RS232_Command_ON();
		IRSend_NEC(true);
		// IRSend_NEC(true);
	}
	if (strstr((char*)uri, (char*)"button=4") != NULL)
	{
		printf("button4"); // button1 pressedà
		SetBtnPress(false, 2);
		Send_BTN_ON(1, 0);
		Send_RS232_Command_OFF();
		IRSend_NEC(false);
		// IRSend_NEC(false);
		// IRSend_NEC(false);
	}
	if (strstr((char*)uri, (char*)"button=5") != NULL)
	{
		SetBtnPress(false, 2);
		Send_BTN_ON(0, 6);
		on_receive = 1;
		locked = false;
		//	IR_Receive_State = INIT_IR;
		//	IR_Receive_OFF_State = INIT2;
		//	timestamp_1min_lock = HAL_GetTick();
		Send_Version_Data();
	}
	if (strstr((char*)uri, (char*)"button=6") != NULL)
	{
		Send_BTN_ON(0, 5);
		SetBtnPress(false, 1);
		locked = false;
		on_receive = 0;
		//	timestamp_1min_lock = HAL_GetTick();
		//	IR_Receive_State = INIT_IR;
		//	IR_Receive_OFF_State = INIT2;
		//		if(strcmp(pch+7,"1")){
		//			printf("button1");//button1 pressed
		//		}else if(strcmp(pch+7,"2")){
		//			printf("button2");//button2 pressed
		//		}else if(strcmp(pch+7,"3")){
		//			printf("button3");//button3 pressed
		//		}else if(strcmp(pch+7,"4")){
		//			printf("button4");//button4 pressed
		//		}
		//	}
	}
	if (strstr((char*)uri, (char*)"TV=1") != NULL)
	{
		printf("sumsung"); // sumsung
		tv = 1;
	}
	if (strstr((char*)uri, (char*)"TV=2") != NULL)
	{
		printf("LG"); // LG
		tv = 0;
	}
	if (strstr((char*)uri, (char*)"TV=3") != NULL)
	{
		printf("Panasonic"); // LG
		tv = 2;
	}
	if (strstr((char*)uri, (char*)"TV=4") != NULL)
	{
		printf("Sony"); // LG
		tv = 3;
	}
	if (strstr((char*)uri, (char*)"TV=5") != NULL)
	{
		printf("RC5"); // LG
		tv = 4;
	}
	if (strstr((char*)uri, (char*)"TV=6") != NULL)
	{
		printf("RC6"); // LG
		tv = 5;
	}
	if (strstr((char*)uri, (char*)"TV=7") != NULL)
	{
		printf("Sharp"); // LG
		tv = 6;
	}
	pch = strstr((char*)uri, (char*)"pir_delay_on=");
	hn = strchr(pch, '&');
	if (pch != NULL)
	{
		strncpy((char *)sPIRDelayON, pch + 13, hn - pch - 13);
		// printf("OK");
		printf("\nPIRDelayON: %s\n\n", sPIRDelayON);
	}
	pch = strstr((char*)uri, (char*)"pir_delay_off=");
	hn = strchr(pch + 14, '&');
	if (pch != NULL)
	{
		strncpy((char *)sPIRDelayOFF, pch + 14, hn - pch - 14);
		printf("\nPIRDelayOFF: %s\n\n", sPIRDelayOFF);
	}
	pch = strstr((char*)uri, (char*)"T_min_threshold=");
	hn = strchr(pch + 16, '&');
	if (pch != NULL)
	{
		strncpy((char *)sSetTempTreshMin, pch + 16, hn - pch - 16);
		printf("\nSetTempTreshMin: %s\n\n", sSetTempTreshMin);
	}
	pch = strstr((char*)uri, (char*)"T_max_threshold=");
	hn = strchr(pch + 16, '&');
	if (pch != NULL)
	{
		strncpy((char *)sSetTempTreshMax, pch + 16, hn - pch - 16);
		printf("\nSetTempTreshMax: %s\n\n", sSetTempTreshMax);
	}
	pch = strstr((char*)uri, (char*)"IR_com_on=");
	hn = strchr(pch + 10, '&');
	// printf("\nnumberSetIRON: %d  %d\n\n", pch,hn);
	if (pch != NULL)
	{
		strncpy((char *)sSetIRON, pch + 10, hn - pch - 10);
		printf("\nSetIRON: %s\n\n", sSetIRON);
	}
	pch = strstr((char*)uri, (char*)"IR_com_off=");
	hn = strchr(pch + 11, '&');
	if (pch != NULL)
	{
		strncpy((char *)sSetIROFF, pch + 11, hn - pch - 11);
		printf("\nSetIROFF: %s\n\n", sSetIROFF);
	}
	pch = strstr((char*)uri, (char*)"RS232_com_on=");
	hn = strchr(pch + 13, '&');
	if (pch != NULL)
	{
		strncpy((char *)sSetRS232ON, pch + 13, hn - pch - 13);
		printf("\nSetRS232ON: %s\n\n", sSetRS232ON);
	}
	pch = strstr((char*)uri, (char*)"RS232_com_off=");
	hn = strchr(pch + 14, '&');
	if (pch != NULL)
	{
		strncpy((char *)sSetRS232OFF, pch + 14, hn - pch - 14);
		printf("\nSetRS232OFF: %s\n\n", sSetRS232OFF);
	}
	pch = strstr((char*)uri, (char*)"RS232_set_rs1=");
	hn = strchr(pch + 14, '&');
	if (pch != NULL)
	{
		strncpy((char *)rs1, pch + 14, hn - pch - 14);
		printf("\nrs1: %s\n\n", rs1);
	}
	pch = strstr((char*)uri, (char*)"RS232_set_rs2=");
	hn = strchr(pch + 14, '&');
	if (pch != NULL)
	{
		strncpy((char *)rs2, pch + 14, hn - pch - 14);
		printf("\nrs2: %s\n\n", rs2);
	}
	pch = strstr((char*)uri, (char*)"RS232_set_rs3=");
	hn = strchr((char*)(pch + 14), 0);
	if (pch != NULL)
	{
		strncpy((char *)rs3, pch + 14, hn - pch - 14);
		printf("\nrs3: %s\n\n", rs3);
	}
	pch = strstr((char*)uri, (char*)"function=");
	hn = strchr(pch + 9, '&');
	if (pch != NULL)
	{
		strncpy((char *)function, pch + 9, hn - pch - 9);
		printf("\nfunction: %s\n\n", function);
	}
	pch = strstr((char*)uri, (char*)"param1=");
	hn = strchr(pch + 7, '&');
	if (pch != NULL)
	{
		strncpy((char *)param1, pch + 7, hn - pch - 7);
		printf("\nparam1: %s\n\n", param1);
	}
	pch = strstr((char*)uri, (char*)"param2=");
	hn = strchr((char*)(pch + 7), 0);
	if (pch != NULL)
	{
		strncpy((char *)param2, pch + 7, hn - pch - 7);
		printf("\nparam2: %s\n\n", param2);
	}
	/*if(pch != NULL){
		strcpy(txt, pch+7);
		printf("\nOutput Text: %s\n\n", txt);
	}*/

	if (strcmp((char *)uri_ptr, "/"))
		uri_ptr++;
	strcpy((char *)uri_buf, (char *)uri_ptr);

#ifdef _HTTPPARSER_DEBUG_
	printf("  uri_name = %s\r\n", uri_buf);
#endif

	// NOTE: ERHAN 3 new params
	if (strstr((char*)uri, (char*)"LOOPON=1") != NULL)
	{
		printf("LOOPON=1");
		loopon = 1;
	}
	if (strstr((char*)uri, (char*)"LOOPON=2") != NULL)
	{
		printf("LOOPON=2");
		loopon = 2;
	}

	if (strstr((char*)uri, (char*)"LOOPOFF=1") != NULL)
	{
		printf("LOOPOFF=1");
		loopoff = 1;
	}
	if (strstr((char*)uri, (char*)"LOOPOFF=2") != NULL)
	{
		printf("LOOPOFF=2");
		loopoff = 2;
	}

	if (strstr((char*)uri, (char*)"loop_time=") != NULL)
	{
		pch = strstr((char*)uri, (char*)"loop_time=");
		//char first_digit = pch[10];
		char second_digit = pch[11];
		if (second_digit == '&')
		{
			looptime = ((uint8_t)pch[10]) - 48;
		}
		else
		{
			looptime = (((uint8_t)pch[10]) - 48) * 10;
			looptime += ((uint8_t)pch[11]) - 48;
		}
	}

#if 0
	if(pch != NULL)
	{
		strncpy((char *)sPIRDelayON, pch+13, hn-pch-13);
		printf("\nLOOP TIME: %s\n\n", sPIRDelayON);
	}
#endif

	return 1;
}

#endif

void inet_addr_(uint8_t *addr, uint8_t *ip)
{
	uint8_t i;
	uint8_t taddr[30];
	uint8_t *nexttok;
	uint8_t num;

	strcpy((char *)taddr, (char *)addr);

	nexttok = taddr;
	for (i = 0; i < 4; i++)
	{
		nexttok = (uint8_t *)strtok((char *)nexttok, ".");
		if (nexttok[0] == '0' && nexttok[1] == 'x')
			num = ATOI(nexttok + 2, 0x10);
		else
			num = ATOI(nexttok, 10);
		ip[i] = num;
		nexttok = NULL;
	}
}

/**
@brief	CONVERT STRING INTO INTEGER
@return	a integer number
*/
uint32_t ATOI(
	uint8_t *str, /**< is a pointer to convert */
	uint8_t base  /**< is a base value (must be in the range 2 - 16) */
)
{
	unsigned int num = 0;
	// debug_2013_11_25
	//        while (*str !=0)
	while ((*str != 0) && (*str != 0x20)) // not include the space(0x020)
		num = num * base + C2D(*str++);
	return num;
}

/**
 * @brief Check strings and then execute callback function by each string.
 * @param src The information of URI
 * @param s1 The start string to be researched
 * @param s2 The end string to be researched
 * @param sub The string between s1 and s2
 * @return The length value atfer working
 */
void mid(char *src, char *s1, char *s2, char *sub)
{
	char *sub1;
	char *sub2;
	uint16_t n;

	sub1 = strstr((char *)src, (char *)s1);
	sub1 += strlen((char *)s1);
	sub2 = strstr((char *)sub1, (char *)s2);

	n = sub2 - sub1;
	strncpy((char *)sub, (char *)sub1, n);
	sub[n] = '\0';
}

////////////////////////////////////////////////////////////////////
// Static functions
////////////////////////////////////////////////////////////////////

/**
@brief	replace the specified character in a string with new character
*/
static void replacetochar(
	uint8_t *str,	 /**< pointer to be replaced */
	uint8_t oldchar, /**< old character */
	uint8_t newchar	 /**< new character */
)
{
	int x;
	for (x = 0; str[x]; x++)
		if (str[x] == oldchar)
			str[x] = newchar;
}

/**
@brief	CONVERT CHAR INTO HEX
@return	HEX

This function converts HEX(0-F) to a character
*/
static uint8_t C2D(
	uint8_t c /**< is a character('0'-'F') to convert to HEX */
)
{
	if (c >= '0' && c <= '9')
		return c - '0';
	if (c >= 'a' && c <= 'f')
		return 10 + c - 'a';
	if (c >= 'A' && c <= 'F')
		return 10 + c - 'A';

	return (char)c;
}
