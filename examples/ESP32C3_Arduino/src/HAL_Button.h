#ifndef __HAL_BUTTON_H__
#define __HAL_BUTTON_H__


#ifdef __cplusplus
extern "C"{
#endif

#include "stdint.h"

typedef enum
{
    NONE,
    NEXT,
    PREV,
    SELECT
} BUTTON_EVENT;


void button_init(void);
uint8_t key_scan(void);

#ifdef __cplusplus
}
#endif

#endif
