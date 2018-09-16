#ifndef RANDOM_H
#define RANDOM_H

#include <iostream>
#include <math.h>
#include <time.h>

class Random
{
private:

public:
	Random();

	//! return value from 0.0 - 1.0
	static float rand_0_1(void);

	//! return int value in between min, max (including min and max itself)
	//exp : rani(10.0f,20.0f) , possible results : 10.4f, 19.334f, 12.047f etc)
	static float randf(float min, float max);

	//! return float value in between min, max (including min and max itself)
	//exp : rani (10,20), possible results : 11, 12, 16,20, etc)
	static float randi(int min, int max);

	//! Set the seed of the randomizer, call this function before performing any randomization
	static void SetSeed(int seed);
};

#endif