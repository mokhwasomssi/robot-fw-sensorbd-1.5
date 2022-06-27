/*
 * DOT_MATRIX.h
 *
 *  Created on: Nov 5, 2021
 *      Author: Taesoo
 */
#ifndef __DOT_MATRIX0_H_
#define __DOT_MATRIX0_H_
// Replace The "#include" File Below With The CPU Relevant One For Your Board
//#include "stm32f1xx.h"

// The Number OF Separate DOT MATRIX Units (Whether Single or Cascaded) To Be Used In The Project
#define DOT_MATRIX_UNITS  1
// The Matrix Units Count Of The Longest Cascaded String In The System
#define MAX_CASCADED_NUM  1

// DOT Matrix SPI Options

// DOT Matrix Other Definitions
#define STATIC_MODE       0
#define SCROLL_MODE       1

#define DOT_BLANK (0)
#define DOT_I (1)
#define DOT_A (2)
#define DOT_M (3)
#define DOT_N (4)
#define DOT_B (5)
#define DOT_HI (6)
#define DOT_DEFAULT (7)
#define DOT_HEART (8)
#define DOT_EXCITED (9)
#define DOT_HAPPY (10)
#define DOT_BATT_FULL (11)
#define DOT_BATT_NINE (12)
#define DOT_BATT_EIGHT (13)
#define DOT_BATT_SEVEN (14)
#define DOT_BATT_SIX (15)
#define DOT_BATT_FIVE (16)
#define DOT_BATT_FOUR (17)
#define DOT_BATT_THREE (18)
#define DOT_BATT_EMPTY (19)

#endif
