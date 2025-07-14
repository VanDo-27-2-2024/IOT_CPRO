#include "config.h"
#include "utils.h"
#include <stdio.h>

void init_default_config(config_t* system_config)
{
    LOG_CONFIG_INFO("Init default system config");

    *system_config = (config_t)
    {
        .moisture_min_threshold  = 30,
        .moisture_max_threshold  = 85,
        .max_watering_time_s     = 4,
        .sensor_check_interval_s = 6,
        .system_mode = MODE_AUTO
    };
}

void change_config(config_t* system_config)
{
    uint8_t choice, new_value_u8;
    uint16_t new_value_u16;

    do
    {
        LOG_INFO("Press number to config");
        LOG_INFO("0. Exit\
                  1. Change moisture_min_threshold\
                  2. Change moisture_max_threshold\
                  3. Change max_watering_time_s\
                  4. Change sensor_check_interval_s\
                  5. Change system_mode");

        if (scanf("%hhu", &choice) != 1)
        {
            LOG_ERR("Invalid input, please enter a valid option");
            continue;
        }

        switch (choice)
        {
            case 0:
                break;

            case 1:
                LOG_INFO("Enter new moisture_min_threshold (1-100%%) or 0 to exit");
                LOG_INFO("Current moisture_min_threshold: %hhu", system_config->moisture_min_threshold);

                if (scanf("%hhu", &new_value_u8) == 1)
                {
                    if (new_value_u8 <= 100)
                    {
                        system_config->moisture_min_threshold = new_value_u8;
                        LOG_INFO("Config updated");
                    }
                    else if (new_value_u8 == 0)
                    {
                        LOG_INFO("Operation cancelled");
                    }
                    else
                    {
                        LOG_ERR("Invalid value");
                    }
                }

                break;

            case 2:
                LOG_INFO("Enter new moisture_max_threshold (1-100%%) 0 to exit");
                LOG_INFO("Current moisture_max_threshold: %hhu", system_config->moisture_max_threshold);

                if (scanf("%hhu", &new_value_u8) == 1)
                {
                    if (new_value_u8 <= 100)
                    {
                        system_config->moisture_max_threshold = new_value_u8;
                        LOG_INFO("Config updated");
                    }
                    else if (new_value_u8 == 0)
                    {
                        LOG_INFO("Operation cancelled");
                    }
                    else
                    {
                        LOG_ERR("Invalid value");
                    }
                }

                break;

            case 3:
                LOG_INFO("Enter new max_watering_time_s (1-600ms) or 0 to exit");
                LOG_INFO("Current max_watering_time_s: %hu", system_config->max_watering_time_s);

                if (scanf("%hu", &new_value_u16) == 1)
                {
                    if (new_value_u16 >= 100 && new_value_u16 <= 60000)
                    {
                        system_config->max_watering_time_s = new_value_u16;
                        LOG_INFO("Config updated");
                    }
                    else if (new_value_u8 == 0)
                    {
                        LOG_INFO("Operation cancelled");
                    }
                    else
                    {
                        LOG_ERR("Invalid value");
                    }
                }

                break;

            case 4:
                LOG_INFO("Enter new sensor_check_interval_s (1-3600s) or 0 to exit");
                LOG_INFO("Current sensor_check_interval_s: %hu", system_config->sensor_check_interval_s);

                if (scanf("%hu", &new_value_u16) == 1)
                {
                    if (new_value_u16 >= 1 && new_value_u16 <= 3600)
                    {
                        system_config->sensor_check_interval_s = new_value_u16;
                        LOG_INFO("Config updated");
                    }
                    else if (new_value_u8 == 0)
                    {
                        LOG_INFO("Operation cancelled");
                    }
                    else
                    {
                        LOG_ERR("Invalid value");
                    }
                }

                break;

            case 5:
                LOG_INFO("Select system mode (0: AUTO, 1: MANUAL) or 2 to exit");
                LOG_INFO("Current system mode: %hhu", system_config->system_mode);

                if (scanf("%hhu", &new_value_u8) == 1)
                {
                    if (new_value_u8 <= 1)
                    {
                        system_config->system_mode = (system_mode_t)new_value_u8;
                        LOG_INFO("Config updated");
                    }
                    else if (new_value_u8 == 2)
                    {
                        LOG_INFO("Operation cancelled");
                    }
                    else
                    {
                        LOG_ERR("Invalid value");
                    }
                }
                break;

            default:
                LOG_ERR("Invalid choice");
                break;
        }
    } while (choice != 0);
}

void show_config(const config_t* system_config)
{
    LOG_INFO("Current System Configuration:");
    LOG_INFO("----------------------------");
    LOG_INFO("Moisture Minimum Threshold: %hhu%%", system_config->moisture_min_threshold);
    LOG_INFO("Moisture Maximum Threshold: %hhu%%", system_config->moisture_max_threshold);
    LOG_INFO("Maximum Watering Time: %hu ms", system_config->max_watering_time_s);
    LOG_INFO("Sensor Check Interval: %hu seconds", system_config->sensor_check_interval_s);

    const char* mode_str = (system_config->system_mode == MODE_AUTO) ? "AUTO" : "MANUAL";
    LOG_INFO("System Mode: %s", mode_str);
    LOG_INFO("----------------------------");
}

void change_system_mode(system_mode_t new_mode, system_mode_t* mode)
{
    *mode = new_mode;
    LOG_CONFIG_INFO("System mode change to %s", mode_to_str[*mode]);
}
