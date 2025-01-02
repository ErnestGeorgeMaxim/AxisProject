// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include "Car.h"

class Volvo : public Car{
public:
	Volvo() {
		this->carModel = "S90";
		this->fuelCapacity = 60.1;
		this->fuelConsumption = 9.41;
		averageSpeed[0] = 68.5;
		averageSpeed[1] = 289.5;
		averageSpeed[2] = 50.4;
	}
	std::string getModel() const override { return carModel; }
	void setModel(const std::string& model) override { carModel = model; }
	float getFuelCapacity() const override { return fuelCapacity; }
	float getFuelConsumption() const override { return fuelConsumption; }
	float getAverageSpeed(Weather weather) override {
		return averageSpeed[static_cast<int>(weather)];
	}
};

