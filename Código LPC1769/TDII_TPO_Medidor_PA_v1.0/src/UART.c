/*
 * UART.c
 *
 *  Created on: 28 de nov. de 2018
 *      Author: root
 */

//-----------------------------------------------------------------------------

#include "UART.h"


void UART3_Init(void)
{
	Board_UART_Init(LPC_UART3,BAUDRATE_UART3);
	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_UART3, (UART_IER_RBRINT | UART_IER_RLSINT));
	NVIC_EnableIRQ(UART3_IRQn);
}


void Bluethooth_Init (void)
{
	Chip_IOCON_PinMux(LPC_IOCON, ENABLE_BT, IOCON_MODE_PULLDOWN, IOCON_FUNC0);//uart2 al modulito
	Chip_IOCON_PinMux(LPC_IOCON, STATE_BT , IOCON_MODE_PULLDOWN, IOCON_FUNC0);

	Chip_IOCON_PinMux(LPC_IOCON, TX_UART3,IOCON_MODE_INACT, 3);//uart2 al modulito
	Chip_IOCON_PinMux(LPC_IOCON, RX_UART3,IOCON_MODE_INACT, 3);

	Chip_GPIO_SetPinDIRInput(LPCP0, ENABLE_BT);
	Chip_GPIO_SetPinDIRInput(LPCP0, STATE_BT);

	UART3_Init();

}

void UART3_IRQHandler(void)
{
	uint8_t rx_aux;
	portBASE_TYPE xPUart3 = pdFALSE;
	if(Chip_UART_ReadLineStatus(LPC_UART3) & UART_LSR_RDR)
		{
		rx_aux = Board_UARTGetChar(LPC_UART3);
		//printf ("%c",rx_aux);
	    //Board_UARTPutChar(LPC_UART2,rx_aux);
		}
	portEND_SWITCHING_ISR( xPUart3 );
}

void tx_bluetooth ( uint16_t adc_valor)
{
	uint8_t tx[2];
	uint16_t aux;
	aux = adc_valor;
	tx[0] = aux & 0xFF;		 //BYTE Menos significativo
	tx[1] = (aux >> 8) & 0xFF; //BYTE Mas significativo

	Board_UARTPutChar(LPC_UART3,'$');
	Board_UARTPutChar(LPC_UART3, tx[1]);
	Board_UARTPutChar(LPC_UART3, tx[0]);
}


void WIFI_Init(void)
{
	Chip_IOCON_PinMux(LPC_IOCON, RESET_WIFI, IOCON_MODE_PULLDOWN, IOCON_FUNC0);
	Chip_IOCON_PinMux(LPC_IOCON, POWER_DOWN_WIFI , IOCON_MODE_PULLDOWN, IOCON_FUNC0);

	Chip_IOCON_PinMux(LPC_IOCON, TX_UART2,IOCON_MODE_INACT, 1);
	Chip_IOCON_PinMux(LPC_IOCON, RX_UART2,IOCON_MODE_INACT, 1);

	Chip_GPIO_SetPinDIROutput(LPCP0, RESET_WIFI);
	Chip_GPIO_SetPinDIROutput(LPCP0, POWER_DOWN_WIFI);

	Chip_GPIO_WritePortBit (LPCP0,RESET_WIFI, TRUE);
	Chip_GPIO_WritePortBit (LPCP0,POWER_DOWN_WIFI, TRUE);

	UART2_Init();

	Chip_GPIO_WritePortBit (LPCP0,RESET_WIFI, FALSE);


}

void UART2_Init(void)
{
	Board_UART_Init(LPC_UART2,BAUDRATE_UART2);
	/* Enable receive data and line status interrupt */
	Chip_UART_IntEnable(LPC_UART2, (UART_IER_RBRINT | UART_IER_RLSINT));
	NVIC_EnableIRQ(UART2_IRQn);

}

void UART2_IRQHandler(void)
{
	uint8_t rx_aux;
	portBASE_TYPE xPUart2 = pdFALSE;
	if(Chip_UART_ReadLineStatus(LPC_UART2) & UART_LSR_RDR)
		{
		rx_aux = Board_UARTGetChar(LPC_UART2);
		//printf ("%c",rx_aux);
	    //Board_UARTPutChar(LPC_UART3,rx_aux);
		}
	portEND_SWITCHING_ISR( xPUart2 );
}

