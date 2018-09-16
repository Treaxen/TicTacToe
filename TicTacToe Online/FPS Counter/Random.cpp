#include "Random.h"

Random::Random()
{
}

float Random::rand_0_1(void)
{
	float result = static_cast<float> (rand() / static_cast<float>(RAND_MAX));
	return result;
}

float Random::randf(float min, float max)
{
	float result = min + static_cast<float> (rand()) / (static_cast<float>(RAND_MAX / (max - min)));
	return result;
}

float Random::randi(int min, int max)
{
	int result = rand() % max + 1 + (min);
	return result;
}

void Random::SetSeed(int seed)
{
	srand(static_cast <unsigned> (seed));
}
