/*
 * interface_board.c
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */

#include "app_sensorboard.h"

#define UART_INTERFACBD ( &huart4 )

#define MAX_PACKET_LENGTH ( 22 )

#define PID_S2L_CONTROL (11)
#define PID_E2S_SENSOR_DATA	(12)
#define INTERFACE_HEADER_1 ( 0xFF )
#define INTERFACE_HEADER_2 ( 0xFF )
#define INTERFACE_MID ( 0x0B )

uint8_t TX_PACKET_B2B[30];

extern osMessageQueueId_t queue_interfaceBDHandle;

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void init_p_interfaceboard(void)
{
	Uart_Init_Custom(UART_INTERFACBD);
	osThreadResume (p_interfaceBDHandle);

	TX_PACKET_B2B[0] = 0xFF;
	TX_PACKET_B2B[1] = 0xFF;
	TX_PACKET_B2B[2] = 0x0A;
	TX_PACKET_B2B[3] = PID_E2S_SENSOR_DATA;
}


/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
uint8_t B2BChksumMake(uint8_t* _data, uint8_t _len)
{
	uint8_t chksum = 0;

	for(int i = 0 ; i < _len ; i++)
	{
		chksum += _data[i];
	}
	chksum ^= 0xFF;
	chksum += 1;

	return chksum;
}
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool RosChksumChk(uint8_t* Data)
{
	uint8_t sum = 0;
	uint8_t len = Data[4] + 5 - 1; // len + 5 - 1

	if(Data[4] == 0) return false;


	for	(int i=0 ;i < len; i++)
		sum += Data[i];
	if( ((sum + Data[len]) & 0x00FF) == 0)
		return true;
	else
		return false;
}


static bool start_parsing = true;
static uint32_t execute_idx = 0;
static uint8_t buf[MAX_PACKET_LENGTH];
static uint8_t buffer_len = 0;
static uint8_t data_seq = 0;
void p_interfaceBD_task(void *argument)
{
	//uint8_t data_seq = 0;
	u8 data;
	osMessageQueueReset(queue_interfaceBDHandle);

	while(1)
	{
		if(osMessageQueueGet(queue_interfaceBDHandle, &data, NULL, 10) == osOK)
		{
			if(start_parsing == true)
			{
				if((data_seq == 0) && data == INTERFACE_HEADER_1) data_seq = 1; // HEADER1
				if((data_seq == 1) && (data == INTERFACE_HEADER_2)) data_seq = 2; // HEADER2
				if((data_seq == 2) && (data == INTERFACE_MID)) // MID
				{
					// Start
					data_seq = 0;
					buffer_len = 0;
					start_parsing = false;
					memset(buf,0x00,MAX_PACKET_LENGTH);
					buf[buffer_len++] = INTERFACE_HEADER_1;
					buf[buffer_len++] = INTERFACE_HEADER_2;
					buf[buffer_len++] = INTERFACE_MID;
				}
			}
			else buf[buffer_len++] = data;

			if((buffer_len >= (buf[4]+5)) && (buf[4] > 2) && (start_parsing == false))
			{
				if(RosChksumChk(buf))
				{
					switch(buf[3]) // pid
					{
						case PID_S2L_CONTROL : LED_Control_Set(buf[5],buf[6], buf[7]); break;
						default : printf("%s\r\n",buf); break;
					}
				}
				buffer_len = 0;
				start_parsing = true;
				memset(buf,0x00,MAX_PACKET_LENGTH);
			}

			if(buffer_len > MAX_PACKET_LENGTH)
			{
				buffer_len = 0;
				start_parsing = true;
				memset(buf,0x00,MAX_PACKET_LENGTH);
			}
		}
		else
		{
			// SEND

			TX_PACKET_B2B[0] = 0xFF;
			TX_PACKET_B2B[1] = 0xFF;
			TX_PACKET_B2B[2] = 0x0A;
			TX_PACKET_B2B[3] = 0x0C; // protocol defined

			TX_PACKET_B2B[4] = 8 + 1;// data + chksum
			// TOF 1
			TX_PACKET_B2B[5] = 0x00;
			TX_PACKET_B2B[6] = 0x00;
			// TOF 2
			TX_PACKET_B2B[7] = 0x00;
			TX_PACKET_B2B[8] = 0x00;

			TX_PACKET_B2B[9] = 0xDE;
			TX_PACKET_B2B[10] = 0xDE;
			TX_PACKET_B2B[11] = 0xDE;
			TX_PACKET_B2B[12] = 0xDE;
			if(gv.ultrasonic_1 != 9999)
			{
				TX_PACKET_B2B[9] = (uint8_t)((gv.ultrasonic_1 / 10 ) & 0x00FF);
				TX_PACKET_B2B[10] = (uint8_t)(((gv.ultrasonic_1 / 10 ) & 0xFF00) >> 8);

			}
			if(gv.ultrasonic_2 != 9999)
			{
				TX_PACKET_B2B[11] = (uint8_t)((gv.ultrasonic_2 / 10 ) & 0x00FF);
				TX_PACKET_B2B[12] = (uint8_t)(((gv.ultrasonic_2 / 10 ) & 0xFF00) >> 8);
			}
			TX_PACKET_B2B[13] = B2BChksumMake(TX_PACKET_B2B, 13);
			HAL_UART_Transmit(UART_INTERFACBD, TX_PACKET_B2B, 14, 100);
			osDelay(100);
		}

	}
}
