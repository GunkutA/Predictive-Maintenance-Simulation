#include <random>
#include "GenerateRandom.h"

double GenerateRandom::randomDouble(double minValue, double maxValue)
{
	std::random_device randomDevice;
	std::default_random_engine engine(randomDevice());
	std::uniform_real_distribution<double> distribution(minValue, maxValue);
	return distribution(randomDevice);
};