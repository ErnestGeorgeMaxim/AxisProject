#pragma once
#include <cstdint>


class IPriceable
{
public:
	virtual ~IPriceable() = default;
	virtual int32_t GetVat() const = 0;
	virtual float GetPrice() const = 0;
};
