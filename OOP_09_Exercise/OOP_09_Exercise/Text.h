#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <iostream>
#include <cstring>
#include <stdexcept>

class Text {
private:
    class Paragraph {
    public:
        int id;
        char* string;
        Paragraph* prev;
        Paragraph* next;
        Paragraph(int id, const char* str) : id(id), prev(nullptr), next(nullptr) {
            string = new char[strlen(str) + 1];
            strcpy(string, str);
        }
        ~Paragraph() {
            delete[] string;
        }
    };
    Paragraph* head;
    int size;
public:
    Text();
    ~Text();
    void push(int id, const char* str);
    void pop(int id);
    Paragraph* find(int id);
    void display() const;
};
