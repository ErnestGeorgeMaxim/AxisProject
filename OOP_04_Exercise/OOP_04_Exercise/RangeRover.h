// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include "Car.h"
class RangeRover : public Car{
public:
	RangeRover() {
		this->carModel = "Velar";
		this->fuelCapacity = 83;
		this->fuelConsumption = 10.2;
		averageSpeed[0] = 71.5;
		averageSpeed[1] = 304.9;
		averageSpeed[2] = 69.3;
	}
	std::string getModel() const override { return carModel; }
	void setModel(const std::string& model) override { carModel = model; }
	float getFuelCapacity() const override { return fuelCapacity; }
	float getFuelConsumption() const override { return fuelConsumption; }
	float getAverageSpeed(Weather weather) override {return averageSpeed[static_cast<int>(weather)];}
};

