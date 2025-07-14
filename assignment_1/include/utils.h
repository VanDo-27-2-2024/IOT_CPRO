#ifndef UTILS_H
#define UTILS_H

#include "common_type.h"
#include "actuators.h"
#include "config.h"
#include "sensors.h"
#include "led.h"
#include <inttypes.h>

extern const char* mode_to_str[];
extern const char* pump_state_to_str[];
extern const char* led_state_to_str[];

typedef uint32_t system_time_t;

typedef struct system_info
{
    actuator_state_t pump_state;
    config_t system_config;
    led_t led_state;
    sensor_info_t sensor_info;
} system_info_t;

result_t init_system(system_info_t* system_info);
void log_system_operation(sensor_info_t sensor_info, config_t sys_config, actuator_state_t pump_state);
system_time_t get_current_time_s();

#endif // UTILS_H