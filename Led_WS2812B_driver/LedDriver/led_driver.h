#ifndef LED_DRIVER_H
#define LED_DRIVER_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>


/*
 * color_data_structure_t - alias for a 32-bit container that holds 24-bit color
 * Format used (bits 31..0): 0x00 G G  R R  B B  (i.e. 0x00GGRRBB)
 */
typedef uint32_t color_data_structure_t;


typedef struct led_strip
{
    color_data_structure_t *color_strip;
    size_t led_length;
} led_strip_t;


/*
 * led_init - Initializes a buffer for the LED strip with the given number of pixels
 * @num_pixels:	Number of pixels want to control
 *
 * Returns:
 *   0  on success
 *  -1  invalid input (num_pixels == 0)
 *  -2  memory allocation failed
 */
int led_init(size_t num_pixels);


/*
 * led_shutdown - Frees the memory allocated for the LED strip
 */
void led_shutdown();


/*
 * led_set_pixel_color - Sets the color of a specific pixel at the given 'index'
 *                        Uses 3 separate 8-bit values for Red, Green, and Blue
 * @index:	Position of led want to control
 * @r:	Red value
 * @g:	Green value
 * @b:	Blue value
 *
 */
void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b);


/*
 * led_fill - Fills the entire strip with a single color
 * @r:	Red value
 * @g:	Green value
 * @b:	Blue value
 *
 */
void led_fill(uint8_t r, uint8_t g, uint8_t b);


/*
 * led_clear - Turns off all pixels (by setting their color to black)
 */
void led_clear();


/*
 * led_get_buffer - Gets a constant (read-only) pointer to the data buffer, ready to be "sent" out
 *                      This function is used for testing purposes in this exercise
 */
const uint32_t* led_get_buffer();


/*
 * led_get_pixel_count - Gets the number of pixels on the LED strip
 */
size_t led_get_pixel_count();

#endif
