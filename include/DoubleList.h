#pragma once    
#include <stdexcept>
#include <iostream>
#include <algorithm>

template <typename T>
class DoubleList {
private:
    class Element {
    public:
        T data;
        Element* next;
        Element* prev;

        Element(const T& value) : data(value), next(nullptr), prev(nullptr) {}
    };

    Element* head;
    Element* tail;
    int count;

public:
    DoubleList() : head(nullptr), tail(nullptr), count(0) {}

    ~DoubleList() {
        clear();
    }

    void clear() {
        while (!empty()) {
            pop_front();
        }
    }

    DoubleList(const DoubleList& other) : head(nullptr), tail(nullptr), count(0) {
        Element* current = other.head;
        while (current != nullptr) {
            push_back(current->data);
            current = current->next;
        }
    }

    DoubleList& operator=(const DoubleList& other) {
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
            head->prev = newElement;
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
            newElement->prev = tail;
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

            if (position < count / 2) {
                Element* current = head;
                for (int i = 0; i < position; i++) {
                    current = current->next;
                }

                newElement->prev = current->prev;
                newElement->next = current;
                current->prev->next = newElement;
                current->prev = newElement;
            }
            else {
                Element* current = tail;
                for (int i = count - 1; i > position; i--) {
                    current = current->prev;
                }

                newElement->prev = current->prev;
                newElement->next = current;
                current->prev->next = newElement;
                current->prev = newElement;
            }
            count++;
        }
    }

    void pop_front() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        Element* temp = head;
        head = head->next;

        if (head != nullptr) {
            head->prev = nullptr;
        }
        else {
            tail = nullptr;
        }

        delete temp;
        count--;
    }

    void pop_back() {
        if (empty()) {
            throw std::runtime_error("List is empty");
        }

        Element* temp = tail;
        tail = tail->prev;

        if (tail != nullptr) {
            tail->next = nullptr;
        }
        else {
            head = nullptr;
        }

        delete temp;
        count--;
    }

    void remove(const T& value) {
        Element* current = head;

        while (current != nullptr) {
            if (current->data == value) {
                Element* temp = current;

                if (current->prev != nullptr) {
                    current->prev->next = current->next;
                }
                else {
                    head = current->next;
                }

                if (current->next != nullptr) {
                    current->next->prev = current->prev;
                }
                else {
                    tail = current->prev;
                }

                current = current->next;
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

    void printReverse() const {
        Element* current = tail;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->prev;
        }
        std::cout << std::endl;
    }

    T& operator[](int index) {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }

        if (index < count / 2) {
            Element* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        else {
            Element* current = tail;
            for (int i = count - 1; i > index; i--) {
                current = current->prev;
            }
            return current->data;
        }
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= count) {
            throw std::out_of_range("Index out of range");
        }

        if (index < count / 2) {
            Element* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current->data;
        }
        else {
            Element* current = tail;
            for (int i = count - 1; i > index; i--) {
                current = current->prev;
            }
            return current->data;
        }
    }

    void shell_sort() {
        if (count <= 1) return;

        for (int gap = count / 2; gap > 0; gap /= 2) {
            for (int i = gap; i < count; ++i) {
                Element* current = getElement(i);
                T temp = current->data;

                int j = i;
                while (j >= gap) {
                    Element* prev = getElement(j - gap);
                    if (temp < prev->data) {
                        Element* current_j = getElement(j);
                        current_j->data = prev->data;
                        j -= gap;
                    }
                    else {
                        break;
                    }
                }

                Element* pos = getElement(j);
                pos->data = temp;
            }
        }
    }

private:
    Element* getElement(int index) {
        if (index < 0 || index >= count) {
            return nullptr;
        }

        if (index < count / 2) {
            Element* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            return current;
        }
        else {
            Element* current = tail;
            for (int i = count - 1; i > index; i--) {
                current = current->prev;
            }
            return current;
        }
    }
};