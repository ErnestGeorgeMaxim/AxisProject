// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include "Car.h"
class Fiat : public Car{
public:
	Fiat() {
		this->carModel = "Grande Panda";
		this->fuelCapacity = 40;
		this->fuelConsumption = 5.8;
		averageSpeed[0] = 51.3;
		averageSpeed[1] = 240.5;
		averageSpeed[2] = 46.8;
	}
	std::string getModel() const override { return carModel; }
	void setModel(const std::string& model) override { carModel = model; }
	float getFuelCapacity() const override { return fuelCapacity; }
	float getFuelConsumption() const override { return fuelConsumption; }
	float getAverageSpeed(Weather weather) override {
		return averageSpeed[static_cast<int>(weather)];
	}
};

