// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include "Car.h"
class Seat : public Car{
public:
	Seat() {
		this->carModel = "Arona";
		this->fuelCapacity = 40;
		this->fuelConsumption = 6.2;
		averageSpeed[0] = 40.3;
		averageSpeed[1] = 230.2;
		averageSpeed[2] = 30.1;
	}
	std::string getModel() const override { return carModel; }
	void setModel(const std::string& model) override { carModel = model; }
	float getFuelCapacity() const override { return fuelCapacity; }
	float getFuelConsumption() const override { return fuelConsumption; }
	float getAverageSpeed(Weather weather) override {
		return averageSpeed[static_cast<int>(weather)];
	}
};

