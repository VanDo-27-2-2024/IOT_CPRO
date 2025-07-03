#ifndef SENSORS_H
#define SENSORS_H

#include "common_type.h"

typedef struct sensor_info
{
    uint8_t mois_info;
    float temp_info;
} sensor_info_t;

result_t init_GPIO_sensor(void);
sensor_info_t read_all_sensors(void);

#endif // SENSORS_H