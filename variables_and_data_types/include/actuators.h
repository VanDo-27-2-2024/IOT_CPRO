#ifndef ACTUATORS_H
#define ACTUATORS_H

#include "common_type.h"

typedef enum actuator_state
{
    PUMP_OFF = 0,
    PUMP_ON  = 1
} actuator_state_t;

result_t init_GPIO_pump(void);
result_t set_pump_state(actuator_state_t state);
actuator_state_t get_pump_state();

#endif // ACTUATORS_H
