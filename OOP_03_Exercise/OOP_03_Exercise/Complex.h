// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#pragma once
#include <iostream>
#include <cmath>

class Complex {
private:
    double real_data;
    double imag_data;

public:
    Complex() {
        this->real_data = 0;
        this->imag_data = 0;
    }
    Complex(double real, double imag) {
        this->real_data = real;
        this->imag_data = imag;
    }

    bool is_real() const {
        return imag() == 0;
    }

    double real() const {
        return real_data;
    }
    void setReal(const double& real) {
        this->real_data = real;
    }
    double imag() const {
        return imag_data;
    }
    void setImag(const double& imag) {
        this->imag_data = imag;
    }
    double abs() const {
        return sqrt(real() * real() + imag() * imag());
    }
    Complex conjugate() const {
        return { real(), -imag() };
    }

    Complex& operator()(double real, double imag) {
        this->real_data = real;
        this->imag_data = imag;
        return *this;
    }

    Complex& operator++() {
        this->real_data++;
        return *this;
    }

    Complex operator++(int) {
        Complex temp = *this;
        ++(*this);
        return temp;
    }

    Complex& operator--() {
        this->real_data--;
        return *this;
    }

    Complex operator--(int) {
        Complex temp = *this;
        --(*this);
        return temp;
    }
};

Complex operator+(const Complex& l, const Complex& r) {
    Complex result;
    result.operator()(l.real() + r.real(), l.imag() + r.imag());
    return result;
}

Complex operator-(const Complex& l, const Complex& r) {
    Complex result;
    result.operator()(l.real() - r.real(), l.imag() - r.imag());
    return result;
}

Complex operator-(const Complex& l, double r) {
    Complex result;
    result.operator()(l.real() - r, l.imag());
    return result;
}

Complex operator-(double l, const Complex& r) {
    Complex result;
    result.operator()(r.real() - l, r.imag());
    return result;
}

Complex operator*(const Complex& l, const Complex& r) {
    Complex result;
    result.operator()(l.real() * r.real() - l.imag() * r.imag(), l.real() * r.imag() + l.imag() * r.real());
    return result;
}

Complex operator*(const Complex& l, double r) {
    Complex result;
    result.operator()(l.real() * r, l.imag() * r);
    return result;
}

Complex operator*(double l, const Complex& r) {
    Complex result;
    result.operator()(r.real() * l, r.imag() * l);
    return result;
}

Complex operator+(const Complex& l, double r) {
    Complex result;
    result.operator()(l.real() + r, l.imag());
    return result;
}
Complex operator+(double l, const Complex& r){
    Complex result;
    result.operator()(r.real() + l, r.imag());
    return result;
}

Complex operator-(const Complex& obj) {
    Complex result;
    result.operator()(-obj.real(), -obj.imag());
    return result;
}

bool operator!=(const Complex& l, const Complex& r) {
    return(l.real() != r.real() && l.imag() != r.imag());
}

bool operator==(const Complex& l, const Complex& r) {
    return (l.real() == r.real() && l.imag() == r.imag());
}

std::ostream& operator<<(std::ostream& out, const Complex& complex) {
    if (complex.imag() == 0 && complex.real() != 0)
        out << complex.real() << "\n";
    else if (complex.real() == 0 && complex.imag() != 0)
        out << complex.imag() << "i\n";
    else if (complex.real() < 0 && complex.imag() < 0)
        out << "(" << complex.real() << ") + (" << complex.imag() << "i)\n";
    else if (complex.real() < 0 && complex.imag() > 0)
        out << "(" << complex.real() << ") + " << complex.imag() << "i\n";
    else if (complex.real() > 0 && complex.imag() < 0)
        out << complex.real() << " + (" << complex.imag() << "i)\n";
    else if (complex.real() < 0 && complex.imag() == 0)
        out << "(" << complex.real() << ")" << "\n";
    else if (complex.imag() < 0 && complex.real() == 0)
        out << "(" << complex.imag() << "i)" << "\n";
    else if (complex.real() == 0 && complex.imag() == 0)
        out << "Doesn't exists!\n";
    else 
        out << complex.real() << " + " << complex.imag() << "i\n";
    return out;
}

