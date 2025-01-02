#include <iostream>

class Queue {
private:
    class Node {
    public:
        int info;
        Node* next;
        Node* prev;
        Node(int info) : info(info), next(nullptr), prev(nullptr) {}
    };
    Node* head;
    Node* tail;

public:
    Queue() : head(nullptr), tail(nullptr) {}

    ~Queue() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* aux = temp;
            temp = temp->next;
            delete aux;
        }
    }

    void push(int info) {
        Node* newNode = new Node(info);
        if (head == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void pop() {
        if (tail == nullptr)
            return;

        Node* temp = tail;
        if (tail->prev != nullptr) {
            tail = tail->prev;
            tail->next = nullptr;
        }
        else {
            // Queue becomes empty
            head = tail = nullptr;
        }
        delete temp;
    }

    friend std::ostream& operator<<(std::ostream& os, const Queue& q) {
        Node* it = q.head;
        while (it != nullptr) {
            os << it->info << " ";
            it = it->next;
        }
        return os;
    }
};

int main() {
    Queue q;
    q.push(4);
    q.push(3);
    q.push(12);
    q.push(34);
    std::cout << q << std::endl;

    q.pop();
    std::cout << q << std::endl;

    return 0;
}
