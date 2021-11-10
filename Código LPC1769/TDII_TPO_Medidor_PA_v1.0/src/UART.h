/*
 * UART.h
 *
*/
#include "FreeRTOS.h"
#include "board.h"


#define RX_UART0	0,3
#define TX_UART0	0,2
#define BAUDRATE_UART0	38400


#define BAUDRATE_UART3	38400
#define RX_UART3	0,26
#define TX_UART3	0,25
#define ENABLE_BT	0,27
#define STATE_BT	0,24


#define BAUDRATE_UART2	2400
#define TX_UART2	0,10
#define RX_UART2	0,11
#define RESET_WIFI	3,26
#define POWER_DOWN_WIFI	3,25


#define LPCP0 				LPC_GPIO


void UART3_Init(void);
void Bluethooth_Init(void);
void UART3_IRQHandler(void);
void tx_bluetooth( uint16_t adc_valor);

void WIFI_Init(void);
void UART2_Init(void);
void UART2_IRQHandler(void);

