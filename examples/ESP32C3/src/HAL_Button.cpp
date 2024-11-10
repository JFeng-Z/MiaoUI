#include "HAL_Button.h"
#include "Arduino.h"

uint8_t key_scan(void)
{
    uint8_t key;
    if(Serial.available())
    Serial.readBytes(&key, 1);
    else key = 0;

    switch (key)
    {
    case 1:
        return 1;
        break;
    case 2:
        return 2;
        break;
    case 3:
        return 3;
        break;
    default:
        break;
    }
    return 0;
}