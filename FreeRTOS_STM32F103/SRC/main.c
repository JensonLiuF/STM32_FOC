#include "config.h"
#include "main.h"

char* temp = NULL;
uint8_t data[THRID_PLATFORM_ID_LEN];
NET_CFG_ST net_cfg={0};
//char *p_buf = "http://168.63.43.199:18765/charge/v1/try_to_charge";
char *p_buf ="http://47.104.90.117:8089/NovaX?500";
//char *p_buf = "http://abb.down.chargedot.com/NovaX?500";
char *ptr0, *ptr1;
int i = 0;
HTTP_UPGRADE *p_http_upgrade;
int main(void)
{
//	data_init(data);
//	set_thrid_platform_id((char*)&data[16], (data[4]+(data[5]<<8)), 0);
//	temp = get_thrid_platform_id();

//	i = http_upgrade_parse(p_buf, p_http_upgrade);
	SysInit();
	while(1)
	{
		dev_beep_on();
		dev_led_on();
		SysTickDelayMs(1000);
		dev_beep_off();
		dev_led_off();
		SysTickDelayMs(1000);
	}

}


int http_upgrade_parse(char *p_buf, HTTP_UPGRADE *p_http_upgrade)
{
    int tempi;
    char *ptr0, *ptr1;
    ptr0 = p_buf;
    ptr1 = strstr(ptr0, "http://");
    if(ptr1 == NULL)
    {
        return -1; 
    }
    ptr0 += 7;
    ptr1 = strchr(ptr0, ':');
    /* "http://abb.down.chargedot.com/NovaX?500" */
    if(ptr1 == NULL)
    {
        ptr1 = strchr(ptr0, '/');
        if(ptr1 == NULL)
        {
            return -1;
        }
        else
        {
            if(ptr1 - ptr0 < sizeof(p_http_upgrade->ip))
            {
                memset(p_http_upgrade->ip, 0, sizeof(p_http_upgrade->ip));
                strncpy(p_http_upgrade->ip, ptr0, ptr1 - ptr0);
            }
            else
            {
                return -1;
            }
        }
        
        p_http_upgrade->port = 80;
    }
    /* "http://47.104.90.117:8089/NovaX?500" */
    else
    {
        if(ptr1 - ptr0 < sizeof(p_http_upgrade->ip))
        {
            memset(p_http_upgrade->ip, 0, sizeof(p_http_upgrade->ip));
            strncpy(p_http_upgrade->ip, ptr0, ptr1 - ptr0);
        }
        else
        {
            return -1;
        }
        
        ptr0 = ptr1 + 1;
        ptr1 = strchr(ptr0, '/');
        tempi = atoi(ptr0);
        if(tempi < 0 || tempi > 0xffff)
        {
            return -1;
        }
        else
        {
            p_http_upgrade->port = tempi;
        }
    }

    ptr0 = ptr1 + 1;
    ptr1 = strchr(ptr0, '?');
    if(ptr1 == NULL)
    {
        return -1;
    }
    else
    {
        if(ptr1 - ptr0 < sizeof(p_http_upgrade->dir))
        {
            memset(p_http_upgrade->dir, 0, sizeof(p_http_upgrade->dir));
            strncpy(p_http_upgrade->dir, ptr0, ptr1 - ptr0);
        }
        else
        {
            return -1;
        }
    }

    ptr0 = ptr1 + 1;
    tempi = atoi(ptr0);
    if(tempi < 0 || tempi > MAX_OCPP_FW_PCS)
    {
        return -1;
    }
    else
    {
        p_http_upgrade->total_package = tempi;
    }

    return 0;
}


void data_init(uint8_t *data)
{
	int i;
	for(i = 0; i < THRID_PLATFORM_ID_LEN; i++)
	{
		data[i] = 0;
	}
	data[4] = 30;
	data[5] = 1;
	data[16] = 65;
	data[17] = 66;
	data[18] = 66;
	data[19] = 95;
	data[20] = 84;
	data[21] = 69;
	data[22] = 83;
	data[23] = 84;
	data[24] = 45;
	data[25] = 48;
	data[26] = 48;
	data[27] = 48;
	data[28] = 45;
	data[29] = 84;
	data[30] = 53;
	data[31] = 51;
	data[32] = 72;
	data[33] = 85;
	data[34] = 49;
	data[35] = 52;
	data[36] = 57;
	data[37] = 49;
	data[38] = 56;
	data[39] = 48;
	data[40] = 49;
	data[41] = 53;

}

char *get_thrid_platform_id(void)
{
	return net_cfg.NetCfgFile.ThridPlatformId;
}

void set_thrid_platform_id(const char *tempbuf,uint8_t len,uint8_t flag)
{
	if(tempbuf != NULL)
	{
		if(len >= THRID_PLATFORM_ID_LEN)
		{
			len = THRID_PLATFORM_ID_LEN-1;
		}
		memset(net_cfg.NetCfgFile.ThridPlatformId,0x00,THRID_PLATFORM_ID_LEN);
		memcpy(net_cfg.NetCfgFile.ThridPlatformId,tempbuf,len);
	}

}
