/*
 * TIMER.c
 *
 *  Created on: 26 de oct. de 2018
 *      Author: root
 */

#include "TIMER.h"


void TIMER_Init(uint8_t channel,uint32_t matchVal)
{
	/* Enable timer 1 clock */
		Chip_TIMER_Init(LPC_TIMER2);
	/* Timer setup for match and interrupt at TICKRATE_HZ */
		Chip_TIMER_Reset(LPC_TIMER2); 				//Resets the timer terminal and prescale counts to 0.

		Chip_TIMER_MatchEnableInt(LPC_TIMER2, channel);	     //Enables a match interrupt that fires

		Chip_TIMER_SetMatch(LPC_TIMER2, channel, matchVal); //Sets a timer match value.

		Chip_TIMER_ResetOnMatchEnable(LPC_TIMER2, channel); //For the specific match counter,
													        //enables reset of the terminal count register when a match occurs
		NVIC_ClearPendingIRQ(TIMER2_IRQn);

}
/*****************************************************************************
 * Public functions
 ****************************************************************************/

/**
 * @brief	Handle interrupt from 32-bit timer
 * @return	Nothing
 */
void TIMER2_IRQHandler(void)
{
	portBASE_TYPE pTIMER = pdFALSE;

	if (Chip_TIMER_MatchPending(LPC_TIMER2, 2))
	{
	Chip_TIMER_ClearMatch(LPC_TIMER2,2);
	flag_timer = FALSE;
	}

	portEND_SWITCHING_ISR( pTIMER );
}


