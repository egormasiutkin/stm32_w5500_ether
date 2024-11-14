/**
 * @file	userHandler.c
 * @brief	User Control Example
 * @version 1.0
 * @date	2014/07/15
 * @par Revision
 *			2014/07/15 - 1.0 Release
 * @author
 * \n\n @par Copyright (C) 1998 - 2014 WIZnet. All rights reserved.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "main.h"
#include "httpUtil.h"
#include "userHandler.h"
//#include "adcHandler.h"
#include "wizchip_conf.h"
/* Unavailable Pins  (W5500-EVB component preempted) */
// >> UART Rx/Tx 		: D0 (Rx), D1 (Tx)
// >> W5500 SPI(SPI0)	: D11 (MOSI), D12 (MISO), D13 (SCK)

/* On-board Devices */
// >> Input		: D14 (SW1) / D15 (SW2)
// >> Input		: AIN (Potentiometer / TEMP.Sensor)
// >> Output	: D8 (LED R) / D9 (LED G) / D10 (LED B)

/* NXP LPC11Exx GPIO functions */
// GPIO: Pin state
//Chip_GPIO_GetPinState(LPC_GPIO, dio_ports[pin], dio_pins[pin]);
//Chip_GPIO_SetPinState(LPC_GPIO, dio_ports[pin], dio_pins[pin], true);
//Chip_GPIO_SetPinState(LPC_GPIO, dio_ports[pin], dio_pins[pin], false);

// GPIO: Pin direction
//Chip_GPIO_GetPinDIR((LPC_GPIO, dio_ports[pin], dio_pins[pin]);
//Chip_GPIO_SetPinDIROutput(LPC_GPIO, dio_ports[pin], dio_pins[pin]);
//Chip_GPIO_SetPinDIRInput(LPC_GPIO, dio_ports[pin], dio_pins[pin]);

// Pre-defined Get CGI functions
void make_json_dio(uint8_t * buf, uint16_t * len, uint8_t pin);
void make_json_ain(uint8_t * buf, uint16_t * len, uint8_t pin);
void make_json_netinfo(uint8_t * buf, uint16_t * len);

extern pFunction JumpToApplication;
extern uint32_t JumpAddress;
// Pre-defined Set CGI functions
int8_t set_diodir(uint8_t * uri);
int8_t set_diostate(uint8_t * uri);
uint32_t strtoI(char*s)
{
	uint32_t ret = 0;
	while(*s)
	{
		ret = ret*10 + (*s - '0');
		s++;
	}
	return ret;
}
#include <stdint.h>
#include <string.h>

// Base64 lookup table: maps Base64 characters to their 6-bit values
static const uint8_t base64_table[256] = {
    ['A'] = 0,  ['B'] = 1,  ['C'] = 2,  ['D'] = 3,  ['E'] = 4,  ['F'] = 5,  ['G'] = 6,  ['H'] = 7,
    ['I'] = 8,  ['J'] = 9,  ['K'] = 10, ['L'] = 11, ['M'] = 12, ['N'] = 13, ['O'] = 14, ['P'] = 15,
    ['Q'] = 16, ['R'] = 17, ['S'] = 18, ['T'] = 19, ['U'] = 20, ['V'] = 21, ['W'] = 22, ['X'] = 23,
    ['Y'] = 24, ['Z'] = 25, ['a'] = 26, ['b'] = 27, ['c'] = 28, ['d'] = 29, ['e'] = 30, ['f'] = 31,
    ['g'] = 32, ['h'] = 33, ['i'] = 34, ['j'] = 35, ['k'] = 36, ['l'] = 37, ['m'] = 38, ['n'] = 39,
    ['o'] = 40, ['p'] = 41, ['q'] = 42, ['r'] = 43, ['s'] = 44, ['t'] = 45, ['u'] = 46, ['v'] = 47,
    ['w'] = 48, ['x'] = 49, ['y'] = 50, ['z'] = 51, ['0'] = 52, ['1'] = 53, ['2'] = 54, ['3'] = 55,
    ['4'] = 56, ['5'] = 57, ['6'] = 58, ['7'] = 59, ['8'] = 60, ['9'] = 61, ['+'] = 62, ['/'] = 63,
    // '=' (padding) is mapped to 0xFF, we'll handle it explicitly later
    ['='] = 0xFF
};

// Function to decode Base64 string into binary data
int base64_decode(const char *input, uint8_t *output, int *output_len) {
    size_t input_len = strlen(input);
    size_t decoded_len = (input_len / 4) * 3;

    if (input_len % 4 != 0) {
        // Invalid Base64 string length
        return -1;
    }

    // Adjust decoded length based on padding
    if (input[input_len - 1] == '=') decoded_len--;
    if (input[input_len - 2] == '=') decoded_len--;

    *output_len = decoded_len;  // Set the output length

    for (size_t i = 0, j = 0; i < input_len;) {
        // Get the 4 characters to decode
        uint32_t sextet_a = input[i] == '=' ? 0 & i++ : base64_table[(unsigned char)input[i++]];
        uint32_t sextet_b = input[i] == '=' ? 0 & i++ : base64_table[(unsigned char)input[i++]];
        uint32_t sextet_c = input[i] == '=' ? 0 & i++ : base64_table[(unsigned char)input[i++]];
        uint32_t sextet_d = input[i] == '=' ? 0 & i++ : base64_table[(unsigned char)input[i++]];

        // Combine into 24-bit binary
        uint32_t triple = (sextet_a << 18) | (sextet_b << 12) | (sextet_c << 6) | sextet_d;

        // Extract and write the 3 bytes
        if (j < decoded_len) output[j++] = (triple >> 16) & 0xFF;
        if (j < decoded_len) output[j++] = (triple >> 8) & 0xFF;
        if (j < decoded_len) output[j++] = triple & 0xFF;
    }

    return 0;  // Success
}

void extract(char * s, char * PATTERN1, char * PATTERN2, char* ret)
{
	char *start, *end;
	start = strstr( s, PATTERN1 );
	if (start)
	{
		start += strlen( PATTERN1 );
		end = strstr( start, PATTERN2 );
		if (end)
		{
			memcpy( ret, start, end - start );
			ret[end - start] = '\0';
		}
		else ret[0] = 0;
	}
	else ret[0] = 0;
}
uint8_t predefined_get_cgi_processor(uint8_t * uri_name, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = 1 means 'uri_name' matched
	uint8_t cgibuf[14] = {0, };
	int8_t cgi_dio = -1;
	int8_t cgi_ain = -1;

	uint8_t i;

	if(strcmp((const char *)uri_name, "todo.cgi") == 0)
	{
		// to do
		;//make_json_todo(buf, len);
	}
	else if(strcmp((const char *)uri_name, "get_netinfo.cgi") == 0)
	{
		make_json_netinfo(buf, len);
	}
	else
	{
		// get_dio0.cgi ~ get_dio15.cgi
		for(i = 0; i < 53; i++)
		{
			memset(cgibuf, 0x00, 14);
			sprintf((char *)cgibuf, "get_dio%d.cgi", i);
			if(strcmp((const char *)uri_name, (const char *)cgibuf) == 0)
			{
				make_json_dio(buf, len, i);
				cgi_dio = i;
				break;
			}
		}

		if(cgi_dio < 0)
		{
			// get_ain0.cgi ~ get_ain5.cgi (A0 - A5), get_ain6.cgi for on-board potentiometer / Temp.Sensor
			for(i = 0; i < 28; i++)
			{
				memset(cgibuf, 0x00, 14);
				sprintf((char *)cgibuf, "get_ain%d.cgi", i);
				if(strcmp((const char *)uri_name, (const char *)cgibuf) == 0)
				{
					make_json_ain(buf, len, i);
					cgi_ain = i;
					break;
				}
			}
		}

		if((cgi_dio < 0) && (cgi_ain < 0)) ret = 0;
	}

	return ret;
}

uint8_t predefined_set_cgi_processor(uint8_t * uri_name, uint8_t * uri, uint8_t * buf, uint16_t * len)
{
	uint8_t ret = 1;	// ret = '1' means 'uri_name' matched
	uint8_t val = 0;
	uint32_t crc;
	uint32_t crc_calc;
	uint64_t data;
	int index;
	int totalSize = 0;
	int chunksize = 0;
	int br;
	uint8_t payload[512];
	char temp_str[1024];

	// Here we run the firmware.cgi receiving the data chosen in the file by the user on the browser
	if(strcmp((const char *)uri_name, "firmware.cgi") == 0)
	{
		// We start by getting the BODY
		char  * full_string = strstr((char*)uri,(char*)"WebKitFormBoundary");
		// Ignore the "WebKitFormBoundary" part
		full_string = full_string + 36;
		extract((char*)full_string, (char*)"currentChunk_", (char*)"_totalSize_",temp_str);
		index = atoi(temp_str);
		extract((char*)full_string, (char*)"_totalSize_", (char*)"_endChunk",temp_str);
		totalSize = atoi(temp_str);
		chunksize = totalSize - 512*index;
		if(chunksize > 512) chunksize = 512;
		extract(full_string, "crc32\"\r\n\r\n", "\r\n------WebKitFormBoundary",temp_str);
		crc = strtoI(temp_str);
		extract(full_string, "fileChunk\"\r\n\r\n", "\r\n------WebKitFormBoundary",temp_str);
		if(!temp_str[0])
			return 0;
		base64_decode(temp_str, payload, &br);
		//TODO: CALCULATE CRC32 FOR EACH CHUNK before
		if(br != chunksize)
			return 0;
		crc_calc = crc32((uint8_t*)payload,chunksize);
		if(crc != crc_calc)
			return 0;
		uint32_t PageError = 0;
		FLASH_EraseInitTypeDef EraseInitStruct = {0};
		HAL_FLASH_Unlock();
		EraseInitStruct.Banks = FLASH_BANK_2;
		EraseInitStruct.TypeErase   = FLASH_TYPEERASE_MASS;

		if(index == 0){
			HAL_FLASHEx_Erase(&EraseInitStruct, &PageError);
			data = ((uint64_t)totalSize<<32)|0x1234ABCD;
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, META_ADDRESS, data);
		}
		for(int i = 0 ; i < 512 ; i += 8){
			memcpy(&data, payload + i, 8);
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, APPLICATION_ADDRESS + index*512 + i, data);
		}
		if((index+1)*512 >= totalSize)
		{
			data = crc32((uint8_t*)APPLICATION_ADDRESS, totalSize);
			HAL_FLASH_Program(FLASH_TYPEPROGRAM_DOUBLEWORD, META_ADDRESS + 8, data);
			firmware_update = 1;
		}
		HAL_FLASH_Lock();
	}
	else if(strcmp((const char *)uri_name, "todo.cgi") == 0)
	{
		// to do
		;//val = todo(uri);
		//*len = sprintf((char *)buf, "%d", val);
	}
	// Digital I/O; dio_s, dio_d
	else if(strcmp((const char *)uri_name, "set_diodir.cgi") == 0)
	{
		val = set_diodir(uri);
		*len = sprintf((char *)buf, "%d", val);
	}
	else if(strcmp((const char *)uri_name, "set_diostate.cgi") == 0)
	{
		val = set_diostate(uri);
		*len = sprintf((char *)buf, "%d", val);
	}
	else
	{
		ret = 0;
	}

	return ret;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined Get CGI functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void make_json_dio(uint8_t * buf, uint16_t * len, uint8_t pin)
{
	uint8_t pin_state 	= 36;
	uint8_t pin_dir 	= 1;

	*len = sprintf((char *)buf, "DioCallback({\"dio_p\":\"%d\",\
											\"dio_s\":\"%d\",\
											\"dio_d\":\"%d\"\
											});",
											pin,					// Digital io pin number
											pin_state,				// Digital io status
											pin_dir					// Digital io directions
											);
}

void make_json_ain(uint8_t * buf, uint16_t * len, uint8_t pin)
{
	*len = sprintf((char *)buf, "AinCallback({\"ain_p\":\"%d\",\
											\"ain_v\":\"%d\"\
											});",
											pin,					// ADC input pin number
											67		// ADC input value
											);
}

void make_json_netinfo(uint8_t * buf, uint16_t * len)
{
	wiz_NetInfo netinfo;
	ctlnetwork(CN_GET_NETINFO, (void*) &netinfo);

	// DHCP: 1 - Static, 2 - DHCP
	*len = sprintf((char *)buf, "NetinfoCallback({\"mac\":\"%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\",\
											\"ip\":\"%d.%d.%d.%d\",\
											\"gw\":\"%d.%d.%d.%d\",\
											\"sn\":\"%d.%d.%d.%d\",\
											\"dns\":\"%d.%d.%d.%d\",\
											\"dhcp\":\"%d\"\
											});",
											netinfo.mac[0], netinfo.mac[1], netinfo.mac[2], netinfo.mac[3], netinfo.mac[4], netinfo.mac[5],
											netinfo.ip[0], netinfo.ip[1], netinfo.ip[2], netinfo.ip[3],
											netinfo.gw[0], netinfo.gw[1], netinfo.gw[2], netinfo.gw[3],
											netinfo.sn[0], netinfo.sn[1], netinfo.sn[2], netinfo.sn[3],
											netinfo.dns[0], netinfo.dns[1], netinfo.dns[2], netinfo.dns[3],
											netinfo.dhcp
											);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Pre-defined Set CGI functions
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int8_t set_diodir(uint8_t * uri)
{
	uint8_t * param;
	uint8_t pin = 0;
	//, val = 0;

	if((param = get_http_param_value((char *)uri, "pin"))) // GPIO; D0 ~ D15
	{
		pin = (uint8_t)ATOI(param, 10);
		if(pin > 15) return -1;

		if((param = get_http_param_value((char *)uri, "val")))  // Direction; NotUsed/Input/Output
		{
			//val = (uint8_t)ATOI(param, 10);
			//if(val > Output) val = Output;
		}
	}

	//if(val == Input) 		Chip_GPIO_SetPinDIRInput(LPC_GPIO, dio_ports[pin], dio_pins[pin]);	// Input
	//else 					Chip_GPIO_SetPinDIROutput(LPC_GPIO, dio_ports[pin], dio_pins[pin]); // Output

	return pin;
}

int8_t set_diostate(uint8_t * uri)
{
	uint8_t * param;
	uint8_t pin = 0;//, val = 0;

	if((param = get_http_param_value((char *)uri, "pin"))) // GPIO; D0 ~ D15
	{
		pin = (uint8_t)ATOI(param, 10);
		if(pin > 15) return -1;

		if((param = get_http_param_value((char *)uri, "val")))  // State; high(on)/low(off)
		{
			//val = (uint8_t)ATOI(param, 10);
			//if(val > On) val = On;
		}

		//if(val == On) 		Chip_GPIO_SetPinState(LPC_GPIO, dio_ports[pin], dio_pins[pin], true); 	// High
		//else				Chip_GPIO_SetPinState(LPC_GPIO, dio_ports[pin], dio_pins[pin], false);	// Low
	}

	return pin;
}

uint32_t crc32(const uint8_t *data, size_t length) {
    static uint32_t crcTable[256];
    static int tableGenerated = 0;

    if (!tableGenerated) {
        // Generate the CRC table
        uint32_t crc;
        for (int i = 0; i < 256; i++) {
            crc = i;
            for (int j = 8; j > 0; j--) {
                if (crc & 1) {
                    crc = (crc >> 1) ^ 0xEDB88320;
                } else {
                    crc >>= 1;
                }
            }
            crcTable[i] = crc;
        }
        tableGenerated = 1;
    }

    // Calculate the CRC
    uint32_t crc = 0xFFFFFFFF;
    while (length--) {
        crc = (crc >> 8) ^ crcTable[(crc ^ *data++) & 0xFF];
    }

    return crc ^ 0xFFFFFFFF;
}
