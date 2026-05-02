#include "btn_bsp.h"

#include "gd32f4xx.h"

static const uint32_t btn_ports[BTN_COUNT] = {
    GPIOE,
    GPIOE,
    GPIOE,
    GPIOE,
    GPIOE,
    GPIOB,
    GPIOA,
};

static const uint32_t btn_pins[BTN_COUNT] = {
    GPIO_PIN_15,
    GPIO_PIN_13,
    GPIO_PIN_11,
    GPIO_PIN_9,
    GPIO_PIN_7,
    GPIO_PIN_0,
    GPIO_PIN_0,
};

static uint8_t btn_is_valid(btn_id_t btn)
{
    return ((uint32_t)btn < (uint32_t)BTN_COUNT);
}

void btn_init(void)
{
    rcu_periph_clock_enable(RCU_GPIOE);
    rcu_periph_clock_enable(RCU_GPIOB);
    rcu_periph_clock_enable(RCU_GPIOA);

    gpio_mode_set(GPIOE, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP,
                  GPIO_PIN_15 | GPIO_PIN_13 | GPIO_PIN_11 | GPIO_PIN_9 | GPIO_PIN_7);
    gpio_mode_set(GPIOB, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);
    gpio_mode_set(GPIOA, GPIO_MODE_INPUT, GPIO_PUPD_PULLUP, GPIO_PIN_0);
}

uint8_t btn_read(btn_id_t btn)
{
    if (btn_is_valid(btn) == 0U)
    {
        return 0U;
    }

    return (gpio_input_bit_get(btn_ports[btn], btn_pins[btn]) == RESET) ? 1U : 0U;
}
