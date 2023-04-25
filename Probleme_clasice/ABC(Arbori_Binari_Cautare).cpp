/*
Un arbore binar de căutare este o structură de date de tip arbore în care fiecare nod are cel mult doi fii și toți fiii din stânga sunt mai mici decât nodul părinte, iar toți fiii din dreapta sunt mai mari decât nodul părinte. 
Această proprietate face ca arborele binar de căutare să fie util în căutarea, inserarea și ștergerea rapidă a elementelor, având o complexitate medie de timp O(log n) pentru aceste operații.
Pentru a implementa un arbore binar de căutare în C++, vom crea o clasă BinarySearchTree, care va conține un nod Node și trei funcții principale: insert pentru inserarea unui nod în arbore, search pentru căutarea unui nod în arbore și remove pentru ștergerea unui nod din arbore.
*/

#include <iostream>
using namespace std;

class BinarySearchTree {
private:
    struct Node {
        int data;
        Node* left;
        Node* right;
        Node(int val) : data(val), left(nullptr), right(nullptr) {}
    };

    Node* root;

public:
    BinarySearchTree() : root(nullptr) {}

    void insert(int val) {
        if (root == nullptr) {
            root = new Node(val);
        } else {
            Node* current = root;
            while (true) {
                if (val < current->data) {
                    if (current->left == nullptr) {
                        current->left = new Node(val);
                        break;
                    } else {
                        current = current->left;
                    }
                } else {
                    if (current->right == nullptr) {
                        current->right = new Node(val);
                        break;
                    } else {
                        current = current->right;
                    }
                }
            }
        }
    }

    bool search(int val) {
        Node* current = root;
        while (current != nullptr) {
            if (current->data == val) {
                return true;
            } else if (val < current->data) {
                current = current->left;
            } else {
                current = current->right;
            }
        }
        return false;
    }

    void remove(int val) {
        root = remove(root, val);
    }

    Node* remove(Node* node, int val) {
        if (node == nullptr) {
            return nullptr;
        } else if (val < node->data) {
            node->left = remove(node->left, val);
        } else if (val > node->data) {
            node->right = remove(node->right, val);
        } else {
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                node = nullptr;
            } else if (node->left == nullptr) {
                Node* temp = node;
                node = node->right;
                delete temp;
            } else if (node->right == nullptr) {
                Node* temp = node;
                node = node->left;
                delete temp;
            } else {
                Node* temp = findMin(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }
        return node;
    }

    Node* findMin(Node* node) {
        while (node->left != nullptr) {
            node = node->left;
        }
        return node;
    }
};

// Exemplu de utilizare a ABC

int main() {
BinarySearchTree bst;
bst.insert(8);
bst.insert(3);
bst.insert(10);
bst.insert(1);
bst.insert(6);
bst.insert(14);
bst.insert(4);
bst.insert(7);
bst.insert(13);

cout << "Tree traversal in-order: ";
bst.inOrderTraversal();
cout << endl;

cout << "Tree traversal pre-order: ";
bst.preOrderTraversal();
cout << endl;

cout << "Tree traversal post-order: ";
bst.postOrderTraversal();
cout << endl;

int valToRemove = 6;
bst.remove(valToRemove);
cout << "After removing " << valToRemove << " from the tree, in-order traversal: ";
bst.inOrderTraversal();
cout << endl;

int valToFind = 14;
if (bst.search(valToFind)) {
    cout << valToFind << " is in the tree." << endl;
} else {
    cout << valToFind << " is not in the tree." << endl;
}

return 0;
}
