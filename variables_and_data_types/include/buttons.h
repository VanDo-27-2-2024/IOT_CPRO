#ifndef BUTTONS_H
#define BUTTONS_H

#include "common_type.h"

result_t init_GPIO_button(void);
bool is_mod_button_pressed();
bool is_pump_button_pressed();

#endif // BUTTONS_H