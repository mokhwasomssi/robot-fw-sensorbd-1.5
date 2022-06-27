/*
 * ultrasonic_HG_C40U.h
 *
 *  Created on: Jun 23, 2022
 *      Author: 82106
 */

#ifndef SRC_PERIPHERAL_ULTRASONIC_HG_C40U_H_
#define SRC_PERIPHERAL_ULTRASONIC_HG_C40U_H_


extern uint8_t TX_PACKET_HGC40U_Trigger[20];
extern uint8_t TX_PACKET_HGC40U_SET_UART_Trigger[20];
#define HGC40_HEADER_1 (0x02)
#define HGC40_HEADER_2 (0x5E)
#define HGC40_TAIL (0x03)

void Init_HGC40_Packet(void);
uint16_t Read_HGC40(uint8_t* rxPacket);
int Send_HGC40_Trigger(void);

extern void init_ultrasonic_hg_c40u(void);

#endif /* SRC_PERIPHERAL_ULTRASONIC_HG_C40U_H_ */
