/*
 * bits.h
 *
 * Created: 13.11.2021 15:08:22
 *  Author: Marvin
 */ 


#ifndef BITS_H_
#define BITS_H_

#define set(var, bit)		{(var) |= (1 << (bit));}
#define clr(var, bit)		{(var) &= ~(1 << (bit));}
#define get(var, bit)		(((var) & (1 << (bit))) >> (bit))

#endif /* BITS_H_ */