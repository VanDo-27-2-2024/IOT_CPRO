#ifndef BUTTONS_H
#define BUTTONS_H

#include "common_type.h"

result_t init_GPIO_button(void);
bool is_button1_pressed();
bool is_button2_pressed();

#endif // BUTTONS_H