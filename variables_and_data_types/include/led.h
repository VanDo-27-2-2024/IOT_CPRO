#ifndef LED_H
#define LED_H

#include "common_type.h"

typedef enum led
{
    LED_NORMAL = 0,
    LED_WATERING = 1,
    LED_ERROR = 2
} led_t;

result_t init_GPIO_led(void);
result_t set_led_state(led_t led_state);

#endif // LED_H