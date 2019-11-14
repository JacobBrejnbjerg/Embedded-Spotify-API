/*
* IRLibrary.h
*
* Created: 28-01-2019 14:27:57
*  Author: Bruger
*/

char ConvertIRTimeToBit(int* pulseLength);
int GetButton(char *values);
int GetButtonPressed(void);
void InitIR(void);

#ifndef IR_H_
#define IR_H_

#ifndef F_CPU
#define F_CPU			16E6
#endif

#define CyclesInUS		16		// Amount of cycles in a microsecond
#define StartCount		-1		// When it should start

#define Unrecognized	22
#define Powerbutton		0
#define	VolUp			1
#define FuncStop		2
#define SkipLeft		3
#define ArrowDown		4
#define ArrowUp			5
#define StartPause		6
#define Number1			7
#define Number2			8
#define Number3			9
#define SkipRight		10

#endif /* IR_H_ */