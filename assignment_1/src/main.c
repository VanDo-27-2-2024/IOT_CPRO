#include "watering_logic.h"
#include "utils.h"
#include "led.h"
#include "config.h"
#include "actuators.h"
#include <stdlib.h>

volatile bool should_exit = false;

int main(void)
{
    result_t res                            = SUCCESS;
    sensor_info_t sensor_info               = {0};
    static system_time_t sensor_start_time  = 0;
    system_info_t system_info;

    res = init_system(&system_info);
    if (res != SUCCESS)
    {
        LOG_ERR("Init system fail !!!");
        return 0;
    }

    while (!should_exit)
    {
        res = handle_button(&system_info); // MODE_MANUAL is handled in this function
        if (res != SUCCESS)
        {
            LOG_ERR("Fail to handle button");
            set_led_state(LED_ERROR, &system_info.led_state);
        }

        if (system_info.system_config.system_mode == MODE_AUTO)
        {
            if ((get_current_time_s() - sensor_start_time > system_info.system_config.sensor_check_interval_s) ||
                (system_info.pump_state == PUMP_ON)) // Need to read sensor when PUMP is ON
            {
                sensor_info = read_all_sensors();
                handle_sensor(sensor_info, &system_info);
                sensor_start_time = get_current_time_s();
            }
        }
    }

    return 0;
}