/*
 * led_control.c
 *
 *  Created on: 2022. 1. 19.
 *      Author: Best360
 */
#include "_typedef.h"
#include "led_control.h"
#include <DOT_MATRIX_cfg1.h>
#include <DOT_MATRIX_cfg2.h>

uint8_t Belt_Brightness = 0;
uint8_t Belt_Brightness_flag = 0;
uint8_t Ring1_Brightness = 0;
uint8_t Ring1_Brightness_flag = 0;
uint8_t Ring2_Brightness = 0;
uint8_t Ring2_Brightness_flag = 0;

uint8_t eyeHelloFlag = 0;

uint8_t Belt_LED_Data[MAX_LED_BELT][3];
uint8_t Ring1_LED_Data[MAX_LED_RING][3] = {0,};
uint8_t Ring2_LED_Data[MAX_LED_RING][3] = {0,};

uint16_t beltPwmData[(24*MAX_LED_BELT)+50];
uint16_t ring1PwmData[(24*MAX_LED_RING)+50] = {0,};
uint16_t ring2PwmData[(24*MAX_LED_RING)+50] = {0,};

int32_t Belt_LED_rotateData[MAX_LED_BELT + 1];
int32_t Ring1_LED_rotateData[MAX_LED_RING + 1];
int32_t Ring2_LED_rotateData[MAX_LED_RING + 1];

uint8_t beltdatasentflag=0;
uint8_t ring1datasentflag=0;
uint8_t ring2datasentflag=0;

uint8_t beltToggle = 0;

uint16_t LED_PWM_low = 0;//LED_PWM_PERIOD / 3;
uint16_t LED_PWM_high = 0;//LED_PWM_PERIOD / 3 * 2;

color ledRGB;
color beltRGB;

uint8_t beltStatus = 6;
uint8_t beltAction = 10;
uint8_t eyeStatus = EYESTATUSHELLO;
uint8_t eyeAction = 10;
uint8_t helloItr = 0;

uint8_t ledCategory = LEDCATEGORYEYE;
uint8_t ledMode = EYESTATUSHELLO;
uint8_t ledAction = 0;

void LED_PWM_init()
{
	LED_PWM_low = TIM1_PWM_LED_LOW;
	LED_PWM_high = TIM1_PWM_LED_HIGH;
}

/*
 * SET WS2812 LED RGB
 * */
void Set_LED (int LEDnum, int led, color _color)
{
	switch(led){
	case 1:
		Ring1_LED_Data[LEDnum][0] = (uint8_t)_color.Green;
		Ring1_LED_Data[LEDnum][1] = (uint8_t)_color.Red;
		Ring1_LED_Data[LEDnum][2] = (uint8_t)_color.Blue;
		break;
	case 2:
		Ring2_LED_Data[LEDnum][0] = (uint8_t)_color.Green;;
		Ring2_LED_Data[LEDnum][1] = (uint8_t)_color.Red;
		Ring2_LED_Data[LEDnum][2] = (uint8_t)_color.Blue;
		break;
	case 3:
		Belt_LED_Data[LEDnum][0] = (uint8_t)_color.Green;
		Belt_LED_Data[LEDnum][1] = (uint8_t)_color.Red;
		Belt_LED_Data[LEDnum][2] = (uint8_t)_color.Blue;
	}
}



void WS2812_Send (int led)
{
	uint32_t indx=0;
	uint32_t color;

	switch(led){
	case 0:
		for (int i= 0; i<MAX_LED_RING; i++)
		{
			for (int i=23; i>=0; i--)
			{
				ring1PwmData[indx] = 0;
				ring2PwmData[indx] = 0;
			}
		}
		for (int i= 0; i<MAX_LED_BELT; i++)
		{
			for (int i=23; i>=0; i--)
			{
				beltPwmData[indx] = 0;
			}
		}

		for (int i=0; i<50; i++)
		{
			ring1PwmData[indx] = 0;
			ring2PwmData[indx] = 0;
			beltPwmData[indx] = 0;
			indx++;
		}

		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t *)ring1PwmData, indx);
		while (!ring1datasentflag){};
		ring1datasentflag = 0;

		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)ring2PwmData, indx);
		while (!ring2datasentflag){};
		ring2datasentflag = 0;

		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)beltPwmData, indx);
		while (!beltdatasentflag){};
		beltdatasentflag = 0;
		break;

	case 1:
		for (int i= 0; i<MAX_LED_RING; i++)
		{
			color = ((Ring1_LED_Data[i][0]<<16) | (Ring1_LED_Data[i][1]<<8) | (Ring1_LED_Data[i][2]));
			for (int i=23; i>=0; i--)
			{
				if (color&(1<<i))
				{
					ring1PwmData[indx] = LED_PWM_high;  // 2/3 of period
				}

				else ring1PwmData[indx] = LED_PWM_low;  // 1/3 of period
				indx++;
			}
		}

		for (int i=0; i<50; i++)
		{
			ring1PwmData[indx] = 0;
			indx++;
		}

		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_2, (uint32_t *)ring1PwmData, indx);
		while (!ring1datasentflag){};
		ring1datasentflag = 0;

		break;

	case 2:
	for (int i= 0; i<MAX_LED_RING; i++)
		{
			color = ((Ring2_LED_Data[i][0]<<16) | (Ring2_LED_Data[i][1]<<8) | (Ring2_LED_Data[i][2]));
			for (int i=23; i>=0; i--)
			{
				if (color&(1<<i))
				{
					ring2PwmData[indx] = LED_PWM_high;  // 2/3 of period
				}

				else ring2PwmData[indx] = LED_PWM_low;  // 1/3 of period
				indx++;
			}
		}

		for (int i=0; i<50; i++)
		{
			ring2PwmData[indx] = 0;
			indx++;
		}

		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_3, (uint32_t *)ring2PwmData, indx);
		while (!ring2datasentflag){};
		ring2datasentflag = 0;
		break;

	case 3:
		for (int i= 0; i<MAX_LED_BELT; i++)
		{
			color = ((Belt_LED_Data[i][0]<<16) | (Belt_LED_Data[i][1]<<8) | (Belt_LED_Data[i][2]));
			for (int i=23; i>=0; i--)
			{
				if (color&(1<<i))
				{
					beltPwmData[indx] = LED_PWM_high;  // 2/3 of period
				}

				else beltPwmData[indx] = LED_PWM_low;  // 1/3 of period
				indx++;
			}
		}

		for (int i=0; i<50; i++)
		{
			beltPwmData[indx] = 0;
			indx++;
		}

		HAL_TIM_PWM_Start_DMA(&htim1, TIM_CHANNEL_1, (uint32_t *)beltPwmData, indx);
		while (!beltdatasentflag){};
		beltdatasentflag = 0;
		break;
	}


}

void Belt_Toggle_LED (color _color)
{
	if(beltToggle == 0)
	{
		Belt_Reset_LED();
		beltToggle = 1;
	}
	else
	{
		Belt_Allset_LED (_color);
		beltToggle = 0;
	}
}

void Belt_Reset_LED (void)
{
	for (int i=0; i<MAX_LED_BELT; i++)
	{
		Belt_LED_Data[i][0] = 0;
		Belt_LED_Data[i][1] = 0;
		Belt_LED_Data[i][2] = 0;
	}
}

void Belt_Allset_LED (color _color)
{
	for (int i=0; i<MAX_LED_BELT; i++)
	{
		Set_LED (i, LED_BELT, _color);
	}
}

void Ring1_Reset_LED (void)
{
	for (int i=0; i<MAX_LED_RING; i++)
	{
		Ring1_LED_Data[i][0] = 0;
		Ring1_LED_Data[i][1] = 0;
		Ring1_LED_Data[i][2] = 0;
	}
}

void Ring2_Reset_LED (void)
{
	for (int i=0; i<MAX_LED_RING; i++)
	{
		Ring2_LED_Data[i][0] = 0;
		Ring2_LED_Data[i][1] = 0;
		Ring2_LED_Data[i][2] = 0;
	}
}

void Belt_Rotate_Init(void)
{
	for(int i = 0; i < MAX_LED_BELT; i += 10)
	{
		Belt_LED_rotateData[i] = 50;
		Belt_LED_rotateData[i+1] = 50;
		Belt_LED_rotateData[i+2] = 50;
		Belt_LED_rotateData[i+3] = 50;
		Belt_LED_rotateData[i+4] = 50;
		Belt_LED_rotateData[i+5] = 0;
		Belt_LED_rotateData[i+6] = 0;
		Belt_LED_rotateData[i+7] = 0;
		Belt_LED_rotateData[i+8] = 0;
		Belt_LED_rotateData[i+9] = 0;
	}
}

void Ring_Rotate_Init(void)
{
	for(int i = 0; i < MAX_LED_RING; i += 5)
	{
		Ring1_LED_rotateData[i] = 50;
		Ring1_LED_rotateData[i+1] = 50;
		Ring1_LED_rotateData[i+2] = 50;
		Ring1_LED_rotateData[i+3] = 0;
		Ring1_LED_rotateData[i+4] = 0;

		Ring2_LED_rotateData[i] = 50;
		Ring2_LED_rotateData[i+1] = 50;
		Ring2_LED_rotateData[i+2] = 50;
		Ring2_LED_rotateData[i+3] = 0;
		Ring2_LED_rotateData[i+4] = 0;

	}
}


void Set_LED_violet(uint8_t lednumber ,uint8_t led, uint8_t brightness)
{
	color SetColor;
	SetColor.Red = brightness;
	SetColor.Green = 0;
	SetColor.Blue = brightness;

	Set_LED(lednumber,led,SetColor);
}
void Set_LED_skyblue(uint8_t lednumber ,uint8_t led, uint8_t brightness)
{
	color SetColor;
	SetColor.Red = 0;
	SetColor.Green = 0;
	SetColor.Blue = brightness;
	Set_LED(lednumber,led,SetColor);
}
void Set_LED_green(uint8_t lednumber ,uint8_t led, uint8_t brightness)
{
	color SetColor;
	SetColor.Red = 0;
	SetColor.Green = brightness;
	SetColor.Blue = 0;
	Set_LED(lednumber,led,SetColor);
}
void Set_LED_red(uint8_t lednumber ,uint8_t led, uint8_t brightness)
{
	color SetColor;
	SetColor.Red = brightness;
	SetColor.Green = brightness*0.2;
	SetColor.Blue = 0;
	Set_LED(lednumber,led,SetColor);
}
void Set_LED_yellow(uint8_t lednumber ,uint8_t led, uint8_t brightness)
{
	color SetColor;
	SetColor.Red = brightness;
	SetColor.Green = brightness*0.5;
	SetColor.Blue = 0;
	Set_LED(lednumber,led,SetColor);
}
void Set_LED_white(uint8_t lednumber ,uint8_t led, uint8_t brightness)
{
	color SetColor;
	SetColor.Red = brightness;
	SetColor.Green = brightness*0.8;
	SetColor.Blue = brightness*0.6;

	Set_LED(lednumber,led,SetColor);
}
void Set_LED_black(uint8_t lednumber ,uint8_t led)
{
	color SetColor;
	SetColor.Red = 0;
	SetColor.Green = 0;
	SetColor.Blue = 0;
	Set_LED(lednumber,led,SetColor);
}

color GetColorCode(uint8_t colorselect)
{
	color code = {0,0,0};
	switch (colorselect)
	{
	case COLORRED:
		code.Red = 150;
		code.Green = 0;
		code.Blue = 0;
		break;

	case COLORSKYBLUE:
		code.Red = 20;
		code.Green = 70;
		code.Blue = 70;
		break;

	case COLORVIOLET:
		code.Red = 75;
		code.Green = 0;
		code.Blue = 75;
		break;

	case COLORORANGE:
		code.Red = 130;
		code.Green = 20;
		code.Blue = 0;
		break;

	case COLORGREEN:
		code.Red = 0;
		code.Green = 150;
		code.Blue = 0;
		break;

	case COLOROFF:
		code.Red = 0;
		code.Green = 0;
		code.Blue = 0;
		break;

	default:
		code.Red = 130;
		code.Green = 20;
		code.Blue = 0;
		break;

	}

	return code;
}
void Belt_MODE_breathing(uint8_t maxBrightness, color _color)
{
	color setled;
	if(Belt_Brightness_flag == 0)
	{
		Belt_Brightness++;
		if(Belt_Brightness > maxBrightness)
		{
			Belt_Brightness_flag = 1;
		}
	}

	if(Belt_Brightness_flag == 1)
	{
		Belt_Brightness--;
		if(Belt_Brightness <= 0)
		{
			Belt_Brightness_flag = 0;
		}
	}

	for(int j = 0; j<MAX_LED_BELT; j++)
	{
		setled.Red = (Belt_Brightness*_color.Red)/maxBrightness;
		setled.Green = (Belt_Brightness*_color.Green)/maxBrightness;
		setled.Blue = (Belt_Brightness*_color.Blue)/maxBrightness;

		Set_LED(j,LED_BELT,setled);
	}
	WS2812_Send(LED_BELT);
}

void Belt_MODE_rotation(uint8_t direction, color _color)
{
	if (direction == 0)
	{
		shiftLeft(Belt_LED_rotateData, 1, MAX_LED_BELT);

		for(int i = 0; i < MAX_LED_BELT; i++)
		{
			Set_LED(i,LED_BELT,_color);
		}
		WS2812_Send(LED_BELT);
	}
	else
	{
		shiftRight(Belt_LED_rotateData, 1, MAX_LED_BELT);

		for(int i = 0; i < MAX_LED_BELT; i++)
		{
			Set_LED(i,LED_BELT,_color);
		}
		WS2812_Send(LED_BELT);
	}
}


void Ring1_MODE_breathing(uint8_t maxBrightness)//left
{
	uint8_t offset = 60;

	if(Ring1_Brightness_flag == 0)
	{
		Ring1_Brightness++;
		if(Ring1_Brightness >= maxBrightness+offset)
		{
			Ring1_Brightness_flag = 1;
		}
	}

	if(Ring1_Brightness_flag == 1)
	{
		Ring1_Brightness--;
		if(Ring1_Brightness <= offset)
		{
			Ring1_Brightness_flag = 0;
		}
	}


	for(int j = 0; j<MAX_LED_RING; j++)
	{
	  	Set_LED_white(j,LED_RING1,Ring1_Brightness);
	}
	WS2812_Send(LED_RING1);
}

void Ring1_MODE_rotation(uint8_t direction)
{
	if (direction == 0)
	{
		shiftLeft(Ring1_LED_rotateData, 1, MAX_LED_RING);

		for(int i = 0; i < MAX_LED_RING; i++)
		{
			Set_LED_violet(i,LED_RING1,Ring1_LED_rotateData[i]);
		}
		WS2812_Send(LED_RING1);
	}
	else
	{
		shiftRight(Ring1_LED_rotateData, 1, MAX_LED_RING);

		for(int i = 0; i < MAX_LED_RING; i++)
		{
			Set_LED_violet(i,LED_RING1,Ring1_LED_rotateData[i]);
		}
		WS2812_Send(LED_RING1);
	}
}

void Ring2_MODE_breathing(uint8_t maxBrightness)
{
	uint8_t offset = 60;
	if(Ring2_Brightness_flag == 0)
	{
		Ring2_Brightness++;
		if(Ring2_Brightness >= maxBrightness + offset)
		{
			Ring2_Brightness_flag = 1;
		}
	}

	if(Ring2_Brightness_flag == 1)
	{
		Ring2_Brightness--;
		if(Ring2_Brightness <= offset)
		{
			Ring2_Brightness_flag = 0;
		}
	}


	for(int j = 0; j<MAX_LED_RING; j++)
	{
		Set_LED_white(j,LED_RING2,Ring2_Brightness);
	}
	WS2812_Send(LED_RING2);
}

void Ring2_MODE_rotation(uint8_t direction)
{
	if (direction == 0)
	{
		shiftLeft(Ring2_LED_rotateData, 1, MAX_LED_RING);

		for(int i = 0; i < MAX_LED_RING; i++)
		{
			Set_LED_violet(i,LED_RING2,Ring2_LED_rotateData[i]);
		}
		WS2812_Send(LED_RING2);
	}
	else
	{
		shiftRight(Ring2_LED_rotateData, 1, MAX_LED_RING);

		for(int i = 0; i < MAX_LED_RING; i++)
		{
			Set_LED_violet(i,LED_RING2,Ring2_LED_rotateData[i]);
		}
		WS2812_Send(LED_RING2);
	}
}

void Starting_anime(void)
{
	for(int j = 0; j<MAX_LED_RING; j++)
	{
		Set_LED_white(j,LED_RING1,100);
		Set_LED_white(j,LED_RING2,100);
	}
	WS2812_Send(LED_RING1);
	WS2812_Send(LED_RING2);

	for(int k = 0; k < 35; k++)
	{
		MATRIX1_Write_Clab(0,k);
		MATRIX2_Write_SR(0,k);
		HAL_Delay(100);
	}
	for(int k = 0; k < 35; k++)
	{
		MATRIX1_Write_Clab(0,k);
		MATRIX2_Write_SR(0,k);
		HAL_Delay(100);
	}
	for(int k = 0; k < 35; k++)
	{
		MATRIX1_Write_Clab(0,k);
		MATRIX2_Write_SR(0,k);
		HAL_Delay(100);
	}


	MATRIX2_Write_Char(0, DOT_BLANK);
	MATRIX1_Write_Char(0, DOT_BLANK);
	HAL_Delay(1000);

	MATRIX2_Write_Char(0, DOT_I);
	MATRIX1_Write_Char(0, DOT_HEART);
	HAL_Delay(1000);

	MATRIX2_Write_Char(0, DOT_A);
	MATRIX1_Write_Char(0, DOT_M);
	HAL_Delay(1000);

	MATRIX2_Write_Char(0, DOT_BLANK);
	MATRIX1_Write_Char(0, DOT_BLANK);
	HAL_Delay(700);

	MATRIX2_Write_Char(0, DOT_N);
	MATRIX1_Write_Char(0, DOT_B);
	HAL_Delay(700);

	MATRIX2_Write_Char(0, DOT_BLANK);
	MATRIX1_Write_Char(0, DOT_BLANK);
	HAL_Delay(700);

	MATRIX2_Write_Char(0, DOT_N);
	MATRIX1_Write_Char(0, DOT_B);
	HAL_Delay(700);

	MATRIX2_Write_Char(0, DOT_BLANK);
	MATRIX1_Write_Char(0, DOT_BLANK);
	HAL_Delay(700);

	MATRIX2_Write_Char(0, DOT_N);
	MATRIX1_Write_Char(0, DOT_B);
	HAL_Delay(1200);

	MATRIX2_Write_Char(0, DOT_DEFAULT);
	MATRIX1_Write_Char(0, DOT_DEFAULT);
	HAL_Delay(1000);

	MATRIX2_Write_Char(0, DOT_DEFAULT);
	MATRIX1_Write_Char(0, DOT_EXCITED);
	HAL_Delay(1000);

	MATRIX2_Write_Char(0, DOT_DEFAULT);
	MATRIX1_Write_Char(0, DOT_DEFAULT);
}

void ShowBatteryStatus(uint8_t batteryLevel)
{
	if(batteryLevel > 100)
	{
		MATRIX1_Write_Char(0, DOT_N);
		MATRIX2_Write_Char(0, DOT_N);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_violet(j,LED_RING1,100);
			Set_LED_violet(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);		//ovf error
	}
	else if((batteryLevel <= 100) && (batteryLevel > 90))
	{
		MATRIX1_Write_Char(0, DOT_BATT_FULL);
		MATRIX2_Write_Char(0, DOT_BATT_FULL);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_white(j,LED_RING1,100);
			Set_LED_white(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 90) && (batteryLevel > 80))
	{
		MATRIX1_Write_Char(0, DOT_BATT_NINE);
		MATRIX2_Write_Char(0, DOT_BATT_NINE);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_white(j,LED_RING1,100);
			Set_LED_white(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 80) && (batteryLevel > 70))
	{
		MATRIX1_Write_Char(0, DOT_BATT_EIGHT);
		MATRIX2_Write_Char(0, DOT_BATT_EIGHT);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_white(j,LED_RING1,100);
			Set_LED_white(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 70) && (batteryLevel > 60))
	{
		MATRIX1_Write_Char(0, DOT_BATT_SEVEN);
		MATRIX2_Write_Char(0, DOT_BATT_SEVEN);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_white(j,LED_RING1,100);
			Set_LED_white(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 60) && (batteryLevel > 50))
	{
		MATRIX1_Write_Char(0, DOT_BATT_SIX);
		MATRIX2_Write_Char(0, DOT_BATT_SIX);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_yellow(j,LED_RING1,100);
			Set_LED_yellow(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 50) && (batteryLevel > 40))
	{
		MATRIX1_Write_Char(0, DOT_BATT_FIVE);
		MATRIX2_Write_Char(0, DOT_BATT_FIVE);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_yellow(j,LED_RING1,100);
			Set_LED_yellow(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 40) && (batteryLevel > 30))
	{
		MATRIX1_Write_Char(0, DOT_BATT_FOUR);
		MATRIX2_Write_Char(0, DOT_BATT_FOUR);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_yellow(j,LED_RING1,100);
			Set_LED_yellow(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if((batteryLevel <= 30) && (batteryLevel > 20))
	{
		MATRIX1_Write_Char(0, DOT_BATT_THREE);
		MATRIX2_Write_Char(0, DOT_BATT_THREE);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_red(j,LED_RING1,100);
			Set_LED_red(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
	}
	else if(batteryLevel <= 20)
	{
		MATRIX1_Write_Char(0, DOT_BATT_EMPTY);
		MATRIX2_Write_Char(0, DOT_BATT_EMPTY);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_red(j,LED_RING1,100);
			Set_LED_red(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);	//empty
	}
	else
	{
		MATRIX1_Write_Char(0, DOT_I);
		MATRIX2_Write_Char(0, DOT_I);

		for(int j = 0; j<MAX_LED_RING; j++)
		{
			Set_LED_violet(j,LED_RING1,100);
			Set_LED_violet(j,LED_RING2,100);
		}
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);		//ovf error
	}
}

void reverse(int32_t arr[], int start, int end)
{
	int temp;
    end = end - 1;
    while (start < end) {
        temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
    }
}

void shiftRight(int32_t arr[], int d, int n)
{
    reverse(arr, 0, n - d);
    reverse(arr, n - d, n);
    reverse(arr, 0, n);
}

void shiftLeft(int32_t arr[], int d, int n)
{
    reverse(arr, 0, d);
    reverse(arr, d, n);
    reverse(arr, 0, n);
}

bool InterfaceChksumChk(uint8_t* Data)
{
	uint8_t sum = 0;
	uint8_t len = Data[4] + 5 - 1; // len + 5 - 1

	for	(int i=0 ;i < len; i++)
		sum += Data[i];
	if( ((sum + Data[len]) & 0x00FF) == 0)
		return true;
	else
		return false;
}


/*FrontLight*/
void FrontLight_SetPWM(uint16_t _pwm)
{
	htim4.Instance->CCR1 = _pwm;
}
void FrontLight_Enable(bool _bool)
{
	if(_bool == true)
		HAL_TIM_PWM_Start(&htim4, TIM_CHANNEL_1);
	else
		HAL_TIM_PWM_Stop(&htim4, TIM_CHANNEL_1);
}

void LedControlCategorySet()
{
	if(ledCategory == LEDCATEGORYEYE) // Face
	{
		eyeStatus = ledMode;//6
		eyeAction = ledAction;//7
	}
	else if(ledCategory == LEDCATEGORYBELT)//Belt
	{
		beltStatus = ledMode;
		beltAction = ledAction;
	}

	else if(ledCategory == LEDCATEGORYHEAD)//Head
	{
		if(ledAction == 0)
		{
			if(ledMode == 1) FrontLight_SetPWM(250);//LED ON
			else if(ledMode == 2) FrontLight_SetPWM(0);//LED OFF

		}
		else FrontLight_SetPWM(ledAction);

	}
	else if(ledCategory == LEDCATEGORYBACK)//Back
	{
		//if(ledMode == 0x01)
		//	HAL_GPIO_WritePin(GPIOB, BACKLIT1_Pin, GPIO_PIN_SET);
		//if(ledMode == 0x02)
		//	HAL_GPIO_WritePin(GPIOB, BACKLIT2_Pin, GPIO_PIN_SET);
		//if(ledMode == 0x03)
		//	HAL_GPIO_WritePin(GPIOB, BACKLIT1_Pin, GPIO_PIN_RESET);
		//if(ledMode == 0x04)
		//	HAL_GPIO_WritePin(GPIOB, BACKLIT2_Pin, GPIO_PIN_RESET);
	}
}


/*Control algorithm*/
static uint16_t belt_action_cnt = 0;
void BeltControl()
{

	switch(beltStatus)
	{
		case 1 : //default(orange)
			beltRGB = GetColorCode(COLORDEFAULT);
			break;
		case 2 : //off
			beltRGB = GetColorCode(COLOROFF);
			break;
		case 3 : //orange
			beltRGB = GetColorCode(COLORORANGE);
			break;
		case 4 : //red
			beltRGB = GetColorCode(COLORRED);
			break;
		case 5 : //sky blue
			beltRGB = GetColorCode(COLORSKYBLUE);
			break;
		case 6 : //purple , violet
			beltRGB = GetColorCode(COLORVIOLET);
			break;
		case 7 : //green
			beltRGB = GetColorCode(COLORGREEN);
			break;
		default : //default(orange)
			beltRGB = GetColorCode(COLORDEFAULT);
			break;
	}

	switch(beltAction)
	{

		case 0 : //STOP
			belt_action_cnt = 0;
			Belt_Allset_LED(beltRGB);
			WS2812_Send(LED_BELT);
			break;

		case 1 : //move_CW
			belt_action_cnt++;
			if(belt_action_cnt >= 3)
			{
				belt_action_cnt = 0;
				Belt_MODE_rotation(0,beltRGB);
			}
			break;

		case 2 : //move_CCW
			belt_action_cnt++;
			if(belt_action_cnt >= 3)
			{
				belt_action_cnt = 0;
				Belt_MODE_rotation(1,beltRGB);
			}
			break;

		case 3 : //blink
			belt_action_cnt++;
			if(belt_action_cnt >= 100)
			{
				belt_action_cnt = 0;
				Belt_Toggle_LED(beltRGB);
				WS2812_Send(LED_BELT);
			}
			break;
		case 4 :
			belt_action_cnt = 0;
			Belt_MODE_breathing(100,beltRGB);
			break;
		default :
			belt_action_cnt = 0;
			break;
	}
}

static uint16_t eye_action_cnt = 0;
void EyeControl()
{
	switch(eyeStatus)
	{
	case EYESTATUSOFF : //OFF mode
		Ring1_Reset_LED();
		Ring2_Reset_LED();
		WS2812_Send(LED_RING1);
		WS2812_Send(LED_RING2);
		break;

	case EYESTATUSDEFAULT : //default mode
		Ring1_MODE_breathing(100);
		Ring2_MODE_breathing(100);
		MATRIX1_Write_Char(0, DOT_DEFAULT);
		MATRIX2_Write_Char(0, DOT_DEFAULT);
		break;

	case EYESTATUSBATTERY : //battery mode
		ShowBatteryStatus(eyeAction);
		break;

	case EYESTATUSSMILE : //smile mode
		Ring1_MODE_breathing(100);
		Ring2_MODE_breathing(100);
		MATRIX1_Write_Char(0, DOT_EXCITED);
		MATRIX2_Write_Char(0, DOT_EXCITED);
		break;

	case EYESTATUSHEART : //heart mode
		Ring1_MODE_breathing(100);
		Ring2_MODE_breathing(100);
		MATRIX1_Write_Char(0, DOT_HEART);
		MATRIX2_Write_Char(0, DOT_HEART);
		break;

	case EYESTATUSHELLO : //hello mode
		if(eyeHelloFlag == 0) helloItr++;
		else helloItr = helloItr + 5;

		Ring1_MODE_breathing(100);
		Ring2_MODE_breathing(100);

		if(helloItr >= 100)
		{
			if(eyeHelloFlag == 0) eyeHelloFlag = 1;
			else eyeHelloFlag = 0;
			helloItr = 0;
		}
		if(eyeHelloFlag == 0)
		{
			MATRIX1_Write_Char(0, 6);DWT_Delay_us(50);
			MATRIX2_Write_Char(0, 6);DWT_Delay_us(50);
		}
		if(eyeHelloFlag == 1)
		{
			MATRIX1_Write_Char(0, 0);DWT_Delay_us(50);
			MATRIX2_Write_Char(0, 0);DWT_Delay_us(50);
		}

		break;

	case EYESTATUSHAPPY : //happy mode
			Ring1_MODE_breathing(100);
			Ring2_MODE_breathing(100);
			MATRIX1_Write_Char(0, 10);
			MATRIX2_Write_Char(0, 10);
		break;

	default :
			Ring1_MODE_rotation(1);
			Ring2_MODE_rotation(0);
		break;
	}
}
