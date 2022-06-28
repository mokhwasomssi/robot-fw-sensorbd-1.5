/*
 * apps_init.h
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */

#ifndef SRC_APPS_APPS_INIT_H_
#define SRC_APPS_APPS_INIT_H_





#define MAX_LED_BELT (120)
#define MAX_LED_RING (30)

#define LED_RING1 (1)
#define LED_RING2 (2)
#define LED_BELT (3)

#define TIM1_PWM_PERIOD 	((htim1.Instance->ARR))//Get Period
#define TIM1_PWM_LED_LOW 	((TIM1_PWM_PERIOD+1)/3 - 1)
#define TIM1_PWM_LED_HIGH 	((TIM1_PWM_PERIOD+1)/3*2 - 1)

#define FRONTLIGHTON ((htim4.Instance->ARR) * 0.95)

enum LEDCOLOR{
	COLORDEFAULT=1,
	COLOROFF,
	COLORORANGE,
	COLORRED,
	COLORSKYBLUE,
	COLORVIOLET,
	COLORGREEN
};//WS2812

enum LEDCATEGORY{
	LEDCATEGORYEYE=1,
	LEDCATEGORYBELT,
	LEDCATEGORYHEAD,
	LEDCATEGORYBACK
};

enum EYESSTATUS{
	EYESTATUSOFF=0,
	EYESTATUSDEFAULT,
	EYESTATUSBATTERY,
	EYESTATUSSMILE,
	EYESTATUSHEART,
	EYESTATUSHELLO,
	EYESTATUSHAPPY
};

enum BELT_ACTION{
	BELT_STOP=0,
	BELT_MOVE_CW,
	BELT_MOVE_CCW,
	BELT_BLINK,
	BELT_BREATH,


	MAX_BELT_ACTION_CNT
};

typedef struct color
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
}color;


extern void LED_Control_Set(uint8_t category,uint8_t mode, uint8_t action);


extern void init_apps_init_app(void);


#endif /* SRC_APPS_APPS_INIT_H_ */
