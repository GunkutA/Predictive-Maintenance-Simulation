#include "Simulation.h"
#pragma once

class TempSimulation : public Simulation
{
public:
	TempSimulation();
	~TempSimulation(){};
	std::vector<double> createFaultTempSimulation();
	std::vector<double> createTempSimulation();
	double getCoolingCoefficient(double& coolingCoefficient);
private:
	const int targetTemp = 35;
	const int baseTemp = 20;
	const int targetTempInFault = 80;

};
