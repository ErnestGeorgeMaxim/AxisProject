#include "Text.h"

// Constructor for Text
Text::Text() : head(nullptr), size(0) {}

// Destructor for Text
Text::~Text() {
    Paragraph* temp = head;
    while (temp != nullptr) {
        Paragraph* next = temp->next;
        delete temp;
        temp = next;
    }
}

// Method to add a paragraph with a given id and string
void Text::push(int id, const char* str) {
    try {
        Paragraph* newNode = new Paragraph(id, str);

        if (head == nullptr) {
            // List is empty, so new node becomes the head
            head = newNode;
        }
        else {
            Paragraph* it = head;
            Paragraph* prev = nullptr;

            while (it != nullptr && it->id < id) {
                prev = it;
                it = it->next;
            }

            if (it != nullptr && it->id == id) {
                // ID already exists, clean up and throw an error
                delete newNode;
                throw std::runtime_error("The id is already in the list");
            }

            // Inserting the new node in the correct position
            newNode->next = it;
            newNode->prev = prev;

            if (prev != nullptr) {
                prev->next = newNode;
            }
            else {
                head = newNode;
            }

            if (it != nullptr) {
                it->prev = newNode;
            }
        }
        size++;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Method to remove a paragraph with a given id
void Text::pop(int id) {
    try {
        Paragraph* it = head;
        while (it != nullptr && it->id != id) {
            it = it->next;
        }

        if (it == nullptr) {
            throw std::runtime_error("The id doesn't exist");
        }

        if (it->prev != nullptr) {
            it->prev->next = it->next;
        }
        else {
            head = it->next;
        }

        if (it->next != nullptr) {
            it->next->prev = it->prev;
        }

        delete it;
        size--;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// Method to find a paragraph with a given id
Text::Paragraph* Text::find(int id) {
    Paragraph* it = head;
    while (it != nullptr && it->id != id) {
        it = it->next;
    }
    return it; // Returns nullptr if not found
}

// Method to display the list of paragraphs
void Text::display() const {
    Paragraph* it = head;
    while (it->next != nullptr) {
        std::cout << it->id << " : " << it->string << "\n";
        it = it->next;
    }
    std::cout << it->id << " : " << it->string << "\n";
}
