/*
 * u_timer.c
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */



#include "u_timer.h"
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

#define MAX_TIMER          (12)
#define MAX_INTERRUP_TIMER (3)

typedef struct
{
  s8   id;
  bool busy;
  u32  tick;
  u32  period;
  timer_handler handler;
}timers_t;

static timers_t timers[MAX_TIMER]={0};

extern TIM_HandleTypeDef htim13;
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void timers_init(void)
{
  HAL_TIM_Base_Start_IT(&htim13);
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
s8 timers_register_timer(u32 period, timer_handler handler)
{
  u8 i;

  for(i=0; i<MAX_TIMER; i++)
  {
    if(timers[i].handler == null)
    {
      timers[i].tick = 0;
      timers[i].id = i;
      timers[i].period = period;
      timers[i].handler = handler;
      return i;
    }
  }
  return -1;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
s8 timers_remove_timer(s8 timer_id)
{
  u8 i;

  for(i=0; i<MAX_TIMER; i++)
  {
    if(timers[i].id == timer_id)
    {
      timers[i].handler = null;
      return -1;
    }
  }
  return -1;
}

void timers_remove_all_timer(void)
{
  for(u8 i=0; i<MAX_TIMER; i++)
  {
    timers[i].tick = 0;
    timers[i].id = i;
    timers[i].period = 0;
    timers[i].handler = null;
  }
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void timers_tick_timer(void)
{
  u8 i;

  for(i=0; i<MAX_TIMER; i++)
  {
    if(timers[i].handler == null)
      continue;

    if(timers[i].busy == false)
      timers[i].tick++;
  }
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void apps_timer_task(void *argument)
{
  u8 i;

  while(1)
  {
    for(i=0; i<MAX_TIMER; i++)
    {
      if(timers[i].handler == null)
        continue;

      if(timers[i].tick >= timers[i].period)
      {
        timers[i].busy = true;
        timers[i].tick = 0;
        timers[i].handler(timers[i].id, *(u32 *)(argument));
        timers[i].busy = false;
      }
    }
    osDelay(5);
  }
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static timers_t interrupt_timers[MAX_INTERRUP_TIMER]={0};

s8 timers_register_interrupt_timer(u32 period, timer_handler handler)
{
  u8 i;

  for(i=0; i<MAX_INTERRUP_TIMER; i++)
  {
    if(interrupt_timers[i].handler == null)
    {
      interrupt_timers[i].tick = 0;
      interrupt_timers[i].id = i;
      interrupt_timers[i].period = period;
      interrupt_timers[i].handler = handler;
      return i;
    }
  }
  return -1;
}

s8 timers_remove_interrupt_timer(s8 timer_id)
{
  u8 i;

  for(i=0; i<MAX_INTERRUP_TIMER; i++)
  {
    if(interrupt_timers[i].id == timer_id)
    {
      interrupt_timers[i].handler = null;
      return -1;
    }
  }
  return -1;
}

void timers_remove_all_interrupt_timer(void)
{
  for(u8 i=0; i<MAX_INTERRUP_TIMER; i++)
  {
    interrupt_timers[i].tick = 0;
    interrupt_timers[i].id = i;
    interrupt_timers[i].period = 0;
    interrupt_timers[i].handler = null;
  }
}

void timers_process_tick_interrupt_timer(u32 param1)
{
	u8 i;

	for(i=0; i<MAX_INTERRUP_TIMER; i++)
	{
		if(interrupt_timers[i].handler == null) continue;
		if(interrupt_timers[i].busy == true) continue;
		interrupt_timers[i].tick++;
		if(interrupt_timers[i].tick >= interrupt_timers[i].period)
		{
			interrupt_timers[i].busy = true;
			interrupt_timers[i].tick = 0;
			interrupt_timers[i].handler(interrupt_timers[i].id, param1);
			interrupt_timers[i].busy = false;
		}
	}
}

