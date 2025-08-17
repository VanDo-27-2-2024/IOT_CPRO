#include "watering_logic.h"
#include "utils.h"
#include "led.h"
#include "config.h"
#include "actuators.h"
#include "buttons.h"
#include <unistd.h>
#include <stdlib.h>

volatile bool should_exit = false;

int main(void)
{
    result_t res                            = SUCCESS;
    static system_time_t sensor_start_time  = 0;
    system_info_t system_info;

    res = init_system(&system_info);
    if (res != SUCCESS)
    {
        LOG_ERR("Init system fail !!!");
        return 0;
    }

    while (!should_exit)
    {
        print_system_info(system_info);

        if ((get_current_time_s() - sensor_start_time > system_info.system_config.sensor_check_interval_s)) // Need to read sensor when PUMP is ON
        {
            read_all_sensors(&system_info);
            read_all_button(&system_info);
            sensor_start_time = get_current_time_s();
        }

        handle_button(&system_info);
        handle_sensor(&system_info);
        sleep(2); // Delay for system handling

    }

    return 0;
}