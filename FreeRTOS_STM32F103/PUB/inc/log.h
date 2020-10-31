#ifndef __LOG_H__
#define __LOG_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>

#define PRINTFLOG(format, args...)\
        printf(format, ##args)
#else

#ifdef __cplusplus
}
#endif   
#endif 
