#include "mcu_cmic_gd32f470vet6.h"

extern rtc_parameter_struct rtc_initpara;

/*!
    \brief      display the current time
    \param[in]  none
    \param[out] none
    \retval     none
*/
void rtc_task(void)
{
    rtc_current_time_get(&rtc_initpara);

    (void)oled_fill_rect(48, 16, 127, 23, 0U);
    oled_printf(48, 16, "%0.2x:%0.2x:%0.2x", rtc_initpara.hour, rtc_initpara.minute, rtc_initpara.second);
}
