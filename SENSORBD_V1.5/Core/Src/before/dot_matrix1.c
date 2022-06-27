/*
 * dot_matrix.c
 *
 *  Created on: Nov 5, 2021
 *      Author: Taesoo
 */


#include "DOT_MATRIX_cfg1.h"
#include "DOT_MATRIX1.h"

const DOT_MATRIX_CfgType1 DOT_MATRIX_CfgParam1[DOT_MATRIX_UNITS] =
{
	// DOT_MATRIX 1 Configurations
    {
		GPIOA,
		GPIO_PIN_6,
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

static DOT_MATRIX_info gs_MATRIX_info1[DOT_MATRIX_UNITS] = {0};

SPI_HandleTypeDef hspi_dot1;

char IMAGES1[20][8] = {//Y axis mirror, CCW 90deg rotate
  {0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00},//blank
  {0x42,0xc3,0xc3,0xff,0xff,0xc3,0xc3,0x42},//I
  {0x7e,0xff,0x1b,0x1b,0x1b,0x1b,0xff,0x7e},//A
  {0x7e,0xff,0x06,0x0c,0x0c,0x06,0xff,0x7e},//M
  {0x7e,0xff,0x30,0x18,0x0c,0x06,0xff,0x7e},//N
  {0x76,0xff,0xdb,0xdb,0xdb,0xdb,0xff,0x7e},//B
  {0x00,0x00,0xc3,0xc3,0xff,0xff,0xc3,0xc3},//I_small
  {0x00,0x00,0x00,0x00,0x1c,0x3e,0x3e,0x1c},//upleft(default)
  {0x00,0x0c,0x1e,0x3e,0x7c,0x3e,0x1e,0x0c},//heart
  {0x00,0x00,0x01,0x83,0xc6,0x6c,0x38,0x10},//expression
  {0x18,0x0c,0x06,0x06,0x06,0x06,0x0c,0x18},//happy
  {0x7e,0xff,0xff,0xff,0xff,0xff,0xff,0x7e},//100~91
  {0x7e,0xfe,0xfe,0xfe,0xfe,0xfe,0xfe,0x7e},//90~81
  {0x7c,0xfc,0xfc,0xfc,0xfc,0xfc,0xfc,0x7c},//80~71
  {0x78,0xf8,0xf8,0xf8,0xf8,0xf8,0xf8,0x78},//70~61
  {0x70,0xf0,0xf0,0xf0,0xf0,0xf0,0xf0,0x70},//60~51
  {0x60,0xe0,0xe0,0xe0,0xe0,0xe0,0xe0,0x60},//50~41
  {0x40,0xc0,0xc0,0xc0,0xc0,0xc0,0xc0,0x40},//40~31
  {0x00,0x80,0x80,0x80,0x80,0x80,0x80,0x00},//30~21
  {0x81,0x42,0x24,0x18,0x18,0x24,0x42,0x81}//20~1
};

char IMAGE_SAMSUNG1[47] = {

		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //Blank
		0x7A,0x49,0x41,0x3E, //G
		0x00, //Blank
		0x7F,0x30,0x08,0x06,0x7F, //N
		0x00, //Blank
		0x3F,0x40,0x40,0x3F, //U
		0x00, //Blank
		0x31,0x49,0x49,0x46, //S
		0x00, //Blank
		0x7F,0x02,0x04,0x02,0x7F, //M
		0x00, //Blank
		0x7E,0x09,0x09,0x7E, //A
		0x00, //Blank
		0x31,0x49,0x49,0x46, //S
		0x00,0x00,0x00//Blank
};

char IMAGE_Clab1[40] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //Blank
		0x38,0x44,0x44,0x7F, //b
		0x00, //Blank
		0x78,0x54,0x54,0x20, // a
		0x00, //Blank
		0x40,0x7F,0x41, //l
		0x00, //Blank
		0x60,0x60, // .
		0x00, //Blank
		0x22,0x41,0x41,0x3E, //C
		0x00, //Blank
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00
};

char IMAGE_CLab1[42] = {
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //Blank9
		0x38,0x44,0x44,0x7F, //b4
		0x00, //Blank1
		0x78,0x54,0x54,0x20, // a4
		0x00, //Blank1
		0x40,0x40,0x40,0x7F, //L4
		0x00, //Blank1
		0x08,0x08,0x08, // -3
		0x00, //Blank1
		0x22,0x41,0x41,0x3E, //C4
		0x00, //Blank1
		0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00 //Blank9
};
//-----------------------------[ Static Functions' Definitions ]----------------------------

// Static Functions Used By Library But Not Visible To User Who Include The Library (Driver)

static void SPI1_TX_Byte(uint8_t au8_DATA)
{
	HAL_SPI_Transmit(&hspi_dot1, &au8_DATA, 1, 10);
	DWT_Delay_us(1);
}

static void SS1_ENABLE(uint8_t au8_MATRIX_Instance)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, 1);//ss2_disable
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 0);
	DWT_Delay_us(1);
}

static void SS1_DISABLE(uint8_t au8_MATRIX_Instance)
{
	HAL_GPIO_WritePin(GPIOA, GPIO_PIN_6, 1);
	DWT_Delay_us(1);
}

static void TxByte1(uint8_t au8_MATRIX_Instance, uint8_t au8_Col, uint8_t au8_Val)
{
	SS1_ENABLE(au8_MATRIX_Instance);
	SPI1_TX_Byte(au8_Col);
	SPI1_TX_Byte(au8_Val);
	SS1_DISABLE(au8_MATRIX_Instance);
}
//----------------------------[ Library Functions' Definitions ]---------------------------

// Functions To Be Used By The User Who Include The Library (Driver)

void DOT_MATRIX1_Init(SPI_HandleTypeDef _hspi)
{
    uint8_t i = 0, j = 0;
    hspi_dot1 = _hspi;
    /*--------[ Initialize & Configure The MAX7219 Devices ]-------*/
    for(i = 0; i<DOT_MATRIX_UNITS; i++)
    {
    	// Set BCD Decode Mode
    	SS1_ENABLE(i);
    	SPI1_TX_Byte(0x09);
    	SPI1_TX_Byte(0x00);
    	SS1_DISABLE(i);

    	// Set Dot Matrix Unit Brightness
    	SS1_ENABLE(i);
    	SPI1_TX_Byte(0x0A); // Select Intensity register
    	SPI1_TX_Byte(0x09);
    	SS1_DISABLE(i);

    	// Set Display Refresh
    	SS1_ENABLE(i);
    	SPI1_TX_Byte(0x0B); // Select Scan-Limit register
    	SPI1_TX_Byte(0x07); // 1-7
    	SS1_DISABLE(i);

    	// Turn ON The Display
    	SS1_ENABLE(i);
    	SPI1_TX_Byte(0x0C);
    	SPI1_TX_Byte(0x01);
    	SS1_DISABLE(i);

    	// Disable Display Test
    	SS1_ENABLE(i);
    	SPI1_TX_Byte(0x0F);
    	SPI1_TX_Byte(0x00);
    	SS1_DISABLE(i);

        // Initialize The Global Structure
        gs_MATRIX_info1[i].Ticks = 0;
        gs_MATRIX_info1[i].BufferInit = 0;
        gs_MATRIX_info1[i].Arr_Index = 0;
        gs_MATRIX_info1[i].Col_Index = 0;
        gs_MATRIX_info1[i].Max_Ticks = DOT_MATRIX_CfgParam1[i].SCROLL_SPEED;
        for(j = 0; j < DOT_MATRIX_CfgParam1[i].CASCADED_DEVICES*8; j++)
        {
        	gs_MATRIX_info1[i].Buffer[j] = 0x00;
        }
    }
}

void MATRIX1_CLEAR(uint8_t au8_MATRIX_Instance)
{
	uint8_t i = 0, col = 1;

	for(i = 0; i<DOT_MATRIX_CfgParam1[au8_MATRIX_Instance].CASCADED_DEVICES; i++)
	{
		for(col = 1; col < 9; col++)
		{
			TxByte1(au8_MATRIX_Instance, col, 0x00);
			DWT_Delay_us(30);
		}
	}
}

void MATRIX1_Write_Char(uint8_t au8_MATRIX_Instance, uint8_t pos)
{
    uint8_t Column = 0;
    uint8_t FONT_W = 8;

    TxByte1(au8_MATRIX_Instance, Column, 0x00);DWT_Delay_us(30);
    for(Column=1; Column<=FONT_W; Column++)
    {
    	TxByte1(au8_MATRIX_Instance, Column, IMAGES1[pos][Column-1]);
    	DWT_Delay_us(30);
    }
    TxByte1(au8_MATRIX_Instance, Column, 0x00);
}

void MATRIX1_Write_SAMSUNG(uint8_t au8_MATRIX_Instance,uint8_t Row)
{
    uint8_t Column = 0;
    if(Row >= 40)
    {
    	//Do Nothing
    }
    else
    {
    	TxByte1(au8_MATRIX_Instance, Column, 0x00);DWT_Delay_us(30);
    	for(Column=1; Column<=8; Column++)
    	{
    	    TxByte1(au8_MATRIX_Instance, Column, IMAGE_SAMSUNG1[39 - Row + Column - 1]);
    	    DWT_Delay_us(30);
    	}
    	TxByte1(au8_MATRIX_Instance, Column, 0x00);
    }


}

void MATRIX1_Write_Clab(uint8_t au8_MATRIX_Instance,uint8_t Row)
{
	uint8_t Column = 0;
	if(Row >= 30)
	{
		//Do Nothing
	}
	else
	{
		TxByte1(au8_MATRIX_Instance, Column, 0x00);DWT_Delay_us(30);
		for(Column=1; Column<=8; Column++)
		{
			TxByte1(au8_MATRIX_Instance, Column, IMAGE_Clab1[29 - Row + Column - 1]);
			DWT_Delay_us(30);
		}
		TxByte1(au8_MATRIX_Instance, Column, 0x00);
	}

}

void MATRIX1_Write_CLab(uint8_t au8_MATRIX_Instance,uint8_t Row)
{
	uint8_t Column = 0;
	if(Row >= 35)
	{
		//Do Nothing
	}
	else
	{
		TxByte1(au8_MATRIX_Instance, Column, 0x00);//DWT_Delay_us(30);
		for(Column=1; Column<=8; Column++)
		{
			TxByte1(au8_MATRIX_Instance, Column, IMAGE_CLab1[34 - Row + Column - 1]);
			//DWT_Delay_us(30);
		}
		TxByte1(au8_MATRIX_Instance, Column, 0x00);
	}

}
