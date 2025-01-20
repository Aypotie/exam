#ifndef DLIST_H
#define DLIST_H

#include <iostream>
#include <stdexcept>

using namespace std;

template <typename T>
struct DNode {
    T value;
    DNode<T>* next;
    DNode<T>* prev;

    DNode(const T& val) : value(val), next(nullptr), prev(nullptr) {}
};

template <typename T>
struct Dlist {
private:
    int len;

public:
    DNode<T>* head;
    DNode<T>* tail;

    Dlist() {
        head = nullptr;
        tail = nullptr;
        len = 0;
    }

    int size() const {
        return len;
    }

    T get(int index) const {
        if (index < 0 || index >= len) {
            throw runtime_error("Index out of bounds");
        }

        DNode<T>* current = head;
        int c = 0;
        while (c != index && current != nullptr) {
            current = current->next;
            c++;
        }
        return current->value;
    }

    void pushBack(T value) {
        DNode<T>* node = new DNode<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node; // Присоединяем к хвосту
            node->prev = tail;
            tail = node; // Обновляем хвост
        }
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        DNode<T>* oldHead = head;
        head = head->next;
        if (head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // Если голова удалена, хвост тоже
        }
        delete oldHead;
        len--;
    }

};


template <typename T>
ostream& operator<<(ostream& os, const Dlist<T>& list) {
    auto head = list.head;
    while (head != nullptr) {
        os << head->value << " ";
        head = head->next;
    }
    return os;
}

#endif