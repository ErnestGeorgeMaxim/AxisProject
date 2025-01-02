#include <iostream>

// push pop top 

class Stack {
private:
	class Node {
	public:
		int info;
		Node* next;
		Node* prev;
		Node(int info) {
			this->info = info;
			this->next = nullptr;
			this->prev = nullptr;
		}
		~Node() = default;
	};
	Node* top;
public:
	Stack() {
		top = nullptr;
	}
	void push(int info) {
		Node* newNode = new Node(info);
		if (top == nullptr)
			top = newNode;

		top->prev = newNode;
		top = newNode;
	}
	void pop() {
		if (top == nullptr)
			return;

		Node* temp = top;
		top = temp->next;
		delete[] temp;
	}
	int getTop() {
		return top->info;
	}
};

int main() {

	Stack s;
	s.push(34);
	s.push(32);
	s.push(35);
	std::cout << s.getTop() << "\n";
	s.pop();
	std::cout << s.getTop() << "\n";

	return 0;
}