#ifndef LOGIC_H
#define LOGIC_H

#include "common_type.h"
#include "sensors.h"
#include "config.h"

result_t handle_button(void);
result_t handle_sensor(sensor_info_t sensor_info, config_t sys_config);

#endif // LOGIC_H