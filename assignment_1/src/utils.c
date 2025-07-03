#include "utils.h"
#include "buttons.h"
#include "led.h"
#include "sensors.h"
#include "config.h"
#include "actuators.h"
#include "time.h"

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

result_t init_system(void)
{
    result_t res;

    init_default_config();

    res = init_GPIO_led();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for LED");
    }

    res = init_GPIO_button();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for BUTTON");
    }

    res = init_GPIO_pump();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for PUMP");
    }

    return SUCCESS;
}

void log_system_operatioin(sensor_info_t sensor_info, config_t sys_config, actuator_state_t pump_state)
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
