#include "PowerSimulation.h"

PowerSimulation::PowerSimulation(){}
PowerSimulation::~PowerSimulation(){}

std::vector<int> PowerSimulation::createPowerSimulation()
{
	std::vector<int> powerSimulationDatas;
	cycleStatus = accelerating;
	int tempPower = basePower;
	RandomNoise RandNoise(1, time(NULL));
	for (int i = 0; i < getCycleCount(); i++)
	{
		for (int k = 0; k < getCycleDuration(); k++)
		{
			switch (cycleStatus)
			{
			case accelerating:
				tempPower = maxPower + maxFluctuation * GenerateRandom::randomDouble(-1, 1);
				if (k >= getCycleAccelerationDuration()) cycleStatus = idle;
				break;
			case idle:
				tempPower = basePower + idleFluctuation * GenerateRandom::randomDouble(-1, 1);
				if (k >= getCycleDuration() - 1) cycleStatus = accelerating;
				break;
			}
			powerSimulationDatas.push_back(tempPower);
		}
	}
	return powerSimulationDatas;
}