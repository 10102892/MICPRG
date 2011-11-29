#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>

void wait(void) {

    // er moet 250 ms gewacht worden
    // met een prescaler van 1024 en een frequentie van 3686400 hz
    // geeft dat 900 pulsen per 0.25 sec
    

    // normal mode: WGMO1 en WGM00 op 0;
    TCCR1A&=~(1<<WGM01|1<<WGM00); 
    // prescaler 1024. CS02 1, CS01 0, CS00, 1
    TCCR1B&=~(1<<CS01) ;
    TCCR1B|=1<<CS02|1<<CS00;
    
    
    TCNT1 = 64635; /* overflow na 900, dus 2^16-1 - 900 */

    // reset TOV1
    TIFR=1<<TOV1;

    // wachten op overflow TOV1
    while(!(TIFR&1<<TOV1)); 
    
    // counter uitzetten
    TCCR1B&=~(1<<CS02|1<<CS01|1<<CS00);


}

int main() {
 
    uint8_t c1, c2, i, which=0x00;

    DDRA=0x00;
    DDRB=0xFF;
    while (1) {


        if ((PINA&0x80)==0x00) {

            which = ~which;
        } 
        
        if (which == 0x00 )
        {

            c1=0x80;
            c2=0x01;
            for (i=0;i<4;i++) {
                wait();
                PORTB=~(c1|c2);
                c1>>=1;
                c2<<=1;
            }

        } 
        else 
        {

            c1=0x01;
            for (i=0;i<8;i++) {
                wait();
                PORTB=~c1;
                c1<<=1;
            }
           
        }

		void wait();

    }
    return 0;
}
