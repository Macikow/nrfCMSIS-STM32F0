/*
 * uart.h
 *
 *  Created on: Nov 21, 2016
 *      Author: Macikow
 */


#ifndef USART_H_
#define USART_H_

void initUart(void);
void sendChar(unsigned char data);
void sendString(char* data);

#endif /* USART_H_ */

