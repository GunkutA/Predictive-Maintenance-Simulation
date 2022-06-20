#include "Simulation.h"

Simulation::Simulation()
{
	cycleStatus = accelerating;
}
int Simulation::getCycleAccelerationDuration()
{
	return cycleAccelerationDuration;
}
int Simulation::getCycleConstantDuration()
{
	return cycleConstantDuration;
}
int Simulation::getCycleCount()
{
	return cycleCount;
}

int Simulation::getCycleDuration()
{
	return cycleDuration;
}

int Simulation::getCycleIdleDuration()
{
	return cycleIdleDuration;
}