#include <iostream>

using namespace std;

template<typename T>
struct DNode {
    T value;
    DNode<T>* next;
    DNode<T>* prev;

    DNode(const T& val): value(val), next(nullptr), prev(nullptr) {}
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

    DNode<T>* removeForward() {
        if (head == nullptr) {
            throw runtime_error("list is empty");
        }
        DNode<T>* oldhead = head;
        head = head->next;
        if(head != nullptr) {
            head->prev = nullptr;
        } else {
            tail = nullptr;
        }
        len--;
        return oldhead;
    }
};

template <typename T>
ostream& operator<<(ostream& os, const Dlist<T>& dlist) {
    auto head = dlist.head;
    while(head != nullptr) {
        os << head->value << endl;
        head = head->next;
    }
    return os;
};

struct Node {
    Node* left;
    Node* right;
    int value;

    Node(int val): value(val), left(nullptr), right(nullptr) {} 
};

struct Tree {
private:
    Node* head;

    Node* insert(int value, Node* node) {
        if(node == nullptr) {
            return new Node(value);
        } else {
            if(node->value > value) {
                node->left = insert(value, node->left);
            } else if (node->value < value) {
                node->right = insert(value, node->right);
            }
        }
        return node;
    }

    void getLeft(int glubina, Node* head, Dlist<int>& list) {
        if (head == nullptr) {
            return;
        }
        if (glubina == 1) {
            list.pushback(head->value);
        } else {
            getLeft(glubina - 1, head->left, list);
            getLeft(glubina - 1, head->right, list);
        }

    }

    void getRight(int glubina, Node* head, Dlist<int>& list) {
        if (head == nullptr) {
            return;
        }
        if (glubina == 1) {
            list.pushback(head->value);
        } else {
            getRight(glubina - 1, head->right, list);
            getRight(glubina - 1, head->left, list);
        }
    }

    int maxDepth(Node* node) {
        if (node == nullptr) {
            return 0;
        }
        int leftDepth = maxDepth(node->left);
        int rightDepth  = maxDepth(node->right);
        return max(leftDepth, rightDepth) + 1;
    }

public:
    Tree() {
        head = nullptr;
    }

    Node* getHead() const {
        return head;
    }

    void push(int value) {
        head = insert(value, head);
    }

    void snake(Node* node) {
        Dlist<int> list;
        int depth = maxDepth(head);
        
        for (int i = 1; i <= depth; i++) {
            if (i % 2 == 0) {
                getLeft(i, head, list);
            } else {
                getRight(i, head, list);
            }
        }
        cout << list << endl;

    }

};

int main() {
    /*
    Dlist<int> dlist;
    dlist.pushback(1);
    dlist.pushback(2);
    dlist.pushback(3);
    dlist.pushback(4);
    dlist.pushback(5);
    cout << dlist << endl;
    cout << "deleted " << dlist.removeForward()->value << endl;
    cout << "deleted " << dlist.removeForward()->value << endl;
    cout << endl;
    cout << dlist << endl;
    */

    Tree tree;
    tree.push(22);
    tree.push(16);
    tree.push(51);
    tree.push(7);
    tree.push(19);
    tree.push(43);
    tree.push(57);
    //cout << tree.getHead()->value << endl; //6
    //cout << tree.getHead()->right->left->value << endl;//7

    tree.snake(tree.getHead());


    return 0;
}