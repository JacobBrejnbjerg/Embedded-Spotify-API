/*
 * song_progress_timer.c
 *
 * Created: 14/11/2019 11.10.55
 *  Author: Bruger
 */ 

#include "song_progress_timer.h"

void Init_Progress_Timer(void)
{
	// Enable CTC Mode
	TCCR1B |= (1<<WGM12);


	// Prescaler: clk/256
	TCCR1B |= (1<<CS12);
	
	// Output Compare A Match Interrupt Enable
	TIMSK1 |= (1<<OCIE1A);
	
	// Set OCR1A to 62499 in order to trigger interrupt every second.
	OCR1A = 62499;
	
	// Enable global interrupts
	sei();
}

// Disable progress timer by setting prescaler to 0. (Prescaler = disables timer)
void Disable_Progress_Timer(void)
{
	// Disable timer Table 17-6 (17.11.9)
	TCCR1B |= (1<<CS12)|(1<<CS11)|(1<<CS10);
}

// Enable progress timer by setting prescaler to 256.
void Enable_Progress_Timer(void)
{
	// Enable timer by setting Prescaler again. Prescaler: clk/256
	TCCR1B |= (1<<CS12);
	
	// Set CS11 and CS10 to 0 again. This way only CS12 is high.
	TCCR1B &= ~((1<<CS11)|(1<<CS10));
}