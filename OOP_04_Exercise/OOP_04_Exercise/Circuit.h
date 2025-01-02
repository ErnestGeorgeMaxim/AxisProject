// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <iostream>
#include <algorithm>
#include <vector>
#include "Car.h"
#include "Weather.h"

class Circuit{
private:
	int length;
	Weather weatherCondition;
	std::vector<Car*> cars;
	std::vector<std::pair<Car*, float>> finalRanks;
	std::vector<Car*> didNotFinish;
public:
	void SetLength(int length) {
		this->length = length;
	}

	void SetWeather(Weather w) {
		this->weatherCondition = w;
	}

	void AddCar(Car* c) {
		cars.push_back(c);
	}
	void Race() {
		for (const auto& car : cars) {
			float speed = car->getAverageSpeed(weatherCondition);
			float fuelNeeded = (length / 100.0) * car->getFuelConsumption();
			if (fuelNeeded <= car->getFuelCapacity()) {
				float time = length / speed;
				finalRanks.emplace_back(std::make_pair(car, time));
			}
			else
				didNotFinish.push_back(car);
		}
	}
	void ShowFinalRanks() {
		std::sort(finalRanks.begin(), finalRanks.end(), [](const std::pair<Car*, float>& a, const std::pair<Car*, float>& b) {
			return a.second < b.second; });
		for (const auto& rank : finalRanks) {
			std::cout << rank.first->getModel() << " finished in " << rank.second << " hours." << std::endl;
		}
	}
	void ShowWhoDidNotFinish() {
		for (const auto& car : didNotFinish) {
			std::cout << car->getModel() << " did not finish." << std::endl;
		}
	}
};

