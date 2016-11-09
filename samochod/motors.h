/*
 * motors.h
 *
 *  Created on: 09.11.2016
 *      Author: dawid
 */

#ifndef MOTORS_H_
#define MOTORS_H_

#include <avr/io.h>

#define L_FOV PD5
#define L_BACK PD6
#define R_FOV PD7
#define R_BACK PB0

#define L_FOV_PORT PORTD
#define L_BACK_PORT PORTD
#define R_FOV_PORT PORTD
#define R_BACK_PORT PORTB

#define L_FOV_DIR DDRD
#define L_BACK_DIR DDRD
#define R_FOV_DIR DDRD
#define R_BACK_DIR DDRB

#define SET_L_FOV L_FOV_DIR |= (1<<L_FOV)
#define SET_L_BACK L_BACK_DIR |= (1<<L_BACK)
#define SET_R_FOV R_FOV_DIR |= (1<<R_FOV)
#define SET_R_BACK R_BACK_DIR |= (1<<R_BACK)

#define L_FOV_ON L_FOV_PORT |= (1<<L_FOV)
#define L_BACK_ON L_BACK_PORT |= (1<<L_BACK)
#define R_FOV_ON R_FOV_PORT |= (1<<R_FOV)
#define R_BACK_ON R_BACK_PORT |= (1<<R_BACK)

#define L_FOV_OFF L_FOV_PORT &=~ (1<<L_FOV)
#define L_BACK_OFF L_BACK_PORT  &=~ (1<<L_BACK)
#define R_FOV_OFF R_FOV_PORT  &=~ (1<<R_FOV)
#define R_BACK_OFF R_BACK_PORT  &=~ (1<<R_BACK)

#define MAX_SIGNAL_VALUE 35
#define MIN_SIGNAL_VALUE 0

#define TRIGGER_L_SIGNAL 'q'
#define TRIGGER_R_SIGNAL 'e'

#define L_BUMPER_PRESSED_SIGNAL 'k'
#define L_BUMPER_FREE_SIGNAL 'l'

#define R_BUMPER_PRESSED_SIGNAL 'm'
#define R_BUMPER_FREE_SIGNAL 'n'

#define FOWARD_SIGNAL 'w'
#define BACK_SIGNAL 's'
#define LEFT_SIGNAL 'a'
#define RIGHT_SIGNAL 'd'

#define L_DIR_BIT 0
#define R_DIR_BIT 1
#define STOP_BIT 2

#define L_DIR_FLAG flag_reg & (1<<L_DIR_BIT)
#define R_DIR_FLAG flag_reg & (1<<R_DIR_BIT)
#define STOP_FLAG flag_reg & (1<<STOP_BIT)

#define SET_L_DIR_ON flag_reg |= (1<<L_DIR_BIT)
#define SET_R_DIR_ON flag_reg |= (1<<R_DIR_BIT)
#define SET_STOP_ON flag_reg |= (1<<STOP_BIT)

#define SET_L_DIR_OFF flag_reg &=~ (1<<L_DIR_BIT)
#define SET_R_DIR_OFF flag_reg &=~ (1<<R_DIR_BIT)
#define SET_STOP_OFF flag_reg &=~ (1<STOP_BIT)

#define TOGGLE_STOP flag_reg ^= (1<<STOP_BIT)
#define LED_PORT PORTC
#define LED_PIN PC3
#define LED_ON LED_PORT |= (1<<LED_PIN)
#define LED_OFF LED_PORT  &=~ (1<<LED_PIN)

#define STOP_SIGNAL 27 //esc ASCII signal

volatile unsigned char l_motor_pwm;
volatile unsigned char r_motor_pwm;
volatile unsigned char flag_reg;

void execute_command(unsigned char comm, unsigned char val);
unsigned char is_in_range(unsigned char data);
void init_motors();




#endif /* MOTORS_H_ */
