#include "utils.h"
#include "buttons.h"
#include "led.h"
#include "sensors.h"
#include "config.h"
#include "actuators.h"
#include "time.h"
#include <time.h>
#include <stdlib.h>

const char* mode_to_str[] =
{
    [MODE_AUTO]   = "AUTO",
    [MODE_MANUAL] = "MANUAL"
};

const char* pump_state_to_str[] =
{
    [PUMP_OFF] = "OFF",
    [PUMP_ON]  = "ON"
};

const char* led_state_to_str[] =
{
    [LED_NORMAL] = "LED_NORMAL",
    [LED_WATERING] = "LED_WATERING",
    [LED_ERROR] = "LED_ERROR",
    [LED_LOW_MOISTURE_ALERT] = "LED_LOW_MOISTURE_ALERT",
    [LED_TOO_MUCH_WATER_ALERT] = "LED_TOO_MUCH_WATER_ALERT",
};

result_t init_system(system_info_t* system_info)
{
    result_t res = SUCCESS;

    srand(time(NULL)); // For random value of sensor simulation
    system_info->sensor_info.mois_info = 40; // Init moisture

    init_default_config(&system_info->system_config);

    res = init_GPIO_led(&system_info->led_state);
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for LED");
    }

    res = init_GPIO_button();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for BUTTON");
    }

    res = init_GPIO_pump(&system_info->pump_state);
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init resource for PUMP");
    }

    res = init_GPIO_sensor();
    if (res != SUCCESS)
    {
        LOG_ERR("Fail to init SENSOR");
    }

    return SUCCESS;
}

void log_system_operation(sensor_info_t sensor_info, config_t sys_config, actuator_state_t pump_state)
{
    printf("--->>>\n");
    printf("[INFO][SYSTEM]  Moisture: %hhu*C  PUMP state: %s  system mode: %s \n",
            sensor_info.mois_info, pump_state_to_str[pump_state], mode_to_str[sys_config.system_mode]);
    printf("<<<---\n");
}

system_time_t get_current_time_s()
{
    return time(NULL);
}

void print_system_info(system_info_t system_info)
{
    printf("[INFO][SYSTEM]  Moisture: %hhu*C  PUMP state: %s  system mode: %s  Led state: %s\n",
            system_info.sensor_info.mois_info, pump_state_to_str[system_info.pump_state],
            mode_to_str[system_info.system_config.system_mode], led_state_to_str[system_info.led_state]);
}

void read_all_button(system_info_t *system_info)
{
    int state = 0;

    printf("Enter state of mode_button (1 or 0): ");
    while(scanf("%d", &state) != 1) {
        printf("Invalid input. Please enter a number: ");
        // Clear the input buffer
        while(fgetc(stdin) != '\n');  // Alternative to getchar()
    }

    if (state == 0)
    {
        system_info->button_info.mode_button = 0;
    }
    else if (state == 1)
    {
        system_info->button_info.mode_button = 1;
    }
    else
    {
        printf("[ERR ][INPUT] INVALID button state !!!");
    }

    printf("Enter state of pump_button (1 or 0): ");
    while(scanf("%d", &state) != 1) {
        printf("Invalid input. Please enter a number: ");
        // Clear the input buffer
        while(fgetc(stdin) != '\n');  // Alternative to getchar()
    }

    if (state == 0)
    {
        system_info->button_info.pump_button = 0;
    }
    else if (state == 1)
    {
        system_info->button_info.pump_button = 1;
    }
    else
    {
        printf("[ERR ][INPUT] INVALID button state !!!");
    }
}

void read_all_sensors(system_info_t *system_info)
{
    int input_data = 0;

    printf("Enter Moisture data (0 or 100): ");
    while(scanf("%d", &input_data) != 1) {
        printf("Invalid input. Please enter a number: ");
        // Clear the input buffer
        while(fgetc(stdin) != '\n');  // Alternative to getchar()
    }
    system_info->sensor_info.mois_info = input_data;

    printf("Enter Temperature data (0 or 100): ");
    while(scanf("%d", &input_data) != 1) {
        printf("Invalid input. Please enter a number: ");
        // Clear the input buffer
        while(fgetc(stdin) != '\n');  // Alternative to getchar()
    }
    system_info->sensor_info.temp_info = input_data;
}