
#include "FreeRTOS.h"
#include "task.h"
#include "board.h"
#include "semphr.h"
#include "queue.h"

#define CHANNEL_4 1,30

#define LPC_ADC_ID LPC_ADC
#define _ADC_CH	ADC_CH4
#define _LPC_ADC_ID LPC_ADC
#define _LPC_ADC_IRQ ADC_IRQn
#define _VREF 3.2
#define _INT


typedef struct ADC_CLOCK_SETUP_T{
uint32_t adcRate;
uint8_t  bitsAccuracy;
bool     burstMode;
};

xSemaphoreHandle xSignal;
xQueueHandle xDato_ADC;

void ADC_Init(void);
void ADC_IRQHandler(void);

