/*
 * app_sensorboard.h
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */

#ifndef SRC_APPS_APP_SENSORBOARD_H_
#define SRC_APPS_APP_SENSORBOARD_H_

#include "_app_config.h"
#include "_typedef.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"


#include "apps_init.h"
#include "msgs.h"
#include "cmsis_os.h"

#include "interface_board.h"
#include "ultrasonic_HG_C40U.h"
#include "uart_test.h"

#include "u_timer.h"
#include "u_strings.h"
#include "u_bsp_driver.h"
// before
#include "DOT_MATRIX1.h"
#include "DOT_MATRIX2.h"

typedef enum
{
  APPS_INIT_APP,
  //APPS_ADD_SOMETING..,
  APPS_COUNT,
  APPS_NONE,
}app_id_t;

typedef struct
{
  app_id_t id;
  app_id_t prev_id;
  u32 flags;
  void (*start)(u32 param1);
  void (*stop)(void);
  void (*on_msg)(msg_t msg, u32 param1, u32 param2);
}app_t;








typedef struct
{
	bool debug_mode;
	uint16_t ultrasonic_1;
	uint16_t ultrasonic_2;

	// LED Current state
	uint8_t LED_EYE_Status;
	uint8_t LED_EYE_Action;
	uint8_t LED_Belt_Status;
	uint8_t LED_Belt_Action;
	uint8_t LED_Front_Status;
	uint8_t LED_Front_Action;

	uint8_t beltdatasentflag;
	uint8_t ring1datasentflag;
	uint8_t ring2datasentflag;
} global_volatile_t;

extern global_volatile_t gv;





extern void apps_init_app(app_t *app);
extern bool apps_start_app(app_id_t id, u32 param1);
extern bool apps_switch_app(app_id_t id, u32 param1);
extern void apps_on_msg_app(msg_t msg, u32 param1, u32 param2);


extern osThreadId_t p_ultrasonicHandle;
extern osThreadId_t p_interfaceBDHandle;
extern osThreadId_t p_uart_testHandle;






#define DBG_MSG(msg, ...) do{ \
                          if(gv.debug_mode == false) \
                            break;  \
                          printf(msg, ## __VA_ARGS__);  \
                        }while (0)
#endif /* SRC_APPS_APP_SENSORBOARD_H_ */
