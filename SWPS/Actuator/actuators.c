#include "actuators.h"
#include "utils.h"
#include <stdio.h>

result_t init_GPIO_pump(actuator_state_t* pump_state)
{
    LOG_PUMP_INFO("Init config for PUMP");

    *pump_state = PUMP_OFF;
    // TODO: set GPIO pin for pump control

    return SUCCESS;
}

result_t set_pump_state(actuator_state_t new_state, actuator_state_t* pump_state)
{
    *pump_state = new_state;
    // LOG_PUMP_INFO("PUMP is %s", pump_state_to_str[*pump_state]);

    return SUCCESS;
}
