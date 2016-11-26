/*
 * uart.c
 *
 *  Created on: Nov 21, 2016
 *      Author: Macikow
 */

#include "stm32f0xx.h"
//#include "stm32f0xx_usart.h"
//#include "stm32f0xx_rcc.h"


#define USART1_TX GPIO_Pin_9
#define USART1_RX GPIO_Pin_10



void initUart(void)
{
	GPIO_InitTypeDef GPIO;	// struktura do gpio
	USART_InitTypeDef USART; 		//  struktura do USART1

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1 , ENABLE); // wlaczenie taktowanie ukdu usart1
	RCC_APB1PeriphClockCmd(RCC_AHBPeriph_GPIOA , ENABLE); //  wczenie taktowania portu I/O


	// GPIO  init
	//GPIO_PinAFConfig(GPIOA, USART1_TX, USART1);
	GPIOA->AFR[1] = (1 << 4) | (1 << 8); // ok
	GPIO.GPIO_Pin = USART1_TX | USART1_RX;
	GPIO.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO.GPIO_Mode = GPIO_Mode_AF;
	GPIO.GPIO_OType = GPIO_OType_PP;
	GPIO.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_Init(GPIOA, &GPIO);
	// USART1


	USART.USART_BaudRate = 9600;
	USART.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART.USART_WordLength = USART_WordLength_8b;
	USART.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART.USART_Parity = USART_Parity_No;
	USART.USART_StopBits = USART_StopBits_1;
	USART_Init(USART1, &USART);
	USART_Cmd( USART1, ENABLE );

	//USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	    /* Enable USART1 global interrupt */
	//NVIC_EnableIRQ(USART1_IRQn);

}

void sendChar(uint8_t data)
{
	while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET);
	USART1->TDR = data;

}
void sendString(char* data)
{
	while(*data != '\0'){
		sendChar(*data++);
	}
}
