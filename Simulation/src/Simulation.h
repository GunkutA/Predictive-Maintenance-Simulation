#ifndef Simulation_h
#define Simulation_h
#endif
#pragma once

class Simulation
{
public:
	Simulation();
	virtual ~Simulation(){};
	int getCycleCount();
	int getCycleDuration();
	int getCycleAccelerationDuration();
	int getCycleConstantDuration();
	int getCycleIdleDuration();
	enum CycleStatus { accelerating, constant, idle };
	CycleStatus cycleStatus;

private:
	const int cycleDuration{ 170 };
	const int cycleAccelerationDuration{ 40 };
	const int cycleConstantDuration{ 10 };
	const int cycleIdleDuration{ 120 };
	const int cycleCount{ 200 };
	

};