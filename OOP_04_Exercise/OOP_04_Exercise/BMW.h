// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include "Car.h"
class BMW : public Car{
public:
	BMW() {
		this->carModel = "M4 CSL";
		this->fuelCapacity = 59;
		this->fuelConsumption = 9.8;
		averageSpeed[0] = 70.5;
		averageSpeed[1] = 307.2;
		averageSpeed[2] = 40.4;
	}
	std::string getModel() const override { return carModel; }
	void setModel(const std::string& model) override { carModel = model; }
	float getFuelCapacity() const override { return fuelCapacity; }
	float getFuelConsumption() const override { return fuelConsumption; }
	float getAverageSpeed(Weather weather)override {
		return averageSpeed[static_cast<int>(weather)];
	}
};

