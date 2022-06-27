/*
 * uart_test.c
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */


#include "app_sensorboard.h"

#define MAX_CONFIG_LENGTH         (512)
u8 buffer[MAX_CONFIG_LENGTH];
u8 buffer_len=0;
#define STR_DEBUG_MODE_ON         "DEBUGON"
#define STR_DEBUG_MODE_OFF	 	  "DEBUGOFF"

#define STR_FRONTLIGHT_ON         "FRONTON"
#define STR_FRONTLIGHT_OFF	 	  "FRONTOFF"



extern osMessageQueueId_t queue_debug_testHandle;

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void init_p_uart_test(void)
{
	Uart_Init_Custom(&huart6); // DBG TEST
	osThreadResume (p_uart_testHandle);
}



void p_uart_test_task(void *argument)
{
	bool is_arrival_packet = false;
	u8 data;
	memset(buffer, 0x00, MAX_CONFIG_LENGTH);

	osMessageQueueReset(queue_debug_testHandle);

	while(1)
	{
		if(osMessageQueueGet(queue_debug_testHandle, &data, NULL, 100) == osOK)
		{
			if(data == '[')
			{
				buffer_len = 0;
				is_arrival_packet = false;
				memset(buffer, 0x00, MAX_CONFIG_LENGTH);
			}
			else if(data == ']') is_arrival_packet = true;
			else buffer[buffer_len++] = data;

		    if((is_arrival_packet == true) && (buffer_len > 4))
			{
		        if (strncmp((char *)buffer, STR_DEBUG_MODE_ON, strlen(STR_DEBUG_MODE_ON)) == 0) gv.debug_mode = true;
		        else if (strncmp((char *)buffer, STR_DEBUG_MODE_OFF, strlen(STR_DEBUG_MODE_OFF)) == 0) gv.debug_mode = false;
		        else if (strncmp((char *)buffer, STR_FRONTLIGHT_ON, strlen(STR_FRONTLIGHT_ON)) == 0) FrontLight_SetPWM(FRONTLIGHTON);
		        else if (strncmp((char *)buffer, STR_FRONTLIGHT_OFF, strlen(STR_FRONTLIGHT_OFF)) == 0) FrontLight_SetPWM(FRONTLIGHTOFF);
		        else printf("command not found\r\n");

				buffer_len = 0;
				memset(buffer, 0x00, MAX_CONFIG_LENGTH);
				is_arrival_packet = false;
			}
			if(buffer_len > MAX_CONFIG_LENGTH) buffer_len = 0;
		}
		else osDelay(100);
	}
}
