#ifndef Main_h
#define Main_h
#endif
#include <vector>


class TempSimulator
{
public:
	//Create a vector to store fluctuation data
	std::vector<double> simulationData;
	std::vector<double> simulationDataFault;
	enum CyclePeriod {  heating, top, cooling, idle };
	enum DeviceRole { deviceServer, deviceClient};
	CyclePeriod cylePeriod;
	DeviceRole deviceRole;
	TempSimulator()
	{
		cycleCount = 200;
		fluctuationChance = 5;
		maxFluctuation = 1;
		baseTemp = 20;
		targetTemp = 35;
		targetTempInFault = 80;
		cylePeriod = heating;
	}

	TempSimulator(int cycleCount, int fluctuationChance, int baseTemp, int maxFluctuation) : cycleCount(cycleCount), fluctuationChance(fluctuationChance),
		baseTemp(baseTemp), maxFluctuation(maxFluctuation)
	{ 
	}
	//Getters
	int getCycleCount()
	{
		return cycleCount;
	}
	int getFluctuationChance()
	{
		return fluctuationChance;
	}
	int getBaseTemp()
	{
		return baseTemp;
	}
	int getMaxFluctuation()
	{
		return maxFluctuation;
	}
	//Setters
	void setCycleCount(int cycleCountSetter)
	{
		cycleCount = cycleCountSetter;
	}
	void setFluctuationChance(int fluctuationChanceSetter)
	{
		fluctuationChance = fluctuationChanceSetter;
	}
	void setBaseTemp(int baseTempSetter)
	{
		baseTemp = baseTempSetter;
	}
	void setMaxFluctuation(int maxFluctuationSetter)
	{
		maxFluctuation = maxFluctuationSetter;
	}
	void createTempSim(); //Create a vector for temperature simulation
	void createCSVFile(std::string fileName, std::vector<double> tempData); //create an CSV file
	void createFaultTempSim(); //Create a vector for temperature simulation
	

private:
	int cycleCount, fluctuationChance, baseTemp, maxFluctuation, targetTemp, targetTempInFault;
	
};
