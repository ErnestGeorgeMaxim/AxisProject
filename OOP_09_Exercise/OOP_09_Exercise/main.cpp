#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "Text.h"

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

    bool isEmpty() {
        if (head == nullptr)
            return true;
        return false;
    }

    Node* find(int info) {
        Node* it = head;
        while (it != nullptr && it->info != info)
            it = it->next;
        return it;
    }

    void erase(int info) {
        Node* it = head;
        while (it != nullptr && it->info != info) {
            it = it->next;
        }
        if (it == nullptr) {
            return; // Element not found
        }

        if (it == head && it == tail) { // Only one element
            head = tail = nullptr;
        }
        else if (it == head) { // Element is at the head
            head = it->next;
            head->prev = nullptr;
        }
        else if (it == tail) { // Element is at the tail
            tail = it->prev;
            tail->next = nullptr;
        }
        else { // Element is in the middle
            it->prev->next = it->next;
            it->next->prev = it->prev;
        }
        delete it;
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
	//Text s;
	//s.push(2, "Ana are mere");
	//s.push(5, "Helau");
	//s.push(3, "Caca");
	//s.push(1, "Maca");
	//s.display();
	//s.pop(2);
	//s.display();

    Queue q;
    q.push(4);
    q.push(3);
    q.push(12);
    q.push(34);
    std::cout << q << std::endl;
    q.erase(3);
    std::cout << q ;
	return 0;
}