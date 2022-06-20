#pragma once
#include "Simulation.h"

class PowerSimulation : public Simulation
{
public:
	PowerSimulation();
	~PowerSimulation();
	std::vector<int> createPowerSimulation();
	std::vector<int> createFaultPowerSimulation();
private:
	const int basePower = 100;
	const int maxPower = 800;
	const int cycleWorkDuration = 40;
	const int maxFluctuation = 200;
	const int idleFluctuation = 10;
};
#pragma once
