/*
 * interface_board.c
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */

#include "app_sensorboard.h"

extern osMessageQueueId_t queue_interfaceBDHandle;
extern osMessageQueueId_t queue_debug_testHandle;

uint8_t TX_PACKET_B2B[256];
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void init_p_interfaceboard(void)
{
	Uart_Init_Custom(&huart4);
	osThreadResume (p_interfaceBDHandle);
}

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


void p_interfaceBD_task(void *argument)
{
	//uint8_t data_seq = 0;
	u8 data;
	osMessageQueueReset(queue_interfaceBDHandle);

	while(1)
	{
		if(osMessageQueueGet(queue_interfaceBDHandle, &data, NULL, 10) == osOK)
		{
			// B2B Read Process..... to do ....
//			if(data == HGC40_HEADER_1) data_seq1 = 1; // HEADER1
//			else if((data_seq1 == 1) && (data == HGC40_HEADER_2))
//			{
//				data_seq1 = 2; // HEADER2
//				rx_buf1_len = 0;
//				memset(rx_buf1, 0x00, 10);
//			}
//			else if(data_seq1 == 2)
//			{
//				if(data == HGC40_TAIL)
//				{
//					if(rx_buf1_len < 6) sensor1.m_fail_cnt = 0;
//					if(rx_buf1_len == 4)
//						gv.ultrasonic_1 = (rx_buf1[0] - '0') * 1000
//									+ (rx_buf1[1] - '0') * 100
//									+ (rx_buf1[2] - '0') * 10
//									+ (rx_buf1[3] - '0');
//					else if(rx_buf1_len == 3)
//						gv.ultrasonic_1 = (rx_buf1[0] - '0') * 100
//									+ (rx_buf1[1] - '0') * 10
//									+ (rx_buf1[2] - '0');
//					else if(rx_buf1_len == 2)
//						gv.ultrasonic_1 = (rx_buf1[0] - '0') * 10
//									+ (rx_buf1[1] - '0');
//					else if(rx_buf1_len == 1)
//						gv.ultrasonic_1 = (rx_buf1[0] - '0');
//					else gv.ultrasonic_1 = 9999;
//				}
//				else rx_buf1[rx_buf1_len++] = data;
//			}
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
			HAL_UART_Transmit(&huart3, TX_PACKET_B2B, 14, 100);
			osDelay(100);
		}

	}
}
