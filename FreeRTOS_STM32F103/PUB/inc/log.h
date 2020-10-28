#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define LOGD_LVL 3
#define LOGW_LVL 2
#define LOGE_LVL 1

#define LOG_FILTER_LVL (3)


#if (LOG_FILTER_LVL >= LOGE_LVL)
#define LOGE(format, args...)\
        printf(format, ##args)
#else
#define LOGE(format, args...)
#endif

#if (LOG_FILTER_LVL >= LOGW_LVL)
#define LOGW(format, args...)\
        printf(format, ##args)
#else
#define LOGW(format, args...)
#endif

#if (LOG_FILTER_LVL >= LOGD_LVL)
#define LOGD(format, args...)\
        printf(format, ##args)
#else
#define LOGD(format, args...)
#endif


#ifdef __cplusplus
}
#endif   
#endif 
