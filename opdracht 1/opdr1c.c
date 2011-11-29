#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>

void wait(void) {
	uint8_t i;
 	for (i=0; i<10; ++i)
		_delay_ms(25);
}

int main() {
	void wait();
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

	}
	return 0;
}
