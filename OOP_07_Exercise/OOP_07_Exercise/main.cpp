// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <exception>
#include <vector>
#include <queue>

class exception1 : public std::exception {
	virtual const char* what() const throw() {
		return "Impartire la 0!";
	}
};

class exception2 : public std::exception {
	virtual const char* what() const throw() {
		return "Indexul este inafara domeniului!";
	}
};

class Rational {
private:
    long a, b;
    void simplify() {
        long A = a, B = b, r;
        while (B) {
            r = A % B;
            A = B;
            B = r;
        }
        if (A) {
            a /= A;
            b /= A;
        }
    }

public:
    Rational(long a = 0, long b = 1) : a(a), b(b) {}
    long getNumarator() const { return this->a; }
    long getNumitor() const { return this->b; }
    Rational operator+(Rational x) {
        Rational rez;
        rez.a = a * x.b + b * x.a;
        rez.b = b * x.b;
        rez.simplify();
        return rez;
    }
    Rational operator-(Rational x) {
        Rational rez;
        rez.a = a * x.b - b * x.a;
        rez.b = b * x.b;
        rez.simplify();
        return rez;
    }
    Rational operator*(Rational x) {
        Rational rez;
        rez.a = a * x.a;
        rez.b = b * x.b;
        rez.simplify();
        return rez;
    }
    Rational operator/(Rational x) {
        Rational rez;
        rez.a = a * x.b;
        rez.b = b * x.a;
        rez.simplify();
        return rez;
    }
    Rational operator=(Rational x) {
        a = x.a;
        b = x.b;
        return *this;
    }
    Rational operator+=(Rational x) {
        return *this = *this + x;
    }
    Rational operator-=(Rational x) {
        return *this = *this - x;
    }
    Rational operator*=(Rational x) {
        return *this = *this * x;
    }
    Rational operator/=(Rational x) {
        return *this = *this / x;
    }
    bool operator==(Rational x) {
        return(a == x.a && b == x.b);
    }
    bool operator!=(Rational x) {
        return(a != x.a && b != x.b);
    }
    Rational& operator++() {
        a += b;
        return *this;
    }
    Rational operator++(int) {
        Rational temp = *this;
        ++(*this);
        return temp;
    }
    Rational& operator--() {
        a -= b;
        return *this;
    }
    Rational operator--(int) {
        Rational temp = *this;
        --(*this);
        return temp;
    }
    long operator!() {
        return !a;
    }
    friend std::ostream& operator<<(std::ostream& os, Rational x);
    friend std::istream& operator>>(std::istream& in, Rational& x);
};

std::ostream& operator<<(std::ostream& os, Rational x) {
    os << x.a << "/" << x.b;
    return os;
}
std::istream& operator>>(std::istream& in, Rational& x) {
    in >> x.a >> x.b;
    return in;
}


class Complex {
private:
    double real;
    double imag;
public:
    Complex(double real = 0, double imag = 0) : real(real), imag(imag) {}
    double getReal() const { return this->real; }
    double getImag() const { return this->imag; }
    void setReal(double real) { this->real = real; }
    void setImag(double imag) { this->imag = imag; }
    friend std::ostream& operator<<(std::ostream& os, Complex a);
    friend std::istream& operator>>(std::istream& in, Complex& a);
    Complex operator*(Complex a) {
        Complex rez;
        rez.real = (real * a.real) - (imag * a.imag);
        rez.imag = real * a.imag + imag * a.real;
        return rez;
    }
    Complex operator+(Complex a) {
        Complex rez;
        rez.real = real + a.real;
        rez.imag = imag + a.imag;
        return rez;
    }
    Complex operator-(Complex a) {
        Complex rez;
        rez.real = real - a.real;
        rez.imag = imag - a.imag;
        return rez;
    }
    Complex operator=(Complex a) {
        real = a.real;
        imag = a.imag;
        return *this;
    }
    Complex operator+=(Complex a){
        return *this = *this + a;
    }
    Complex operator-=(Complex a) {
        return *this = *this - a;
    }
    Complex operator*=(Complex a) {
        return *this = *this * a;
    }
    bool operator==(Complex a) {
        return (real == a.real && imag == a.imag);
    }
    bool operator!=(Complex a) {
        return (real != a.real || imag != a.imag);
    }
    Complex operator !(){
        Complex rez;
        rez.real = real;
        rez.imag = -imag;
        return rez;
    }
    friend Complex& operator*(Complex a, double x);
    friend Complex& operator*(double x, Complex a);
    friend Complex& operator+(Complex a, double x);
    friend Complex& operator+(double x, Complex a);
    friend Complex& operator-(Complex a, double x);
    friend Complex& operator-(double x, Complex a);

};

Complex& operator*(Complex a, double x) {
    Complex rez;
    rez.real = a.real * x;
    rez.imag = a.imag * x;
    return rez;
}
Complex& operator*(double x,Complex a) {
    Complex rez;
    rez.real = a.real * x;
    rez.imag = a.imag * x;
    return rez;
}
Complex& operator+(Complex a, double x) {
    Complex rez;
    rez.real = a.real + x;
    rez.imag = a.imag;
    return rez;
}
Complex& operator+(double x, Complex a) {
    Complex rez;
    rez.real = a.real + x;
    rez.imag = a.imag;
    return rez;
}
Complex& operator-(Complex a, double x) {
    Complex rez;
    rez.real = a.real - x;
    rez.imag = a.imag;
    return rez;
}
Complex& operator-(double x, Complex a) {
    Complex rez;
    rez.real = a.real - x;
    rez.imag = a.imag;
    return rez;
}

std::ostream& operator<<(std::ostream& os, Complex a) {
    os << a.real << " + " << a.imag << "i\n";
    return os;
}

std::istream& operator>>(std::istream& in, Complex& a) {
    in >> a.real >> a.imag;
    return in;
}

class String {
private:
    char* s;
public:
    String(const char* st = "") {
        s = new char[strlen(st) + 1];
        strcpy(s, st);
    }
    String(const String& str) {
        delete[] s;
        s = new char[strlen(str.s) + 1];
        strcpy(s, str.s);
    }
    ~String() {
        delete[] s;
    }
    String operator+(String str) {
        char* st;
        st = new char[strlen(str.s) + 1 + strlen(s)];
        String str2(st);
        sprintf(str2.s, "%s%s", s, str.s);
        return str2;
    }
    String operator=(const String& str) {
        delete[] s;
        s = new char[strlen(str.s) + 1];
        strcpy(s, str.s);
        return *this;
    }
    String operator+=(const String& str) {
        return *this = *this + str;
    }
    int operator==(const String& str) {
        if (!strcmp(s, str.s))
            return 1;
        return 0;
    }
    int operator<(const String& str) {
        if (strcmp(s, str.s) < 0)
            return 1;
        return 0;
    }
    int operator<=(const String& str)
    {
        if (strcmp(s, str.s) <= 0) 
            return 1;
        return 0;
    }
    int operator>(const String& str)
    {
        if (strcmp(s, str.s) > 0) 
            return 1;
        return 0;
    }
    int operator>=(const String& str)
    {
        if (strcmp(s, str.s) >= 0) 
            return 1;
        return 0;
    }
    void setString(const char* str) {
        delete[] s;
        s = new char[strlen(str) + 1];
        strcpy(s, str);
    } 
    void get(char* st) // extragere sir caractere din obiectul string
    {
        strcpy(st, s);
    }
    int operator!() // se returneaza lungimea string-ului
    {
        return strlen(s);
    }
    char operator[](int i) // returneaza caracterul de pe pozitia i
    {
        return s[i];
    }
    friend std::ostream& operator<<(std::ostream& os, const String& str);
    friend std::istream& operator<<(std::istream& in, const String& str);

};

std::ostream& operator<<(std::ostream& os, const String& str) {
    os << str.s;
    return os;
}
std::istream& operator<<(std::istream& in, const String& str) {
    in >> str.s;
    return in;
}

class Figure {
protected:
    char name[20];
public:
    virtual float arie() = 0;
    virtual float perimetru() = 0;
    char* getName() {
        return name;
    }
};

class Rectangle : public Figure {
protected:
    float x1, y1, x2, y2;
public:
    Rectangle(float x1, float y1, float x2, float y2) {
        strcpy(name, "Rectangle");
        this->x1 = x1;
        this->y1 = y1;
        this->x2 = x2;
        this->y2 = y2;
    }
    virtual float arie() {
        return fabs((x2 - x1) * (y2 - y1));
    }
    virtual float perimetru() {
        return 2 * (fabs(x2 - x1) + fabs(y2 - y1));
    }

};

class Square : public Rectangle {
protected:
    float x, y, l;
public:
    Square(float x, float y, float l) : Rectangle(x,y,x+l,y+l){
        strcpy(name, "Square");
        this->x = x;
        this->y = y;
        this->l = l;
    }
    virtual float arie() {
        return 4 * l;
    }
    virtual float perimetru() {
        return Rectangle::perimetru();
    }
};

#define PI 3.14159
class Circle : public Figure {
protected:
    float x, y, r;
public:
    Circle(float x, float y, float r) {
        strcpy(name, "Circle");
        this->x = x;
        this->y = y;
        this->r = r;
    }
    virtual float arie() {
        return PI * r * r;
    }
    virtual float perimetru() {
        return 2 * PI * r;
    }


};




int main() {

    Rectangle d(100, 50, 200, 200);
    Square p(200, 100, 80);
    std::cout << "Arie " << d.getName() << ": " << d.arie() << std::endl;
    std::cout << "Perimetru " << d.getName() << ": " << d.perimetru() << std::endl;
    std::cout << "Arie " << p.getName() << ": " << p.arie() << std::endl;
    std::cout << "Perimetru " << p.getName() << ": " << p.perimetru() << std::endl;

    /* 
    String s1("string-ul 1"), s2, s;
    char st[100];
    s2.setString("string-ul 2");
    s = s1 + s2;
    std::cout << "Concatenarea celor doua string-uri: " << s << std::endl;
    s += s1;
    std::cout << "Concatenarea celor doua string-uri: " << s << std::endl;
    std::cout << "Lungimea string-ului: " << !s << std::endl;
    std::cout << "Pe pozitia 5 se afla caracterul: " << s[4] << std::endl;
    if (s1 == s2) std::cout << "String-urile sunt identice" << std::endl;
    else std::cout << "String-urile difera" << std::endl;
    if (s1 < s2) std::cout << "s1 < s2" << std::endl;
    s.get(st);
    std::cout << "String-ul extras:       " << st << std::endl;*/

   /* Complex a(2, 4), b(4,1);
    Complex c;
    std::cin >> c;
    std::cout << c;
    std::cout << a + b;
    std::cout << a * b;
    std::cout << a - b;
    std::cout << a + 3;
    std::cout << a * 3;
    std::cout << a - 3;
    std::cout << !a;


    Rational x(7, 15), y(1, 5), z;
    z = x + y;
    std::cout << x << " + " << y << " = " << z << std::endl;
    std::cout << x << " - " << y << " = " << (x - y) << std::endl;
    std::cout << x << " * " << y << " = " << (x * y) << std::endl;
    std::cout << x << " / " << y << " = " << (x / y) << std::endl;*/

	/*int z = -1, x = 50, y = 0;
	int arr[4] = { 0 };
	int i = 20;

	exception1 divide0;
	exception2 index_out_of_bounds;

	try {
		if (y == 0)
			throw divide0;
		z = x / y;
		std::cout << "Fara exceptie: z=" << z << "\n";
	}
	catch (std::exception& e) {
		std::cout << "Exceptie: " << e.what() << "\n";
	}

	try {
		if (i > 3)
			throw index_out_of_bounds;
		arr[i] = z;
		for (i = 0; i < 4; i++)
			std::cout << "arr[" << i << "] = " << arr[i] << "\n";
	}
	catch (std::exception& e) {
		std::cout << "Exception: " << e.what() << "\n";
	}*/



	return 0;
}