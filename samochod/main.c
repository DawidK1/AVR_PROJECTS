/*
 * main.c
 *
 *  Created on: 05.11.2016
 *      Author: dawid
 */
/*
 * main.c
 *
 *  Created on: 05.11.2016
 *      Author: dawid
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#include "motors.h"
#include  "uart.h"

unsigned char received_data;
unsigned char is_next_value;
unsigned char command;
unsigned char command_value;

volatile unsigned char signal_value;
volatile unsigned char timer_counter;

unsigned char is_in_range(unsigned char data);
void execute_command(unsigned char comm, unsigned char val);

int main(){

	//TIMER SETUP
	timer_counter = 0;
	TIMSK0 |= (1<<TOIE0);
	TCCR0B |= (1<<CS02); //start timer, prescaller 256

	init_motors();
	uart_init();

	sei();
	while(1){

		received_data = uart_receive();

		if(is_next_value && is_in_range(received_data - 'A')){
				execute_command(command, received_data - 'A');
			}
		else
			{
				switch(received_data){
					case FOWARD_SIGNAL:
					case BACK_SIGNAL:
					case LEFT_SIGNAL:
					case RIGHT_SIGNAL:
					case TRIGGER_L_SIGNAL:
					case TRIGGER_R_SIGNAL:

						command = received_data;
						is_next_value = 1;
						break;

					default:
						execute_command(received_data, 0);
						is_next_value = 0;
						break;
				}
			}
		}//end of infinite loop*/
	return 0;
	}


////////////////////////////////////////////////////////////////////////////

	ISR(TIMER0_OVF_vect) {

		TCNT0 = 254;

		if(L_DIR_FLAG){
			if(timer_counter == MIN_SIGNAL_VALUE){
				L_BACK_OFF;
				L_FOV_ON;
			}
			if(timer_counter == l_motor_pwm){
				L_FOV_OFF;
			}
		}
		else{
			if(timer_counter == MIN_SIGNAL_VALUE){
				L_FOV_OFF;
				L_BACK_ON;
			}

			if(timer_counter == l_motor_pwm)
				L_BACK_OFF;
		}


		if(R_DIR_FLAG){
			if(timer_counter == MIN_SIGNAL_VALUE){
				R_BACK_OFF;
				R_FOV_ON;
			}
			if(timer_counter == r_motor_pwm)
				R_FOV_OFF;
		}
		else{
			if(timer_counter == MIN_SIGNAL_VALUE){
				R_FOV_OFF;
				R_BACK_ON;
			}
			if(timer_counter == r_motor_pwm)
				R_BACK_OFF;
		}


		timer_counter++;
		if(timer_counter > MAX_SIGNAL_VALUE)
			timer_counter = MIN_SIGNAL_VALUE;
	}
////////////////////////////////////////////////////////////////////////////////


