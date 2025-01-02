#include <iostream>
#include <vector>

class PriorityQueue {
private:
    std::vector<int> data;
    void heapify(int index);

public:
    void insert(int key);
    int top() { return data.empty() ? -1 : data[0]; }
    void extractTop();
    void display();
};

int main() {
    PriorityQueue pq;
    int choice, key;

    do {
        std::cout << "\nPriority Queue Operations\n";
        std::cout << "1. Insert Element\n";
        std::cout << "2. Extract Top Element\n";
        std::cout << "3. Get Top Element\n";
        std::cout << "4. Display Priority Queue\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1:
            std::cout << "Enter the key to insert: ";
            std::cin >> key;
            pq.insert(key);
            break;
        case 2:
            pq.extractTop();
            break;
        case 3:
            std::cout << "Top element: " << pq.top() << std::endl;
            break;
        case 4:
            std::cout << "Priority Queue: ";
            pq.display();
            std::cout << std::endl;
            break;
        case 5:
            std::cout << "Exiting program...\n";
            break;
        default:
            std::cout << "Invalid choice! Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}

void PriorityQueue::insert(int key) {
    data.push_back(key);
    int index = data.size() - 1;
    while (index > 0 && data[index] > data[(index - 1) / 2]) {
        std::swap(data[index], data[(index - 1) / 2]);
        index = (index - 1) / 2;
    }
}

void PriorityQueue::extractTop() {
    if (data.empty()) {
        std::cout << "Priority Queue is empty!\n";
        return;
    }
    std::swap(data[0], data.back());
    data.pop_back();
    heapify(0);
}

void PriorityQueue::heapify(int index) {
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int largest = index;

    if (left < data.size() && data[left] > data[largest])
        largest = left;
    if (right < data.size() && data[right] > data[largest])
        largest = right;

    if (largest != index) {
        std::swap(data[index], data[largest]);
        heapify(largest);
    }
}

void PriorityQueue::display() {
    for (int i = 0; i < data.size(); ++i) {
        std::cout << data[i] << " ";
    }
}
