#include "led_driver.h"


int main()
{
    const size_t NUM_PIXELS = 10;
    const uint32_t *color_buffer = led_get_buffer();

    if (led_init(NUM_PIXELS))
    {
        printf("Failed to initialize LED strip\n");
        led_shutdown();
        return -1;
    }

    color_buffer = led_get_buffer();
    if (color_buffer == NULL)
    {
        printf("Buffer is NULL after init\n");
        led_shutdown();
        return -1;
    }

    for (size_t i = 0; i < NUM_PIXELS; i++)
    {
        if (color_buffer[i] != 0)
        {
            printf("Test FAIL: buffer not zero at index %zu (value=0x%08X)\n", i, (unsigned)color_buffer[i]);
            led_shutdown();
            return -1;
        }
    }

    printf("Initial zero-check PASS\n");

    led_set_pixel_color(0, 255, 0, 0);
    led_set_pixel_color(9, 0, 0, 255);
    led_set_pixel_color(5, 255, 255, 255);

    /* Validate expected values */
    if (color_buffer[0] != 0x0000FF00U) {
        printf("Test FAIL: index 0 expected 0x0000FF00\n");
        led_shutdown();
        return 1;
    }
    if (color_buffer[9] != 0x000000FFU) {
        printf("Test FAIL: index 9 expected 0x000000FF\n");
        led_shutdown();
        return 1;
    }
    if (color_buffer[5] != 0x00FFFFFFU) {
        printf("Test FAIL: index 4 expected 0x00FFFFFF\n");
        led_shutdown();
        return 1;
    }

    printf("Individual color checks PASS\n");

    led_fill(0, 255, 0);

    for (size_t i = 0; i < NUM_PIXELS; i++)
    {
        if (color_buffer[i] != 0x00FF0000U)
        {
            printf("Test FAIL: not all green at index %zu (value=0x%08X)\n", i, (unsigned)color_buffer[i]);
            led_shutdown();
            return -1;
        }
    }
    printf("Fill GREEN check PASS\n");

    led_shutdown();
    printf("All tests PASS, resources freed\n");

    return 0;
}