#include <iostream>

using namespace std;

struct Node {
    Node* left;
    Node* right;
    int value;
    Node(int val) : value(val), left(nullptr), right(nullptr) {}
};

class Tree {
private:
    Node* head;

    Node* insert(int value, Node* node) {
        if (node == nullptr) {
            return new Node(value);
        } else {
            if(node->value > value) {
                node->left = insert(value, node->left);
            } else  if (node->value < value) {
                node->right = insert(value, node->right);
            }
        }
        return node;
    }
public:
    Tree() {
        head = nullptr;
    }

    Node* getHead() {
        return head;
    }

    void push(int value) {
        head = insert(value, head);
    }

};

int main() {
    Tree tree;
    tree.push(3);
    tree.push(1);
    tree.push(8);
    tree.push(10);
    tree.push(5);
    cout << tree.getHead()->value << endl; //3
    cout << tree.getHead()->left->value << endl; //1
    cout << tree.getHead()->right->right->value << endl; //10

    return 0;
}