/*
 * bitmanipulator.c
 *
 * Created: 07/11/2019 13.44.21
 *  Author: Bruger
 */ 

#include "bitmanipulator.h"

// Loops through bit array from index x to index y and return the int value of the bits put together.
// Starts at MSB
int bitsToInt(int* bits, uint8_t start, uint8_t end) {
	float value = 0;
	
	for (int i = start; i <= end; i++)
	{
		// Increments value by value from the bit position z.
		// Formula z*2^i
		// This means that i is the position of the bit array starting with msb.
		// Therefore i becomes 7, 6, 5 and so on.
		// z is the value of the bit at the current array index. Either 1 or 0.
		value += bits[i]*pow(2, end-i);
	}
	
	// Converts value to int.
	return (int)value;
}