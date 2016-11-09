/*
 * UART.c
 *
 *  Created on: 05.11.2016
 *      Author: dawid
 */
#include "UART.h"

void uart_init(void)
{
     UBRR0H = (unsigned char)(__UBRR>>8);
     UBRR0L = (unsigned char)__UBRR;

     UCSR0B |= (1<<RXEN0);
}

unsigned char uart_receive(void)
{

while (!(UCSR0A & (1<<RXC0)))
;

return UDR0;
}
