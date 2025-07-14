#include "sensors.h"
#include <stdlib.h>
#include <time.h>

result_t init_GPIO_sensor(void)
{
    LOG_SENSOR_INFO("Init config for SENSOR");

    // TODO: set GPIO pin for led

    return SUCCESS;
}

sensor_info_t read_all_sensors(void)
{
    sensor_info_t sensor_info;

    int min = 1;
    int max = 100;
    int random_mois = (rand() % (max - min + 1)) + min; // Simulate moisture info between 1 and 100
    int random_temp = (rand() % (max - min + 1)) + min; // Simulate temp info between 1 and 100

    LOG_SENSOR_INFO("Moisture info: %d", random_mois);
    LOG_SENSOR_INFO("Temp info: %d", random_temp);

    sensor_info.mois_info = random_mois;
    sensor_info.temp_info = random_temp;

    return sensor_info;
}