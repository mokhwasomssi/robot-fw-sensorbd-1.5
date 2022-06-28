/*
 * u_timer.h
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */

#ifndef SRC_UTIL_U_TIMER_H_
#define SRC_UTIL_U_TIMER_H_


#include "_typedef.h"

#define UTIL_TIMER_TICK   (1) /*1ms*/
#define UTIL_TIMER_1ms   ((u32)(UTIL_TIMER_TICK))
#define UTIL_TIMER_10ms   ((u32)(10/UTIL_TIMER_TICK))
#define UTIL_TIMER_50ms   ((u32)(50/UTIL_TIMER_TICK))
#define UTIL_TIMER_100ms  ((u32)(100/UTIL_TIMER_TICK))
#define UTIL_TIMER_500ms  ((u32)(500/UTIL_TIMER_TICK))
#define UTIL_TIMER_1s     ((u32)(1000/UTIL_TIMER_TICK))
#define UTIL_TIMER_2s     ((u32)(2000/UTIL_TIMER_TICK))
#define UTIL_TIMER_3s     ((u32)(3000/UTIL_TIMER_TICK)))
#define UTIL_TIMER_5s     ((u32)(5000/UTIL_TIMER_TICK))
#define UTIL_TIMER_10s    ((u32)(10000/UTIL_TIMER_TICK))
#define UTIL_TIMER_30s    ((u32)(30000/UTIL_TIMER_TICK))
#define UTIL_TIMER_1min   ((u32)(60000/UTIL_TIMER_TICK))
#define UTIL_TIMER_2min   ((u32)(120000/UTIL_TIMER_TICK))
#define UTIL_TIMER_5min   ((u32)(300000/UTIL_TIMER_TICK))
#define UTIL_TIMER_10min  ((u32)(600000/UTIL_TIMER_TICK))
#define UTIL_TIMER_15min  ((u32)(900000/UTIL_TIMER_TICK))
#define UTIL_TIMER_30min  ((u32)(1800000/UTIL_TIMER_TICK))
#define UTIL_TIMER_1h  ((u32)(3600000/UTIL_TIMER_TICK))
#define UTIL_TIMER_3h  ((u32)(10800000/UTIL_TIMER_TICK))

typedef void (*timer_handler)(s8 timer_id, u32 param1);

extern void timers_init(void);
extern s8   timers_register_timer(u32 period, timer_handler handler);
extern s8   timers_remove_timer(s8 timer_id);
extern void timers_remove_all_timer(void);
extern void timers_tick_timer(void);
extern void timers_process_timer(u32 param1);

extern s8   timers_register_interrupt_timer(u32 period, timer_handler handler);
extern s8   timers_remove_interrupt_timer(s8 timer_id);
extern void timers_remove_all_interrupt_timer(void);
extern void timers_process_tick_interrupt_timer(u32 param1);


#endif /* SRC_UTIL_U_TIMER_H_ */
