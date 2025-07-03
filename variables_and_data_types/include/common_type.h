#ifndef COMMON_TYPE_H
#define COMMON_TYPE_H

#include "stdint.h"
#include <stdio.h>

// #define LOG_INFO(msg)   printf("[INFO] %s\n", msg)
#define LOG_INFO(msg, ...) printf("[INFO  ]  " msg "\n", ##__VA_ARGS__)
#define LOG_SENSOR_INFO(msg, ...) printf("[INFO][SENSOR]  " msg "\n", ##__VA_ARGS__)
#define LOG_PUMP_INFO(msg, ...) printf("[INFO][PUMP  ]  " msg "\n", ##__VA_ARGS__)
#define LOG_BUTTON_INFO(msg, ...) printf("[INFO][BUTTON]  " msg "\n", ##__VA_ARGS__)
#define LOG_CONFIG_INFO(msg, ...) printf("[INFO][CONFIG]  " msg "\n", ##__VA_ARGS__)
#define LOG_LED_INFO(msg, ...) printf("[INFO][LED   ]  " msg "\n", ##__VA_ARGS__)
#define LOG_ERR(msg)   printf("[ERR] %s\n", msg)

#define true 1
#define false 0

typedef int bool;
typedef enum result
{
    SUCCESS = 0,
    ERROR = -1,
    TIMEOUT = -2,
} result_t;

#endif // COMMON_TYPE_H