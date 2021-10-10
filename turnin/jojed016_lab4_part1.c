/*      Author: Jasmine Ojeda jojed016@ucr.edu
 *      Lab Section: 022
 *      Assignment: Lab 4  Exercise 1
 *      Exercise Description: LEDS and buttons
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {START, OFF_RELEASE, OFF_PRESS, ON_RELEASE, ON_PRESS} state;

void Tick() {
    /* State transitions */
    switch(state) {
        case START:
            state = OFF_RELEASE;
            PORTB = 0x01;
            break;
        case OFF_RELEASE:
            if (PINA == 0x01) {
                state = ON_PRESS;
            }
            else {
                state = OFF_RELEASE;
            }
            break;
        case ON_PRESS:
            if (PINA == 0x01) {
                state = ON_PRESS;
            }
            else {
                state = ON_RELEASE;
            }
            break;
        case ON_RELEASE:
            if (PINA == 0x01) {
                state = OFF_PRESS;
            }
            else {
                state = ON_RELEASE;
            }
            break;
        case OFF_PRESS:
            if (PINA == 0x01) {
                state = OFF_PRESS;
            }
            else {
                state = OFF_RELEASE;
            }
            break;
        default:
	    break; 
    }

    /* State actions */
    switch(state) {
        case START:
            PORTB = 0x01;
            break;
        case OFF_PRESS:
            PORTB = 0x01;
            break;
        case ON_PRESS:
            PORTB = 0x02;
            break;
        default:
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}
