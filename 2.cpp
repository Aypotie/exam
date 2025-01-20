#ifndef DLIDT_H
#define DLIST_H

#include <iostream>

using namespace std;

template <typename T>
struct DNode {
    T value;
    DNode<T>* prev;
    DNode<T>* next;
    DNOde(const T& val): value(val), next(nullptr), prev(nullptr) {}
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

    void pushback(T value) {
        DNode<T>* node = new DNode<T>(value);
        if (head == nullptr) {
            head = node;
            tail = node;
        } else {
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("empty");
        }
        DNode<T>* oldhead = head;
        head = head->next;
        if (head != nullpt) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        delete oldhead;
        len--;
    }
};

#endif