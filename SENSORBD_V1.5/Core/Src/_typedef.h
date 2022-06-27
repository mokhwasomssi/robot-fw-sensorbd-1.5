/*
 * _typedef.h
 *
 *  Created on: Jun 22, 2022
 *      Author: 82106
 */

#ifndef SRC__TYPEDEF_H_
#define SRC__TYPEDEF_H_

#include <stdio.h>

#define nop() __asm("nop")
#define null (void *)0
#define _critical_start()   taskENTER_CRITICAL()
#define _critical_exit()    taskEXIT_CRITICAL()
#define restart_system()    NVIC_SystemReset()

typedef unsigned char  u8;
typedef signed char    s8;

typedef unsigned short u16;
typedef signed short   s16;

typedef unsigned long  u32;
typedef signed long    s32;

typedef void (*event_handler_t)(u32 msg, u32 param1);
typedef void (*callback_handler_t)(u32 param1, u32 param2, u32 param3);
typedef void (*on_click_t)(void);

typedef enum
{
  false = 0,
  true  = 1
}bool;


typedef struct
{
  u8 tick;
  u8 period;
}tim_t;

#define FLAGS_ADD(x, y)     ((x) |= (y))
#define FLAGS_CLEAR(x, y)   ((x) &= (~(y)))
#define FLAGS_CHECK(x, y)   ((x) & (y))

#define BITSET(var, i)      ((var) |= (1 << (i)))
#define BITUNSET(var, i)    ((var) &= ~(1 << (i)))
#define BITISSET(var, i)    ((var) & (1 << (i)))

#define BIT_CHECK(var, i)    (((var) & (1 << (i))) >> (i))

// Bit control type
typedef union {
	uint8_t val;
	struct {
		uint8_t b0 : 1;        // LSB
		uint8_t b1 : 1;
		uint8_t b2 : 1;
		uint8_t b3 : 1;
		uint8_t b4 : 1;
		uint8_t b5 : 1;
		uint8_t b6 : 1;
		uint8_t b7 : 1;        // MSB
	};
} _8BITs;

typedef union {
	uint16_t val;
	struct {
		_8BITs _8L;                        // LSB
		_8BITs _8H;                        // MSB
	};
	uint8_t bytes[2];
} _16BITs;

typedef union {
	uint32_t val;
	struct {
		_16BITs _16L;                        // LSB
		_16BITs _16H;                        // MSB
	};
	uint8_t bytes[4];
} _32BITs;


#endif /* SRC__TYPEDEF_H_ */
