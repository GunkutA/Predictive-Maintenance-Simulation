#pragma once
#ifndef TimeSeries_h
#define TimeSeries_h
#endif

class TimeSeries
{
public:
	virtual double getValue(double time) = 0;
	virtual ~TimeSeries(){};
};