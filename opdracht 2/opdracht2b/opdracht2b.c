#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

ISR(TIMER1_OVF_vect) 
{
	// reset counter
	TCNT1 = 64635;
    /* volgende patroon */ 
    PORTB<<=1;

	
}

int main() 
{

    // normal mode: WGMO1 en WGM00 op 0;
    // TCCR1A&=~(1<<WGM01|1<<WGM00); 
    // prescaler 1024. CS02 1, CS01 0, CS00, 1
    TCCR1B&=~(1<<CS11) ;
    TCCR1B|=1<<CS12|1<<CS10;
    
    /* overflow na 900, dus 2^16-1 - 900 > om de 250 ms een interrupt aanroep */
    TCNT1 = 64635; 
    
    // 
    TIMSK|=1<<TOIE1;


    // port B instellen, 1 ledje aan..
    DDRB=0xFF;
    PORTB=0xFE;

    sei();

    while (1) {
        /* hier kun je iets anders doen */
    }

    return 0;
}
