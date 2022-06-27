/*
 * app_sensorboard.c
 *
 *  Created on: Jun 22, 2022
 *      Author: sangjun
 */

#include "app_sensorboard.h"

static app_id_t current_app_id = APPS_NONE;
static app_t *apps[APPS_COUNT]={0, };
global_volatile_t gv = {0};

static void apps_timer_10ms(s8 timer_id, u32 param1);
static void apps_timer_100ms(s8 timer_id, u32 param1);
static void apps_timer_1s(s8 timer_id, u32 param1);
static void apps_timer_5s(s8 timer_id, u32 param1);
static void apps_timer_1min(s8 timer_id, u32 param1);

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/

void apps_process_task(void *argument)
{
	static msg_t msg;
	static u32 param1, param2;
	static u8 process_index = 0;

	init_apps_init_app();

	apps_start_app(APPS_INIT_APP, 0);
	/********** timer init ***********/
	timers_init();
	//timers_register_timer(UTIL_TIMER_10ms, apps_timer_10ms);
	timers_register_timer(UTIL_TIMER_100ms, apps_timer_100ms);
	timers_register_timer(UTIL_TIMER_1s, apps_timer_1s);
	//timers_register_timer(UTIL_TIMER_5s, apps_timer_5s);
	timers_register_timer(UTIL_TIMER_1min, apps_timer_1min);

	while(1)
	{
		//printf("apps_process_task %d 1s\r\n",process_index);
		switch(process_index++)
		{
			case 1:
				//ret = sensor_read(SENSOR_A_NOISE, (u32)&sensors.c_val[SENSOR_NOISE], 0, 0);
				break;
			case 2 :
				process_index = 0;
				break;
		}

		if(msgs_get_msg(&msg, &param1, &param2) == true) apps_on_msg_app(msg, param1, param2);
		osDelay(1000);
	}
}


/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void apps_init_app(app_t *app)
{
	if(app == NULL) return;
	apps[app->id] = app;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool apps_start_app(app_id_t id, u32 param1)
{
	if(apps[id]->start == NULL) return false;

	current_app_id = id;
	apps[id]->start(param1);

	return true;
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool apps_switch_app(app_id_t id, u32 param1)
{
	if((id == APPS_NONE) || (apps[id] == null)) return false;
	if(current_app_id == id) return false;

	apps[current_app_id]->stop();
	apps[id]->prev_id = current_app_id;
	current_app_id = id;
	apps[id]->start(param1);

	return true;
}


/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void apps_on_msg_app(msg_t msg, u32 param1, u32 param2)
{
	if(apps[current_app_id]->on_msg == NULL) return;
	apps[current_app_id]->on_msg(msg, param1, param2);
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void apps_timer_10ms(s8 timer_id, u32 param1)
{
//	LedControlCategorySet();
//	BeltControl();
//	EyeControl();
	//printf("500ms ULTRA[%03d][%03d]\r\n",gv.ultrasonic_1,gv.ultrasonic_2);
}
static void apps_timer_100ms(s8 timer_id, u32 param1)
{
	DBG_MSG("ULTRA[%04d][%04d]\r\n",gv.ultrasonic_1,gv.ultrasonic_2);
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void apps_timer_1s(s8 timer_id, u32 param1)
{
	//DBG_MSG("apps_timer_1s\r\n");
}
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void apps_timer_5s(s8 timer_id, u32 param1)
{
	DOT_MATRIX1_Init(hspi1);
	DOT_MATRIX2_Init(hspi1);

	MATRIX1_CLEAR(0);
	MATRIX2_CLEAR(0);

	eyeStatus++;
	if(eyeStatus > EYESTATUSHAPPY )eyeStatus = EYESTATUSOFF;
}
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void apps_timer_1min(s8 timer_id, u32 param1)
{
	//DBG_MSG("apps_timer_1min\r\n");
}
