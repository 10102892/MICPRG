#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

int main(void) {
	//settings

	// 1) pwm and led
	// WGM01 = 1 WGM00 = 1 COM01 = 1 COM00 = 1
	
	TCCR0 = 0x7B;
	DRRB  = 0x08;
	OCR0  = 65;
	
	// 2) adc on, left justify adc + flag reset
    ADCSRA |= 1<<ADEN;
	ADMUX  |= 1<<ADLAR;

	while(1)
	{
		// start adc
		ADCSRA |= 1<<ADSC|1<<ADIF;

		// poll ready
		while(~ADCSRA&1<<ADIF);	

		// update pwm
		OCR0 = ADCH;

	}
}
