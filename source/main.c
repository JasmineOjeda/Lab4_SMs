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

enum States {START, WAIT, COMBO, END_COMBO, LOCK} state;

unsigned char i = 0x01;
unsigned char combo[] = {0x04, 0x01, 0x02, 0x01};
unsigned char wasReleased = 0x00;
unsigned char c = 0x00;

void Tick() {

    /* State transitions */
    switch(state) {
        case START:
	    PORTB = 0x00;
	    state = WAIT;
	    break;

	case WAIT:
	    if (PINA == 0x04) {
                state = COMBO;
            }
	    else if (PINA == 0x80) {
                state = LOCK;
            }
	    else {
                state = WAIT;
            }
	    break;

	case COMBO:
	    c = combo[i];
            
	    if (PINA == c) {
                if (i == 3) {
	            i = 1;
                    state = END_COMBO;
		}
		else {
                    i++;
		    wasReleased = 0x00;
		    state = COMBO;
	        }
            }
	    else if (PINA == 0x00) {
		wasReleased = 0x01;
	        state = COMBO;
	    }
	    else if ((PINA == combo[i-1]) && !wasReleased) {
                state = COMBO;
            }
	    else if (PINA == 0x80) {
		i = 1;
                state = LOCK;
            }
	    else {
		i = 1;
                state = WAIT;
            }

	    break;

	case END_COMBO:
            state = WAIT;
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

	case COMBO:
	    PORTC = 0x03;
	    break;

	case END_COMBO:
	    PORTC = 0x04;

	    if (PORTB) {
                PORTB = 0x00;
            }
	    else {
                PORTB = 0x01;
	    }
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

