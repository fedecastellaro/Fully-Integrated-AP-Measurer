/*
===============================================================================
 Name        : ADC ANDANDO
 Author      :
 Version     :
 Copyright   :)
 Description :
===============================================================================
*/

#include "stdio.h"
#include "ILI9340.h"
#include "UART.h"
#include "ADC.h"
#include "EINT.h"
#include "TIMER.h"
#include "PULSO.h"
#include "presentacion.h"

#define	WINDOW_SIZE	200

#define GRILLA 		ENABLE
#define OFFSET 		1
#define ESCALA_X	1.1
#define ESCALA_Y	1.1


uint8_t flag_timer = TRUE;

uint8_t wifi = FALSE;
uint8_t bluetooth = TRUE;

xSemaphoreHandle xSemaforo;

xQueueHandle xQueue_TFT;
xQueueHandle xON_OFF;

TaskHandle_t xHandler_ADC;


//DEFINO LAS TAREAS
void static ADC_Filter   (void)
{
	uint16_t ADC_valor = 0;

	uint16_t datoadc4  = 0;

	static uint32_t 	circularBuffer[WINDOW_SIZE] = {0};   //circular buffer
	static uint32_t		*circularBufferAccessor 	= circularBuffer; //actual value
	static uint32_t		sum 						= 0;
	//const  uint32_t 	*circularBufferStart		= &circularBuffer[0]; // constant pointer -> start buff
	static const  uint32_t 	*circularBufferEnd		= &circularBuffer[WINDOW_SIZE]; // constant pointer -> end buff


	for(;;)
	{
		if(uxQueueMessagesWaiting(xDato_ADC) != pdFALSE)//se fija si hay algo, si no, da semaforo
			{

				xSemaphoreTake(xSignal,portMAX_DELAY);//mutex
				xQueueReceive(xDato_ADC,&datoadc4,0);
				xSemaphoreGive(xSignal);

				sum -= *circularBufferAccessor;
				sum += datoadc4;

				*circularBufferAccessor = datoadc4;
				circularBufferAccessor++;

				if (circularBufferAccessor == circularBufferEnd )
					circularBufferAccessor = circularBuffer;

				ADC_valor = ( sum / WINDOW_SIZE );

				////TRASMITO DATOS////

				if (xSemaphoreTake(xSemaforo,portMAX_DELAY) != pdFALSE){
				 xQueueOverwrite( xQueue_TFT, &ADC_valor); //se va a bloquear hasta que la task de grafico levante esto
				 xSemaphoreGive(xSemaforo);
				}
			}

	}
//////////////////////////////////////////////////////////////////////////

}//fin de task

void static TFT_Graph    (void)
{
	uint16_t valor_adc 		= 0;

	 volatile int x_actual   =1;
	 volatile int x_anterior =0;
	 volatile int y_actual   =0;
	 volatile int y_anterior =0;

	  NVIC_EnableIRQ(ADC_IRQn);
	  Chip_ADC_Int_SetChannelCmd(LPC_ADC, ADC_CH4, ENABLE);

	for (;;)
	{
		if(uxQueueMessagesWaiting(xQueue_TFT) != pdFALSE)
		{
		xSemaphoreTake(xSemaforo,0);
		xQueueReceive(xQueue_TFT,&valor_adc,0);
		xSemaphoreGive(xSemaforo);

		y_actual = 205-0.09*valor_adc;//esto es asi pues el (0,0) esta arriba de todo a la izq. Se cuenta desde el eje de abajo que es y=230

	    grilla();


		 if (x_actual == 1 )
		 {
			 fillRect(OFFSET, 100, 2, 134, ILI9340_BLACK);//offset de +5 por el eje
			 drawLine(OFFSET, 230, (x_actual+OFFSET), y_actual, ILI9340_WHITE);//offset de +5 por el eje
			 drawLine(OFFSET, 230, (x_actual+OFFSET), y_actual, ILI9340_WHITE);//offset de +5 por el eje
		 }

		 else
		 {
			 if (x_actual == 317)
				 fillRect(x_actual+OFFSET, 100, 1, 134, ILI9340_BLACK);//offset de +5 por el eje
			 else
				 fillRect(x_actual+OFFSET, 100, 2, 134, ILI9340_BLACK);//offset de +5 por el eje

			 drawLine((x_anterior+OFFSET),y_anterior, (x_actual+OFFSET), y_actual, ILI9340_WHITE);//offset de +5 por el eje
			 drawLine((x_anterior+OFFSET),y_anterior, (x_actual+OFFSET), y_actual, ILI9340_WHITE);//offset de +5 por el eje
		 }

		 if(bluetooth)
			 tx_bluetooth(valor_adc);

		 y_anterior= y_actual;
		 x_anterior= x_actual;
		 x_actual++; //es simplemente un contador de valores graficados.

		 if (x_actual > 290)
			 version();	//solo grafica la version del programa en el margen derecho de la pantalla

		 if(x_actual==318)//cuando x sea 300 significa que alcanzo el final de la pantalla. 300 son los valores de x que soporta.
			 x_actual =1;

		}

		 else
			taskYIELD();
		}
	}

void static Controlador  (void)
{
	static uint8_t transmision = FALSE;

	xQueueReceive(xON_OFF,&transmision,0);
	if (transmision)
		vTaskResume(xHandler_ADC);
	else
		vTaskSuspend(xHandler_ADC);

	for (;;)
	{
		xQueueReceive(xON_OFF,&transmision,portMAX_DELAY);

		if (transmision)
		{
			vTaskResume(xHandler_ADC);
			modo_activo();
		}
		else
		{
			vTaskSuspend(xHandler_ADC);
			modo_inactivo();
		}
	}
}

void static Presentation (void)
{
    setRotation(3);//modo landscape
    fillScreen(ILI9340_WHITE);
    fillRect(0,150,320,30,ILI9340_WHITE);

	drawBitmap(0, 70, UTN_LOGO, 296, 107,ILI9340_BLACK);

	flag_timer = TRUE;
	Chip_TIMER_Reset(LPC_TIMER2);
	Chip_TIMER_Enable(LPC_TIMER2);				        //Enables the timer (starts count)
	NVIC_EnableIRQ(TIMER2_IRQn);

    while (flag_timer == TRUE);

	setRotation(1);
	fillScreen(ILI9340_RED);
	setRotation(3);
	fillScreen(ILI9340_WHITE);

	drawBitmap(10, 80, GIBIO_LOGO, 297, 104,ILI9340_BLACK);

	flag_timer = TRUE;
	Chip_TIMER_Reset(LPC_TIMER2); 				//Resets the timer terminal and prescale counts to 0
	Chip_TIMER_Enable(LPC_TIMER2);				        //Enables the timer (starts count)
	NVIC_EnableIRQ(TIMER2_IRQn);

    while (flag_timer == TRUE);

	vTaskSuspend(NULL);

}

void static Datos        (void)
{
	portTickType xLastTicks;
	xLastTicks = xTaskGetTickCount();
	uint8_t flag_bt = FALSE;
	  setRotation(3);//modo landscape
	  fillScreen(ILI9340_BLACK);
	  fillRect(0,150,320,30,ILI9340_BLACK);


	  /****************CUADRADO PARCIAL****************/
	  drawFastVLine(0,   100, 139, ILI9340_GREEN);
	  drawFastVLine(319, 100, 139, ILI9340_GREEN);
	  drawFastHLine(0  , 239, 319, ILI9340_GREEN);
      drawFastHLine(0  , 100, 319, ILI9340_GREEN);
      grilla();

	  /****************GRAFICO LOGOS****************/

	  fillRect(0,0, 320,100,ILI9340_WHITE);


	  ////////////////// BLUETOOTH /////////////////////////
	  drawBitmap(5,5, bt_logo, 37 ,50,ILI9340_BLUE);
	  off_bt();

	  ////////////////// WIFI /////////////////////////

	  drawBitmap(0,50, wifi_logo, 50 ,50,ILI9340_BLACK);
	  setTextColor(ILI9340_BLACK);setTextSize(1);setCursor(0, 87);println("(disable)");
	  off_wifi();

	  ///////////////// PPM /////////////////////////
	  drawBitmap(160,0, ppm_logo, 60 ,60,ILI9340_RED);
	  setTextColor(ILI9340_BLACK);setTextSize(3);setCursor(215,21);println("PPM:");

	  ///////////////// ESTADO /////////////////////////

	  setTextColor(ILI9340_BLACK);setTextSize(1);setCursor(155,66);println("Medidor de Presion Arterial");
	  version();

	  setTextColor(ILI9340_BLACK);setTextSize(1);setCursor(165,81);println("ESTADO:");
	  modo_inactivo();

		/* As per most tasks, this task is implemented in an infinite loop. */
		for( ;; )
		{
			 if (bluetooth)
			 {
			 if ( flag_bt == FALSE)
			 	 {
				 //off_wifi();
				 on_bt();
				 flag_bt = TRUE;
			 	 }
			 }
			 else
			 {
			 if (flag_bt == TRUE)
			 	 {
			 	 off_bt();
				 //on_wifi();
				 flag_bt = FALSE;
			 	 }
			 }

		vTaskDelayUntil( &xLastTicks, ( 500 / portTICK_RATE_MS ) );
		}
}


//////////////////////MAIN///////////////////////////////////////////////////////////////
int main (void)
{
 	SystemCoreClockUpdate();
	Board_Init();
	SPI_Init();
	TFT_Init();
	ADC_Init();
	EINT_Init();
	Bluethooth_Init();
	WIFI_Init();

	TIMER_Init( TIMER_MATCH_2, SEG_1*3);

//////////////////////////////////////////////////////////////////////////

	xSemaforo = xSemaphoreCreateMutex();
	xSignal   = xSemaphoreCreateMutex();

//////////////////////////////////////////////////////////////////////////

	xON_OFF	  = xQueueCreate( 1   , sizeof( uint8_t ) );
	xQueue_TFT= xQueueCreate( 100 , sizeof( uint16_t ) );
	xDato_ADC = xQueueCreate( 400 , sizeof( uint16_t ) );

//////////////////////////////////////////////////////////////////////////

	xTaskCreate(ADC_Filter	, "ADC_Filter"   ,1024, NULL, 1, &xHandler_ADC);
	xTaskCreate(TFT_Graph 	, "TFT_Graph"    ,1024, NULL, 1, NULL);
	xTaskCreate(Controlador , "Controlador"  , 128, NULL, 2, NULL);
	xTaskCreate(Datos		, "Datos"	     , 512, NULL, 2, NULL);
	xTaskCreate(Presentation, "Presentation" , 128, NULL, 3, NULL);

///////////////////////////////////////////////////////////////////////

	vTaskStartScheduler();
	while(1);
}
