/* Licence
* Company: MCUSTUDIO
* Auther: Ahypnis.
* Version: V0.10
* Time: 2025/06/05
* Note:
*/
#include "mcu_cmic_gd32f470vet6.h"

typedef struct {
    void (*task_handler)(void);
    uint32_t period_ms;
    uint32_t last_run_ms;
} scheduler_task_t;

/* Static task table: function pointer, run period in ms, and last run time. */
static scheduler_task_t scheduler_tasks[] =
{
    {led_task,  1U,   0U},
    {adc_task,  100U, 0U},
    {oled_task, 10U,  0U},
    {btn_task,  5U,   0U},
    {uart_task, 5U,   0U},
    {rtc_task,  500U, 0U},
};

static const uint32_t scheduler_task_count = sizeof(scheduler_tasks) / sizeof(scheduler_tasks[0]);

/**
 * @brief Initialize scheduler task timestamps.
 */
void scheduler_init(void)
{
    uint32_t now_ms = systick_get_ms();

    for (uint32_t task_index = 0U; task_index < scheduler_task_count; task_index++)
    {
        scheduler_tasks[task_index].last_run_ms = now_ms;
    }
}

/**
 * @brief Run due tasks according to their millisecond period.
 */
void scheduler_run(void)
{
    uint32_t now_ms = systick_get_ms();

    for (uint32_t task_index = 0U; task_index < scheduler_task_count; task_index++)
    {
        scheduler_task_t *task = &scheduler_tasks[task_index];

        if ((task->task_handler != NULL) &&
            (task->period_ms > 0U) &&
            ((uint32_t)(now_ms - task->last_run_ms) >= task->period_ms))
        {
            task->last_run_ms = now_ms;
            task->task_handler();
        }
    }
}
