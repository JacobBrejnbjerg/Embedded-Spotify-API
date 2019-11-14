/*
 * song_progress_timer.h
 *
 * Created: 14/11/2019 11.11.02
 *  Author: Bruger
 */ 


#ifndef SONG_PROGRESS_TIMER_H_
#define SONG_PROGRESS_TIMER_H_

#include <avr/io.h>
#include <avr/interrupt.h>

void Init_Progress_Timer(void);
void Disable_Progress_Timer(void);
void Enable_Progress_Timer(void);



#endif /* SONG_PROGRESS_TIMER_H_ */