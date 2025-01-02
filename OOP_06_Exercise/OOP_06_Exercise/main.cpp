#include <iostream>
#include <vector>
#include <algorithm>


template <typename T>
class Vector {
private:
    std::vector<T> data;
public:
    Vector() = default;
    Vector(const Vector& other) : data(other.data) {}
    Vector(Vector&& other) noexcept : data(std::move(other.data)) {}
    void insert(int index, const T& element) {
        if (index > data.size()) {
            throw std::out_of_range("Index out of range!\n");
        }
        data.insert(data.begin() + index, element);
    }
    void remove(size_t index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        data.erase(data.begin() + index);
    }
    void sort(int (*cmp)(T, T)) {
        std::sort(data.begin(), data.end(), [cmp](T a, T b) {
            return cmp(a, b) > 0;
            });
    }

    void sort() {
        std::sort(data.begin(), data.end());
    }

    void print() const {
        for (const auto& d : data) {
            std::cout << d << " ";
        }
        std::cout << "\n";
    }
    T& operator[](int index) {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range!\n");
        }
        return data[index];
    }
    const T& operator[](size_t index) const {
        if (index >= data.size()) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }
};

int compare_ints(int x, int y) {
    if (x < y)
        return -1;
    if (x > y)
        return 1;
    else
        return 0;
}

int main() {
    Vector<int> v;

    // index, element
    v.insert(0, 10);
    v.insert(1, 5);
    v.insert(2, 20);

    Vector<int> w = v;

    // index
    v.remove(0);
    v.sort(compare_ints);
    printf("%d\n", w[0]);

    v.print();
    return 0;
}