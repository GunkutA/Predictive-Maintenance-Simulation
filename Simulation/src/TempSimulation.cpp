#include "TempSimulation.h"
#include "GenerateRandom.h"
#include "RandomNoise.h"
#include <iostream>

TempSimulation::TempSimulation()
{

}

double TempSimulation::getCoolingCoefficient(double& coolingCoefficient)
{
	const double coolingDeteriorationRate = 0.9999;
	return coolingDeteriorationRate * coolingCoefficient;
}


std::vector<double> TempSimulation::createTempSimulation()
{
	cycleStatus = accelerating;
	std::vector <double> tempSimulationDatas;
	RandomNoise RandNoise(1,time(NULL));
	double tempData = baseTemp;
	double fluctuationCoefficient = (double)(targetTemp - baseTemp) / (getCycleAccelerationDuration());
	tempSimulationDatas.push_back(tempData); //first index of the vector
	for (int i = 0; i < getCycleCount(); i++)
	{
		for(int k = 0; k < getCycleDuration(); k++)
		{
			switch (cycleStatus)
			{
			case accelerating:
				tempData = (fluctuationCoefficient * GenerateRandom::randomDouble(0,1) + baseTemp+(fluctuationCoefficient*(double)(k-1)));
				if (k >= getCycleAccelerationDuration()) cycleStatus = constant;
				break;
			case constant:
				tempData = (fluctuationCoefficient) * RandNoise.getValue(k + (i * 180)) + targetTemp;
				if (k >= getCycleAccelerationDuration() + getCycleConstantDuration()) cycleStatus = idle;
				break;
			case idle:
				if (tempSimulationDatas.back() > baseTemp + 0.5) //If the temperature is greater than baseTemp+0.5 keep cooling
				{
					tempData = tempSimulationDatas.back()-(fluctuationCoefficient*GenerateRandom::randomDouble(0,1));
				}
				else //Else just some random noises
				{
					tempData = (fluctuationCoefficient)*RandNoise.getValue(k + (i * getCycleCount())) + baseTemp;
				}
				if (k >= getCycleAccelerationDuration() + getCycleConstantDuration() + getCycleIdleDuration()-1) cycleStatus = accelerating;
				break;
			}
			tempSimulationDatas.push_back(tempData);
		//	std::cout <<i << "  ->  "<< cycleStatus<< "  ->  "<< tempSimulationDatas.at(k+(170*i)) << std::endl;
		}
	}
	return tempSimulationDatas;
};

std::vector<double> TempSimulation::createFaultTempSimulation()
{
	
	cycleStatus = accelerating;
	int coolingDeteriorationRatio = 0.9999;
	std::vector <double> tempSimulationFaultDatas;
	RandomNoise RandNoise(1, time(NULL));
	double tempData = baseTemp;
	double heatingCoefficient = (double)(targetTempInFault - baseTemp) / (getCycleDuration()*20);//Without cooling 20 cycles it will reach max Temp
	double coolingCoefficient = heatingCoefficient; //At the beginning coolingCoeff is equal to heatingCoeff
	double topPoint = tempData; //For recording the last point before changing state.
	tempSimulationFaultDatas.push_back(tempData); //first index of the vector
	for (int i = 0; i < getCycleCount(); i++)
	{
		for (int k = 0; k < getCycleDuration(); k++)
		{
			double noiseIncreasingRatio = i * 3 / 2;
			if ((tempSimulationFaultDatas.back() >= targetTempInFault - 1) && (k < getCycleAccelerationDuration() + getCycleConstantDuration()))
			{
				cycleStatus = constant;
			}
			else if (k >= (getCycleConstantDuration() + getCycleAccelerationDuration()))
			{
				cycleStatus = idle;
			}
			switch (cycleStatus)
			{
			case accelerating:
				tempData = (heatingCoefficient * GenerateRandom::randomDouble(0, 1)) + tempSimulationFaultDatas.back();
				topPoint = tempData;
				if (k >= getCycleAccelerationDuration()) cycleStatus = constant;
				break;
			case constant:
				tempData = (noiseIncreasingRatio * heatingCoefficient * RandNoise.getValue(k + (i * getCycleCount()))) + targetTempInFault; //Noises increases as time goes
				if (k >= getCycleConstantDuration() + getCycleAccelerationDuration()) cycleStatus = idle;
				else if (k < getCycleAccelerationDuration()) cycleStatus = accelerating;
				break;
			case idle:
				coolingCoefficient *= coolingDeteriorationRatio;
				break;
			}
			tempSimulationFaultDatas.push_back(tempData);
			if (tempSimulationFaultDatas.back() <= baseTemp + 3.0) //// If the Current temperature is <= baseTemp+3 C Then go idle instead of cooling.
			{
				tempData = (coolingCoefficient * RandNoise.getValue(k + (i * getCycleCount())))+topPoint;
				topPoint = tempData;
			}
			else if (tempSimulationFaultDatas.back() <= baseTemp + 5.0)//when currentTemp is between baseTemp+5 and baseTemp+3, reduce cooling to smooth the change 
			{
				tempData = tempSimulationFaultDatas.back() - (coolingCoefficient * (0.75) * GenerateRandom::randomDouble(0, 1));//Multiply by 0.75 to smooth change from cooling to idle
				topPoint = tempData;
			}
			else //Else is normal cooling
			{
				tempData = tempSimulationFaultDatas.back() - (coolingCoefficient * GenerateRandom::randomDouble(0, 1));
				topPoint = tempData;
			}
			if (k >= (getCycleAccelerationDuration() + getCycleConstantDuration() + getCycleIdleDuration() - 1)) cycleStatus = accelerating;
			else if (k < (getCycleAccelerationDuration() + getCycleConstantDuration())) cycleStatus = idle;
			break;
		}
		tempSimulationFaultDatas.push_back(tempData);
	}
	return tempSimulationFaultDatas;
}