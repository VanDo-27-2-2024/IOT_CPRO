#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdlib.h>
#include <stdint.h>


typedef struct color_data_structure
{
    uint32_t color;
} color_data_structure_t;


typedef struct led_strip
{
    color_data_structure_t *color_strip;
    size_t led_length;
} led_strip_t;


/*
 * led_init - Initializes a buffer for the LED strip with the given number of pixels
 * @num_pixels:	Number of pixels want to control
 *
 * Returns 0 on success, -1 on failure (e.g., memory allocation failed)
 */
int led_init(size_t num_pixels);


/*
Frees the memory allocated for the LED strip
*/
void led_shutdown();


/*
Sets the color of a specific pixel at the given 'index'
Uses 3 separate 8-bit values for Red, Green, and Blue
*/
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);


/*
Fills the entire strip with a single color
*/
void led_fill(uint8_t r, uint8_t g, uint8_t b);


/*
Turns off all pixels (by setting their color to black)
*/
void led_clear();


/*
Gets a constant (read-only) pointer to the data buffer, ready to be "sent" out
This function is used for testing purposes in this exercise
*/
const uint32_t* led_get_buffer();


/*
Gets the number of pixels on the LED strip
*/
size_t led_get_pixel_count();

#endif
