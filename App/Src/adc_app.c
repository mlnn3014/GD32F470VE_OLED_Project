/**
 * @FilePath: adc_app.c
 * @Author: Ahypnis
 * @Date: 2026-04-18 23:46:48
 * @LastEditors: Please set LastEditors
 * @LastEditTime: 2026-04-19 01:35:51
 * @Copyright: 2026 0668STO CO.,LTD. All Rights Reserved.
*/
#include "mcu_cmic_gd32f470vet6.h"

extern uint16_t adc_value[1];
extern uint16_t convertarr[CONVERT_NUM];

void adc_task(void)
{
    convertarr[0] = adc_value[0];
}

