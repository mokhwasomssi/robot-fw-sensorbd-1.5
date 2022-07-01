/*
 * ultrasonic_HG_C40U.c
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */

#include "app_sensorboard.h"

typedef struct
{
  u16 distance_cm;
  bool m_state;
  u8 m_fail_cnt;
}hg_c40u;

uint8_t TX_PACKET_HGC40U_Trigger[20];
uint8_t TX_PACKET_HGC40U_SET_UART_Trigger[20];


static hg_c40u sensor1 ={0,false,0,};
static hg_c40u sensor2 ={0,false,0,};

extern osMessageQueueId_t queue_ultrasonic1Handle;
extern osMessageQueueId_t queue_ultrasonic2Handle;

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void init_ultrasonic_hg_c40u(void)
{

	TX_PACKET_HGC40U_Trigger[0] = 0x02;
	TX_PACKET_HGC40U_Trigger[1] = '#';
	TX_PACKET_HGC40U_Trigger[2] = 'T';
	TX_PACKET_HGC40U_Trigger[3] = 'r';
	TX_PACKET_HGC40U_Trigger[4] = 'i';
	TX_PACKET_HGC40U_Trigger[5] = 'g';
	TX_PACKET_HGC40U_Trigger[6] = 'g';
	TX_PACKET_HGC40U_Trigger[7] = 'e';
	TX_PACKET_HGC40U_Trigger[8] = 'r';
	TX_PACKET_HGC40U_Trigger[9] = 0x03;

	TX_PACKET_HGC40U_SET_UART_Trigger[0] = 0x02;
	TX_PACKET_HGC40U_SET_UART_Trigger[1] = '#';
	TX_PACKET_HGC40U_SET_UART_Trigger[2] = 'M';
	TX_PACKET_HGC40U_SET_UART_Trigger[3] = 'o';
	TX_PACKET_HGC40U_SET_UART_Trigger[4] = 'd';
	TX_PACKET_HGC40U_SET_UART_Trigger[5] = 'e';
	TX_PACKET_HGC40U_SET_UART_Trigger[6] = '|';
	TX_PACKET_HGC40U_SET_UART_Trigger[7] = '1';
	TX_PACKET_HGC40U_SET_UART_Trigger[8] = 0x03;


	Uart_Init_Custom(&huart2);
	Uart_Init_Custom(&huart3);

	HAL_UART_Transmit(&huart2, TX_PACKET_HGC40U_Trigger, 9, 100);
	HAL_UART_Transmit(&huart3, TX_PACKET_HGC40U_Trigger, 9, 100);

	osDelay(1000);

	HAL_UART_Transmit(&huart2, TX_PACKET_HGC40U_Trigger, 9, 100);
	HAL_UART_Transmit(&huart3, TX_PACKET_HGC40U_Trigger, 9, 100);
	osThreadResume (p_ultrasonicHandle);


}




uint8_t rx_buf1[10];
uint8_t rx_buf2[10];
uint8_t rx_buf1_len;
uint8_t rx_buf2_len;
void p_ultrasonic_task(void *argument)
{
	uint8_t data_seq1 = 0;
	uint8_t data_seq2 = 0;

	uint8_t sensor_idx = 0;
	u8 data;
	osMessageQueueReset(queue_ultrasonic1Handle);
	osMessageQueueReset(queue_ultrasonic2Handle);

	while(1)
	{
		if(osMessageQueueGet(queue_ultrasonic1Handle, &data, NULL, 10) == osOK)
		{
			if(data == HGC40_HEADER_1) data_seq1 = 1; // HEADER1
			else if((data_seq1 == 1) && (data == HGC40_HEADER_2))
			{
				data_seq1 = 2; // HEADER2
				rx_buf1_len = 0;
				memset(rx_buf1, 0x00, 10);
			}
			else if(data_seq1 == 2)
			{
				if(data == HGC40_TAIL)
				{
					if(rx_buf1_len < 6) sensor1.m_fail_cnt = 0;
					if(rx_buf1_len == 4)
						gv.ultrasonic_1 = (rx_buf1[0] - '0') * 1000
									+ (rx_buf1[1] - '0') * 100
									+ (rx_buf1[2] - '0') * 10
									+ (rx_buf1[3] - '0');
					else if(rx_buf1_len == 3)
						gv.ultrasonic_1 = (rx_buf1[0] - '0') * 100
									+ (rx_buf1[1] - '0') * 10
									+ (rx_buf1[2] - '0');
					else if(rx_buf1_len == 2)
						gv.ultrasonic_1 = (rx_buf1[0] - '0') * 10
									+ (rx_buf1[1] - '0');
					else if(rx_buf1_len == 1)
						gv.ultrasonic_1 = (rx_buf1[0] - '0');
					else gv.ultrasonic_1 = 9999;
				}
				else rx_buf1[rx_buf1_len++] = data;
			}
		}
		else if(osMessageQueueGet(queue_ultrasonic2Handle, &data, NULL, 10) == osOK)
		{
			if(data == HGC40_HEADER_1) data_seq2 = 1; // HEADER1
			else if((data_seq2 == 1) && (data == HGC40_HEADER_2))
			{
				data_seq2 = 2; // HEADER2
				rx_buf2_len = 0;
				memset(rx_buf2, 0x00, 10);
			}
			else if(data_seq2 == 2)
			{
				if(data == HGC40_TAIL)
				{
					if(rx_buf2_len < 6) sensor2.m_fail_cnt = 0;
					if(rx_buf2_len == 4)
						gv.ultrasonic_2 = (rx_buf2[0] - '0') * 1000
									+ (rx_buf2[1] - '0') * 100
									+ (rx_buf2[2] - '0') * 10
									+ (rx_buf2[3] - '0');
					else if(rx_buf2_len == 3)
						gv.ultrasonic_2 = (rx_buf2[0] - '0') * 100
									+ (rx_buf2[1] - '0') * 10
									+ (rx_buf2[2] - '0');
					else if(rx_buf2_len == 2)
						gv.ultrasonic_2 = (rx_buf2[0] - '0') * 10
									+ (rx_buf2[1] - '0');
					else if(rx_buf2_len == 1)
						gv.ultrasonic_2 = (rx_buf2[0] - '0');
					else gv.ultrasonic_2 = 9999;
				}
				else rx_buf2[rx_buf2_len++] = data;
			}
		}
		else
		{
			if(sensor_idx % 2 == 0)
			{
				HAL_UART_Transmit(&huart2, TX_PACKET_HGC40U_Trigger, 10, 10);
				sensor1.m_fail_cnt++;
				if(sensor1.m_fail_cnt > 3 )
				{
					HAL_UART_DeInit(&huart2);
					HAL_UART_Init(&huart2);
					Uart_Init_Custom(&huart2);
					gv.ultrasonic_1 = 9999;
				}
			}
			else
			{
				HAL_UART_Transmit(&huart3, TX_PACKET_HGC40U_Trigger, 10, 10);
				sensor2.m_fail_cnt++;
				if(sensor2.m_fail_cnt > 3 )
				{
					HAL_UART_DeInit(&huart3);
					HAL_UART_Init(&huart3);
					Uart_Init_Custom(&huart3);
					gv.ultrasonic_2 = 9999;

				}
			}
			sensor_idx++;
			if(sensor_idx > 1) sensor_idx = 0;
			osDelay(10);
		}

	}
}



