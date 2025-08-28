#include "led_driver.h"

static led_strip_t *led_strip_p;

int led_init(size_t num_pixels)
{
    if (num_pixels <= 0)
    {
        printf("Invalid pixels size\n");
        return -1;
    }

    // Free old buffer if already initialized to avoid memory leak
    if (led_strip_p != NULL)
    {
        free(led_strip_p->color_strip);
        // led_strip_p->color_strip = NULL; // unnecessary -> cuz the struct is gone when free led_strip_p
        free(led_strip_p);
        led_strip_p = NULL;
    }

    led_strip_p = malloc(sizeof(led_strip_t));
    if (led_strip_p == NULL)
    {
        return -2; // Allocation failed
    }

    led_strip_p->color_strip = calloc(num_pixels, sizeof(color_data_structure_t));
    if (led_strip_p->color_strip == NULL)
    {
        free(led_strip_p);
        led_strip_p = NULL;

        return -2; // Allocation failed
    }

    led_strip_p->led_length = num_pixels;

    return 0;
}


void led_shutdown()
{
    if (led_strip_p != NULL)
    {
        free(led_strip_p->color_strip);
        free(led_strip_p);
        led_strip_p = NULL;
    }
}


void led_set_pixel_color(size_t index, uint8_t r, uint8_t g, uint8_t b)
{
    if (!led_strip_p || index >= led_strip_p->led_length)
    {
        printf("Invalid index\n");
        return;
    }

    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b; // Format: 0x00GGRRBB
    *(led_strip_p->color_strip + index) = color;
}


void led_fill(uint8_t r, uint8_t g, uint8_t b)
{
    if (led_strip_p == NULL)
    {
        return;
    }

    /*
     * Note: Gán trực tiếp mà không dùng hàm led_set_pixel_color vì:
     *       - Bỏ qua những check không cần thiết
     *       - Chỉ cần gói màu 1 lần thôi -> tránh lặp -> chậm code
     */
    uint32_t color = ((uint32_t)g << 16) | ((uint32_t)r << 8) | (uint32_t)b;
    for (size_t i = 0; i < led_strip_p->led_length; i++)
    {
        led_strip_p->color_strip[i] = color;
    }
}


void led_clear()
{
    led_fill(0, 0, 0);
}


const uint32_t* led_get_buffer()
{
    if (led_strip_p == NULL)
    {
        return NULL;
    }

    return (const uint32_t*)(led_strip_p->color_strip);
}


size_t led_get_pixel_count()
{
    if (led_strip_p == NULL)
    {
        return 0;
    }

    return led_strip_p->led_length;
}