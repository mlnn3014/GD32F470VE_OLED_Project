#ifndef BTN_BSP_H
#define BTN_BSP_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum {
    BTN_1 = 0,
    BTN_2,
    BTN_3,
    BTN_4,
    BTN_5,
    BTN_6,
    BTN_7,
    BTN_COUNT
} btn_id_t;

void btn_init(void);
uint8_t btn_read(btn_id_t btn);

#ifdef __cplusplus
}
#endif

#endif /* BTN_BSP_H */
