/*
 * UART.h
 *
 *  Created on: 05.11.2016
 *      Author: dawid
 */

#ifndef UART_H_
#define UART_H_

#include <avr/io.h>

#define UART_BAUD 9600
#define __UBRR ((F_CPU+UART_BAUD*8UL) / (16UL*UART_BAUD)-1)


void uart_init();
unsigned char uart_receive(void);

//_________________________________













#endif /* UART_H_ */
