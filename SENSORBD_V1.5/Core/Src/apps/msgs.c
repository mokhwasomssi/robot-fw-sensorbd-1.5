/*
 * mesgs.h
 *
 *  Created on: Jun 22, 2022
 *      Author: sangjun
 */



#include "../_typedef.h"
#include "msgs.h"

#define MSGS_QUEUE_LEN (64)
static msgs_t g_msgs_queue[MSGS_QUEUE_LEN]={MSG_NONE};
static u8 g_msgs_queue_head = 0;
static u8 g_msgs_queue_tail = 0;

/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void msgs_clear_msg(void)
{
  g_msgs_queue_head = 0;
  g_msgs_queue_tail = 0;
}
/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
void msgs_set_msg(msg_t msg, u32 param1, u32 param2)
{
  g_msgs_queue[g_msgs_queue_head].msg = msg;
  g_msgs_queue[g_msgs_queue_head].param1 = param1;
  g_msgs_queue[g_msgs_queue_head].param2 = param2;

  g_msgs_queue_head++;

  if(g_msgs_queue_head >= MSGS_QUEUE_LEN)
    g_msgs_queue_head = 0;
}


/**
********************************************************************************************************************************
********************************************************************************************************************************
*/
bool msgs_get_msg(msg_t *msg, u32 *param1, u32 *param2)
{
  if(g_msgs_queue_head == g_msgs_queue_tail)
    return false;

  *msg = g_msgs_queue[g_msgs_queue_tail].msg;
  *param1 = g_msgs_queue[g_msgs_queue_tail].param1;
  *param2 = g_msgs_queue[g_msgs_queue_tail].param2;

  g_msgs_queue_tail++;

  if(g_msgs_queue_tail >= MSGS_QUEUE_LEN)
    g_msgs_queue_tail = 0;

  return true;
}

