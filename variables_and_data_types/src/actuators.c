#include "actuators.h"
#include <stdio.h>

static actuator_state_t pump_state;

result_t init_GPIO_pump(void)
{
    LOG_PUMP_INFO("Init config for PUMP");

    pump_state = PUMP_OFF;
    // TODO: set GPIO pin for pump control

    return SUCCESS;
}

result_t set_pump_state(actuator_state_t state)
{
    if (state == PUMP_OFF)
    {
        LOG_PUMP_INFO("PUMP is OFF");
        pump_state = PUMP_OFF;

        // TODO: Set GPIO to turn OFF the pump
    }
    else if (state == PUMP_ON)
    {
        LOG_PUMP_INFO("PUMP is ON");
        pump_state = PUMP_ON;

        // TODO: Set GPIO to turn ON the pump
    }

    return SUCCESS;
}

actuator_state_t get_pump_state()
{
    return pump_state;
}
