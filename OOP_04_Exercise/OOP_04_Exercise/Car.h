// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <iostream>
#include "Weather.h"

class Car{
protected:
	std::string carModel;
	float fuelCapacity;
	float fuelConsumption;
	float averageSpeed[3];
public:
	virtual std::string getModel() const = 0;
	virtual void setModel(const std::string& model) = 0;
	virtual float getFuelCapacity() const = 0;
	virtual float getFuelConsumption() const = 0;
	virtual float getAverageSpeed(Weather weather) = 0;
};

