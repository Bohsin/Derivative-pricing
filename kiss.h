#ifndef KISS_H
#define KISS_H

#define _CRT_RAND_S

#include <stdlib.h>
#include <math.h>



struct kiss_state {
	/*
	* Seed variables.  Note that kiss requires a moderately complex
	* seeding using a "seed rng" that we will arbitrarily set to be
	* mt19937_1999 from the GSL.
	*/
	unsigned int x;
	unsigned int y;
	unsigned int z;
	unsigned int c;
};


unsigned int kiss_get(struct kiss_state* vstate);
double kiss_get_double(struct kiss_state* vstate);
double kiss_get_double_better(struct kiss_state* vstate);
void init_kiss(struct kiss_state* vstate);
unsigned int randInt();
int kiss_int(struct kiss_state* random_seed, int n);
#pragma once




#endif // !KISS_H


