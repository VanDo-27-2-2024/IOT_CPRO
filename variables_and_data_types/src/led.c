#include "led.h"

static led_t led_state;

result_t init_GPIO_led(void)
{
    LOG_LED_INFO("Init config for LEDLED");

    led_state = LED_NORMAL;
    // TODO: set GPIO pin for led

    return SUCCESS;
}

result_t set_led_state(led_t led_state)
{
    if (led_state == LED_NORMAL)
    {
        LOG_LED_INFO("LED is GREEN");
        led_state = LED_NORMAL;

        // TODO: Set GPIO to change the led
    }
    else if (led_state == LED_WATERING)
    {
        LOG_LED_INFO("LED is YELLOW");
        led_state = LED_WATERING;

        // TODO: Set GPIO to change the led
    }
    else if (led_state == LED_ERROR)
    {
        LOG_LED_INFO("LED is RED");
        led_state = LED_ERROR;

        // TODO: Set GPIO to change the led
    }

    return SUCCESS;
}