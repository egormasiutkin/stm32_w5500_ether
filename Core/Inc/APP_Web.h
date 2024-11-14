#include "w5500_init.h"

#include "string.h"
#include "stdlib.h"
#include "stdio.h"
#include <stdarg.h>
#include <stdbool.h>
#include <ctype.h>
#include <httpParser.h>
#include <time.h>
//#include "socket.h"
//#include "dhcp.h"
//#include "dns.h"
#include "httpServer.h"
#include "webpage.h"

#include "loopback.h"

extern wiz_NetInfo gWIZNETINFO;

// Socket 8 Port number definition for Examples //

#define SOCK_TCPS		 0
#define SOCK_UDPS        1
#define PORT_TCPS        5000
#define PORT_UDPS        3000

#define MAX_HTTPSOCK     6

#define DEFAULT_NTP_SYNC_TIMEOUT (3600 * 1000)

void Init_WebAPP (void) ;
void Task_WebAPP (void) ;

/**
 * Get the time from the sntp server and update the rtc
*/
void App_web_get_time_and_sync();

/**
 * @brief This function is the callback function for the URL "timesyncpage"
 * @param[in] content - Pointer to the web content structure
 * @param[in] arg - Pointer to the HTTP request structure
 * @return None
 */
void time_sync_page_callback(void *content,st_http_request *arg);


/**
 * @brief This function is the callback function for the URL "timesync" to
 *        receive and parse the HTTP request data and update the time sync
 *        settings.
 * @param[in] content - Pointer to the web content structure
 * @param[in] arg - Pointer to the HTTP request structure
 * @return None
 */
void set_time_sync_callback(void *content,st_http_request *arg);

/**
 * @brief This function is the callback function for the URL "timesyncset"
 * @param[in] content - Pointer to the web content structure
 * @param[in] arg - Pointer to the HTTP request structure
 * @return None
 */
void get_time_sync_callback(void *content,st_http_request *arg);

void set_alarm_callback(void *content,st_http_request *arg);

void get_alarm_callback(void *content,st_http_request *arg);
void set_file_callback(void *content,st_http_request *arg);
void get_file_callback(void *content,st_http_request *arg);
time_t get_epoch_time(void);
uint8_t Get_Minutes(void);
uint8_t Get_Hours(void);

