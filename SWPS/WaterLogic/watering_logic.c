#include "watering_logic.h"
#include "actuators.h"
#include "config.h"
#include "buttons.h"
#include "led.h"
#include "utils.h"
#include <unistd.h>

#define DELAY_TIME_MS 10000
#define DELAY_TIME_TO_CHECK_SENSOR_S 2

result_t handle_button(system_info_t* system_info)
{
    result_t res = SUCCESS;
    system_mode_t mode = system_info->system_config.system_mode;

    if (is_mod_button_pressed() || (system_info->button_info.mode_button == 1))
    {
        if (mode == MODE_AUTO)
        {
            change_system_mode(MODE_MANUAL, &system_info->system_config.system_mode);
        }
        else if (mode == MODE_MANUAL)
        {
            change_system_mode(MODE_AUTO, &system_info->system_config.system_mode);
        }

        res = set_pump_state(PUMP_OFF, &system_info->pump_state); // Turn off Pump when change mode
        if (res != SUCCESS)
        {
            LOG_ERR("Fail to turn OFF the PUMP");
        }

        // Reset button
        system_info->button_info.mode_button = 0;
    }

    if ((is_pump_button_pressed() || system_info->button_info.pump_button == 1) &&  mode == MODE_MANUAL)
    {
        if (system_info->pump_state == PUMP_OFF)
        {
            res = set_pump_state(PUMP_ON, &system_info->pump_state);
            if (res != SUCCESS)
            {
                LOG_ERR("Fail to turn ON the PUMP");
                set_led_state(LED_ERROR, &system_info->led_state);
                system_info->led_state = LED_ERROR;

                return res;
            }

            set_led_state(LED_WATERING, &system_info->led_state);
            system_info->led_state = LED_WATERING;
            LOG_PUMP_INFO("PUMP is ON");
        }
        else if (system_info->pump_state == PUMP_ON)
        {
            res = set_pump_state(PUMP_OFF, &system_info->pump_state);
            if (res != SUCCESS)
            {
                LOG_ERR("Fail to turn OFF the PUMP");
                set_led_state(LED_ERROR, &system_info->led_state);
                system_info->led_state = LED_ERROR;

                return res;
            }

            set_led_state(LED_NORMAL, &system_info->led_state);
            system_info->led_state = LED_NORMAL;
            LOG_PUMP_INFO("PUMP is OFF");
        }

        // NOTE: This is for auto handling turn off the PUMP when it run over the config time
        // sleep(DELAY_TIME_MS / 1000);
        // res = set_pump_state(PUMP_OFF, &system_info->pump_state);
        // if (res != SUCCESS)
        // {
        //     LOG_ERR("Fail to turn OFF the PUMP");
        //     set_led_state(LED_ERROR, &system_info->led_state);

        //     return res;
        // }

        // set_led_state(LED_NORMAL, &system_info->led_state);
        // LOG_PUMP_INFO("Turn OFF the PUMP");

        // Reset button
        system_info->button_info.pump_button = 0;
    }

    return SUCCESS;
}

result_t handle_sensor(system_info_t* system_info)
{
    result_t res                               = SUCCESS;
    config_t sys_config                        = system_info->system_config;
    actuator_state_t pump_state                = system_info->pump_state;
    static system_time_t watering_start_time   = 0;
    system_time_t current_time                 = get_current_time_s();
    sensor_info_t sensor_info                  = system_info->sensor_info;

    if (sys_config.system_mode == MODE_MANUAL)
    {
        if (sensor_info.mois_info < sys_config.moisture_min_threshold)
        {
            set_led_state(LED_LOW_MOISTURE_ALERT, &system_info->led_state);
        }
        else if (sensor_info.mois_info > sys_config.moisture_max_threshold)
        {
            set_led_state(LED_TOO_MUCH_WATER_ALERT, &system_info->led_state);
        }
        return SUCCESS;
    }

    if (pump_state == PUMP_OFF)
    {
        if (sensor_info.mois_info <= sys_config.moisture_min_threshold)
        {
            res = set_pump_state(PUMP_ON, &system_info->pump_state);
            if (res != SUCCESS)
            {
                LOG_ERR("Fail to turn ON the PUMP");
            }

            watering_start_time = current_time;
            set_led_state(LED_WATERING, &system_info->led_state);
            system_info->led_state = LED_WATERING;
            // log_system_operation(sensor_info, sys_config, PUMP_ON);
        }
    }
    else if (pump_state == PUMP_ON)
    {
        bool should_stop = (sensor_info.mois_info >= sys_config.moisture_max_threshold) ||
                            ((current_time - watering_start_time) >= sys_config.max_watering_time_s);

        if (should_stop)
        {
            res = set_pump_state(PUMP_OFF, &system_info->pump_state);
            if (res != SUCCESS)
            {
                LOG_ERR("Fail to turn OFF the PUMP");
            }

            set_led_state(LED_NORMAL, &system_info->led_state);
            system_info->led_state = LED_NORMAL;

            // Simulate that after a long time of watering the moisture is above threshold
            if ((current_time - watering_start_time) >= sys_config.max_watering_time_s)
            {
                system_info->sensor_info.mois_info = 80;
            }

            // log_system_operation(system_info->sensor_info, sys_config, PUMP_OFF);
        }

        sleep(DELAY_TIME_TO_CHECK_SENSOR_S);
    }

    return SUCCESS;
}
