#ifndef __MAIN_H__
#define __MAIN_H__

#define THRID_PLATFORM_ID_LEN		80
#define WEBSITE_LEN					48
#define AUTH_PASSWORD_LEN			32
#define HTTPSERVER_LEN				80
#define MAX_OCPP_FW_PCS	1200

typedef enum
{
    CONN_NONE=0,
    CONN_INIT=1,
    CONN_PRECONNECTED,
    CONN_CONNECTED,    
    CONN_WEBSOCK,
    CONN_ACCEPTED,
    CONN_REJECTED,
    CONN_PENDING,
    /* for http upgrade */
    CONN_HTTPFWINFO,
	CONN_HTTPUPGRADE,
} CONN_STATE;

typedef enum
{
	PROTOCOL_OCPP=1,
	PROTOCOL_CHARGEDOT,
}NET_PROTOCOL;

typedef struct
{
	uint8_t Socket_A_Enable;
	NET_PROTOCOL Socket_A_Protocol;
	uint8_t Encrypted_A_Enable;
	char Server_A_IP_address[WEBSITE_LEN];
	uint16_t Server_A_Port;
	
	uint8_t Socket_B_Enable;
	NET_PROTOCOL Socket_B_Protocol;
	uint8_t Encrypted_B_Enable;
	char Server_B_IP_address[WEBSITE_LEN];
	uint16_t Server_B_Port;

	uint8_t TlsSupport;
	uint16_t NetOverTime;			//unit s
	uint16_t HeartBeatInterval;		//unit s
	uint16_t ChargeMeterInterval;	//unit s
	uint8_t InitialAuthPassword[AUTH_PASSWORD_LEN];
	char HttpAuthPassword[AUTH_PASSWORD_LEN];
	char HttpServerAddr[HTTPSERVER_LEN];
	char ThridPlatformId[THRID_PLATFORM_ID_LEN];
} NET_BASIC_CFG;

typedef enum 
{
	TCP_CONN_0 = 0,
	TCP_CONN_DATA = TCP_CONN_0,
	TCP_CONN_1,
	TCP_CONN_HTTPOTA = TCP_CONN_1,
	TCP_CONN_MAX,
} TCP_CONN_ID;
typedef struct
{
	CONN_STATE net_state[TCP_CONN_MAX];
	NET_BASIC_CFG NetCfgFile;
    uint16_t boot_notify_interval;
	uint16_t CommunicationOverTime;
	volatile int send_state;
} NET_CFG_ST;
typedef enum
{
	UPGRADE_PACKAGE_IDLE=1,
	UPGRADE_PACKAGE_TANSED,
	UPGRADE_PACKAGE_RECVED,
	UPGRADE_PACKAGE_FINISH,
}UPGRADE_PACKAGE_STATE;
typedef struct
{
	UPGRADE_PACKAGE_STATE upgrade_package_state;
	uint16_t  total_package;
	uint16_t  package_index;
	uint8_t Status;
	uint8_t connect_count;
	uint8_t get_count;
	//char address[64];
	char ip[48];
	uint16_t port;
	char dir[64];
	uint32_t  value_crc;
	uint32_t  value_len;
	uint8_t   result;
	uint8_t   err_code;
}HTTP_UPGRADE;
int http_upgrade_parse(char *p_buf, HTTP_UPGRADE *p_http_upgrade);
char *get_thrid_platform_id(void);
void set_thrid_platform_id(const char *tempbuf,uint8_t len,uint8_t flag);
void data_init(uint8_t *data);
#endif
