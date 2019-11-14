/*
 * bitmanipulator.h
 *
 * Created: 07/11/2019 10.36.42
 *  Author: Bruger
 */ 


#ifndef BITMANIPULATOR_H_
#define BITMANIPULATOR_H_

#include <avr/io.h>
#include <math.h>
#include "printf.h"

#define setbit(port, bit) (port) |= (1<<(bit))
#define clearbit(port, bit) (port) &= ~(1<<(bit))

#define bit_is_set(sfr,bit) \
(_SFR_BYTE(sfr) & _BV(bit))

#define bit_is_clear(sfr,bit) \
(!(_SFR_BYTE(sfr) & _BV(bit)))

#define loop_until_bit_is_set(sfr, bit) do { } while (bit_is_clear(sfr, bit))
#define loop_until_bit_is_clear(sfr, bit) do { } while (bit_is_set(sfr, bit))
	
int bitsToInt(int* bits, uint8_t start, uint8_t end);



#endif /* BITMANIPULATOR_H_ */