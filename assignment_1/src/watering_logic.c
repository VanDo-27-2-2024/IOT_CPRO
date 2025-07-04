#include "watering_logic.h"
#include "actuators.h"
#include "config.h"
#include "buttons.h"
#include "led.h"
#include "utils.h"
#include <unistd.h>

#define DELAY_TIME_MS 10000
#define DELAY_TIME_TO_CHECK_SENSOR_S 2

result_t handle_button(void)
{
    result_t res;
    system_mode_t mode;
    mode = get_system_mode();

    if (is_mod_button_pressed())
    {
        if (mode == MODE_AUTO)
        {
            change_system_mode(MODE_MANUAL);
        }
        else if (mode == MODE_MANUAL)
        {
            change_system_mode(MODE_AUTO);
        }

        res = set_pump_state(PUMP_OFF); // Turn off Pump when change mode
        if (res != SUCCESS)
        {
            LOG_ERR("Fail to turn OFF the PUMP");
        }

        return res;
    }

    if (is_pump_button_pressed() &&  mode == MODE_MANUAL)
    {
        res = set_pump_state(PUMP_ON);
        if (res != SUCCESS)
        {
            LOG_ERR("Fail to turn ON the PUMP");
            set_led_state(LED_ERROR);

            return res;
        }

        set_led_state(LED_WATERING);
        LOG_PUMP_INFO("Turn ON the PUMP");

        sleep(DELAY_TIME_MS / 1000);

        set_pump_state(PUMP_OFF);
        if (res != SUCCESS)
        {
            LOG_ERR("Fail to turn OFF the PUMP");
            set_led_state(LED_ERROR);

            return res;
        }

        set_led_state(LED_NORMAL);
        LOG_PUMP_INFO("Turn OFF the PUMP");
    }

    return SUCCESS;
}

result_t handle_sensor(sensor_info_t sensor_info, config_t sys_config)
{
    actuator_state_t pump_state = get_pump_state();
    static system_time_t watering_start_time = 0;
    system_time_t current_time = get_current_time_s();

    if (sys_config.system_mode != MODE_AUTO)
    {
        return SUCCESS;
    }

    if (pump_state == PUMP_OFF)
    {
        if (sensor_info.mois_info <= sys_config.moisture_min_threshold)
        {
            set_pump_state(PUMP_ON);
            watering_start_time = current_time;
            set_led_state(LED_WATERING);
            log_system_operatioin(sensor_info, sys_config, PUMP_ON);
        }
    }
    else if (pump_state == PUMP_ON)
    {
        bool should_stop = (sensor_info.mois_info >= sys_config.moisture_max_threshold) ||
                            ((current_time - watering_start_time) >= sys_config.max_watering_time_s);

        if (should_stop)
        {
            set_pump_state(PUMP_OFF);
            set_led_state(LED_NORMAL);
            log_system_operatioin(sensor_info, sys_config, PUMP_OFF);
        }

        sleep(DELAY_TIME_TO_CHECK_SENSOR_S);
    }

    return SUCCESS;
}
