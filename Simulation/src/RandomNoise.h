#ifndef RandomNoise_h
#define RandomNoise_h
#endif
#include "TimeSeries.h"
#include <random>
#pragma once
class RandomNoise : public TimeSeries
{
	double standardDeviation;
	std::default_random_engine generator;
	std::normal_distribution<double> distribution;

public:
	RandomNoise(double _standardDeviation, int seed);
	  ~RandomNoise() {}
	 double getValue(double time) override;
};