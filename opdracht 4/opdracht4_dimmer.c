#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include <avr/interrupt.h>


int main(void) {
	//settings

	// 1) pwm and led
	//
	// WGM01 = 1 WGM00 = 1 COM01 = 1 COM00 = 1
	
	TCCR0 = 0x7B;
	DRRB  = 0x08;
	OCR0  = 65;
	

	// 2) adc on, left justify adc + flag reset
    ADCSRA |= 1<<ADEN;
	ADMUX  |= 1<<ADLAR;
	ADCSRA |= 1<<ADSC;

	while(1)
	{
		// start adc
		ADCSRA |= 1<<ADSC;

		// poll ready
		while(~ADCSRA&1<<ADIF);

		// update flag
		ADCSRA |= 1<<ADSC;		

		// update pwm
		TCCR0 = ADCH;


	}


}
