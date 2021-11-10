#include "FreeRTOS.h"
#include "queue.h"


#define		__RW		volatile

#define		EXTINT			*( ( __RW uint32_t * ) 0x400FC140UL)
#define	    EXTMODE 		*( ( __RW uint32_t * ) 0x400FC148UL)
#define	    EXTPOLAR 		*( ( __RW uint32_t * ) 0x400FC14CUL)

#define 	CLEAR_INTERRUPT(x)		EXTINT |= 0x1 << x

//Defines
#define		EINT0		0
#define		EINT1		1
#define		EINT2		2
#define		EINT3		3

#define 	EXTMODE_NIVEL		0
#define 	EXTMODE_FLANCO		1

#define 	EXTPOLAR_ACTIVO_BAJO_O_DESCENDENTE		0
#define 	EXTPOLAR_ACTIVO_ALTO_O_ASCENDENTE		1
//


void EINT_SetMode(uint8_t EXTINTx, uint8_t modo);
void EINT_SetPolarity(uint8_t EINTx, uint8_t polaridad);

void EINT_Init(void);
void EINT3_IRQHandler(void);
void EINT2_IRQHandler(void);

extern xQueueHandle xON_OFF;
extern uint8_t bluetooth;
extern uint8_t wifi;
