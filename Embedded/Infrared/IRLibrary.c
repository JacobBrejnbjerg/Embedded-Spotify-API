/*
* IRLibrary.c
*
* Created: 28-01-2019 14:27:49
*  Author: Bruger
*/


#include <stdio.h>
#include <stdlib.h>
#include "IRLibrary.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "avr/delay.h"

char firstPulse = 1;

int counterValues[32];
char irBits[32];
int irCount = StartCount; // StartCount removes the leading pulse
char buttonPressed = Unrecognized;

// Array which can contain 21 buttons. Each with 32 bits
char irButtonValues[21][32] = {
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,1,0,0,0,1,0,0,1,0,1,1,1,0,1},	// Powerbutton
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,0,0,0,1,0,1,0,0,1,1,1,0,1},	// Vol+
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,1,0,0,0,0,1,1,1,0,1},	// Func/Stop
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,0,0,0,1,0,1,1,0,1,1,1,0,1},	// Skip Left
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,1,1,1,1,1},	// Arrow Down
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,0,0,1,0,0,0,0,0,1,1,0,1,1,1,1},	// Arrow Up
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0,0,0,1,0,1,1,1,1,1,1,0,1},	// Start/Pause
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,1,1,0,0,0,0,1,1,0,0,1,1,1,1},	// Number 1
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,1,1,0,0,0,1,1,1,0,0,1,1,1},	// Number 2
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,0,0,0,0,1,0,1},	// Number 3
	{0,0,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,0,0,0,0,1,0,0,0,1,1,1,1,0,1}	// Skip Right
};

void InitIR(void)
{
	// Forcing PL0 as input pin
	DDRL &= (1<<PL0);
	
	// Enable TCCR4B edge capture which creates an interrupt whenever the PL0 pin goes high    Datasheet: 17.11.7
	// When a capture is triggered according to the ICESn setting, the counter value is copied into the Input Capture Register (ICRn).
	TCCR4B |= (1<<ICES4);

	// Enable Input Capture Interrupt on Timer 4 Datasheet: 17.11.35
	TIMSK4 |= (1<<ICIE4);

	// Prescaler: clk/256	Datasheet: Table 17-6
	TCCR4B |= (1<<CS40) | (1<<CS42);

	// Enable interrupts
	sei();
}

// Interrupt which triggers whenever PL0 goes high
ISR(TIMER4_CAPT_vect)
{
	// irCount is less than 0 when the leadingpulse is being measured.
	if (irCount < 0)
	{
		irCount++;
		TCNT4 = 0;
		return;
	}

	// First measurement
	if (firstPulse)
	{
		//TCNT4's værdi bliver lagt ind i ICR4 når dette interrupt bliver kaldt. Det fremgår i teksten til Datasheet: 17.11.31
		firstPulse = 0;
		irCount = StartCount;
	}
	else
	{
		if (irCount >= 0)
		{
			counterValues[irCount] = TCNT4;
		}
		
		irCount++;
	}

	// counterValues can contain 32 bits. If infrared hits/counts is 32, it has recieved the entire signal.
	if (irCount == sizeof(counterValues)/2)
	{
		// Convert the pulse lengths into bits (true/false)
		for (int i = 0; i < sizeof(counterValues)/2; i++)
		{
			if (i == 0)
			irBits[i] = ConvertIRTimeToBit(counterValues[i]);
			else
			irBits[i] = ConvertIRTimeToBit(counterValues[i] - counterValues[i-1]); // This calculation finds the difference in time between the pulses
		}

		_delay_ms(100); // Must be here. For some reason GetButton does not work if this is not here.

		irCount = StartCount;
		firstPulse = 1;
		buttonPressed = GetButton((irBits));
		printf("\r\nButton pressed: %i", buttonPressed);
	}
}

// Converts the time to a bit (1 or 0)
char ConvertIRTimeToBit(int* pulseLength)
{
	// 25 Is the amount of cycles to compare the time to.
	// A false takes ~17 and a true ~35.
	if (pulseLength > 25)
	return 1;
	else
	return 0;
}

// Gets the button pressed using the values which has been registered
int GetButton(char *values)
{
	char matched = 0;
	// Loops through the buttons
	for (int i =0; i<11; i++)
	{
		matched = 0;

		for (int j=0; j<32; j++)
		{
			// Loop through the bits
			if (irButtonValues[i][j] == values[j])
			matched++;
			else
			break;

			if (matched == 32)
			{
				// Returns i which is the button pressed
				return i;
			}
		}
	}
	
	// If button not found, it returns 22.
	return 22;
}

// Gets the last button pressed/registered.
// Resets the last button pressed to 22 whenever the value is read.
int GetButtonPressed(void){
	int tempValue = buttonPressed;
	
	if (buttonPressed != Unrecognized)
	{
		// Resets the button
		buttonPressed = Unrecognized;
	}

	return tempValue;
}