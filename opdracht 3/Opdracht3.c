#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include <avr/interrupt.h>

volatile uint8_t environment_status=0x00; 
    /* in de environment_status wordt bijgehouden wat het systeem moet doen.
     * status = 0x00 - omgeving is 'ongewijzigd'
     * status = 0x01 - omgeving is nu goed
     * status = 0x02 - omgeving is te warm
     * status = 0x03 - omgeving is te koud
     */

void lcd_status_update(void)
{
    switch(environment_status) {
    
        case 0x01:
            lcd_cls(); 
            lcd_puts("niets te doen");

            break;
        case 0x02:
            lcd_cls();
            lcd_puts("opwarmen");

            break;
        case 0x03:
            lcd_cls(); 
            lcd_puts("koelen");

            break;
        default:
            /* mag niet voorkomen, alarm... */
            PORTB=0x00;
            break;
    }
}

void heat_cool_update(void)
{
    switch(environment_status) {
    
        case 0x01:
            // normal mode: P7 en p6 op 1 (0 op led is aan!);
            PORTB |= 1<<PB7|1<<PB6; 
            break;

        case 0x02:
            // koelen: P6 op 0 p7 op 1.
            PORTB &= ~(1<<PB6); 
            PORTB |= 1<<PB7;
            break;

        case 0x03:
            // verwarmen: p7 op 0 p6 op 1.
            PORTB &= ~(1<<PB7);
            PORTB |= 1<<PB6;
            break;

        default:
            /* mag niet voorkomen, alarm... */
            PORTB=0x00;
            break;
    }
}



ISR(TIMER1_OVF_vect) 
{
 	static uint8_t led=0x00, temp_status=0x01;
    uint8_t temperature=0x00;
    
	/* for testing, random environment */
	// environment_status= rand() % 3 + 1;

    // reset counter
    TCNT1 = 61935;

    // statusled
    if(led == 0x00) {
        PORTB &= ~(1<<PB5);
        led = 0x01;

    } else {
    
        led = 0x00;
        PORTB |= 1<<PB5;
    }
}

void setup(void)
{

    // 1 - TIMER

    // normal mode: WGM11 en WGM10 op 0 in TCCR1A WGM12 en WGM13 op 0 in TCCRB;
    // TCCR1A &= ~(1<<WGM11|1<<WGM10); 
    // TCCR1B &= ~(1<<WGM13|1<<WGM12);
	 
    // prescaler 1024. CS12 1, CS11 0, CS10, 1

    TCCR1B &= ~(1<CS11);
    TCCR1B |= 1<<CS12|1<<CS10;
    
    /* overflow na 3600, dus 2^16-1 - 3600 > om de s een interrupt aanroep */
    TCNT1 = 61935;
    
    // enable overflow
    TIMSK|=1<<TOIE1;


    // 2 - LEDJES - PORTB - LEDJES UIT
    DDRB=0xFF;
    PORTB=0xFF;

    // 3 - SENSORS

    // 4 - LCD
    lcd_init();
	lcd_cls();
	lcd_puts("Opstarten");

}

int main(void) 
{
    // setup
	setup();

	// enable interrupts
	sei();

    while (1) {

	
        // er veranderd iets..
        if(environment_status != 0x00) {

            heat_cool_update();
			lcd_status_update();
        
            // afgehandeld
            environment_status = 0x00;
        }
    }
        
    return 0;
}
