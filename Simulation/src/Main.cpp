#include <iostream>
#include "Main.h"
#include <time.h>
#include <stdlib.h>
#include <fstream>
#include <string>
#include "GenerateRandom.h"
#include "RandomNoise.h"
#include "TempSimulation.h"
#include "TCP_IP_server.h"
#include "TCP_IP_client.h"
#include <windows.h>
#define CREATE_FAULT_TEMP_SIM (0)
#define CREATE_TEMP_SIM (0)
constexpr int cycleDuration = 170;
constexpr int cycleHeatingDuration = 40;
constexpr int cycleTopDuration = 10;
constexpr int cycleCoolingDuration = 40;
constexpr int cycleIdleDuration = 80;
constexpr double coolingDeteriorationRate = 0.9999;


void createCSVFile(std::string fileName, std::vector<double> tempData)
{
	//create CSV file
	std::ofstream myFile(fileName);
	for (int i = 0; i < tempData.size(); i++)
	{
		myFile << tempData.at(i) << "\n";
	}
	myFile.close();

}

void TempSimulator::createFaultTempSim()
{
	//now the machine will reach the MaxTemp in CycleCount/2 cycles. (In case of no cool down)
	double maxFluctuationHeating = ((double)(targetTempInFault - baseTemp) / (double)cycleHeatingDuration/(20)); //Without cooling 20 cycles it will reach max Temp (since its random values [0,1]
	//double maxFluctuationCooling = ((double)(targetTempInFault - baseTemp) / ((double)cycleHeatingDuration*(1.5)*(cycleCount))); //Multiply CycleHeating Duration by 1.5
	//double maxFluctuationCooling = (maxFluctuationHeating * cycleHeatingDuration * 0.833 / (cycleCoolingDuration + cycleIdleDuration)); //cooling is 0.84 times slower than heating
	double maxFluctuationCooling = maxFluctuationHeating;
	double tempData = baseTemp;
	//Enter first element of array so we can use vector.back() and won't have empy vector fault.
	simulationDataFault.push_back(baseTemp);
	double topPoint = baseTemp;
	for (int i = 0; i < getCycleCount(); i++)
	{
		for (int k = 0; k < cycleDuration; k++)
		{
			if ((simulationDataFault.back() >= targetTempInFault - 1) && (k < cycleTopDuration + cycleHeatingDuration)) // If the machine reaches MaxTemp -1 degrees. It will ossilate in there.
			{
				cylePeriod = top;
			}
			else if (k >= cycleTopDuration + cycleHeatingDuration)
			{
				cylePeriod = cooling;
			}
				//Random equation : (max - min) * ( (double)rand() / (double)RAND_MAX ) + min
				switch (cylePeriod)
				{
				case heating:
					tempData = (maxFluctuationHeating) * (GenerateRandom::randomDouble(0, 1)) + simulationDataFault.back();
					topPoint = tempData;
					if (k >= cycleHeatingDuration) cylePeriod = top;
					break;
				case top:
					tempData = ( 0.5 * maxFluctuationHeating) * (GenerateRandom::randomDouble(-1, 1)) + topPoint ;
					if (k >= cycleTopDuration + cycleHeatingDuration) cylePeriod = cooling;
					else if(k< cycleHeatingDuration) cylePeriod = heating;
					break;
				case cooling:
					maxFluctuationCooling = maxFluctuationCooling * (coolingDeteriorationRate); // As time passes, the cooling effectiveness will decrease.
					if (simulationDataFault.back() <= baseTemp + 3.0)// If the Current temperature is <= baseTemp+3 C Then go idle instead of cooling.
					{
						tempData = (0.5 * maxFluctuationCooling) * (GenerateRandom::randomDouble(-1, 1)) + topPoint;
						topPoint = tempData;
						std::cout << i << "   ->   " << "idle " << std::endl;
					}
					else if(simulationDataFault.back()<=baseTemp+4) //when currentTemp is between baseTemp+5 and baseTemp+3, reduce cooling to smooth the change 
					{
						tempData = (simulationDataFault.back()) - ((maxFluctuationCooling) * (0.75) * (GenerateRandom::randomDouble(0, 1)));//Multiply by 0.33 to smooth change from cooling to idle
						topPoint = tempData;
					}
					else //Else is normal cooling
					{
						tempData = (simulationDataFault.back()) - ((maxFluctuationCooling) * (GenerateRandom::randomDouble(0, 1)));
						topPoint = tempData;
					}
					if (k >= cycleTopDuration + cycleHeatingDuration + cycleCoolingDuration + cycleIdleDuration - 1) cylePeriod = heating;
					else if(k< cycleTopDuration + cycleHeatingDuration)cylePeriod = top;
					break;
				}
			
			simulationDataFault.push_back(tempData);
		//	std::cout << i << " ---> " << k << " ->  " << cylePeriod << "  ->  " << simulationDataFault.at(k + (i * 170)) << std::endl;
			//std::cout << maxFluctuationCooling << "  ->  " << maxFluctuationHeating << std::endl;,
			
		}
	}
}


int main()
{
	std::unique_ptr<TempSimulation> TS = std::make_unique<TempSimulation>();
	char buffer[4096];
	std::cout << "Simulation is created." << std::endl;
	TempSimulator device;
	device.deviceRole = device.deviceClient; //Set server to either Server or Client
	if (CREATE_FAULT_TEMP_SIM)
	{
		//TS->createFaultTempSimulation();
		createCSVFile("TemperatureSimulation.csv", TS->createTempSimulation());
	}
	if (CREATE_TEMP_SIM)
	{
		//TS->createTempSimulation();
		createCSVFile("TemperatureFaultSimulation.csv", TS->createFaultTempSimulation());
	}
	if (device.deviceRole == device.deviceClient)
	{
		std::vector <double> tempSimVector = TS->createTempSimulation(); // Use this vector if you want to create and send TemperatureSimulation data
		//std::vector <double> tempSimVector = TS->createFaultTempSimulation(); //Use this vector if you want to create and send Fault TemperatureSimulation data
		std::unique_ptr <TCP_IP_client> TCP_client = std::make_unique<TCP_IP_client>();
		TCP_client->initWinSocket();
		TCP_client->createSocket();
		TCP_client->connectServer();
		std::string userInput;
		for (int i = 0; i < tempSimVector.size(); i++)
		{
			TCP_client->sendData(std::to_string(tempSimVector.at(i)), sizeof(tempSimVector.at(i)) + 1); // send Data
			std::cout << "Data sent:" << std::to_string(tempSimVector.at(i)) << std::endl;
			Sleep(1000);
		}
	}
	else if (device.deviceRole == device.deviceServer)
	{
		//Create server

		std::unique_ptr<TCP_IP_Server> TCP_server = std::make_unique<TCP_IP_Server>();
		TCP_server->createSocket();
		TCP_server->bindSocket();
		TCP_server->startListening();

		//Server Trial
		while (1)
		{
			memset(buffer, 0, 4096);
			int bytesReceived = recv(TCP_server->socket_accept, buffer, 4096, 0);
			if (bytesReceived == SOCKET_ERROR)
			{
				std::cerr << "Error in receive. Quitting." << std::endl;
				break;
			}
			if (bytesReceived == 0)
			{
				std::cout << "Client disconnected" << std::endl;
				break;
			}
			TCP_server->sendData(buffer, bytesReceived + 1);
		}
		closesocket(TCP_server->socket_accept);
		WSACleanup();
	}

}