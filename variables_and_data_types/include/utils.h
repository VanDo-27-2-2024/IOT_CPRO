#ifndef UTILS_H
#define UTILS_H

#include "common_type.h"
#include "actuators.h"
#include "config.h"
#include "sensors.h"
#include <inttypes.h>

extern const char* mode_to_str[];
extern const char* pump_state_to_str[];

typedef uint32_t system_time_t;

result_t init_system(void);
void log_system_operatioin(sensor_info_t sensor_info, config_t sys_config, actuator_state_t pump_state);
system_time_t get_current_time_s();

#endif // UTILS_H