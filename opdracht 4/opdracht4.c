#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "lcd.h"
#include <avr/interrupt.h>

void setup(void)
{
    // de speaker zit aangesloten op PD5 = OC1A
    DDRD |= 1<<5

    /* timer/counter 1 : prescaler 1, CTC mode, Toggle compare match
     * WGM13  = 0 > TCCR1A
     * WGM12  = 1 > TCCR1A
     * WGM11  = 0 > TCCR1B
     * WGM10  = 0 > TCCR1B
     * CS12   = 0 > TCCR1B
     * CS11   = 0 > TCCR1B
     * CS10   = 1 > TCCR1B
     * COM1A1 = 0 > TCCR1A
     * COM1A0 = 1 > TCCR1A
     */
    TCCR1A |= 1<<WGM12;
    TCCR1B |= 1<<CS10;
    TCCR1A |= 1<<COM1A0;

    // nu in OCR1(A?) het aantal cycles laden.
    

}

int main(void)
{
    void setup(void);        
    return 0;
}
