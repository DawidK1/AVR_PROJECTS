/*
 * motors.c
 *
 *  Created on: 09.11.2016
 *      Author: dawid
 */

#include "motors.h"

void execute_command(unsigned char comm, unsigned char val){

	if(comm == STOP_SIGNAL)
		TOGGLE_STOP;

	if(STOP_FLAG){
		LED_ON;
		l_motor_pwm = 0;
		r_motor_pwm = 0;
		SET_L_DIR_ON;
		SET_R_DIR_ON;
		return;
	}
	else{
		LED_OFF;
	}

	if(val > MIN_SIGNAL_VALUE)
		val = val + MAX_SIGNAL_VALUE/2;


	switch(comm){
	/*
		case FOWARD_SIGNAL:
			SET_L_DIR_ON;
			SET_R_DIR_ON;
			l_motor_pwm = val;
			r_motor_pwm = val;
			break;

		case BACK_SIGNAL:
			SET_L_DIR_OFF;
			SET_R_DIR_OFF;
			l_motor_pwm = val;
			r_motor_pwm = val;
			break;
*/
		case TRIGGER_L_SIGNAL:
			l_motor_pwm = val;
			break;
		case TRIGGER_R_SIGNAL:
			r_motor_pwm = val;
			break;

		case L_BUMPER_PRESSED_SIGNAL:
			SET_L_DIR_ON;
			break;
		case L_BUMPER_FREE_SIGNAL:
			SET_L_DIR_OFF;
			break;

		case R_BUMPER_PRESSED_SIGNAL:
			SET_R_DIR_ON;
			break;
		case R_BUMPER_FREE_SIGNAL:
			SET_R_DIR_OFF;
			break;

		default:
			break;
	}
///////////////////////////////////////////////////////////////////
}
unsigned char is_in_range(unsigned char data)
{
	if(data > MAX_SIGNAL_VALUE || data < MIN_SIGNAL_VALUE)
		return 0;
	else return 1;
}
////////////////////////////////////////////////////////////
void init_motors(){
	SET_L_FOV;
	SET_L_BACK;
	SET_R_FOV;
	SET_R_BACK;
	SET_STOP_OFF;
	SET_L_DIR_ON;
	SET_R_DIR_ON;
	DDRC |= (1>>LED_PIN);
}
