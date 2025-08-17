#include "led.h"
#include "common_type.h"
#include "utils.h"

// static led_t led_state;

result_t init_GPIO_led(led_t* led_state)
{
    LOG_LED_INFO("Init config for LED");

    *led_state = LED_NORMAL;
    // TODO: set GPIO pin for led

    return SUCCESS;
}

result_t set_led_state(led_t new_state, led_t* led_state)
{
    *led_state = new_state;
    // LOG_SENSOR_INFO("LED is %s", led_state_to_str[*led_state]);

    return SUCCESS;
}