// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <iostream>
#include <cstring>
#include <string>
#include <stdexcept>

class Number {
private:
    char* number;
    int base;
    void fromDecimal(int decimalValue) {
        std::string num;
        int temp = decimalValue;

        while (temp > 0) {
            int remainder = temp % base;
            if (remainder < 10)
                num = char(remainder + '0') + num;
            else
                num = char(remainder - 10 + 'A') + num;
            temp /= base;
        }

        if (num.empty()) {
            num = "0"; // Handle the case for zero input
        }

        delete[] number;
        number = new char[num.length() + 1];
        std::strcpy(number, num.c_str());
    }
public:
    Number(const char* value, int base = 10) {
        this->base = base;
        number = new char[strlen(value) + 1];
        strcpy(number, value);
    }
    Number(int value,int base = 10) {
        this->base = base;
        fromDecimal(value); // Convert int value to base and store in 'number'
    }
    ~Number() {
        delete[] number;
    }
    Number(const Number& other) {
        base = other.base;
        number = new char[strlen(other.number) + 1];
        strcpy(number, other.number);
    }
    int getDigitCount() const {
        return strlen(this->number);
    }
    int getBase() const {
        return this->base;
    }
    char operator[](int index) const {
        if (index >= 0 && index < getDigitCount()) {
            return number[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }
    void SwitchBase(int newBase) {
        int decimalValue = this->decimalValue();
        this->base = newBase;
        fromDecimal(decimalValue);
    }
    int decimalValue() const {
        int decimalValue = 0;
        int p = 1;

        // Convert from current base to decimal
        for (int i = strlen(number) - 1; i >= 0; --i) {
            int digit = (number[i] >= '0' && number[i] <= '9') ? number[i] - '0' : (number[i] - 'A' + 10);
            decimalValue += digit * p;
            p *= base;
        }

        return decimalValue;
    }
    void Print() const {
        std::cout << "Number: " << number << ", Base: " << base << "\n";
    }
    bool operator>(const Number& other) const {
        return decimalValue() > other.decimalValue();
    }
    bool operator<(const Number& other) const {
        return decimalValue() < other.decimalValue();
    }
    bool operator==(const Number& other) const {
        return decimalValue() == other.decimalValue();
    }
    bool operator>=(const Number& other) const {
        return decimalValue() >= other.decimalValue();
    }
    bool operator<=(const Number& other) const {
        return decimalValue() <= other.decimalValue();
    }
    Number& operator=(const Number& other) {
        if (this != &other) {
            delete[] number;
            number = new char[strlen(other.number) + 1];
            strcpy(number, other.number);
            base = other.base;
        }
        return *this;
    }
    Number& operator=(int value) {
        fromDecimal(value);
        return *this;
    }
    Number& operator=(char value) {
        int decimalValue = static_cast<int>(value);
        fromDecimal(decimalValue);
        return *this;
    }
    Number& operator--() {
        int length = getDigitCount();
        if (length == 0) {
            // Handle the case where the number is empty
            return *this;
        }

        // Shift all characters to the left
        for (int i = 0; i < length - 1; ++i) {
            number[i] = number[i + 1];
        }

        // Null-terminate the string
        number[length - 1] = '\0';

        return *this;
    }
    Number operator--(int) {
        number[getDigitCount() - 1] = '\0';
        return (*this);
    }
    Number& operator+=(const Number& n) {
        int resultBase = std::max(getBase(), n.getBase());
        int decimalSum = decimalValue() + n.decimalValue();
        fromDecimal(decimalSum);
        base = resultBase; // Update the base of the current object
        return *this;
    }
    friend Number operator+(const Number& n1,const Number& n2);
    friend Number operator-(const Number& n1,const Number& n2);
};

Number operator+(const Number& n1, const Number& n2) {
    int resultBase = std::max(n1.getBase(), n2.getBase());
    int decimalSum = n1.decimalValue() + n2.decimalValue();
    Number result("0", resultBase);
    result.fromDecimal(decimalSum);
    return result;
}

Number operator-(const Number& n1, const Number& n2) {
    int resultBase = std::max(n1.getBase(), n2.getBase());
    int decimalDif = abs(n1.decimalValue() - n2.decimalValue());
    Number result("0", resultBase);
    result.fromDecimal(decimalDif);
    return result;
}

