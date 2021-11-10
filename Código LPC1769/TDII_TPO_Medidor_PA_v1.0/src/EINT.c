/*
 * EINT.c
 *
 *  Created on: 1 de dic. de 2018
 *      Author: root
 */

#include "EINT.h"


/*Pulsador ON/OFF Transmisión de Datos
*EINT3 -> P2[13]
*/

/* Pulsador Selector de WIFI/BT
 *
 * EINT2 -> P2[12]
 *
 */

void EINT_Init(void)
{
	Chip_IOCON_PinMux(LPC_IOCON,2,12,IOCON_MODE_INACT,1); //BOTON WIFI/BT
	Chip_IOCON_PinMux(LPC_IOCON,2,13,IOCON_MODE_INACT,1); //BOTON  ON/OFF Transmisión de Datos

	// Limpio flags y seteo valores por defecto de los registros
	EXTINT = 0x00;	// (recomendado en el Manual de Usuario)
	EXTMODE = 0x00;
	EXTPOLAR = 0X00;

	// Configuro el modo de interrupción de EINT3
	EINT_SetMode(EINT3, EXTMODE_FLANCO);
	EINT_SetMode(EINT2, EXTMODE_FLANCO);

	// Configuro la polaridad para EINT3
	EINT_SetPolarity(EINT3, EXTPOLAR_ACTIVO_BAJO_O_DESCENDENTE);
	EINT_SetPolarity(EINT2, EXTPOLAR_ACTIVO_BAJO_O_DESCENDENTE);

	// Vuelvo a limpiar los flags luego de configurar modo y polaridad
	EXTINT = 0x0F;	// (recomendado en el Manual de Usuario)
	// Habilito la interrupción de EINT3

	NVIC_EnableIRQ(EINT2_IRQn);
	NVIC_EnableIRQ(EINT3_IRQn);

}


void EINT3_IRQHandler(void)
{

	static uint8_t On_off_transmision = FALSE;
	portBASE_TYPE pEINT3 = pdFALSE;

	if (On_off_transmision)
		On_off_transmision = FALSE;
	else
		On_off_transmision = TRUE;

	xQueueSendFromISR(xON_OFF, &On_off_transmision, &pEINT3);

	CLEAR_INTERRUPT(EINT3);
	portEND_SWITCHING_ISR( pEINT3 );

}


void EINT2_IRQHandler(void)
{
	portBASE_TYPE pEINT2 = pdFALSE;

	if (bluetooth)
	{
		bluetooth = FALSE;
		wifi = TRUE;
	}
	else
	{
		bluetooth = TRUE;
		wifi = FALSE;
	}

	CLEAR_INTERRUPT(EINT2);
	portEND_SWITCHING_ISR( pEINT2 );

}


/********************************************************************************
	\fn  		void EINT_SetMode(void)
	\brief 		Setea el modo para el pin de Interrupción Externa.
	\param[in]	EINTx	 línea de Interrupción Externa:
 				- EINT0: interrupción externa 0
 				- EINT1: interrupción externa 1
 				- EINT2: interrupción externa 2
 				- EINT3: interrupción externa 3
 	 \param[in]	modo 	modo de interrupción:
 				- EXTMODE_NIVEL
 				- EXTMODE_FLANCO
	\return		void
 */
void EINT_SetMode(uint8_t EINTx, uint8_t modo)
{
	if( modo == EXTMODE_FLANCO )
	{
		EXTMODE |= ( 1 << EINTx );
	}
	else if( modo == EXTMODE_NIVEL )
	{
		EXTMODE &= ~( 1 << EINTx );
	}
}

/********************************************************************************
	\fn  		void EINT_SetPolarity(void)
	\brief 		Setea el modo para el pin de Interrupción Externa.
	\param[in]	EINTx	 línea de Interrupción Externa:
 				- EINT0: interrupción externa 0
 				- EINT1: interrupción externa 1
 				- EINT2: interrupción externa 2
 				- EINT3: interrupción externa 3
 	 \param[in]	modo 	polaridad de interrupción:
 				- EXTPOLAR_ACTIVO_BAJO_O_DESCENDENTE
 				- EXTPOLAR_ACTIVO_ALTO_O_ASCENDENTE
	\return		void
 */
void EINT_SetPolarity(uint8_t EINTx, uint8_t polaridad)
{
	if( polaridad == EXTPOLAR_ACTIVO_ALTO_O_ASCENDENTE )
	{
		EXTPOLAR |= ( 1 << EINTx );
	}
	else if( polaridad == EXTPOLAR_ACTIVO_BAJO_O_DESCENDENTE )
	{
		EXTPOLAR &= ~( 1 << EINTx );
	}
}

