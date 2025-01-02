#pragma once
#include <cstdint>

class IPriceable {
public:
	virtual uint16_t GetVAT() const = 0;
	virtual float GetPrice() const = 0;
};