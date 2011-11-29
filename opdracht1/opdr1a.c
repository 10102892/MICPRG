typedef unsigned char uint8_t;

void wait(void) {
	volatile int i;
	for (i=0; i<30000; ++i) 
		/*empty*/;
}

int main() {
	void wait();
	uint8_t c1, c2, i;
	volatile uint8_t* ddrb=(uint8_t*)0x37;
	volatile uint8_t* portb=(uint8_t*)0x38;

	*ddrb=0xFF;
	while (1) {
		c1=0x80;
		c2=0x01;
		for (i=0;i<4;i++) {
			wait();
			*portb=~(c1|c2);
			c1>>=1;
			c2<<=1;
		}
	}
	return 0;		
}
