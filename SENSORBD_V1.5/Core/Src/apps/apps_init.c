/*
 * apps_init.c
 *
 *  Created on: Jun 22, 2022
 *      Author: sangjun
 */

#include "app_sensorboard.h"

static void start(u32 param1);
static void stop(void);
static void on_msg(msg_t msg, u32 param1, u32 param2);

static app_t this =
{
    APPS_INIT_APP,
    APPS_NONE,
    0x00000000,

    start,
    stop,
    on_msg,
};


static void default_global_volatile(void);

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void init_apps_init_app(void)
{
  apps_init_app(&this);
  default_global_volatile();
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void default_global_volatile(void)
{
	gv.debug_mode = false;
	gv.ultrasonic_1 = 9999;
	gv.ultrasonic_2 = 9999;


	// need to check
	gv.LED_EYE_Status = 0;
	gv.LED_EYE_Action = 10; // battery
	gv.LED_Belt_Status = 0;
	gv.LED_Belt_Action = 0;
	gv.LED_Front_Status = 0;
	gv.LED_Front_Action = 0;
	// LED DMA FLAG
	gv.beltdatasentflag = 0;
	gv.ring1datasentflag = 0;
	gv.ring2datasentflag = 0;
}



/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void start(u32 param1)
{
	//

	htim1.Instance->CCR1 = htim1.Instance->ARR;
	htim1.Instance->CCR2 = htim1.Instance->ARR;
	htim1.Instance->CCR3 = htim1.Instance->ARR;

    init_ultrasonic_hg_c40u();
    init_p_interfaceboard();
    init_p_uart_test();
}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void stop(void)
{

}

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
static void on_msg(msg_t msg, u32 param1, u32 param2)
{
  switch(msg)
  {
    case MSG_SEND_INFO_TO_IBD:
    	break;

    case MSG_SEND_ULTEASONIC_VALUE:
    	break;

    default:
      break;
  }
}

