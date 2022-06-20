#include <iostream>
#include "RandomNoise.h"


RandomNoise::RandomNoise(double standardDeviation, int seed) :standardDeviation(standardDeviation), distribution(0, standardDeviation)
{
	generator.seed(seed);
};
double RandomNoise::getValue(double time)
{
	return distribution(generator);
}