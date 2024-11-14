#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "socket.h"
#include "wizchip_conf.h"
#include "webpage.h"
#include "httpServer.h"
#include "httpParser.h"
#include "httpUtil.h"
#include "pcb_config.h"
#include "main.h"
#include "APP_Web.h"

#ifdef _USE_SDCARD_
#include "ff.h" // header file for FatFs library (FAT file system)
#endif
#ifndef DATA_BUF_SIZE
#define DATA_BUF_SIZE 2048
#endif

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
int test2 = 0;
int length;
int length3;
static uint8_t HTTPSock_Num[_WIZCHIP_SOCK_NUM_] = {
	0,
};
static st_http_request *http_request;		 /**< Pointer to received HTTP request */
static st_http_request *parsed_http_request; /**< Pointer to parsed HTTP request */
static uint8_t *http_response;				 /**< Pointer to HTTP response */
extern uint32_t tv_type;					 // 0 = lg and 1 = samsung
extern uint8_t BUFPUB[256];

extern uint8_t onSwitch;
extern uint32_t onDateTime;
extern uint8_t offSwitch;
extern uint32_t offDateTime;
extern uint8_t timezone;
extern int Recursion_Alarm_ON[7];
extern int Recursion_Alarm_OFF[7];

extern char sSetIR[6];
extern char sSetIROFF[15];
extern char sSetR2S9C[NB_CHARS_RS232];
extern char sSetRS232OFF[NB_CHARS_RS232];
extern char sSetTempTreshMin[7];
extern char sSetTempTreshMax[7];
extern char sSetTempON[7];
extern char sSetPIRON[7];
extern char sPIRDelayON[10];
extern char sPIRDelayOFF[6];
extern char sSetIRON[15];
extern char sSetRS232ON[NB_CHARS_RS232];
extern char tvtype[6];
extern char rs232nbcharsON[6];
extern char rs232nbcharsOFF[6];
extern char rs1[7];
extern char rs2[7];
extern char rs3[7];
extern char tv;
extern char test;
extern char pir;
extern char Temp;
extern struct PCB_Config pcb_config;
extern uint64_t code_ON[1];
extern uint64_t code_OFF[1];
extern char function[10];
extern char param1[10];
extern char param2[10];
extern uint32_t tv_type; // 0 = lg and 1 = samsung
extern uint8_t time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm;

int test2;
char *firmware = "v770";
char *temp = "12.2";
char *PIRState = "Movement";
char *IRcommand = "0XDF52\0";
uint8_t variable = 0;
extern float temperature_farenheit;
char *PIRon;
char *PIRoff;
char *TEMPon;
char *TEMPoff;
char *samsung;
char *LG;
char *Panasonic;
char *Sony;
char *RC5;
char *RC6;
char *Sharp;
// ERHAN 3 new parameters
uint8_t loopon = 0;
uint8_t loopoff = 0;
uint8_t looptime = 0;
// Number of registered web content in code flash memory
static uint16_t total_content_cnt = 0;
/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
uint8_t *pHTTP_TX;
uint8_t *pHTTP_RX;

volatile uint32_t httpServer_tick_1s = 0;
st_http_socket HTTPSock_Status[_WIZCHIP_SOCK_NUM_] = {
	{
		STATE_HTTP_IDLE,
	},
};
httpServer_webContent web_content[MAX_CONTENT_CALLBACK];

#ifdef _USE_SDCARD_
FIL fs;		// FatFs: File object
FRESULT fr; // FatFs: File function return code
#endif

uint8_t settings_str[6000];

uint8_t str[15000];
uint8_t index_str[60500];

/*****************************************************************************
 * Private functions
 ****************************************************************************/
void httpServer_Sockinit(uint8_t cnt, uint8_t *socklist);
static uint8_t getHTTPSocketNum(uint8_t seqnum);
static int8_t getHTTPSequenceNum(uint8_t socket);
static int8_t http_disconnect(uint8_t sn);

static void http_process_handler(uint8_t s, st_http_request *p_http_request);
static void send_http_response_header(uint8_t s, uint8_t content_type, uint32_t body_len, uint16_t http_status);
static void send_http_response_body(uint8_t s, uint8_t *uri_name, uint8_t *buf, uint32_t start_addr, uint32_t file_len);
static void send_http_response_cgi(uint8_t s, uint8_t *buf, uint8_t *http_body, uint16_t file_len);
//static void APIs(uint8_t *function, uint8_t *param1, uint8_t *param2);

/*****************************************************************************
 * Public functions
 ****************************************************************************/
// Callback functions definition: MCU Reset / WDT Reset
void default_mcu_reset(void) { ; }
void default_wdt_reset(void) { ; }
void (*HTTPServer_ReStart)(void) = default_mcu_reset;
void (*HTTPServer_WDT_Reset)(void) = default_wdt_reset;

void httpServer_Sockinit(uint8_t cnt, uint8_t *socklist)
{
	uint8_t i;

	for (i = 0; i < cnt; i++)
	{
		// Mapping the H/W socket numbers to the sequential index numbers
		HTTPSock_Num[i] = socklist[i];
	}
}

static uint8_t getHTTPSocketNum(uint8_t seqnum)
{
	// Return the 'H/W socket number' corresponding to the index number
	return HTTPSock_Num[seqnum];
}

static int8_t getHTTPSequenceNum(uint8_t socket)
{
	uint8_t i;

	for (i = 0; i < _WIZCHIP_SOCK_NUM_; i++)
		if (HTTPSock_Num[i] == socket)
			return i;

	return -1;
}

void httpServer_init(uint8_t *tx_buf, uint8_t *rx_buf, uint8_t cnt, uint8_t *socklist)
{
	// User's shared buffer
	pHTTP_TX = tx_buf;
	pHTTP_RX = rx_buf;

	// H/W Socket number mapping
	httpServer_Sockinit(cnt, socklist);
}

/* Register the call back functions for HTTP Server */
void reg_httpServer_cbfunc(void (*mcu_reset)(void), void (*wdt_reset)(void))
{
	// Callback: HW Reset and WDT reset function for each MCU platforms
	if (mcu_reset)
		HTTPServer_ReStart = mcu_reset;
	if (wdt_reset)
		HTTPServer_WDT_Reset = wdt_reset;
}

void httpServer_run(uint8_t seqnum)
{
	uint8_t s; // socket number
	uint16_t len;
	uint32_t gettime = 0;

#ifdef _HTTPSERVER_DEBUG_
	uint8_t destip[4] = {
		0,
	};
	uint16_t destport = 0;
#endif

	http_request = (st_http_request *)pHTTP_RX; // Structure of HTTP Request
	parsed_http_request = (st_http_request *)pHTTP_TX;
	// Get the H/W socket number
	s = getHTTPSocketNum(seqnum);

	/* HTTP Service Start */
	switch (getSn_SR(s))
	{
	case SOCK_ESTABLISHED:
		// Interrupt clear
		if (getSn_IR(s) & Sn_IR_CON)
		{
			setSn_IR(s, Sn_IR_CON);
		}
		// HTTP Process states
		switch (HTTPSock_Status[seqnum].sock_status)
		{

		case STATE_HTTP_IDLE:
			if ((len = getSn_RX_RSR(s)) > 0)
			{
				if (len > DATA_BUF_SIZE)
					len = DATA_BUF_SIZE;
				len = recv(s, (uint8_t *)http_request, len);

				*(((uint8_t *)http_request) + len) = '\0';

				parse_http_request(parsed_http_request, (uint8_t *)http_request);

#ifdef _HTTPSERVER_DEBUG_
				getSn_DIPR(s, destip);
				destport = getSn_DPORT(s);
				printf("\r\n");
				printf("> HTTPSocket[%d] : HTTP Request received ", s);
				printf("from %d.%d.%d.%d : %d\r\n", destip[0], destip[1], destip[2], destip[3], destport);
#endif
#ifdef _HTTPSERVER_DEBUG_
				printf("> HTTPSocket[%d] : [State] STATE_HTTP_REQ_DONE\r\n", s);
#endif
				// HTTP 'response' handler; includes send_http_response_header / body function

				http_process_handler(s, parsed_http_request);

				gettime = get_httpServer_timecount();
				// Check the TX socket buffer for End of HTTP response sends
				while (getSn_TX_FSR(s) != (getSn_TxMAX(s)))
				{
					if ((get_httpServer_timecount() - gettime) > 3)
					{
#ifdef _HTTPSERVER_DEBUG_
						printf("> HTTPSocket[%d] : [State] STATE_HTTP_REQ_DONE: TX Buffer clear timeout\r\n", s);
#endif
						break;
					}
				}

				if (HTTPSock_Status[seqnum].file_len > 0)
					HTTPSock_Status[seqnum].sock_status = STATE_HTTP_RES_INPROC;
				else if ((char*)strstr((char*)parsed_http_request->URI, (char*)"/LOAD?TV=") == (char*)NULL)
				{
					HTTPSock_Status[seqnum].sock_status = STATE_HTTP_RES_DONE; // Send the 'HTTP response' end
				}

				if (strstr((char*)parsed_http_request->URI, (char*)"/LOAD?TEMP=") != NULL)
				{
					printf("aborted1\n");
					HTTPSock_Status[seqnum].sock_status = STATE_HTTP_IDLE;
				}

				if (strstr((char*)parsed_http_request->URI, (char*)"/LOAD?PIR=") != NULL)
				{
					printf("aborted3\n");
					HTTPSock_Status[seqnum].sock_status = STATE_HTTP_IDLE;
				}
				if (strstr((char*)parsed_http_request->URI, (char*)"/LOAD?TEST=") != NULL)
				{
					printf("aborted4\n");
					HTTPSock_Status[seqnum].sock_status = STATE_HTTP_IDLE;
				}
			}
			break;

		case STATE_HTTP_RES_INPROC:
			/* Repeat: Send the remain parts of HTTP responses */
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : [State] STATE_HTTP_RES_INPROC\r\n", s);
#endif
			// Repeatedly send remaining data to client
			send_http_response_body(s, 0, http_response, 0, 0);

			if (HTTPSock_Status[seqnum].file_len == 0)
				HTTPSock_Status[seqnum].sock_status = STATE_HTTP_RES_DONE;
			break;

		case STATE_HTTP_RES_DONE:
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : [State] STATE_HTTP_RES_DONE\r\n", s);
#endif
			// Socket file info structure re-initialize
			HTTPSock_Status[seqnum].file_len = 0;
			HTTPSock_Status[seqnum].file_offset = 0;
			HTTPSock_Status[seqnum].file_start = 0;
			HTTPSock_Status[seqnum].sock_status = STATE_HTTP_IDLE;

// #ifdef _USE_SDCARD_
//					f_close(&fs);
// #endif
#ifdef _USE_WATCHDOG_
			HTTPServer_WDT_Reset();
#endif
			http_disconnect(s);
			break;

		default:
			break;
		}
		break;

	case SOCK_CLOSE_WAIT:
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : ClOSE_WAIT\r\n", s); // if a peer requests to close the current connection
#endif
		disconnect(s);
		break;

	case SOCK_CLOSED:
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : CLOSED\r\n", s);
#endif
		if (socket(s, Sn_MR_TCP, HTTP_SERVER_PORT, 0x00) == s) /* Reinitialize the socket */
		{
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : OPEN\r\n", s);
#endif
		}
		break;

	case SOCK_INIT:
		listen(s);
		break;

	case SOCK_LISTEN:
		break;

	default:
		break;

	} // end of switch

#ifdef _USE_WATCHDOG_
	HTTPServer_WDT_Reset();
#endif
}

////////////////////////////////////////////
// Private Functions
////////////////////////////////////////////
static void send_http_response_header(uint8_t s, uint8_t content_type, uint32_t body_len, uint16_t http_status)
{
	switch (http_status)
	{
	case STATUS_OK:														// HTTP/1.1 200 OK
		if ((content_type != PTYPE_CGI) && (content_type != PTYPE_XML)) // CGI/XML type request does not respond HTTP header
		{
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : HTTP Response Header - STATUS_OK\r\n", s);
#endif
			make_http_response_head((char *)http_response, content_type, body_len);
		}
		else
		{
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : HTTP Response Header - NONE / CGI or XML\r\n", s);
#endif
			// CGI/XML type request does not respond HTTP header to client
			http_status = 0;
		}
		break;
	case STATUS_BAD_REQ: // HTTP/1.1 400 OK
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : HTTP Response Header - STATUS_BAD_REQ\r\n", s);
#endif
		memcpy(http_response, ERROR_REQUEST_PAGE, sizeof(ERROR_REQUEST_PAGE));
		break;
	case STATUS_NOT_FOUND: // HTTP/1.1 404 Not Found
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : HTTP Response Header - STATUS_NOT_FOUND\r\n", s);
#endif
		memcpy(http_response, ERROR_HTML_PAGE, sizeof(ERROR_HTML_PAGE));
		break;
	default:
		break;
	}

	// Send the HTTP Response 'header'
	if (http_status)
	{
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : [Send] HTTP Response Header [ %d ]byte\r\n", s, (uint16_t)strlen((char *)http_response));
#endif
		// printf("HTTP Response %s\r\n",(char *)http_response);
		send(s, http_response, strlen((char *)http_response));
		// printf("HTTP Response = %s\r\n",(char *)http_response);
	}
}

static void send_http_response_body(uint8_t s, uint8_t *uri_name, uint8_t *buf, uint32_t start_addr, uint32_t file_len)
{
	int8_t get_seqnum;
	uint32_t send_len;

	uint8_t flag_datasend_end = 0;

#ifdef _USE_SDCARD_
	uint16_t blocklen;
#endif
#ifdef _USE_FLASH_
	uint32_t addr = 0;
#endif

	if ((get_seqnum = getHTTPSequenceNum(s)) == -1)
		return; // exception handling; invalid number

	// Send the HTTP Response 'body'; requested file
	if (!HTTPSock_Status[get_seqnum].file_len) // ### Send HTTP response body: First part ###
	{
		if (file_len > DATA_BUF_SIZE - 1)
		{
			HTTPSock_Status[get_seqnum].file_start = start_addr;
			HTTPSock_Status[get_seqnum].file_len = file_len;
			send_len = DATA_BUF_SIZE - 1;

			/////////////////////////////////////////////////////////////////////////////////////////////////
			// ## 20141219 Eric added, for 'File object structure' (fs) allocation reduced (8 -> 1)
			memset(HTTPSock_Status[get_seqnum].file_name, 0x00, MAX_CONTENT_NAME_LEN);
			strcpy((char *)HTTPSock_Status[get_seqnum].file_name, (char *)uri_name);
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : HTTP Response body - file name [ %s ]\r\n", s, HTTPSock_Status[get_seqnum].file_name);
#endif
			/////////////////////////////////////////////////////////////////////////////////////////////////

#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : HTTP Response body - file len [ %ld ]byte\r\n", s, file_len);
#endif
		}
		else
		{
			// Send process end
			send_len = file_len;

#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : HTTP Response end - file len [ %ld ]byte\r\n", s, send_len);
#endif
		}
#ifdef _USE_FLASH_
		if (HTTPSock_Status[get_seqnum]->storage_type == DATAFLASH)
			addr = start_addr;
#endif
	}
	else // remained parts
	{
#ifdef _USE_FLASH_
		if (HTTPSock_Status[get_seqnum]->storage_type == DATAFLASH)
		{
			addr = HTTPSock_Status[get_seqnum].file_start + HTTPSock_Status[get_seqnum].file_offset;
		}
#endif
		send_len = HTTPSock_Status[get_seqnum].file_len - HTTPSock_Status[get_seqnum].file_offset;

		if (send_len > DATA_BUF_SIZE - 1)
		{
			send_len = DATA_BUF_SIZE - 1;
			// HTTPSock_Status[get_seqnum]->file_offset += send_len;
		}
		else
		{
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : HTTP Response end - file len [ %ld ]byte\r\n", s, HTTPSock_Status[get_seqnum].file_len);
#endif
			// Send process end
			flag_datasend_end = 1;
		}
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : HTTP Response body - send len [ %ld ]byte\r\n", s, send_len);
#endif
	}

	/*****************************************************/
	// HTTPSock_Status[get_seqnum]->storage_type == NONE
	// HTTPSock_Status[get_seqnum]->storage_type == CODEFLASH
	// HTTPSock_Status[get_seqnum]->storage_type == SDCARD
	// HTTPSock_Status[get_seqnum]->storage_type == DATAFLASH
	/*****************************************************/

	if (HTTPSock_Status[get_seqnum].storage_type == CODEFLASH)
	{
		if (HTTPSock_Status[get_seqnum].file_len)
			start_addr = HTTPSock_Status[get_seqnum].file_start;
		read_userReg_webContent(start_addr, &buf[0], HTTPSock_Status[get_seqnum].file_offset, send_len);
	}
#ifdef _USE_SDCARD_
	else if (HTTPSock_Status[get_seqnum].storage_type == SDCARD)
	{
		// Data read from SD Card
		fr = f_read(&fs, &buf[0], send_len, (void *)&blocklen);
		if (fr != FR_OK)
		{
			send_len = 0;
#ifdef _HTTPSERVER_DEBUG_
			printf("> HTTPSocket[%d] : [FatFs] Error code return: %d (File Read) / HTTP Send Failed - %s\r\n", s, fr, HTTPSock_Status[get_seqnum].file_name);
#endif
		}
		else
		{
			*(buf + send_len + 1) = 0; // Insert '/0' for indicates the 'End of String' (null terminated)
		}
	}
#endif

#ifdef _USE_FLASH_
	else if (HTTPSock_Status[get_seqnum]->storage_type == DATAFLASH)
	{
		// Data read from external data flash memory
		read_from_flashbuf(addr, &buf[0], send_len);
		*(buf + send_len + 1) = 0; // Insert '/0' for indicates the 'End of String' (null terminated)
	}
#endif
	else
	{
		send_len = 0;
	}
	// Requested content send to HTTP client
#ifdef _HTTPSERVER_DEBUG_
	printf("> HTTPSocket[%d] : [Send] HTTP Response body [ %ld ]byte\r\n", s, send_len);
#endif

	if (send_len)
		send(s, buf, send_len);
	else
		flag_datasend_end = 1;

	if (flag_datasend_end)
	{
		HTTPSock_Status[get_seqnum].file_start = 0;
		HTTPSock_Status[get_seqnum].file_len = 0;
		HTTPSock_Status[get_seqnum].file_offset = 0;
		flag_datasend_end = 0;
	}
	else
	{
		HTTPSock_Status[get_seqnum].file_offset += send_len;
#ifdef _HTTPSERVER_DEBUG_
		printf("> HTTPSocket[%d] : HTTP Response body - offset [ %ld ]\r\n", s, HTTPSock_Status[get_seqnum].file_offset);
#endif
	}

// ## 20141219 Eric added, for 'File object structure' (fs) allocation reduced (8 -> 1)
#ifdef _USE_SDCARD_
	f_close(&fs);
#endif
	// ## 20141219 added end
}

static void send_http_response_cgi(uint8_t s, uint8_t *buf, uint8_t *http_body, uint16_t file_len)
{
	uint16_t send_len = 0;

#ifdef _HTTPSERVER_DEBUG_
	printf("> HTTPSocket[%d] : HTTP Response Header + Body - CGI\r\n", s);
#endif
	send_len = sprintf((char *)buf, "%s%d\r\n\r\n%s", RES_CGIHEAD_OK, file_len, http_body);
#ifdef _HTTPSERVER_DEBUG_
	printf("> HTTPSocket[%d] : HTTP Response Header + Body - send len [ %d ]byte\r\n", s, send_len);
#endif

	send(s, buf, send_len);
}

static int8_t http_disconnect(uint8_t sn)
{
	setSn_CR(sn, Sn_CR_DISCON);
	/* wait to process the command... */
	while (getSn_CR(sn))
		;

	return SOCK_OK;
}

int parseIPAddress(const char *str, uint8_t *ipAddress)
{
	char *token;
	char strCopy[16]; // IP adresi için maksimum 15 karakter + null byte

	// Giriş dizesini kopyala
	strncpy(strCopy, str, sizeof(strCopy) - 1);
	strCopy[sizeof(strCopy) - 1] = '\0';

	// İlk üç bölümü ayır
	token = strtok(strCopy, ".");
	for (int i = 0; i < 3; ++i)
	{
		if (token == NULL)
		{
			return 0; // Geçersiz IP adresi
		}
		ipAddress[i] = atoi(token);
		token = strtok(NULL, ".");
	}

	// Sonuncu bölümü al, diğerlerini kontrol et
	if (token == NULL || atoi(token) < 0 || atoi(token) > 255)
	{
		return 0; // Geçersiz IP adresi
	}
	ipAddress[3] = atoi(token);

	return 1;
}

void getValues(const char *url)
{
	char *queryString = strchr(url, '?');
	if (queryString != NULL)
	{
		queryString++;

		while (*queryString != '\0')
		{
			char key[50];
			char value[50];
			int keyIndex = 0;
			int valueIndex = 0;

			// Skip the key
			while (*queryString != '=' && *queryString != '\0')
			{
				key[keyIndex++] = *queryString++;
			}
			key[keyIndex] = '\0';

			// Skip '='
			if (*queryString == '=')
			{
				queryString++;

				// Read the value until '&' or end of string
				while (*queryString != '&' && *queryString != '\0')
				{
					// Handle escape characters
					if (*queryString == '\\' && *(queryString + 1) == '0')
					{
						queryString += 2;
					}
					else if (*queryString == '\\' && *(queryString + 1) != '\0')
					{
						queryString++;
					}

					value[valueIndex++] = *queryString++;
				}
				value[valueIndex] = '\0';

				// Remove the extra null character if it exists
				int lastIdx = valueIndex - 1;
				if (valueIndex > 0 && value[lastIdx] == '\\' && (lastIdx == 0 || value[lastIdx - 1] != '\\'))
				{
					value[lastIdx] = '\0';
				}

				// Print the value only if it's not equal to "\\0"
				if (strcmp(value, "\\0") != 0)
				{
					printf("%s=%s\n", key, value);

					// Check if dhcpOrStatic is STATIC
					if (strcmp(key, "dhcpOrStatic") == 0)
					{
						if (strcmp(value, "STATIC") == 0)
						{
							gWIZNETINFO.dhcp = NETINFO_STATIC;
						}
						else if (strcmp(value, "DHCP") == 0)
						{
							gWIZNETINFO.dhcp = NETINFO_DHCP;
						}
					}

					// Check if key is ipAddress
					if (strcmp(key, "ipAddress") == 0)
					{
						parseIPAddress(value, gWIZNETINFO.ip);
					}

					// Check if key is subnetMask
					if (strcmp(key, "subnetMask") == 0)
					{
						parseIPAddress(value, gWIZNETINFO.sn);
					}

					// Check if key is gateway
					if (strcmp(key, "gateway") == 0)
					{
						parseIPAddress(value, gWIZNETINFO.gw);
					}

					// Check if key is dns1
					if (strcmp(key, "dns1") == 0)
					{
						parseIPAddress(value, gWIZNETINFO.dns);
					}

#if 0
                    // Check if key is dns2
                    if (strcmp(key, "dns2") == 0) {
                        parseIPAddress(value, network_settings.dns_2);
                    }
#endif
				}

				// Skip '&'
				if (*queryString == '&')
				{
					queryString++;
				}
			}
		}
	}
}

void changeIP(void)
{
	// Net_Conf(gWIZNETINFO);
	Init_WebAPP();
	Task_WebAPP();
}

static void http_process_handler(uint8_t s, st_http_request *p_http_request)
{
	uint8_t *uri_name;
	uint32_t content_addr = 0;
	uint16_t content_num = 0;
	uint32_t file_len = 0;

	uint8_t uri_buf[MAX_URI_SIZE] = {
		0x00,
	};

	uint16_t http_status;
	int8_t get_seqnum;
	uint8_t content_found;

	if ((get_seqnum = getHTTPSequenceNum(s)) == -1)
		return; // exception handling; invalid number

	http_status = 0;
	http_response = pHTTP_RX;
	file_len = 0;

	// method Analyze
	switch (p_http_request->METHOD)
	{
	case METHOD_ERR:
		http_status = STATUS_BAD_REQ;
		send_http_response_header(s, 0, 0, http_status);
		break;

	case METHOD_HEAD:
	case METHOD_GET:
		get_http_uri_name(p_http_request->URI, uri_buf);
		uri_name = uri_buf;
		if (!strcmp((char *)uri_name, "networksettings.html"))
		{
			if (p_http_request->URI[21] == '?')
			{
				getValues((char*)p_http_request->URI);
				changeIP();
				memcpy(&pcb_config.mac, &gWIZNETINFO.mac, 6);
				memcpy(&pcb_config.dns, &gWIZNETINFO.dns, 4);
				memcpy(&pcb_config.gw, &gWIZNETINFO.gw, 4);
				memcpy(&pcb_config.ip, &gWIZNETINFO.ip, 4);
				memcpy(&pcb_config.sn, &gWIZNETINFO.sn, 4);
				memcpy(&pcb_config.dhcp, &gWIZNETINFO.dhcp, 1);

				WriteToEeprom();
				// reg_httpServer_webContent((uint8_t*) "index.html", (uint8_t*) index_page);
			}

			// uint8_t *settings_str = NULL;
			// settings_str = calloc(5000, sizeof(uint8_t));
			memset(settings_str, 0, sizeof(settings_str));
			if (settings_str == NULL)
			{
				return;
			}

			sprintf((char*)settings_str,setting_page,
					gWIZNETINFO.dhcp == NETINFO_STATIC ? "selected" : "",
					gWIZNETINFO.dhcp == NETINFO_DHCP ? "selected" : "",
					gWIZNETINFO.ip[0], gWIZNETINFO.ip[1], gWIZNETINFO.ip[2], gWIZNETINFO.ip[3],
					gWIZNETINFO.sn[0], gWIZNETINFO.sn[1], gWIZNETINFO.sn[2], gWIZNETINFO.sn[3],
					gWIZNETINFO.gw[0], gWIZNETINFO.gw[1], gWIZNETINFO.gw[2], gWIZNETINFO.gw[3],
					gWIZNETINFO.dns[0],	gWIZNETINFO.dns[1],	gWIZNETINFO.dns[2], gWIZNETINFO.dns[3],
					gWIZNETINFO.dns[0],	gWIZNETINFO.dns[1],	gWIZNETINFO.dns[2],	gWIZNETINFO.dns[3]);

			uint16_t content_num = 0;
			uint32_t file_len = 0;
			if (find_userReg_webContent((uint8_t *)"networksettings.html", &content_num, &file_len))
			{
				web_content[content_num].content_len = sizeof(settings_str);
				web_content[content_num].content = (uint8_t *)settings_str;
			}
			else
			{
				reg_httpServer_webContent((uint8_t *)"networksettings.html", (uint8_t *)settings_str);
			}

			// free(settings_str);
		}
		else if (!strcmp((char *)uri_name, "load") || !strcmp((char *)uri_name, "IP") || !strcmp((char *)uri_name, "CONTROL") || !strcmp((char *)uri_name, "main.html"))
		{
			// IF SAVE BUTTON IS PRESSED
			if (!strcmp((char *)uri_name, "IP"))
			{
				memset(&pcb_config, 0, sizeof(pcb_config));
				pcb_config.MagicNumber[0] = 0xDD;
				pcb_config.MagicNumber[1] = 0x55;
				pcb_config.MagicNumber[2] = MAGIC;
				pcb_config.MagicNumber[3] = 0x11;
				pcb_config.rs232nbcharsON[0] = (char)(strlen(sSetRS232ON) / 2);	  // NB chars on
				pcb_config.rs232nbcharsOFF[0] = (char)(strlen(sSetRS232OFF) / 2); // NB chars off

				memcpy(pcb_config.sSetIR, sSetIRON, sizeof(sSetIRON));							 // IR ON COMMAND
				memcpy(pcb_config.sSetIROFF, sSetIROFF, sizeof(sSetIROFF));						 // IR OFF COMMAND
				memcpy(pcb_config.sSetTempTreshMin, sSetTempTreshMin, sizeof(sSetTempTreshMin)); // TEMP Min TRESHOLD
				memcpy(pcb_config.sSetTempTreshMax, sSetTempTreshMax, sizeof(sSetTempTreshMax)); // TEMP Max TRESHOLD
				memcpy(pcb_config.sSetR2S9COFF, sSetRS232OFF, sizeof(sSetRS232OFF));			 // RS232 OFF COMMAND
				memcpy(pcb_config.sSetR2S9C, sSetRS232ON, sizeof(sSetRS232ON));					 // RS232 COMMAND

				pcb_config.sSetTempON[0] = sSetTempON[0];
				pcb_config.sSetIRON[0] = sSetPIRON[0];
				pcb_config.sSetPIRON[0] = sSetPIRON[0];

				if (sPIRDelayON[0] == '0' && sPIRDelayON[1] == '0' && sPIRDelayON[2] == '0')
				{
					sPIRDelayON[2] = '1';
					sPIRDelayON[3] = '0';
				}
				if (sPIRDelayOFF[0] == '0' && sPIRDelayOFF[1] == '0' && sPIRDelayOFF[2] == '0')
				{
					sPIRDelayOFF[2] = '1';
					sPIRDelayOFF[3] = '0';
				}
				memcpy(pcb_config.sPIRDelayON, sPIRDelayON, sizeof(sPIRDelayON));	 // PIR delay ON
				memcpy(pcb_config.sPIRDelayOFF, sPIRDelayOFF, sizeof(sPIRDelayOFF)); // PIR delay OFF

				tvtype[0] = tv + '0';
				memcpy(pcb_config.tvtype, tvtype, 2); // tv type = samsung, lg etc

				memcpy(pcb_config.rs1, rs1, 6); // Baudrate setting 1
				memcpy(pcb_config.rs2, rs2, 2); // Baudrate setting 2
				memcpy(pcb_config.rs3, rs3, 2); // Baudrate setting 3

				pcb_config.loopon = loopon;
				pcb_config.loopoff = loopoff;
				pcb_config.looptime = looptime;

				memcpy(&pcb_config.mac, &gWIZNETINFO.mac, 6);
				memcpy(&pcb_config.dns, &gWIZNETINFO.dns, 4);
				memcpy(&pcb_config.gw, &gWIZNETINFO.gw, 4);
				memcpy(&pcb_config.ip, &gWIZNETINFO.ip, 4);
				memcpy(&pcb_config.sn, &gWIZNETINFO.sn, 4);
				memcpy(&pcb_config.dhcp, &gWIZNETINFO.dhcp, 1);

				pcb_config.pcb_config_onSwitch = onSwitch;
				pcb_config.pcb_config_onDateTime = onDateTime;
				pcb_config.pcb_config_offSwitch = offSwitch;
				pcb_config.pcb_config_offDateTime = offDateTime;
				pcb_config.pcb_config_timezone = timezone;
				pcb_config.pcb_config_time_alarm_on_hh = time_alarm_on_hh;
				pcb_config.pcb_config_time_alarm_on_mm = time_alarm_on_mm;
				pcb_config.pcb_config_time_alarm_off_hh = time_alarm_off_hh;
				pcb_config.pcb_config_time_alarm_off_mm = time_alarm_off_mm;
				memcpy(pcb_config.pcb_config_Recursion_Alarm_ON, Recursion_Alarm_ON, sizeof(pcb_config.pcb_config_Recursion_Alarm_ON));
				memcpy(pcb_config.pcb_config_Recursion_Alarm_OFF, Recursion_Alarm_OFF, sizeof(pcb_config.pcb_config_Recursion_Alarm_OFF));

				WriteToEeprom();
				Calculate_Temperatures_Offsets();
				ResetLoopProcess();
			}

			uint8_t result[100];
			int dVal, dec, i;
			temperature_farenheit += 0.005; // added after a comment from Matt McNabb, see below.

			dVal = temperature_farenheit;
			dec = (int)(temperature_farenheit * 100) % 100;

			memset(result, 0, 100);
			result[4] = (dec % 10) + '0';
			result[3] = (dec / 10) + '0';
			result[2] = '.';

			i = 1;
			while (dVal > 0)
			{
				result[i] = (dVal % 10) + '0';
				dVal /= 10;
				i--;
			}

			for (int i = 0; i < NB_CHARS_RS232; i++)
				sSetRS232ON[i] = pcb_config.sSetR2S9C[i];
			for (int i = 0; i < NB_CHARS_RS232; i++)
				sSetRS232OFF[i] = pcb_config.sSetR2S9COFF[i];

			for (int i = 0; i < 7; i++)
				sSetTempTreshMin[i] = pcb_config.sSetTempTreshMin[i];
			for (int i = 0; i < 7; i++)
				sSetTempTreshMax[i] = pcb_config.sSetTempTreshMax[i];

			for (int i = 0; i < 7; i++)
				sSetTempON[i] = pcb_config.sSetTempON[i];
			for (int i = 0; i < 7; i++)
				sSetPIRON[i] = pcb_config.sSetPIRON[i];

			for (int i = 0; i < 10; i++)
				sPIRDelayON[i] = pcb_config.sPIRDelayON[i];
			for (int i = 0; i < 6; i++)
				sPIRDelayOFF[i] = pcb_config.sPIRDelayOFF[i];

			for (int i = 0; i < 15; i++)
				sSetIRON[i] = pcb_config.sSetIR[i];
			for (int i = 0; i < 15; i++)
				sSetIROFF[i] = pcb_config.sSetIROFF[i];

			for (int i = 0; i < 2; i++)
				tvtype[i] = pcb_config.tvtype[i];

			for (int i = 0; i < 6; i++)
				rs1[i] = pcb_config.rs1[i];
			for (int i = 0; i < 2; i++)
				rs2[i] = pcb_config.rs2[i];
			for (int i = 0; i < 2; i++)
				rs3[i] = pcb_config.rs3[i];

			rs232nbcharsON[0] = (char)(strlen(sSetRS232ON) / 2);   // Numbers of RS232 chars configured
			rs232nbcharsOFF[0] = (char)(strlen(sSetRS232OFF) / 2); // Numbers of RS232 chars configured

			tv = tvtype[0] - '0';
			tv_type = tv;
			if ((pcb_config.sSetPIRON[0] - '0'))
			{
				PIRon = "selected";
				PIRoff = "";
			}
			else
			{
				PIRon = "";
				PIRoff = "selected";
			}
			if ((pcb_config.sSetTempON[0] - '0'))
			{
				TEMPon = "selected";
				TEMPoff = "";
			}
			else
			{
				TEMPon = "";
				TEMPoff = "selected";
			}
			if (tv == 1)
			{
				samsung = "selected";
				LG = "";
				Panasonic = "";
				Sony = "";
				RC5 = "";
				RC6 = "";
				Sharp = "";
			}
			else if (!tv)
			{
				LG = "selected";
				samsung = "";
				Panasonic = "";
				Sony = "";
				RC5 = "";
				RC6 = "";
				Sharp = "";
			}
			else if (tv == 2)
			{
				LG = "";
				samsung = "";
				Panasonic = "selected";
				Sony = "";
				RC5 = "";
				RC6 = "";
				Sharp = "";
			}
			else if (tv == 3)
			{
				LG = "";
				samsung = "";
				Panasonic = "";
				Sony = "selected";
				RC5 = "";
				RC6 = "";
				Sharp = "";
			}
			else if (tv == 4)
			{
				LG = "";
				samsung = "";
				Panasonic = "";
				Sony = "";
				RC5 = "selected";
				RC6 = "";
				Sharp = "";
			}
			else if (tv == 5)
			{
				LG = "";
				samsung = "";
				Panasonic = "";
				Sony = "";
				RC5 = "";
				RC6 = "selected";
				Sharp = "";
			}
			else if (tv == 6)
			{
				LG = "";
				samsung = "";
				Panasonic = "";
				Sony = "";
				RC5 = "";
				RC6 = "";
				Sharp = "selected";
			}

			temp = (char*)result;
			firmware = FIRMWARE_VERSION;

			if (Motion_Is_Detected())
				PIRState = "pr01";
			else
				PIRState = "pr00";

			char looptime_stringValue[30];
			sprintf(looptime_stringValue, "%d", looptime);

			memset(str, 0, sizeof(str));
			if (str == NULL)
			{
				return;
			}

			sprintf((char*)str,
					option_str,
					firmware, temp, PIRState, IRcommand,
					PIRon, PIRoff, TEMPon, TEMPoff, samsung, LG, Panasonic,
					Sony, RC5, RC6, Sharp,
					loopon == 1 ? "" : "selected",
					loopon == 2 ? "selected" : "",
					loopoff == 1 ? "" : "selected",
					loopoff == 2 ? "selected" : "",
					looptime_stringValue,
					sPIRDelayON, sPIRDelayOFF,
					sSetTempTreshMin, sSetTempTreshMax, sSetIRON,
					sSetIROFF, sSetRS232ON, sSetRS232OFF, rs1, rs2, rs3);

			test2 = strlen((char *)str);
			test2 = strlen((char *)index_page);

			memset(index_str, 0, sizeof(index_str));
			if (index_str == NULL)
			{
				return;
			}
			strcpy((char *)index_str, main_page);
				strcat((char*) index_str, str);

			memset(&sSetRS232ON, 0, sizeof(sSetRS232ON));
			memset(&sSetRS232OFF, 0, sizeof(sSetRS232OFF));
			memset(&sSetTempTreshMax, 0, sizeof(sSetTempTreshMax));
			memset(&sSetTempTreshMin, 0, sizeof(sSetTempTreshMin));
			memset(&sSetIROFF, 0, sizeof(sSetIROFF));
			memset(&sSetIRON, 0, sizeof(sSetIRON));
			memset(&sPIRDelayOFF, 0, sizeof(sPIRDelayOFF));
			memset(&rs1, 0, sizeof(rs1));
			memset(&rs2, 0, sizeof(rs2));
			memset(&rs3, 0, sizeof(rs3));

			uint16_t content_num = 0;
			uint32_t file_len = 0;
			if (find_userReg_webContent((uint8_t *)"main.html", &content_num, &file_len))
			{
				web_content[content_num].content = (uint8_t *)index_str;
			}
			else
			{
				reg_httpServer_webContent((uint8_t *)"main.html", index_str);
			}

			strcpy((char *)uri_name, INITIAL_WEBPAGE);
		}
		else if (!strcmp((char *)uri_name, "/"))
			strcpy((char *)uri_name, "index.html"); // If URI is "/", respond by index.html
		else if (!strcmp((char *)uri_name, "m"))
			strcpy((char *)uri_name, M_INITIAL_WEBPAGE);
		else if (!strcmp((char *)uri_name, "update_firmware.html"))
		{
			uint16_t content_num = 0;
			uint32_t file_len = 0;
			if (find_userReg_webContent((uint8_t *)"update_firmware.html", &content_num, &file_len))
			{
			}
			else
			{
				reg_httpServer_webContent((uint8_t *)"update_firmware.html", (uint8_t *)firmware_page);
			}
		}
		//			if (!strcmp((char *)uri_name, "mobile")) strcpy((char *)uri_name, MOBILE_INITIAL_WEBPAGE);
		find_http_uri_type(&p_http_request->TYPE, uri_name); // Checking requested file types (HTML, TEXT, GIF, JPEG and Etc. are included)

#ifdef _HTTPSERVER_DEBUG_
		printf("\r\n> HTTPSocket[%d] : HTTP Method GET\r\n", s);
		printf("> HTTPSocket[%d] : Request Type = %d\r\n", s,
			   p_http_request->TYPE);
		printf("> HTTPSocket[%d] : Request URI = %s\r\n", s, uri_name);
#endif

		if (p_http_request->TYPE == PTYPE_CGI)
		{
			content_found = http_get_cgi_handler(uri_name, pHTTP_TX, &file_len);
			if (content_found && (file_len <= (DATA_BUF_SIZE - (strlen(RES_CGIHEAD_OK) + 8))))
			{
				// printf("http response = %s\r\n", http_response);
				// printf("pHTTP_TX = %s\r\n", pHTTP_TX);
				send_http_response_cgi(s, http_response, pHTTP_TX,
									   (uint16_t)file_len);
				// printf("http response = %s\r\n", http_response);
				// printf("pHTTP_TX = %s\r\n", pHTTP_TX);
			}
			else
			{
				send_http_response_header(s, PTYPE_CGI, 0, STATUS_NOT_FOUND);
			}
		}
		else
		{
			// Find the User registered index for web content
			if (find_userReg_webContent(uri_buf, &content_num, &file_len))
			{
				content_found = 1; // Web content found in code flash memory
				content_addr = (uint32_t)content_num;
				HTTPSock_Status[get_seqnum].storage_type = CODEFLASH;
#if 1
				if (0 == strcmp((char *)uri_name, "set_file"))
				{
					set_file_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}
				if (0 == strcmp((char *)uri_name, "timesyncpage"))
				{
					time_sync_page_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}

				else if (0 == strcmp((char *)uri_name, "timesync"))
				{
					set_time_sync_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}

				else if (0 == strcmp((char *)uri_name, "gettimesync"))
				{
					get_time_sync_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}
				else if (0 == strcmp((char *)uri_name, "file_get"))
				{
					get_file_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}
				else if (0 == strcmp((char *)uri_name, "get_alarm"))
				{
					get_alarm_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}

				else if (0 == strcmp((char *)uri_name, "set_alarm"))
				{
					set_alarm_callback(web_content + content_num, p_http_request);
					// update file length
					file_len = web_content[content_num].content_len;
				}

#endif
			}
			// Not CGI request, Web content in 'SD card' or 'Data flash' requested
#ifdef _USE_SDCARD_
#ifdef _HTTPSERVER_DEBUG_
			printf("\r\n> HTTPSocket[%d] : Searching the requested content\r\n", s);
#endif
			if ((fr = f_open(&fs, (const char *)uri_name, FA_READ)) == 0)
			{
				content_found = 1; // file open succeed

				file_len = fs.fsize;
				content_addr = fs.sclust;
				HTTPSock_Status[get_seqnum].storage_type = SDCARD;
			}
#elif _USE_FLASH_
			else if (/* Read content from Dataflash */)
			{
				content_found = 1;
				HTTPSock_Status[get_seqnum]->storage_type = DATAFLASH;
				; // To do
			}
#endif
			else
			{
				content_found = 0; // fail to find content
			}

			if (!content_found)
			{
#ifdef _HTTPSERVER_DEBUG_
				printf("> HTTPSocket[%d] : Unknown Page Request\r\n", s);
#endif
				http_status = STATUS_NOT_FOUND;
			}
			else
			{
#ifdef _HTTPSERVER_DEBUG_
				printf("> HTTPSocket[%d] : Find Content [%s] ok - Start [%ld] len [ %ld ]byte\r\n", s, uri_name, content_addr, file_len);
#endif
				http_status = STATUS_OK;
			}

			// Send HTTP header
			if (http_status)
			{
#ifdef _HTTPSERVER_DEBUG_
				printf("> HTTPSocket[%d] : Requested content len = [ %ld ]byte\r\n", s, file_len);
#endif
				send_http_response_header(s, p_http_request->TYPE, file_len, http_status);
			}

			// Send HTTP body (content)
			if (http_status == STATUS_OK)
			{
				send_http_response_body(s, uri_name, http_response, content_addr, file_len);
			}
		}

		// total_content_cnt = 2;
		break;

	case METHOD_POST:
		mid((char *)p_http_request->URI, "/", " HTTP", (char *)uri_buf);
		uri_name = uri_buf;
		find_http_uri_type(&p_http_request->TYPE, uri_name); // Check file type (HTML, TEXT, GIF, JPEG are included)
		if (p_http_request->TYPE == PTYPE_CGI) // HTTP POST Method; CGI Process
		{
			content_found = http_post_cgi_handler(uri_name, p_http_request, http_response, &file_len);

			printf("> HTTPSocket[%d] : [CGI: %s] / Response len [ %ld ]byte\r\n", s, content_found ? "Content found" : "Content not found", file_len);

			if (content_found && (file_len <= (DATA_BUF_SIZE - (strlen(RES_CGIHEAD_OK) + 8))))
			{

				send_http_response_cgi(s, pHTTP_TX, http_response, (uint16_t)file_len);

				// Reset the H/W for apply to the change configuration information
				if (content_found == HTTP_RESET)
					HTTPServer_ReStart();
			}
			else
			{
				send_http_response_header(s, PTYPE_CGI, 0, STATUS_NOT_FOUND);
			}
		}
		else // HTTP POST Method; Content not found
		{
			send_http_response_header(s, 0, 0, STATUS_NOT_FOUND);
		}
		break;

	default:
		http_status = STATUS_BAD_REQ;
		send_http_response_header(s, 0, 0, http_status);
		break;
	}
}

void httpServer_time_handler(void)
{
	httpServer_tick_1s++;
}

uint32_t get_httpServer_timecount(void)
{
	return httpServer_tick_1s;
}

void reg_httpServer_webContent(uint8_t *content_name, uint8_t *content)
{
	uint16_t name_len;
	uint32_t content_len = 0;
	printf("total_content_cnt = %d\n\n", total_content_cnt);

	if (content_name == NULL)
	{
		printf("content null\n");
		printf("content name :%s\n", content_name);
		// printf("content :%s\n",content);
		return;
	}
	else if (total_content_cnt >= MAX_CONTENT_CALLBACK)
	{

		return;
	}

	name_len = strlen((char *)content_name);
	if (NULL != content)
		content_len = strlen((char *)content);

	// if(total_content_cnt>2){
	// 	web_content[2].content_len = content_len;
	// 	//web_content[total_content_cnt].content = malloc(content_len+10);
	// 	web_content[2].content = content;
	// 	//printf("content : %s\n\n", content);
	// }else{
	web_content[total_content_cnt].content_name = malloc(name_len + 1);
	strcpy((char *)web_content[total_content_cnt].content_name, (const char *)content_name);
	web_content[total_content_cnt].content_len = content_len;
	// web_content[total_content_cnt].content = malloc(content_len+10);
	web_content[total_content_cnt].content = content;
	// printf("content : %s\n\n", content);
	total_content_cnt++;
	// }
}

uint8_t display_reg_webContent_list(void)
{
	uint16_t i;
	uint8_t ret;

	if (total_content_cnt == 0)
	{
		printf(">> Web content file not found\r\n");
		ret = 0;
	}
	else
	{
		printf("\r\n=== List of Web content in code flash ===\r\n");
		for (i = 0; i < total_content_cnt; i++)
		{
			printf(" [%d] ", i + 1);
			printf("%s, ", web_content[i].content_name);
			printf("%ld byte, ", web_content[i].content_len);

			if (web_content[i].content_len < 30){
				if(web_content[i].content)
					printf("[%s]\r\n", web_content[i].content);
			}
			else
				printf("[ ... ]\r\n");
		}
		printf("=========================================\r\n\r\n");
		ret = 1;
	}

	return ret;
}

uint8_t find_userReg_webContent(uint8_t *content_name, uint16_t *content_num, uint32_t *file_len)
{
	uint16_t i;
	uint8_t ret = 0; // '0' means 'File Not Found'

	for (i = 0; i < total_content_cnt; i++)
	{
		if (!strcmp((char *)content_name, (char *)web_content[i].content_name))
		{
			*file_len = web_content[i].content_len;
			*content_num = i;
			ret = 1; // If the requested content found, ret set to '1' (Found)
			break;
		}
	}
	return ret;
}

uint16_t read_userReg_webContent(uint16_t content_num, uint8_t *buf, uint32_t offset, uint16_t size)
{
	uint16_t ret = 0;
	uint8_t *ptr;

	if (content_num > total_content_cnt)
		return 0;

	ptr = web_content[content_num].content;
	if (offset)
		ptr += offset;

	strncpy((char *)buf, (char *)ptr, size);
	*(buf + size) = 0; // Insert '/0' for indicates the 'End of String' (null terminated)

	ret = strlen((void *)buf);
	return ret;
}
