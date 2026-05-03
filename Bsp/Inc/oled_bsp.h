#ifndef OLED_BSP_H
#define OLED_BSP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#define OLED_WIDTH  128U
#define OLED_HEIGHT 32U

#define OLED_OK      0U
#define OLED_ERR     1U
#define OLED_BUSY    2U
#define OLED_TIMEOUT 3U

uint8_t oled_init(void);
uint8_t oled_deinit(void);
uint8_t oled_clear(void);
uint8_t oled_update(void);
uint8_t oled_update_async(void);
uint8_t oled_is_busy(void);
uint8_t oled_has_dirty(void);
uint8_t oled_wait_ready(uint32_t timeout_ms);
uint8_t oled_display_on(void);
uint8_t oled_display_off(void);
uint8_t oled_draw_point(uint8_t x, uint8_t y, uint8_t color);
uint8_t oled_fill_rect(uint8_t left, uint8_t top, uint8_t right, uint8_t bottom, uint8_t color);
uint8_t oled_show_string(uint8_t x, uint8_t y, const char *str, uint8_t font, uint8_t color);
int oled_printf(uint8_t x, uint8_t y, const char *format, ...);
void oled_dma_irq_handler(void);

#ifdef __cplusplus
}
#endif

#endif /* OLED_BSP_H */
