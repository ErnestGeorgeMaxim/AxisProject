#include <iostream>
#include <stdexcept>

class Group {
private:
    int* v;
    int n;

    void allocateMemory() {
        if (n > 0)
            v = new int[n];
        else
            v = nullptr;
    }

    void deallocateMemory() {
        delete[] v;
        v = nullptr;
    }

public:
    Group() : n(0), v(nullptr) {}
    Group(int n) : n(n) {
        allocateMemory();
    }
    ~Group() {
        deallocateMemory();
    }

    Group(const Group& other) : n(other.n) {
        allocateMemory();
        for (int i = 0; i < n; i++)
            v[i] = other.v[i];
    }

    Group& operator=(const Group& other) {
        if (this == &other)
            return *this;
        deallocateMemory();
        n = other.n;
        allocateMemory();
        for (int i = 0; i < n; i++) {
            v[i] = other.v[i];
        }
        return *this;
    }

    bool elementExists(int value) const {
        for (int i = 0; i < n; i++) {
            if (v[i] == value)
                return true;
        }
        return false;
    }

    Group& operator+=(int value) {
        if (elementExists(value)) {
            throw std::invalid_argument("Element already exists");
        }
        Group result(n + 1);
        for (int i = 0; i < n; i++) {
            result.v[i] = v[i];
        }
        result.v[n] = value;
        deallocateMemory();
        n = result.n;
        v = result.v;
        result.v = nullptr;  // Prevent deallocation in result's destructor
        return *this;
    }

    Group& operator+=(const Group& other) {
        int newN = 0;
        for (int i = 0; i < other.n; i++) {
            if (!elementExists(other.v[i])) {
                newN++;
            }
        }
        Group result(n + newN);
        for (int i = 0; i < n; i++) {
            result.v[i] = v[i];
        }
        int k = n;
        for (int i = 0; i < other.n; i++) {
            if (!elementExists(other.v[i])) {
                result.v[k++] = other.v[i];
            }
        }
        deallocateMemory();
        n = result.n;
        v = result.v;
        result.v = nullptr;  // Prevent deallocation in result's destructor
        return *this;
    }

    Group& operator-=(int value) {
        int count = 0;
        for (int i = 0; i < n; i++) {
            if (v[i] != value) {
                count++;
            }
        }
        if (count == n) {
            throw std::invalid_argument("Value not found");
        }

        Group result(count);
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (v[i] != value) {
                result.v[j++] = v[i];
            }
        }
        deallocateMemory();
        n = result.n;
        v = result.v;
        result.v = nullptr;  // Prevent deallocation in result's destructor
        return *this;
    }

    Group& operator-=(const Group& other) {
        int newSize = 0;
        for (int i = 0; i < n; i++) {
            if (!other.elementExists(v[i])) {
                newSize++;
            }
        }
        Group result(newSize);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (!other.elementExists(v[i])) {
                result.v[k++] = v[i];
            }
        }
        deallocateMemory();
        n = result.n;
        v = result.v;
        result.v = nullptr;  // Prevent deallocation in result's destructor
        return *this;
    }

    friend std::istream& operator>>(std::istream& in, Group& a);
    friend std::ostream& operator<<(std::ostream& os, const Group& a);
};

std::istream& operator>>(std::istream& in, Group& a) {
    in >> a.n;
    a.deallocateMemory();
    a.allocateMemory();
    for (int i = 0; i < a.n; i++) {
        in >> a.v[i];
    }
    return in;
}

std::ostream& operator<<(std::ostream& os, const Group& a) {
    for (int i = 0; i < a.n; i++) {
        os << a.v[i] << " ";
    }
    os << "\n";
    return os;
}

int main() {
    try {
        Group a, b;
        std::cin >> a >> b;
        a += b;
        std::cout << "After += : " << a;
        a -= b;
        std::cout << "After -= : " << a;
    }
    catch (const std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }
    return 0;
}
