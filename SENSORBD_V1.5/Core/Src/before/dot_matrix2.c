/*
 * dot_matrix2.c
 *
 *  Created on: Nov 5, 2021
 *      Author: Taesoo
 */


#include "DOT_MATRIX_cfg2.h"
#include "DOT_MATRIX2.h"

const DOT_MATRIX_CfgType2 DOT_MATRIX_CfgParam2[DOT_MATRIX_UNITS] =
{
	// DOT_MATRIX 1 Configurations
    {
		GPIOA,
		GPIO_PIN_4,
		75,   /* Scroll Speed*/
		1,    /* Number Of Cascaded Devices*/
		8,    /* Brightness Level */
		STATIC_MODE
	}
};

typedef struct
{
	uint32_t  Ticks;
	uint32_t  Max_Ticks;
	uint16_t  Arr_Index;
	uint8_t   Col_Index;
	uint8_t   BufferInit;
	uint8_t   Buffer[MAX_CASCADED_NUM*8];
	uint16_t  ArrSize;
	char*     ArrPtr;
}DOT_MATRIX_info;

static DOT_MATRIX_info gs_MATRIX_info2[DOT_MATRIX_UNITS] = {0};

SPI_HandleTypeDef hspi_dot2;

char IMAGES2[20][8] = {//Y axis mirror, CW 90deg rotate
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//blank 0
  {0x42,0xc3,0xc3,0xff,0xff,0xc3,0xc3,0x42},//I 1
  {0x7e,0xff,0xd8,0xd8,0xd8,0xd8,0xff,0x7e},//A 2
  {0x7e,0xff,0x60,0x30,0x30,0x60,0xff,0x7e},//M 3
  {0x7e,0xff,0x60,0x30,0x18,0x0c,0xff,0x7e},//N 4
  {0x7e,0xff,0xdb,0xdb,0xdb,0xdb,0xff,0x6e},//B 5
  {0x00,0x00,0xff,0xff,0x18,0x18,0xff,0xff},//H_small 6
  {0x38,0x7c,0x7c,0x38,0x00,0x00,0x00,0x00},//upleft(default) 7
  {0x00,0x30,0x78,0x7c,0x3e,0x7c,0x78,0x30},//heart 8
  {0x00,0x00,0x80,0xc1,0x63,0x36,0x1c,0x08},//expression 9
  {0x18,0x30,0x60,0x60,0x60,0x60,0x30,0x18},//happy 10
  {0x7e,0xff,0xff,0xff,0xff,0xff,0xff,0x7e},//100~91
  {0x7e,0x7f,0x7f,0x7f,0x7f,0x7f,0x7f,0x7e},//90~81
  {0x3e,0x3f,0x3f,0x3f,0x3f,0x3f,0x3f,0x3e},//80~71
  {0x1e,0x1f,0x1f,0x1f,0x1f,0x1f,0x1f,0x1e},//70~61
  {0x0e,0x0f,0x0f,0x0f,0x0f,0x0f,0x0f,0x0e},//60~51
  {0x06,0x07,0x07,0x07,0x07,0x07,0x07,0x06},//50~41
  {0x02,0x03,0x03,0x03,0x03,0x03,0x03,0x02},//40~31
  {0x00,0x01,0x01,0x01,0x01,0x01,0x01,0x00},//30~21
  {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81}//20~1
};

char IMAGE_SR2[42] = {
		0x00,0x00,0x00,0x00,0x00,0x00,
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//Blank
		0x62,0x92,0x92,0x92,0x8C, //Wide S
		0x00,0x00,0x00,0x00, //Blank
		0xFE,0x90,0x90,0x90,0x6E, //Wide R
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//Blank
		0x00,0x00,0x00,0x00,0x00,0x00
};
//-----------------------------[ Static Functions' Definitions ]----------------------------

// Static Functions Used By Library But Not Visible To User Who Include The Library (Driver)

static void SPI2_TX_Byte(uint8_t au8_DATA)
{
	HAL_SPI_Transmit(&hspi_dot2, &au8_DATA, 1, 10);
	DWT_Delay_us(1);
}

static void SS2_ENABLE(uint8_t au8_MATRIX_Instance)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);//ss1_disable
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 0);
	DWT_Delay_us(1);

}

static void SS2_DISABLE(uint8_t au8_MATRIX_Instance)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);
	DWT_Delay_us(1);
}

static void TxByte2(uint8_t au8_MATRIX_Instance, uint8_t au8_Col, uint8_t au8_Val)
{
	SS2_ENABLE(au8_MATRIX_Instance);
	SPI2_TX_Byte(au8_Col);
	SPI2_TX_Byte(au8_Val);
	SS2_DISABLE(au8_MATRIX_Instance);
}
//----------------------------[ Library Functions' Definitions ]---------------------------

// Functions To Be Used By The User Who Include The Library (Driver)

void DOT_MATRIX2_Init(SPI_HandleTypeDef _hspi)
{
    uint8_t i = 0, j = 0;
    hspi_dot2 = _hspi;
    /*--------[ Initialize & Configure The MAX7219 Devices ]-------*/
    for(i = 0; i<DOT_MATRIX_UNITS; i++)
    {
    	// Set BCD Decode Mode
    	SS2_ENABLE(i);
    	SPI2_TX_Byte(0x09);
    	SPI2_TX_Byte(0x00);
    	SS2_DISABLE(i);
    	// Set Dot Matrix Unit Brightness
    	SS2_ENABLE(i);
    	SPI2_TX_Byte(0x0A); // Select Intensity register
    	SPI2_TX_Byte(0x09);
    	SS2_DISABLE(i);
    	// Set Display Refresh
    	SS2_ENABLE(i);
    	SPI2_TX_Byte(0x0B); // Select Scan-Limit register
    	SPI2_TX_Byte(0x07); // 1-7
    	SS2_DISABLE(i);
    	// Turn ON The Display
    	SS2_ENABLE(i);
    	SPI2_TX_Byte(0x0C);
    	SPI2_TX_Byte(0x01);
    	SS2_DISABLE(i);
    	// Disable Display Test
    	SS2_ENABLE(i);
    	SPI2_TX_Byte(0x0F);
    	SPI2_TX_Byte(0x00);
    	SS2_DISABLE(i);

        // Initialize The Global Structure
        gs_MATRIX_info2[i].Ticks = 0;
        gs_MATRIX_info2[i].BufferInit = 0;
        gs_MATRIX_info2[i].Arr_Index = 0;
        gs_MATRIX_info2[i].Col_Index = 0;
        gs_MATRIX_info2[i].Max_Ticks = DOT_MATRIX_CfgParam2[i].SCROLL_SPEED;
        for(j = 0; j < DOT_MATRIX_CfgParam2[i].CASCADED_DEVICES*8; j++)
        {
        	gs_MATRIX_info2[i].Buffer[j] = 0x00;
        }
    }
}

void MATRIX2_CLEAR(uint8_t au8_MATRIX_Instance)
{
	uint8_t i = 0, col = 1;

	for(i = 0; i<DOT_MATRIX_CfgParam2[au8_MATRIX_Instance].CASCADED_DEVICES; i++)
	{
		for(col = 1; col < 9; col++)
		{
			TxByte2(au8_MATRIX_Instance, col, 0x00);
			DWT_Delay_us(30);
		}
	}
}

void MATRIX2_Write_Char(uint8_t au8_MATRIX_Instance, uint8_t pos)
{
    uint8_t Column = 0;
    uint8_t FONT_W = 8;

    TxByte2(au8_MATRIX_Instance, Column, 0x00);DWT_Delay_us(30);
    for(Column=1; Column<=FONT_W; Column++)
    {
    	TxByte2(au8_MATRIX_Instance, Column, IMAGES2[pos][Column-1]);
    	DWT_Delay_us(30);
    }
    TxByte2(au8_MATRIX_Instance, Column, 0x00);
}


void MATRIX2_Write_SR(uint8_t au8_MATRIX_Instance,uint8_t Row)
{
	uint8_t Column = 0;
	if(Row >= 35)
	{
		//Do Nothing
	}
	else
	{
		TxByte2(au8_MATRIX_Instance, Column, 0x00);DWT_Delay_us(30);
		for(Column=1; Column<=8; Column++)
		{
			TxByte2(au8_MATRIX_Instance, Column, IMAGE_SR2[Row + Column - 1]);
			DWT_Delay_us(30);
		}
		TxByte2(au8_MATRIX_Instance, Column, 0x00);
	}

}
