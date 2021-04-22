#include <kiss.h>
#include <iostream>



/*JKISS RNG */
unsigned int kiss_get(struct kiss_state* vstate)
{

	struct kiss_state* state = vstate;
	unsigned long long t;
	state->x = 314527869 * state->x + 1234567;
	state->y ^= state->y << 5;
	state->y ^= state->y >> 7;
	state->y ^= state->y << 22;
	t = 4294584393ULL * state->z + state->c;
	state->c = t >> 32;
	state->z = t;
	unsigned int a = state->x + state->y + state->z;
	return a;

}


/*A simple way to get random real number between 0 and 1;*/
double kiss_get_double(struct kiss_state* vstate)
{
	double a = UINT_MAX + 1.0;
	return kiss_get(vstate) / a;
}

/*A better way to get random real number between 0 and 1;*/
double kiss_get_double_better(struct kiss_state* vstate)
{
	double x;
	unsigned int a, b;
	a = kiss_get(vstate) >> 6; /* Upper 26 bits */
	b = kiss_get(vstate) >> 5; /* Upper 27 bits */
	x = (a * 134217728.0 + b) / 9007199254740992.0;
	return x;
}

/*Initialize KISS with randInd()*/
void init_kiss(struct kiss_state* vstate)
{
	struct kiss_state* state = vstate;
	state->x = randInt();
	while (!(state->y = randInt())) 
		std::cout<<"error\n"; /* y must not be zero! */
	state->z = randInt();
	/* We don¡¯t really need to set c as well but let's anyway¡­ */
	/* NOTE: offset c by 1 to avoid z=c=0 */
	state->c = randInt() % 698769068 + 1; /* Should be less than 698769069 */
}

/*Get randome number with rand_s(), in order to seed KISS*/
unsigned int randInt()
{
	unsigned int u, a;
	unsigned int min = 1;
	unsigned int max = 4294967295;
	rand_s(&u);
	a = ((double)u / ((double)(UINT_MAX)+1.0)) * (max - min) + min;
	return a;
}

/*To generate a random integer number between 0 and n-1*/
int kiss_int(struct kiss_state* random_seed, int n)
{
	init_kiss(random_seed);
	int random_int = kiss_get(random_seed) % n;
	return random_int;
}
