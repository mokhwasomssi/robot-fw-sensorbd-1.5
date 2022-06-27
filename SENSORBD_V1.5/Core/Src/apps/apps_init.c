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
	gv.testmode = false;
	gv.ultrasonic_1 = 9999;
	gv.ultrasonic_2 = 9999;
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

    // FRONT LIGHT
    FrontLight_Enable(true);
    FrontLight_SetPWM(FRONTLIGHTON);



//
    Belt_Rotate_Init();
    Ring_Rotate_Init();
    LED_PWM_init();
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_10, 1); // eye1 en
    HAL_GPIO_WritePin(GPIOD, GPIO_PIN_11, 1); // eye2 en
    osDelay(1000);


    //init 3 led
//	Belt_Reset_LED();
//	WS2812_Send(LED_BELT);
//	Ring1_Reset_LED();
//	WS2812_Send(LED_RING1);
//	Ring2_Reset_LED();
//	WS2812_Send(LED_RING2);
//	WS2812_Send(0);
//
//	// set belt led
//	Belt_Allset_LED(GetColorCode(COLORRED));
//	WS2812_Send(LED_BELT);


//	osDelay(20);
//	DOT_MATRIX1_Init(hspi1);
//	DOT_MATRIX2_Init(hspi1);
//	MATRIX1_CLEAR(0);
//	MATRIX2_CLEAR(0);
//	ledCategory = (uint8_t)LEDCATEGORYEYE;//temp
//	eyeStatus = (uint8_t)EYESTATUSHELLO;//temp
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

