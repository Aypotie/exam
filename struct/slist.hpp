#ifndef SLIST_H
#define SLIST_H

#include <iostream>

using namespace std;

template <typename T>
struct SNode {
    T value;
    SNode<T>* next;

    SNode(const T& val) : value(val), next(nullptr) {}
};

template <typename T>
struct SList {
private:
    int len;

public:
    SNode<T>* head;

    SList() {
        head = nullptr;
        len = 0;
    }

    int size() const {
        return len;
    }

    void pushForward(T value) {
        SNode<T>* node = new SNode<T>(value);
        SNode<T>* oldHead = head;
        head = node;
        node->next = oldHead;
        len++;
    }

    void pushBack(T value) {
        SNode<T>* node = new SNode<T>(value);
        if (head == nullptr) {
            head = node;
        } else {
            SNode<T>* current = head;
            while (current->next!= nullptr) {
                current = current->next;
            }
            current->next = node;
        }
        len++;
    }

    void removeForward() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        SNode<T>* oldHead = head;
        head = head->next;
        delete oldHead;
        len--;
    }

    void removeBack() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }

        if (head->next == nullptr) { // Если в списке только один элемент
            delete head;
            head = nullptr;
        } else {
            SNode<T>* current = head;
            while (current->next->next != nullptr) {
                current = current->next; // Находим предпоследний узел
            }
            delete current->next; // Удаляем последний узел
            current->next = nullptr; // Обнуляем указатель на следующий узел
        }
        len--;
    }

};

template <typename T>
ostream& operator<<(ostream& os, const SList<T>& list) {
    auto head = list.head;
    while (head != nullptr) {
        cout << head->value << endl;
        head = head->next;
    }
    return os;
}

#endif