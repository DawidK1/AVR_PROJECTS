#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define BUTTON ( 1 << PD6 )
#define LED ( 1 << PD2 )

#define BUTTON_DDR DDRD
#define LED_DDR DDRD

#define BUTTON_PORT PORTD
#define LED_PORT PORTD

#define BUTTON_PIN PIND

#define RIGHT_FORW ( 1 << PB0 )
#define RIGHT_BACK ( 1 << PD7 )

#define RIGHT_FORW_PORT PORTB
#define RIGHT_BACK_PORT PORTD

#define RIGHT_FORW_DDR DDRB
#define RIGHT_BACK_DDR DDRD

#define LEFT_FORW ( 1 << PD0 )
#define LEFT_BACK ( 1 << PD1 )

#define LEFT_FORW_PORT PORTD
#define LEFT_BACK_PORT PORTD

#define LEFT_FORW_DDR DDRD
#define LEFT_BACK_DDR DDRD

//USE THIS MACROS TO CHOOSE DIRECTION OF WHEELS

#define L_FORW_OFF LEFT_FORW_PORT &=~ LEFT_FORW
#define L_BACK_OFF LEFT_BACK_PORT &=~ LEFT_BACK

#define L_FORW_ON LEFT_FORW_PORT |= LEFT_FORW ; L_BACK_OFF
#define L_BACK_ON LEFT_BACK_PORT |= LEFT_BACK ; L_FORW_OFF


#define R_FORW_OFF RIGHT_FORW_PORT &=~  RIGHT_FORW
#define R_BACK_OFF RIGHT_BACK_PORT &=~ RIGHT_BACK

#define R_FORW_ON RIGHT_FORW_PORT |= RIGHT_FORW ; R_BACK_OFF
#define R_BACK_ON RIGHT_BACK_PORT |= RIGHT_BACK ; R_FORW_OFF

//LED AND BUTTON MACROS
#define LED_ON LED_PORT |= LED
#define LED_OFF LED_PORT &= ~ LED
#define IS_BUTTON_PRESSED !(BUTTON_PIN & BUTTON)


#define FLOOR_LEFT 1
#define FLOOR_RIGHT 0
#define SHARP 2

#define ADC_VALUE ADCH

//USE THIS MACROS TO MANIPULATE MOTORS PWM
#define LEFT_PWM OCR1B
#define RIGHT_PWM OCR1A

//USE THIS PARAMETERS AS SENSIVITY THRESHOLDS FOR SENSORS

#define FLOOR_DETECT_THRESHOLD 50
#define SHARP_DETECT_THRESHOLD 75


 uint8_t adc_counter;
volatile uint8_t sharp_value;
volatile uint8_t left_floor_value;
volatile uint8_t right_floor_value;

void config(void);
void try_to_escape_from_white_line();
void look_for_enemy();
void push_enemy();


int main(void){



	config();


//INSERT LOGIC HERE
//DATA FROM SENSORS IS UPDATED CONSTANTLY DUE TO ADC INTERRUPT
// PWM IS GENERATED USING TIMER1, TO MANIPULATE PWM DUTY WRITE VALUE 0-255 TO LEFT_PWM OR RIGHT_PWM
// TO CHOOSE WHEELS DIRECTIONS USE MACROS LIKE L_FORW_ON, REMEMBER TO OFF FORW OUTPUT BEFORE ON BACK OUTPUT
// ACTIVE FORW AND BACK OUPTUT AT THE SAME TIME WILL STOP MOtoR, BUT NOTHING WRONG WILL HAPPEN
// CONFIG MUST BE USED IN MAIN ONCE

while(1){


	while(!IS_BUTTON_PRESSED);

	LED_ON;
	_delay_ms(1000);
	LED_OFF;
	_delay_ms(1000);
	LED_ON;
	_delay_ms(1000);
	LED_OFF;
	_delay_ms(1000);
	LED_ON;
	_delay_ms(1000);
	LED_OFF;

	L_FORW_ON;
	R_BACK_ON;

	LEFT_PWM =255;
	RIGHT_PWM =255;

	while(1){

		_delay_ms(10);
		if(IS_BUTTON_PRESSED)
			break;

		if( (left_floor_value < FLOOR_DETECT_THRESHOLD)   ) //(right_floor_value < FLOOR_DETECT_THRESHOLD)
			try_to_escape_from_white_line();

		else{
			if(sharp_value < SHARP_DETECT_THRESHOLD){
				look_for_enemy();
			}
			else{
				push_enemy();
			}
		}



	}

	LEFT_PWM =0;
	RIGHT_PWM =0;
	_delay_ms(1200);
	}
//END OF MAIN
}


void config(void){
	sei();
	//PWM FOR MOTORS CONFIG
	TCCR1B |= (1 << CS12);//PRESCALLER
	TCCR1A|=  (1 << WGM10)// PHASE CORRECT 8BIT PWM
			| (1<< COM1A1)
			| (1 << WGM12)
			| (1<< COM1B1);

	DDRB |= (1 << PB1)
		 |  (1 << PB2);

	//OUTPUTS CONFIG (MOTORS)
	LEFT_FORW_DDR |= LEFT_FORW;
	LEFT_BACK_DDR |= LEFT_BACK;
	RIGHT_FORW_DDR |= RIGHT_FORW;
	RIGHT_BACK_DDR |= RIGHT_BACK;

	LED_DDR |= LED;

	//ADC_CONFIG
    ADMUX |= (1<<REFS0) | (1<<ADLAR); //SET VCC AS REFERENCE VOLTAGE

    ADCSRA |= (1<<ADEN) //ENABLE ADC, ENABLE ADC INTERRUPT, PRESCALLER 128
    		| (1<<ADIE)
    		|(1<<ADPS0)
   	   		|(1<<ADPS1)
	     	|(1<<ADPS2);

	ADCSRA |= (1<<ADSC);//START MEASURES

}


ISR(ADC_vect){
	switch(adc_counter){


		case 0:
			right_floor_value = ADCH;
			ADMUX &=~ 0x0F;
			ADMUX |= 2;
			adc_counter = 1 ;
			ADCSRA |= (1<<ADSC);
			break;

		case 1:
			sharp_value = ADCH;
			ADMUX &=~ 0x0F;
			ADMUX |= 1;
			adc_counter = 2;
			ADCSRA |= (1<<ADSC);
			break;

		case 2:
			left_floor_value =  ADCH;
			ADMUX &=~ 0x0F;
			ADMUX |= 0;
			adc_counter = 0;
			ADCSRA |= (1<<ADSC);
			break;
	}
}


void try_to_escape_from_white_line(){
	L_BACK_ON;
	R_BACK_ON;

	LEFT_PWM = 150;
	RIGHT_PWM = 150;
	if(left_floor_value < FLOOR_DETECT_THRESHOLD)
		LEFT_PWM = 255;
	if(right_floor_value < FLOOR_DETECT_THRESHOLD)
		RIGHT_PWM = 255;

}

void look_for_enemy(){
	L_BACK_ON;
	R_FORW_ON;
	LEFT_PWM = 150;
	RIGHT_PWM = 150;

}
void push_enemy(){
	L_FORW_ON;
	R_FORW_ON;
	LEFT_PWM = 255;
	RIGHT_PWM = 255;
}

