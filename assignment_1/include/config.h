#ifndef CONFIG_H
#define CONFIG_H

#include "common_type.h"
#include "stdint.h"

typedef enum system_mode
{
    MODE_AUTO = 0,
    MODE_MANUAL = 1
} system_mode_t;

typedef struct config
{
    uint8_t moisture_min_threshold;
    uint8_t moisture_max_threshold;
    uint16_t max_watering_time_s;
    uint16_t sensor_check_interval_s;
    system_mode_t system_mode;
} config_t;

void init_default_config(config_t* system_config);
void change_config(config_t* system_config);
void show_config(const config_t* system_config);
void change_system_mode(system_mode_t new_mode, system_mode_t* mode);

#endif // CONFIG_H