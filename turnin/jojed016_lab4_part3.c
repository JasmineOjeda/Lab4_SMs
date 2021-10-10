/*      Author: Jasmine Ojeda jojed016@ucr.edu
 *      Lab Section: 022

 *      Assignment: Lab 4  Exercise 2
 *      Exercise Description: Incrementer/Decrementer
 *
 *      I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {START, WAIT, HASH_PRESS, HASH_RELEASE, UNLOCK, LOCK} state;

void Tick() {
    unsigned char x = PINA & 0x01;
    unsigned char y = (PINA & 0x02) >> 1;
    unsigned char hash = (PINA & 0x04) >> 2;
    unsigned char lock = (PINA & 0x80) >> 7;

    /* State transitions */
    switch(state) {
        case START:
	    PORTB = 0x00;
	    state = WAIT;
	    break;

	case WAIT:
	    if (!lock && !x && !y && hash) {
                state = HASH_PRESS;
            }
	    else if (lock && !x && !y && !hash) {
                state = LOCK;
            }
	    else {
                state = WAIT;
            }
	    break;

	case HASH_PRESS:
	    if (!lock && !x && !y && hash) { 
                state = HASH_PRESS;
            }
            else if (!lock && !x && !y && !hash) {
                state = HASH_RELEASE;
            }
	    else if (lock && !x && !y && !hash) {
                state = LOCK;
            }
            else {
                state = WAIT;
            }
	    break;

	case HASH_RELEASE:
	    if (!lock && !x && !y && !hash) {
                state = HASH_RELEASE;
            }
            else if (!lock && !x && y && !hash) {
                state = UNLOCK;
	    }
            else if (lock && !x && !y && !hash) {
                state = LOCK;
            }
            else {
                state = WAIT;
            }
	    break;

	case UNLOCK:
	    if (!lock && !x && y && !hash) {
                state = UNLOCK;
            }
            else {
                state = WAIT;
            }
	    break;

	case LOCK:
	    state = WAIT;
	    break;

        default:
            break;
    }

    /* State actions */
    switch(state) {
	case START:
	    PORTC = 0x00;
	    break;

	case WAIT:
	    PORTC = 0x01;
	    break;

	case HASH_PRESS:
	    PORTC = 0x02;
	    break;

	case HASH_RELEASE:
	    PORTC = 0x03;
	    break;

	case UNLOCK:
	    PORTC = 0x04;
	    PORTB = 0x01;
	    break;

	case LOCK:
	    PORTC = 0x05;
	    PORTB = 0x00;
	    break;

	default:
	    break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PORTA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;
    DDRC = 0xFF; PORTC = 0x00;

    state = START;
    /* Insert your solution below */
    while (1) {
        Tick();
    }
    return 1;
}

