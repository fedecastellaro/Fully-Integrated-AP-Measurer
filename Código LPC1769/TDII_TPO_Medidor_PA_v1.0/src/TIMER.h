/*
 * TIMER.h
 *
 *  Created on: 26 de oct. de 2018
 *      Author: root
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "FreeRTOS.h"
#include "board.h"

#define LED_BOARD	0,22
#define LPCP0 		LPC_GPIO

#define 	SEG_1			25000000
#define 	TIMER_MATCH_2	2

extern uint8_t flag_timer;



void TIMER_Init(uint8_t channel,uint32_t matchVal);
void TIMER2_IRQHandler(void);

#endif /* TIMER_H_ */
