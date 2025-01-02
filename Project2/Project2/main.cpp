#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <stdexcept>

class BigInt {
private:
	int* digits; // Pointer la vectorul de cifre
	size_t size; // Dimensiunea vectorului
	bool isNegative; // Semnul numărului

	// Helper functions
	BigInt add(const BigInt& other) const;
	BigInt subtract(const BigInt& other) const;
	BigInt multiply(const BigInt& other) const;
	BigInt divide(const BigInt& other) const;

	void removeLeadingZeros();

public:
	// Constructors
	BigInt();
	BigInt(int oth);
	BigInt(const std::string& number);
	BigInt(const BigInt& other); // Copy constructor
	BigInt& operator=(const BigInt& other); // Copy assignment operator
	~BigInt(); // Destructor

	// Overloaded operators
	BigInt operator+(const BigInt& other) const;
	BigInt operator+(int other) const;
	BigInt operator%(const BigInt& other) const;
	BigInt operator-(const BigInt& other) const;
	BigInt operator~() const;
	BigInt operator*(const BigInt& other) const;
	BigInt operator*(int other) const;
	BigInt operator/(const BigInt& other) const;

	// Overloaded stream operators
	friend std::ostream& operator<<(std::ostream& os, const BigInt& bigInt);
	friend std::istream& operator>>(std::istream& is, BigInt& bigInt);
	bool operator>=(const BigInt& other) const;
	bool operator==(const BigInt& other) const;
	bool operator<(const BigInt& other) const;
};

// Constructor implicit
BigInt::BigInt() : digits(new int[1] { 0 }), size(1), isNegative(false) {}

// Constructor din string
BigInt::BigInt(const std::string& number) {
	if (number.empty()) {
		throw std::invalid_argument("Invalid number string");
	}

	isNegative = number[0] == '-';
	size_t startIdx = isNegative ? 1 : 0;
	size = number.size() - startIdx;

	digits = new int[size];
	for (size_t i = 0; i < size; ++i) {
		if (!isdigit(number[number.size() - 1 - i])) {
			throw std::invalid_argument("Invalid character in number string");
		}
		digits[i] = number[number.size() - 1 - i] - '0';
	}

	removeLeadingZeros();
}

// Constructor de copiere
BigInt::BigInt(const BigInt& other) : digits(new int[other.size]), size(other.size), isNegative(other.isNegative) {
	std::copy(other.digits, other.digits + other.size, digits);
}

bool BigInt::operator>=(const BigInt& other) const {
	if (isNegative != other.isNegative) {
		return !isNegative;
	}

	if (size != other.size) {
		return size > other.size == !isNegative;
	}

	for (size_t i = size; i > 0; --i) {
		if (digits[i - 1] != other.digits[i - 1]) {
			return digits[i - 1] > other.digits[i - 1] == !isNegative;
		}
	}
	return true;
}

bool BigInt::operator==(const BigInt& other) const
{
	if (size != other.size)
		return false;
	for (int i = 0; i < size || i < other.size; ++i)
		if (digits[i] != other.digits[i])
			return false;
	return true;
}

bool BigInt::operator<(const BigInt& other) const {
	return !(*this >= other);
}
BigInt::BigInt(int oth)
{
	std::string num = std::to_string(oth);
	*this = BigInt(num);
}

// Operator de atribuire prin copiere
BigInt& BigInt::operator=(const BigInt& other) {
	if (this == &other) {
		return *this;
	}

	delete[] digits;

	size = other.size;
	isNegative = other.isNegative;
	digits = new int[size];
	std::copy(other.digits, other.digits + other.size, digits);

	return *this;
}

// Destructor
BigInt::~BigInt() {
	delete[] digits;
}

// Helper function to remove leading zeros
void BigInt::removeLeadingZeros() {
	while (size > 1 && digits[size - 1] == 0) {
		--size;
	}
}

// Arithmetic operations
BigInt BigInt::add(const BigInt& other) const {
	// Handle addition
	size_t maxSize = std::max(size, other.size) + 1;
	int* resultDigits = new int[maxSize] {0};

	size_t i = 0, carry = 0;
	for (; i < size || i < other.size; ++i) {
		int digitSum = carry;
		if (i < size) digitSum += digits[i];
		if (i < other.size) digitSum += other.digits[i];
		carry = digitSum / 10;
		resultDigits[i] = digitSum % 10;
	}

	if (carry) {
		resultDigits[i++] = carry;
	}

	BigInt result;
	delete[] result.digits;
	result.size = i;
	result.digits = new int[result.size];
	std::copy(resultDigits, resultDigits + result.size, result.digits);
	delete[] resultDigits;
	return result;
}

BigInt BigInt::subtract(const BigInt& other) const {
	// Handle subtraction
	if (~*this < ~other) {
		BigInt result = (~other).subtract(~(*this));
		result.isNegative = !isNegative;
		return result;
	}

	size_t maxSize = size;
	int* resultDigits = new int[maxSize] {0};

	int borrow = 0;
	for (size_t i = 0; i < size; ++i) {
		int digitSub = digits[i] - (i < other.size ? other.digits[i] : 0) - borrow;
		if (digitSub < 0) {
			digitSub += 10;
			borrow = 1;
		}
		else {
			borrow = 0;
		}
		resultDigits[i] = digitSub;
	}

	BigInt result;
	delete[] result.digits;
	result.size = maxSize;
	result.digits = new int[result.size];
	std::copy(resultDigits, resultDigits + result.size, result.digits);
	result.removeLeadingZeros();
	delete[] resultDigits;
	return result;
}

BigInt BigInt::multiply(const BigInt& other) const {
	// Handle multiplication
	size_t resultSize = size + other.size;
	int* resultDigits = new int[resultSize] {0};

	for (size_t i = 0; i < size; ++i) {
		int carry = 0;
		for (size_t j = 0; j < other.size || carry; ++j) {
			long long current = resultDigits[i + j] + digits[i] * (j < other.size ? other.digits[j] : 0) + carry;
			resultDigits[i + j] = current % 10;
			carry = current / 10;
		}
	}

	BigInt result;
	delete[] result.digits;
	result.size = resultSize;
	result.digits = new int[result.size];
	std::copy(resultDigits, resultDigits + result.size, result.digits);
	result.isNegative = isNegative != other.isNegative;
	result.removeLeadingZeros();
	delete[] resultDigits;
	return result;
}

BigInt BigInt::operator~() const
{
	BigInt absolute = *this;
	absolute.isNegative = false;
	return absolute;
}
BigInt BigInt::divide(const BigInt& other) const {
	// Handle division
	if (other == BigInt("0")) {
		throw std::domain_error("Division by zero");
	}

	BigInt dividend = *this;
	BigInt divisor = other;
	dividend.isNegative = false;
	divisor.isNegative = false;

	BigInt quotient;
	delete[] quotient.digits;
	quotient.size = size;
	quotient.digits = new int[quotient.size] { 0 };

	BigInt current;
	for (int i = size - 1; i >= 0; --i) {
		current = current * BigInt("10") + digits[i];
		int q = 0;
		while (current >= divisor) {
			current = current - divisor;
			++q;
		}
		quotient.digits[i] = q;
	}

	quotient.isNegative = isNegative != other.isNegative;
	quotient.removeLeadingZeros();
	return quotient;
}

// Overloaded operators
BigInt BigInt::operator+(const BigInt& other) const {
	if (isNegative == other.isNegative) {
		BigInt result = add(other);
		result.isNegative = isNegative;
		return result;
	}
	else {
		if (isNegative) {
			return other.subtract(*this);
		}
		else {
			return subtract(other);
		}
	}
}

BigInt BigInt::operator%(const BigInt& other) const {
	BigInt rest = ~(*this) - other * (~(*this) / ~other);
	return rest;
}
BigInt BigInt::operator+(int oth) const {
	BigInt other(oth);
	if (isNegative == other.isNegative) {
		BigInt result = add(other);
		result.isNegative = isNegative;
		return result;
	}
	else {
		if (isNegative) {
			return other.subtract(*this);
		}
		else {
			return subtract(other);
		}
	}
}

BigInt BigInt::operator-(const BigInt& other) const {
	if (isNegative == other.isNegative) {
		if (*this >= other) {
			BigInt result = subtract(other);
			result.isNegative = isNegative;
			return result;
		}
		else {
			BigInt result = other.subtract(*this);
			result.isNegative = !isNegative;
			return result;
		}
	}
	else {
		BigInt result = add(other);
		result.isNegative = isNegative;
		return result;
	}
}

BigInt BigInt::operator*(const BigInt& other) const {
	BigInt result = multiply(other);
	return result;
}

BigInt BigInt::operator/(const BigInt& other) const {
	BigInt result = divide(other);
	//result.isNegative = isNegative != other.isNegative;
	return result;
}

// Stream operators
std::ostream& operator<<(std::ostream& os, const BigInt& bigInt) {
	if (bigInt.isNegative) {
		os << '-';
	}
	for (size_t i = bigInt.size; i > 0; --i) {
		os << bigInt.digits[i - 1];
	}
	return os;
}

std::istream& operator>>(std::istream& is, BigInt& bigInt) {
	std::string number;
	is >> number;
	bigInt = BigInt(number);
	return is;
}

// Main function to test the implementation
int main() {
	BigInt num1("92");
	BigInt num2("-198");

	BigInt sum = num1 + num2;
	BigInt diff = num1 - num2;
	BigInt prod = num1 * num2;
	BigInt quot = num2 / num1;
	BigInt rest = num2 % num1;

	std::cout << "Sum: " << sum << std::endl;
	std::cout << "Difference: " << diff << std::endl;
	std::cout << "Product: " << prod << std::endl;
	std::cout << "Quotient: " << quot << std::endl;
	std::cout << "Rest: " << rest << std::endl;

	return 0;
}