#include "led_bsp.h"

#include "gd32f4xx.h"

static const uint32_t led_port = GPIOD;
static const rcu_periph_enum led_clock = RCU_GPIOD;
static const uint32_t led_all_pins = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 |
                                     GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13;

static const uint32_t led_pins[LED_COUNT] = {
    GPIO_PIN_8,
    GPIO_PIN_9,
    GPIO_PIN_10,
    GPIO_PIN_11,
    GPIO_PIN_12,
    GPIO_PIN_13,
};

static uint8_t led_is_valid(led_id_t led)
{
    return ((uint32_t)led < (uint32_t)LED_COUNT);
}

void led_init(void)
{
    rcu_periph_clock_enable(led_clock);

    gpio_mode_set(led_port, GPIO_MODE_OUTPUT, GPIO_PUPD_NONE, led_all_pins);
    gpio_output_options_set(led_port, GPIO_OTYPE_PP, GPIO_OSPEED_50MHZ, led_all_pins);

    gpio_bit_reset(led_port, led_all_pins);
}

void led_set(led_id_t led, uint8_t on)
{
    if (led_is_valid(led) == 0U)
    {
        return;
    }

    gpio_bit_write(led_port, led_pins[led], (on != 0U) ? SET : RESET);
}

void led_on(led_id_t led)
{
    led_set(led, 1U);
}

void led_off(led_id_t led)
{
    led_set(led, 0U);
}

void led_toggle(led_id_t led)
{
    if (led_is_valid(led) == 0U)
    {
        return;
    }

    gpio_bit_toggle(led_port, led_pins[led]);
}
