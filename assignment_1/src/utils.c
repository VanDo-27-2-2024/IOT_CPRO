#include "utils.h"
#include "buttons.h"
#include "led.h"
#include "sensors.h"
#include "config.h"
#include "actuators.h"
#include "time.h"
#include <time.h>
#include <stdlib.h>

const char* mode_to_str[] =
{
    [MODE_AUTO]   = "AUTO",
    [MODE_MANUAL] = "MANUAL"
};

const char* pump_state_to_str[] =
{
    [PUMP_OFF] = "OFF",
    [PUMP_ON]  = "ON"
};

const char* led_state_to_str[] =
{
    [LED_NORMAL] = "LED_NORMAL",
    [LED_WATERING] = "LED_WATERING",
    [LED_ERROR] = "LED_ERROR"
};

result_t init_system(system_info_t* system_info)
{
    result_t res = SUCCESS;

    srand(time(NULL)); // For random value of sensor simulation

    init_default_config(&system_info->system_config);

    res = init_GPIO_led(&system_info->led_state);
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for LED");
    }

    res = init_GPIO_button();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for BUTTON");
    }

    res = init_GPIO_pump(&system_info->pump_state);
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for PUMP");
    }

    res = init_GPIO_sensor();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init SENSOR");
    }

    return SUCCESS;
}

void log_system_operation(sensor_info_t sensor_info, config_t sys_config, actuator_state_t pump_state)
{
    printf("--->>>\n");
    printf("[INFO][SYSTEM]  Moisture: %hhu*C  PUMP state: %s  system mode: %s \n",
            sensor_info.mois_info, pump_state_to_str[pump_state], mode_to_str[sys_config.system_mode]);
    printf("<<<---\n");
}

system_time_t get_current_time_s()
{
    return time(NULL);
}
