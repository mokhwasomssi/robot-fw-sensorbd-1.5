/*
 * mesgs.h
 *
 *  Created on: Jun 22, 2022
 *      Author: sangjun
 */


#ifndef APPS_MSGS_H_
#define APPS_MSGS_H_

typedef enum
{
  MSG_NONE = 0x00,
  // to do message something like belows..
  MSG_SEND_INFO_TO_IBD,
  MSG_SEND_ULTEASONIC_VALUE,

  MSG_MAX_COUNT,
}msg_t;

typedef struct
{
  msg_t msg;
  u32 param1;
  u32 param2;
}msgs_t;

extern void msgs_clear_msg(void);
extern void msgs_set_msg(msg_t msg, u32 param1, u32 param2);
extern bool msgs_get_msg(msg_t *msg, u32 *param1, u32 *param2);

#endif /* APPS_MSGS_H_ */
