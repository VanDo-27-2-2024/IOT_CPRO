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

void init_default_config(void);
void change_config(void);
void show_config(void);
void change_system_mode(system_mode_t mode);
system_mode_t get_system_mode();
config_t get_system_config();

#endif // CONFIG_H