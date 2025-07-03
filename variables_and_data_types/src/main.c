#include "watering_logic.h"
#include "utils.h"
#include "led.h"
#include "config.h"
#include "actuators.h"

int main(void)
{
    result_t res;
    system_mode_t sys_mode;
    config_t sys_config;
    sensor_info_t sensor_info;
    static system_time_t sensor_start_time = 0;

    res = init_system();
    if (res != SUCCESS)
    {
        LOG_ERR("Init system fail !!!");
        return 0;
    }

    while (1)
    {
        res = handle_button(); // MODE_MANUAL is handled in this function
        if (res != SUCCESS)
        {
            LOG_ERR("Fail to handle button");
            set_led_state(LED_ERROR);
        }

        sys_mode = get_system_mode();
        sys_config = get_system_config();
        if (sys_mode == MODE_AUTO)
        {
            if ((get_current_time_s() - sensor_start_time > sys_config.sensor_check_interval_s) ||
                (get_pump_state() == PUMP_ON)) // Need to read sensor when PUMP is ON
            {
                sensor_info = read_all_sensors();
                handle_sensor(sensor_info, sys_config);
                sensor_start_time = get_current_time_s();
            }
        }
    }

    return 0;
}