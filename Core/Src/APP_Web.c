#include "APP_Web.h"
#include "dhcp.h"
#include "pcb_config.h"
#include "httpServer.h"
#include "sntp.h"
#include "usart.h"
#include <stdint.h>
#include <time.h>
#include "httpServer.h"
#include "time_sync.h"
#include "httpParser.h"
#include "main.h"
#define _MAIN_DEBUG_

#define NTP_SOCKET_NUM 1

#define VER_H 1
#define VER_L 00

uint8_t onSwitch = 0;
uint32_t onDateTime = 0;
uint8_t offSwitch = 0;
uint32_t offDateTime = 0;
uint8_t timezone = 0;

uint8_t socknumlist[] = {2, 3, 4, 5, 6, 7};
// sntp server ip address
uint8_t sntp_server[] = {193, 204, 114, 233};
uint8_t tz = 21; // set the value for UTC 0 timezone

int Recursion_Alarm_ON[7];
int Recursion_Alarm_OFF[7];
float realTimeZone = -4.0;
float timezonesarray[50] =
    {
        -12, -11, -10, -9.5, -9,
        -8, -8, -7, -7, -6,
        -6, -5, -5, -5, -4.5,
        -4, -4, -3.5, -3, -2,
        -1, 0, 0, 1, 1,
        1, 2, 2, 3, 3,
        3.5, 4, 4.5, 5, 5.5,
        5.75, 6, 6.5, 7, 8,
        9, 9.5, 10, 10.5, 11,
        11.5, 12, 12.45, 13, 14};

// int TimeOffSetInHours[50] = {-12,-11-,10,-9.5,};

uint32_t data;
/**
 * configure the time after which
 * device sync the time with ntp server
 */
uint32_t update_ntp_time = DEFAULT_NTP_SYNC_TIMEOUT;

/**
 * Variable which hold the last sync time
 */
uint32_t time_last_ntp_sync = 0;

////////////////////////////////////////////////
// Shared Buffer Definition  				  //
////////////////////////////////////////////////
uint8_t RX_BUF[DATA_BUF_SIZE];
uint8_t TX_BUF[DATA_BUF_SIZE];

///////////////////////////
// Network Configuration //
///////////////////////////

wiz_NetInfo gWIZNETINFO = {0};
bool timesynch_on_was_sent;
bool timesynch_off_was_sent;

bool timesynch_off_was_sent;
bool timesynch_off_recursion_was_sent;
bool timesynch_on_recursion_was_sent;

#if 1
/* DATA_BUF_SIZE define for Loopback example */
#ifndef DATA_BUF_SIZE
#define DATA_BUF_SIZE 2048
#endif

uint8_t buf[DATA_BUF_SIZE];

uint8_t buff[DATA_BUF_SIZE];
uint8_t gDATABUF[1024] = {""};
#endif

uint8_t dhcp_retry = 0;
uint8_t buff[DATA_BUF_SIZE];
uint8_t callback_data[100];

void App_web_show_sys_time();

time_t get_epoch_time(void)
{
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;
    HAL_RTC_GetTime(&hrtc, &time, FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, FORMAT_BIN);
    struct tm datetime = {0};
    datetime.tm_sec = time.Seconds;
    datetime.tm_min = time.Minutes;
    datetime.tm_hour = time.Hours;
    datetime.tm_mday = date.Date;
    datetime.tm_mon = date.Month - 1;
    datetime.tm_year = date.Year + 100;
    datetime.tm_isdst = 0;
    return mktime(&datetime);
}
uint8_t Get_Hours(void)
{
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;
    HAL_RTC_GetTime(&hrtc, &time, FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, FORMAT_BIN);
    return time.Hours;
}
uint8_t Get_Minutes(void)
{
    RTC_DateTypeDef date;
    RTC_TimeTypeDef time;
    HAL_RTC_GetTime(&hrtc, &time, FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &date, FORMAT_BIN);
    return time.Minutes;
}

void print_network_information(void)
{
    memset(&gWIZNETINFO, 0, sizeof(gWIZNETINFO));

    wizchip_getnetinfo(&gWIZNETINFO);
    printf("MAC Address : %02x:%02x:%02x:%02x:%02x:%02x\n\r", gWIZNETINFO.mac[0], gWIZNETINFO.mac[1], gWIZNETINFO.mac[2], gWIZNETINFO.mac[3], gWIZNETINFO.mac[4], gWIZNETINFO.mac[5]);
    printf("IP  Address : %d.%d.%d.%d\n\r", gWIZNETINFO.ip[0], gWIZNETINFO.ip[1], gWIZNETINFO.ip[2], gWIZNETINFO.ip[3]);
    printf("Subnet Mask : %d.%d.%d.%d\n\r", gWIZNETINFO.sn[0], gWIZNETINFO.sn[1], gWIZNETINFO.sn[2], gWIZNETINFO.sn[3]);
    printf("Gateway     : %d.%d.%d.%d\n\r", gWIZNETINFO.gw[0], gWIZNETINFO.gw[1], gWIZNETINFO.gw[2], gWIZNETINFO.gw[3]);
    printf("DNS Server  : %d.%d.%d.%d\n\r", gWIZNETINFO.dns[0], gWIZNETINFO.dns[1], gWIZNETINFO.dns[2], gWIZNETINFO.dns[3]);
}

int process_dhcp(void)
{
    int8_t ret = 0;
    while (1)
    {
        ret = DHCP_run();
        if (ret == DHCP_IP_LEASED)
        {
#ifdef _MAIN_DEBUG_
            printf(" - DHCP Success\r\n");
#endif
            printf("=============================\r\n");
            print_network_information();
            printf("=============================\r\n");
            break;
        }
        else if (ret == DHCP_FAILED)
        {
            dhcp_retry++;
#ifdef _MAIN_DEBUG_
            if (dhcp_retry <= 3)
                printf(" - DHCP Timeout occurred and retry [%d]\r\n", dhcp_retry);
#endif
        }

        if (dhcp_retry > 3)
        {
#ifdef _MAIN_DEBUG_
            printf(" - DHCP Failed\r\n\r\n");
#endif
            DHCP_stop();
            break;
        }
    }
    return ret;
}

void Init_WebAPP(void)
{
    W5500_Init();
    setSHAR(gWIZNETINFO.mac);
    wizchip_setnetinfo(&gWIZNETINFO);

    if (gWIZNETINFO.dhcp == NETINFO_STATIC)
    {
        wizchip_getnetinfo(&gWIZNETINFO);
    }
    else if (gWIZNETINFO.dhcp == NETINFO_DHCP)
    {
        DHCP_init(0, gDATABUF);
        while (process_dhcp() != DHCP_IP_LEASED)
        {
            HAL_Delay(500);
            process_dhcp();
        }

        DHCP_stop();

        wizchip_getnetinfo(&gWIZNETINFO);
    }

    // now ip has been alloted, now  we can get request to sntp server
    App_web_get_time_and_sync();

    // debug function just to show rtc is working
    App_web_show_sys_time();

#ifdef _MAIN_DEBUG_
    uint8_t tmpstr[6] = {
        0,
    };

    ctlwizchip(CW_GET_ID, (void *)tmpstr);

    printf(">> W5500 based Web Server \r\n");
    printf("=======================================\r\n");

    Display_Net_Conf(); // Print out the network information to serial terminal
#endif
    httpServer_init(TX_BUF, RX_BUF, MAX_HTTPSOCK, socknumlist); // Tx/Rx buffers (1kB) / The number of W5500 chip H/W sockets in use
    reg_httpServer_cbfunc(NVIC_SystemReset, NULL);              // Callback: NXP MCU Reset

    uint16_t content_num = 0;
    uint32_t file_len = 0;
    if (find_userReg_webContent((uint8_t *)"new_webpage.css", &content_num, &file_len))
    {
        web_content[content_num].content = (uint8_t *)webpage_css;
    }
    else
    {
        reg_httpServer_webContent((uint8_t *)"new_webpage.css", (uint8_t*)webpage_css);
    }
    reg_httpServer_webContent((uint8_t*)"timesyncpage", NULL);
    reg_httpServer_webContent((uint8_t*)"timesync", NULL);
    reg_httpServer_webContent((uint8_t*)"gettimesync", NULL);
    reg_httpServer_webContent((uint8_t*)"set_alarm", NULL);
    reg_httpServer_webContent((uint8_t*)"get_alarm", (uint8_t*)NULL);
    reg_httpServer_webContent((uint8_t*)"set_file", (uint8_t*)NULL);
    reg_httpServer_webContent((uint8_t*)"file_get", (uint8_t*)NULL);
    reg_httpServer_webContent((uint8_t *)"index.html", (uint8_t *)index_page);
    HAL_Delay(1000);

#ifdef _MAIN_DEBUG_
    display_reg_webContent_list();
#endif
#if 0
		{
				/* Web content registration (web content in webpage.h, Example web pages) */
				//reg_httpServer_webContent((uint8_t *)"index.html", (uint8_t *)index_page);
				//reg_httpServer_webContent((uint8_t *)"index4.html", (uint8_t *)index_x);
				//reg_httpServer_webContent((uint8_t *)"index3.html", (uint8_t *)index_page3);
				reg_httpServer_webContent((uint8_t *)"new_webpage.css", (uint8_t *)webpage_css);

#ifdef _MAIN_DEBUG_
				display_reg_webContent_list();
#endif
		}
#endif
}

void Task_WebAPP(void)
{

    for (uint16_t i = 0; i < MAX_HTTPSOCK; i++)
        httpServer_run(i);

    // loopback_tcps(SOCK_TCPS, RX_BUF, 5000);
    // loopback_udps(SOCK_UDPS, RX_BUF, 7000);
    if ((HAL_GetTick() - time_last_ntp_sync) >= DEFAULT_NTP_SYNC_TIMEOUT)
    {
        time_last_ntp_sync = HAL_GetTick();
        App_web_get_time_and_sync();
    }
    App_web_show_sys_time();
}

void App_web_get_time_and_sync()
{
    datetime tm = {0};
    RTC_TimeTypeDef sTime = {0};
    RTC_DateTypeDef sDate = {0};

    SNTP_init(NTP_SOCKET_NUM, sntp_server, tz, gDATABUF);

    uint32_t ticks = HAL_GetTick();
    while ((SNTP_run(&tm) != 1) &&
           (HAL_GetTick() - ticks) < (10 * 1000))
        ; // wait for only 10 sec else leave
#if 0
    char send_time[500]= {0};
    sprintf(send_time,"Internet time: %d-%d-%d %d:%d:%d\r\n", tm.yy, tm.mo, tm.dd, tm.hh, tm.mm, tm.ss);
    Send_String(send_time,strlen(send_time) + 1);
#endif
    printf("GMT time: %d-%d-%d %d:%d:%d\r\n", tm.yy, tm.mo, tm.dd, tm.hh, tm.mm, tm.ss);
    sTime.Hours = tm.hh;
    sTime.Minutes = tm.mm;
    sTime.Seconds = tm.ss;
    sTime.Seconds = tm.ss;
    if (HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    sDate.Month = tm.mo;
    sDate.Date = tm.dd;
    sDate.Year = tm.yy - 2000;
    if (HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN) != HAL_OK)
    {
        Error_Handler();
    }

    time_last_ntp_sync = HAL_GetTick();

    uint32_t now_epoch = get_epoch_time();
    // show epoch time

    printf("Epoch time is %d\r\n", (int)now_epoch);
}

void App_web_show_sys_time()
{
    static uint32_t now_time = 0;

    if (HAL_GetTick() - now_time > (60 * 1000))
    {
        now_time = HAL_GetTick();
        RTC_DateTypeDef getDate = {0};
        RTC_TimeTypeDef getTime = {0};
        if (HAL_RTC_GetTime(&hrtc, &getTime, RTC_FORMAT_BIN) != HAL_OK)
        {
            Error_Handler();
        }
        if (HAL_RTC_GetDate(&hrtc, &getDate, RTC_FORMAT_BIN) != HAL_OK)
        {
            Error_Handler();
        }
        uint32_t now_epoch = get_epoch_time();
        printf("Current GMT time :%02d:%02d:%02d\r\n", getTime.Hours, getTime.Minutes, getTime.Seconds);
        printf("Current GMT Date :%02d/%02d/%02d\r\n", getDate.Date, getDate.Month, getDate.Year);
        // show epoch time
        printf("Epoch time is %d\r\n", (int)now_epoch);
    }
}

void time_sync_page_callback(void *content, st_http_request *arg)
{
    static uint32_t num = 0;
    num++;
    httpServer_webContent *content_info = (httpServer_webContent *)content;

    // print the called uri
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    printf("Param value are %s\r\n", arg->URI);

    // set the content type
    arg->TYPE = PTYPE_HTML;
    // attach the content
    content_info->content = (uint8_t *)timesync_str;
    // attach the content lengthe
    content_info->content_len = sizeof(timesync_str);
}

void set_time_sync_callback(void *content, st_http_request *arg)
{
    timesynch_on_was_sent = 0;
    timesynch_off_was_sent = 0;

    httpServer_webContent *content_info = (httpServer_webContent *)content;
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    printf("Param value are %s\r\n", arg->URI);

    char *uri = (char *)arg->URI;

    char *get_value = strstr(uri, "?");
    get_value = get_value + 1;
    printf("Get value is %s\r\n", get_value);

    char *saveptr;
    char *token = strtok_r(get_value, "&", &saveptr);

    do
    {
        if (token == NULL)
        {
            break;
        }
        char *saveptr_2;
        char *key = strtok_r(token, "=", &saveptr_2);
        char *value = strtok_r(NULL, "=", &saveptr_2);
        if (key != NULL && value != NULL)
        {
            if (strcmp(key, "onSwitch") == 0)
            {
                printf("onSwitch Value is %d\r\n", atoi(value));

                onSwitch = atoi(value);
            }

            else if (strcmp(key, "onDateTime") == 0)
            {
                printf("onDateTime Value is %d\r\n", atoi(value));

                onDateTime = atoi(value);
            }

            else if (strcmp(key, "offSwitch") == 0)
            {
                printf("offSwitch Value is %d\r\n", atoi(value));

                offSwitch = atoi(value);
            }

            else if (strcmp(key, "offDateTime") == 0)
            {
                printf("offDateTime Value is %d\r\n", atoi(value));

                offDateTime = atoi(value);
            }

            else if (strcmp(key, "timezone") == 0)
            {
                printf("timezone Value is %d\r\n", atoi(value));

                timezone = atoi(value);
            }

            else
            {
                break;
            }
        }
        else
        {
            break;
        }
        token = strtok_r(NULL, "&", &saveptr);
    } while (token != NULL);

    // set the content type
    arg->TYPE = PTYPE_TEXT;
    // attach the content
    content_info->content = NULL;
    // attach the content lengthe
    content_info->content_len = 0;

    pcb_config.pcb_config_onSwitch = onSwitch;
    pcb_config.pcb_config_onDateTime = onDateTime;
    pcb_config.pcb_config_offSwitch = offSwitch;
    pcb_config.pcb_config_offDateTime = offDateTime;
    pcb_config.pcb_config_timezone = timezone;

    //    // Calculate number of seconds since midnight 1 Jan 1970 local time
    //    	time_t localtime = get_epoch_time() + (-4 * 60 * 60);
    //    	// Convert to number of days since 1 Jan 1970
    //    	int days_since_epoch = localtime / 86400;
    //    	// 1 Jan 1970 was a Thursday, so add 4 so Sunday is day 0, and mod 7
    //    	int day_of_week = (days_since_epoch + 4) % 7;
    //    	 printf("Test Callback: %d\r\n", day_of_week);
    realTimeZone = timezonesarray[timezone];

    // dayofweek(get_epoch_time(),));

    WriteToEeprom();
}

void get_time_sync_callback(void *content, st_http_request *arg)
{
    httpServer_webContent *content_info = (httpServer_webContent *)content;
    memset(callback_data, 0, sizeof(callback_data));
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    printf("Param value are %s\r\n", arg->URI);
    snprintf((char*)callback_data, sizeof(callback_data), "%d,%d,%d,%d,%d \r\n", onSwitch, (int)onDateTime, offSwitch, (int)offDateTime, timezone);
    printf("callback data %s\r\n", callback_data);
    // set the content type
    arg->TYPE = PTYPE_TEXT;

    // attach the content
    content_info->content = callback_data;
    // attach the content lengthe
    content_info->content_len = strlen((char*)callback_data);
}

uint8_t time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm;
uint8_t time_alarm_on_sun, time_alarm_on_mon, time_alarm_on_tue, time_alarm_on_wed, time_alarm_on_thu, time_alarm_on_fri, time_alarm_on_sat;
uint8_t time_alarm_off_sun, time_alarm_off_mon, time_alarm_off_tue, time_alarm_off_wed, time_alarm_off_thu, time_alarm_off_fri, time_alarm_off_sat;

void set_alarm_callback(void *content, st_http_request *arg)
{
    httpServer_webContent *content_info = (httpServer_webContent *)content;
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    printf("Param value are %s\r\n", arg->URI);

    char *uri = (char *)arg->URI;

    char *get_value = strstr(uri, "?");
    get_value = get_value + 7;
    // printf("Get value is %s\r\n",get_value);

    // parse and save the values
    char *save_ptr;
    char delim[] = "z";
    char *token = strtok_r(get_value, delim, &save_ptr);
    uint8_t index = 0;

    while (NULL != token)
    {
        if (0 == index)
            time_alarm_on_hh = atoi(token);
        if (1 == index)
            time_alarm_on_mm = atoi(token);
        if (2 == index)
            time_alarm_off_hh = atoi(token);
        if (3 == index)
            time_alarm_off_mm = atoi(token);
        if (4 == index)
            time_alarm_on_sun = atoi(token);
        if (5 == index)
            time_alarm_on_mon = atoi(token);
        if (6 == index)
            time_alarm_on_tue = atoi(token);
        if (7 == index)
            time_alarm_on_wed = atoi(token);
        if (8 == index)
            time_alarm_on_thu = atoi(token);
        if (9 == index)
            time_alarm_on_fri = atoi(token);
        if (10 == index)
            time_alarm_on_sat = atoi(token);
        if (11 == index)
            time_alarm_off_sun = atoi(token);
        if (12 == index)
            time_alarm_off_mon = atoi(token);
        if (13 == index)
            time_alarm_off_tue = atoi(token);
        if (14 == index)
            time_alarm_off_wed = atoi(token);
        if (15 == index)
            time_alarm_off_thu = atoi(token);
        if (16 == index)
            time_alarm_off_fri = atoi(token);
        if (17 == index)
            time_alarm_off_sat = atoi(token);
        token = strtok_r((char*)NULL, delim, &save_ptr);
        index++;
    }
    printf("========================Alarm Set=============================\n");
    printf("time_alarm_on: %02d:%02d, time_alarm_off: %02d:%02d\n", time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm);
    printf("time alarm on sun %d, mon %d, tue %d, wed %d, thu %d, fri %d, sat %d\n", time_alarm_on_sun, time_alarm_on_mon, time_alarm_on_tue, time_alarm_on_wed, time_alarm_on_thu, time_alarm_on_fri, time_alarm_on_sat);
    printf("time alarm off sun %d, mon %d, tue %d, wed %d, thu %d, fri %d, sat %d\n", time_alarm_off_sun, time_alarm_off_mon, time_alarm_off_tue, time_alarm_off_wed, time_alarm_off_thu, time_alarm_off_fri, time_alarm_off_sat);
    printf("===============================================================\n");

    Recursion_Alarm_ON[0] = time_alarm_on_sun,
    Recursion_Alarm_ON[1] = time_alarm_on_mon,
    Recursion_Alarm_ON[2] = time_alarm_on_tue,
    Recursion_Alarm_ON[3] = time_alarm_on_wed,
    Recursion_Alarm_ON[4] = time_alarm_on_thu,
    Recursion_Alarm_ON[5] = time_alarm_on_fri,
    Recursion_Alarm_ON[6] = time_alarm_on_sat;

    Recursion_Alarm_OFF[0] = time_alarm_off_sun,
    Recursion_Alarm_OFF[1] = time_alarm_off_mon,
    Recursion_Alarm_OFF[2] = time_alarm_off_tue,
    Recursion_Alarm_OFF[3] = time_alarm_off_wed,
    Recursion_Alarm_OFF[4] = time_alarm_off_thu,
    Recursion_Alarm_OFF[5] = time_alarm_off_fri,
    Recursion_Alarm_OFF[6] = time_alarm_off_sat;

    // set the content type
    arg->TYPE = PTYPE_TEXT;
    // attach the content
    content_info->content = NULL;
    // attach the content lengthe
    content_info->content_len = 0;

    pcb_config.pcb_config_time_alarm_on_hh = time_alarm_on_hh;
    pcb_config.pcb_config_time_alarm_on_mm = time_alarm_on_mm;
    pcb_config.pcb_config_time_alarm_off_hh = time_alarm_off_hh;
    pcb_config.pcb_config_time_alarm_off_mm = time_alarm_off_mm;

    memcpy(pcb_config.pcb_config_Recursion_Alarm_ON, Recursion_Alarm_ON, sizeof(pcb_config.pcb_config_Recursion_Alarm_ON));
    memcpy(pcb_config.pcb_config_Recursion_Alarm_OFF, Recursion_Alarm_OFF, sizeof(pcb_config.pcb_config_Recursion_Alarm_OFF));

    WriteToEeprom();
}
void set_file_callback(void *content, st_http_request *arg)
{
    httpServer_webContent *content_info = (httpServer_webContent *)content;
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    printf("Param value are %s\r\n", arg->URI);

    char *uri = (char *)arg->URI;

    char *get_value = strstr(uri, "?");
    get_value = get_value + 7;
    // printf("Get value is %s\r\n",get_value);

    // parse and save the values
    char *save_ptr;
    char delim[] = "z";
    strtok_r(get_value, delim, &save_ptr);

    // set the content type
    arg->TYPE = PTYPE_TEXT;
    // attach the content
    content_info->content = NULL;
    // attach the content lengthe
    content_info->content_len = 0;
}
void get_file_callback(void *content, st_http_request *arg)
{
    httpServer_webContent *content_info = (httpServer_webContent *)content;
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    //    printf("Param value are %s\r\n",arg->URI);
    //
    //    snprintf(callback_data, sizeof(callback_data), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \r\n",
    //            time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm,
    //            time_alarm_on_sun, time_alarm_on_mon, time_alarm_on_tue, time_alarm_on_wed, time_alarm_on_thu, time_alarm_on_fri, time_alarm_on_sat,
    //            time_alarm_off_sun, time_alarm_off_mon, time_alarm_off_tue, time_alarm_off_wed, time_alarm_off_thu, time_alarm_off_fri, time_alarm_off_sat);
    //    printf("callback data %s\r\n",callback_data);
    // set the content type
    arg->TYPE = PTYPE_TEXT;
    // attach the content
    content_info->content = callback_data;
    // attach the content lengthe
    content_info->content_len = strlen((char*)callback_data);
}
void get_alarm_callback(void *content, st_http_request *arg)
{
    httpServer_webContent *content_info = (httpServer_webContent *)content;
    printf("Test Callback: %s\r\n", content_info->content_name);
    // get the full uri
    printf("Param value are %s\r\n", arg->URI);

    snprintf((char*)callback_data, sizeof(callback_data), "%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d,%d \r\n",
             time_alarm_on_hh, time_alarm_on_mm, time_alarm_off_hh, time_alarm_off_mm,
             time_alarm_on_sun, time_alarm_on_mon, time_alarm_on_tue, time_alarm_on_wed, time_alarm_on_thu, time_alarm_on_fri, time_alarm_on_sat,
             time_alarm_off_sun, time_alarm_off_mon, time_alarm_off_tue, time_alarm_off_wed, time_alarm_off_thu, time_alarm_off_fri, time_alarm_off_sat);
    printf("callback data %s\r\n", callback_data);
    // set the content type
    arg->TYPE = PTYPE_TEXT;
    // attach the content
    content_info->content = callback_data;
    // attach the content lengthe
    content_info->content_len = strlen((char*)callback_data);
}
