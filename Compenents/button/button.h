#ifndef BUTTON_H
#define BUTTON_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define BUTTON_DEFAULT_DEBOUNCE_MS    20U
#define BUTTON_DEFAULT_LONG_PRESS_MS  1000U

typedef enum {
    BUTTON_EVT_PRESS = 0,
    BUTTON_EVT_RELEASE,
    BUTTON_EVT_CLICK,
    BUTTON_EVT_LONG_PRESS
} button_event_t;

typedef struct button {
    uint8_t id;
    uint8_t stable;
    uint8_t raw;
    uint8_t long_sent;
    uint32_t change_ms;
    uint32_t press_ms;
    uint16_t debounce_ms;
    uint16_t long_press_ms;
} button_t;

typedef uint8_t (*button_read_fn)(button_t *button);
typedef void (*button_event_fn)(button_t *button, button_event_t event);

void button_init(button_t *buttons, uint8_t count, button_read_fn read, button_event_fn event);
void button_scan(uint32_t now_ms);

#ifdef __cplusplus
}
#endif

#endif /* BUTTON_H */
