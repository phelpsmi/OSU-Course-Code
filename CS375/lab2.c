
/*
This code will cause a TekBot connected to a mega128 board to 'dance' in a cool
pattern. No pins are used as input, and four Port B pins are used for output.

PORT MAP
Port B, Pin 4 -> Output -> Right Motor Enable
Port B, Pin 5 -> Output -> Right Motor Direction
Port B, Pin 7 -> Output -> Left Motor Enable
Port B, Pin 6 -> Output -> Left Motor Direction
Port D, Pin 1 -> Input -> Left Whisker
Port D, Pin 0 -> Input -> Right Whisker
*/
#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

#define CHECK_BIT(var,pos) ((var) & (1<<(pos))) //Macro to check specific bit from stackoverflow.com

void HitRight();
void HitLeft();

int main(void)
{
	DDRB = 0b11110000;      // configure Port B pins for input/output
	PORTB = 0b01100000;     // set initial value for Port B outputs

	DDRD = 0b00000000;		// configure Port D pins for input
	PORTD = 0b11111111;		//set PORTD to pullup bits

	int buttons; //variable for holding the current values in port D

	// (initially, disable both motors)

	while (1) { // loop forever
		buttons = (PIND ^ PORTD); // xor PIND with PORTD to account for pullup resistor if it is set

		if(CHECK_BIT(buttons, 1)){ //Check Left Whisker
			HitLeft();
		} else if(CHECK_BIT(buttons, 0)){ //Check Right Whisker
			HitRight();
		}
		_delay_ms(100); //wait a bit before checking again
	}
}

void HitRight(){
	PORTB = 0b00000000; //Move backwards
	_delay_ms(1000); //wait a second

	PORTB = 0b00100000; //Turn left
	_delay_ms(1000); //wait a second

	PORTB = 0b01100000; //continue forward again
}

void HitLeft(){
	PORTB = 0b00000000; //move backwards
	_delay_ms(1000); //wait a second

	PORTB = 0b01000000; //turn right
	_delay_ms(1000); //wait a second

	PORTB = 0b01100000; //continue forward again
}

