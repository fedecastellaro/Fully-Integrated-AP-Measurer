/*
 * ADC.c
 *
 *  Created on: 30 de nov. de 2018
 *      Author: root
 */


#include "ADC.h"

uint16_t datoadc0=0,datoadc1=0;


void ADC_Init(void)
{
	////////init adc//////////////////////////////////////////////////////////
		struct ADC_CLOCK_SETUP_T configadc;

		Chip_IOCON_PinMux(LPC_IOCON, CHANNEL_4,IOCON_MODE_INACT,IOCON_FUNC3);

		Chip_IOCON_PinMux(LPC_IOCON, 0,25,IOCON_MODE_INACT,IOCON_FUNC0);
		Chip_GPIO_SetPinDIROutput(LPC_GPIO, 0, 25);

		Chip_ADC_Init (LPC_ADC, &configadc);
	    Chip_ADC_SetStartMode(LPC_ADC, ADC_START_NOW, ADC_TRIGGERMODE_RISING);
		Chip_ADC_SetSampleRate(LPC_ADC, &configadc, 2500);
		Chip_ADC_SetBurstCmd(LPC_ADC, ENABLE);
		Chip_ADC_EnableChannel(LPC_ADC, ADC_CH4 , ENABLE);
}

void Enable_ConvNInterrupt(void)
{
	NVIC_EnableIRQ(_LPC_ADC_IRQ);
	Chip_ADC_Int_SetChannelCmd(_LPC_ADC_ID, _ADC_CH, ENABLE);
}

 void ADC_IRQHandler(void)
 {
	 uint16_t ADC_valor=0;

 	portBASE_TYPE pADC = pdFALSE;

 	//////////////leo valor de los adc//////////////////////////////////////
 		if(Chip_ADC_ReadStatus(LPC_ADC,ADC_CH4, ADC_DR_DONE_STAT) != SET);
 			{
 			Chip_ADC_ReadValue(LPC_ADC,ADC_CH4, &ADC_valor);

 			xSemaphoreTakeFromISR  (xSignal,&pADC);
 			xQueueSendToBackFromISR(xDato_ADC, &ADC_valor, &pADC); //se va a bloquear hasta que la task de grafico levante esto
 			xSemaphoreGiveFromISR  (xSignal, &pADC);

 			}

 			portEND_SWITCHING_ISR( pADC );

 }
