#include "mcu_cmic_gd32f470vet6.h"

static uint8_t led_states[LED_COUNT] = {1U, 0U, 1U, 0U, 1U, 0U};

void led_task(void)
{
    

    for (uint8_t i = 0U; i < (uint8_t)LED_COUNT; i++)
    {
        led_set((led_id_t)i, led_states[i]);
    }
}
