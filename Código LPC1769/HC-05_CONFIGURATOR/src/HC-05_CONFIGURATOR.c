/*
===============================================================================
 Name        : Ex_UartRB_FreeRtosv3.c
 Author      : $(author)
 Version     : 2
 Copyright   : $(copyright)
 Description : UART interrupt example using BaseBoard Layer and FreeRtos
===============================================================================
*/
/* FreeRTOS.org includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "chip.h"
#include "semphr.h"
#include "queue.h"
#include <cr_section_macros.h>

/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/
#define RX_UART0	0,3
#define TX_UART0	0,2
#define BAUDRATE_UART0	38400

#define BAUDRATE_UART3	38400
//#define BAUDRATE_UART3	9600

#define RX_UART3	0,26
#define TX_UART3	0,25
#define ENABLE_BT	0,27
#define STATE_BT	0,24

#define LPCP0 				LPC_GPIO

/*****************************************************************************
 * Public types/enumerations/variables
 ****************************************************************************/
xQueueHandle xQueue;
xQueueHandle xQueue2;

/*****************************************************************************
 * Private functions
 ****************************************************************************/
/*****************************************************************************
 * Public functions
 ****************************************************************************/



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


static void prvSetupHardware(void)
{
   /* Generic Initialization */
	SystemCoreClockUpdate();
	Board_Init();
	Bluethooth_Init();
}


void UART3_IRQHandler(void)
{
	uint8_t rx_aux;
	portBASE_TYPE xHigherPriorityTaskWoken = pdFALSE;
	if(Chip_UART_ReadLineStatus(LPC_UART3) & UART_LSR_RDR)
		rx_aux = Board_UARTGetChar(LPC_UART3);
		Board_UARTPutChar(LPC_UART3,rx_aux);
		printf("%c",(char)rx_aux); //(BT--->LPC)
																//(LPC--->PC)
	portEND_SWITCHING_ISR( xHigherPriorityTaskWoken );
}


/*-----------------------------------------------------------*/


void Task_UART3( void *pvParameters ) //PARA LO UNICO QUE SIRVE ESTA TASK ES PARA
									//ENVIAR EL MENSAJE INICIAL Y CONFIRMAR SI LA COM DE LPC A PC FUNCA
{

	//BT ADRRESS= 98d3,31,7029ce
	//BT COMPU = 98d3,34,90bf2d
	for( ;; )
	{
	/*	Board_UARTPutSTR(LPC_UART3,"AT\r\n"); //DUMMY STRING ( NECESARIO )
		Board_UARTPutSTR(LPC_UART3,"AT+ORGL\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+RMAAD\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+UART=38400,1,0\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+PSWD=4444\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+BIND=98d3,34,90bf2d\r\n");


		Board_UARTPutSTR(LPC_UART3,"AT+CMODE=0\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+ROLE=1\r\n");

*/
		uint8_t i;
		char a;
while(1)
{
	//	Board_UARTPutChar(LPC_UART3,'#');

	//	Board_UARTPutSTR(LPC_UART3,"\r\n");


}


//COMMANDS
		/*
		Board_UARTPutSTR(LPC_UART3,"AT+ORGL\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+IAC=9e8b3f\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+INQM=1,9,48\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+CLASS=0\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+FSAD=d436,39,de7c70\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+BIND=d436,39,de7c70\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+LINK=d436,39,de7c70\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+RMAAD\r\n");


		Board_UARTPutSTR(LPC_UART3,"AT+UART=38400,1,0\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+UART?\r\n");

		Board_UARTPutSTR(LPC_UART3,"AT+PSWD=4444\r\n");
		Board_UARTPutSTR(LPC_UART3,"AT+ROLE=1\r\n");
		 */
while(1);
		//Board_UARTPutSTR(LPC_UART3,"AT+BIND=d436,39,de7c70\r\n");
	}

}


/*-----------------------------------------------------------*/
int main( void )
{

	prvSetupHardware();

		xTaskCreate( Task_UART3, "Handler_Uart3tx", configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) NULL);

		/* Start the scheduler so the created tasks start executing. */
		vTaskStartScheduler();

	return 0;
}

/*-----------------------------------------------------------*/

void vApplicationMallocFailedHook( void )
{
	/* This function will only be called if an API call to create a task, queue
	or semaphore fails because there is too little heap RAM remaining. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( xTaskHandle *pxTask, signed char *pcTaskName )
{
	/* This function will only be called if a task overflows its stack.  Note
	that stack overflow checking does slow down the context switch
	implementation. */
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* This example does not use the idle hook to perform any processing. */
}
/*-----------------------------------------------------------*/

void vApplicationTickHook( void )
{
	/* This example does not use the tick hook to perform any processing. */
}
