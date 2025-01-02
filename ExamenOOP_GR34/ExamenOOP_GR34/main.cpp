#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>

class Text {
private:
	class Paragraf {
	public:
		int id = NULL;
		char* string = nullptr;
		Paragraf(int id, char* str) {
			this->id = id;
			this->string = new char[strlen(str) + 1];
			strcpy(this->string, str);
		}
		~Paragraf() {
			delete[] this->string;
		}
		Paragraf* next = nullptr;
	};
	Paragraf* head = nullptr;

public:
	void push(int id, int idTo,char* str) {
		if (id < 1) return;

		try {
			Paragraf* newNode = new Paragraf(id, str);

			if (head == nullptr) {
				head = newNode;
				return;
			}

			if (idTo == 0) {
				newNode->next = head;
				head = newNode;
				return;
			}

			Paragraf* it = head;
			while (it != nullptr && it->id != idTo) {
				it = it->next;
			}

			if (it == nullptr) {
				delete newNode;
				throw std::runtime_error("Id-ul nu exista");
			}

			newNode->next = it->next;
			it->next = newNode;
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	void pop(int id) {
		if (head == nullptr) return;

		try {
			if (head->id == id) {
				Paragraf* temp = head;
				head = head->next;
				delete temp;
				return;
			}

			Paragraf* it = head;
			while (it->next != nullptr && it->next->id != id) {
				it = it->next;
			}

			if (it->next == nullptr) {
				throw std::runtime_error("Id-ul nu exista");
			}

			Paragraf* temp = it->next;
			it->next = temp->next;
			delete temp;
		}
		catch (const std::exception& e) {
			std::cout << "Error: " << e.what() << std::endl;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, Text& a) {
		Paragraf* it = a.head;
		while (it != nullptr) {
			os << it->string << "\n";
			it = it->next;
		}
		return os;
	}
};

int main() {
	std::ifstream in("Text.txt");
	if (!in) {
		std::cerr << "File can't be opened!\n";
		in.close();
		exit(1);
	}
	int id, idTo;
	char* str;
	Text a;
	while (!in.eof()) {
		char* str = new char[100];
		in >> id >> idTo;
		in.get();
		in.get(str, 100);
		a.push(id, idTo, str);
	}
	in.close();
	std::cout << a;

	return 0;
}