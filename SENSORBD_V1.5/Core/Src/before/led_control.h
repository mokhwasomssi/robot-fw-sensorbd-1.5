/*
 * led_control.h
 *
 *  Created on: 2022. 1. 19.
 *      Author: Best360
 */

#ifndef INC_LED_CONTROL_H_
#define INC_LED_CONTROL_H_

#include "main.h"
#include "stm32f4xx_hal.h"
#include <stdint.h>
//#include <stdbool.h>

#define MAX_LED_BELT (120)
#define MAX_LED_RING (30)

#define LED_RING1 (1)
#define LED_RING2 (2)
#define LED_BELT (3)

#define LEDBOARD 	(0x0C)
#define MAX_INTERFACE_DATA_LEN (9)

#define TIM1_PWM_PERIOD 	((htim1.Instance->ARR))//Get Period
#define TIM1_PWM_LED_LOW 	((TIM1_PWM_PERIOD+1)/3 - 1)
#define TIM1_PWM_LED_HIGH 	((TIM1_PWM_PERIOD+1)/3*2 - 1)

#define FRONTLIGHTON ((htim4.Instance->ARR) * 0.95)
#define FRONTLIGHTOFF (0)


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
	EYESTATUSHAPPY};

typedef struct color
{
	uint8_t Red;
	uint8_t Green;
	uint8_t Blue;
}color;

extern uint8_t Belt_Brightness;
extern uint8_t Belt_Brightness_flag;
extern uint8_t Ring1_Brightness;
extern uint8_t Ring1_Brightness_flag;
extern uint8_t Ring2_Brightness;
extern uint8_t Ring2_Brightness_flag;

extern uint8_t eyeHelloFlag;

extern uint8_t Belt_LED_Data[MAX_LED_BELT][3];
extern uint8_t Ring1_LED_Data[MAX_LED_RING][3];
extern uint8_t Ring2_LED_Data[MAX_LED_RING][3];

extern uint16_t beltPwmData[(24*MAX_LED_BELT)+50];
extern uint16_t ring1PwmData[(24*MAX_LED_RING)+50];
extern uint16_t ring2PwmData[(24*MAX_LED_RING)+50];

extern int32_t Belt_LED_rotateData[MAX_LED_BELT + 1];
extern int32_t Ring1_LED_rotateData[MAX_LED_RING + 1];
extern int32_t Ring2_LED_rotateData[MAX_LED_RING + 1];

extern uint8_t beltdatasentflag;
extern uint8_t ring1datasentflag;
extern uint8_t ring2datasentflag;

extern uint8_t beltToggle;

extern color LedRGB;

extern uint8_t beltStatus;
extern uint8_t beltAction;
extern uint8_t eyeStatus;
extern uint8_t eyeAction;
//uint8_t helloItr = 0;

extern uint8_t ledCategory;
extern uint8_t ledMode;
extern uint8_t ledAction;

void LED_PWM_init();

void Set_LED (int LEDnum, int led, color _color);
void WS2812_Send (int led);

void Belt_Toggle_LED (color _color);
void Belt_Reset_LED (void);
void Belt_Allset_LED (color _color);

void Ring1_Reset_LED (void);
void Ring2_Reset_LED (void);
void Belt_Rotate_Init(void);
void Ring_Rotate_Init(void);
void Set_LED_violet(uint8_t lednumber ,uint8_t led, uint8_t brightness);
void Set_LED_skyblue(uint8_t lednumber ,uint8_t led, uint8_t brightness);
void Set_LED_green(uint8_t lednumber ,uint8_t led, uint8_t brightness);
void Set_LED_red(uint8_t lednumber ,uint8_t led, uint8_t brightness);
void Set_LED_yellow(uint8_t lednumber ,uint8_t led, uint8_t brightness);
void Set_LED_white(uint8_t lednumber ,uint8_t led, uint8_t brightness);
void Set_LED_black(uint8_t lednumber ,uint8_t led);

color GetColorCode(uint8_t colorselect);

void Belt_MODE_breathing(uint8_t maxBrightness, color _color);
void Belt_MODE_rotation(uint8_t direction, color _color);
void Ring1_MODE_breathing(uint8_t maxBrightness);//left
void Ring1_MODE_rotation(uint8_t direction);
void Ring2_MODE_breathing(uint8_t maxBrightness);
void Ring2_MODE_rotation(uint8_t direction);
void Starting_anime(void);
void reverse(int32_t arr[], int start, int end);
void shiftRight(int32_t arr[], int d, int n);
void shiftLeft(int32_t arr[], int d, int n);
bool InterfaceChksumChk(uint8_t* Data);

void FrontLight_SetPWM(uint16_t _pwm);
void FrontLight_Enable(bool _bool);

void LedControlCategorySet();
void BeltControl();
void EyeControl();


#endif /* INC_LED_CONTROL_H_ */

