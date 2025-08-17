#ifndef BUTTONS_H
#define BUTTONS_H

#include "common_type.h"
#include "utils.h"

typedef struct buton_info
{
    uint8_t mode_button;
    uint8_t pump_button;
} button_info_t;

result_t init_GPIO_button(void);
bool is_mod_button_pressed();
bool is_pump_button_pressed();

#endif // BUTTONS_H