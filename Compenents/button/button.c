#include "button.h"

static button_t *button_list;
static uint8_t button_count;
static button_read_fn button_read;
static button_event_fn button_event;

static uint8_t button_is_pressed(button_t *button)
{
    if ((button_read == 0) || (button == 0))
    {
        return 0U;
    }

    return (button_read(button) != 0U) ? 1U : 0U;
}

static void button_send_event(button_t *button, button_event_t event)
{
    if (button_event != 0)
    {
        button_event(button, event);
    }
}

void button_init(button_t *buttons, uint8_t count, button_read_fn read, button_event_fn event)
{
    button_list = buttons;
    button_count = count;
    button_read = read;
    button_event = event;

    if ((button_list == 0) || (button_read == 0))
    {
        button_list = 0;
        button_count = 0U;
        return;
    }

    for (uint8_t i = 0U; i < button_count; i++)
    {
        button_t *button = &button_list[i];
        uint8_t raw = button_is_pressed(button);

        button->raw = raw;
        button->stable = 0U;
        button->long_sent = 0U;
        button->change_ms = 0U;
        button->press_ms = 0U;

        if (button->debounce_ms == 0U)
        {
            button->debounce_ms = BUTTON_DEFAULT_DEBOUNCE_MS;
        }

        if (button->long_press_ms == 0U)
        {
            button->long_press_ms = BUTTON_DEFAULT_LONG_PRESS_MS;
        }
    }
}

void button_scan(uint32_t now_ms)
{
    if ((button_list == 0) || (button_read == 0))
    {
        return;
    }

    for (uint8_t i = 0U; i < button_count; i++)
    {
        button_t *button = &button_list[i];
        uint8_t raw = button_is_pressed(button);

        if (raw != button->raw)
        {
            button->raw = raw;
            button->change_ms = now_ms;
        }

        if ((raw != button->stable) &&
            ((uint32_t)(now_ms - button->change_ms) >= button->debounce_ms))
        {
            button->stable = raw;

            if (button->stable != 0U)
            {
                button->press_ms = now_ms;
                button->long_sent = 0U;
                button_send_event(button, BUTTON_EVT_PRESS);
            }
            else
            {
                button_send_event(button, BUTTON_EVT_RELEASE);

                if (button->long_sent == 0U)
                {
                    button_send_event(button, BUTTON_EVT_CLICK);
                }
            }
        }

        if ((button->stable != 0U) &&
            (button->long_sent == 0U) &&
            ((uint32_t)(now_ms - button->press_ms) >= button->long_press_ms))
        {
            button->long_sent = 1U;
            button_send_event(button, BUTTON_EVT_LONG_PRESS);
        }
    }
}
