#include "common_type.h"
#include "utils.h"

result_t init_GPIO_button(void)
{
    LOG_BUTTON_INFO("Init config for BUTTON");

    return SUCCESS;
}

bool is_mod_button_pressed()
{
    // Simulate button operation
    return false;
}

bool is_pump_button_pressed()
{
    // Simulate button operation
    return false;
}
