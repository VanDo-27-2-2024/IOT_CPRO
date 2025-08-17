#ifndef LOGIC_H
#define LOGIC_H

#include "common_type.h"
#include "sensors.h"
#include "config.h"
#include "utils.h"

result_t handle_button(system_info_t* system_info);
result_t handle_sensor(system_info_t* system_info);

#endif // LOGIC_H