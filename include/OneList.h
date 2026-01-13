#pragma once

#include <stdexcept>
#include <iostream>

template <typename T>
class OneList {
private:
    class Element {
    public:
        T data;
        Element* next;

        Element(const T& value) : data(value), next(nullptr) {}
    };

    Element* head;
    Element* tail;
    int count;

public:
    OneList() : head(nullptr), tail(nullptr), count(0) {}

    ~OneList() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    OneList(const OneList& other) : head(nullptr), tail(nullptr), count(0) {
        Element* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    OneList& operator=(const OneList& other) {
        if (this != &other) {
            clear();
            Element* current = other.head;
            while (current != nullptr) {
                push_back(current->data);
                current = current->next;
            }
        }
        return *this;
    }

    void push_front(const T& value) {
        Element* newElement = new Element(value);
        if (empty()) {
            head = tail = newElement;
        }
        else {
            newElement->next = head;
            head = newElement;
        }
        count++;
    }

    void push_back(const T& value) {
        Element* newElement = new Element(value);
        if (empty()) {
            head = tail = newElement;
        }
        else {
            tail->next = newElement;
            tail = newElement;
        }
        count++;
    }

    void insert(int position, const T& value) {
        if (position < 0 || position > count) {
            throw std::out_of_range("Position out of range");
        }

        if (position == 0) {
            push_front(value);
        }
        else if (position == count) {
            push_back(value);
        }
        else {
            Element* newElement = new Element(value);
            Element* current = head;

            for (int i = 0; i < position - 1; i++) {
                current = current->next;
            }

            newElement->next = current->next;
            current->next = newElement;
            count++;
        }
    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        Element* temp = head;
        head = head->next;
        delete temp;
        count--;

        if (head == nullptr) {
            tail = nullptr;
        }
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        if (head == tail) {
            delete head;
            head = tail = nullptr;
        }
        else {
            Element* current = head;
            while (current->next != tail) {
                current = current->next;
            }

            delete tail;
            tail = current;
            tail->next = nullptr;
        }
        count--;
    }

    void remove(const T& value) {
        if (empty()) return;

        while (head != nullptr && head->data == value) {
            pop_front();
        }

        Element* current = head;
        while (current != nullptr && current->next != nullptr) {
            if (current->next->data == value) {
                Element* temp = current->next;
                current->next = temp->next;

                if (temp == tail) {
                    tail = current;
                }

                delete temp;
                count--;
            }
            else {
                current = current->next;
            }
        }
    }

    int size() const {
        return count;
    }

    T& front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }

    const T& front() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return head->data;
    }

    T& back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }

    const T& back() const {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }
        return tail->data;
    }

    bool empty() const {
        return count == 0;
    }

    void print() const {
        Element* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }

        Element* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }

        Element* current = head;
        for (int i = 0; i < index; i++) {
            current = current->next;
        }
        return current->data;
    }
};

