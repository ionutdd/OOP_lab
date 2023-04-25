/*
Un AVL Tree este un arbore binar de cautare echilibrat, unde inaltimea fiecarei subarbori este echilibrata astfel incat diferenta inaltimii dintre subarborii stang si drept ai unui nod este de cel mult 1.
Pentru a implementa operatiile cerute pentru un AVL Tree, vom utiliza aceleasi functii si algoritmi utilizati pentru un Binary Search Tree, cu exceptia functiilor de insertie si stergere, care trebuie sa mentina proprietatea de echilibrare.
*/

#include <iostream>
#include <algorithm>

using namespace std;

struct Node {
    int value;
    Node* left;
    Node* right;
    int height;
    Node(int val) : value(val), left(NULL), right(NULL), height(1) {}
};

class AVLTree {
private:
    Node* root;

    int height(Node* node) const {
        if (node == NULL) {
            return 0;
        }
        return node->height;
    }

    int balanceFactor(Node* node) const {
        if (node == NULL) {
            return 0;
        }
        return height(node->left) - height(node->right);
    }

    void updateHeight(Node* node) {
        node->height = max(height(node->left), height(node->right)) + 1;
    }

    Node* rotateRight(Node* node) {
        Node* leftChild = node->left;
        Node* leftRightChild = leftChild->right;

        leftChild->right = node;
        node->left = leftRightChild;

        updateHeight(node);
        updateHeight(leftChild);

        return leftChild;
    }

    Node* rotateLeft(Node* node) {
        Node* rightChild = node->right;
        Node* rightLeftChild = rightChild->left;

        rightChild->left = node;
        node->right = rightLeftChild;

        updateHeight(node);
        updateHeight(rightChild);

        return rightChild;
    }

    Node* balance(Node* node) {
        if (node == NULL) {
            return NULL;
        }

        updateHeight(node);

        int balanceFactor = this->balanceFactor(node);

        if (balanceFactor > 1) {
            if (balanceFactor(node->left) < 0) {
                node->left = rotateLeft(node->left);
            }
            return rotateRight(node);
        }
        if (balanceFactor < -1) {
            if (balanceFactor(node->right) > 0) {
                node->right = rotateRight(node->right);
            }
            return rotateLeft(node);
        }

        return node;
    }

    Node* insert(Node* node, int value) {
        if (node == NULL) {
            return new Node(value);
        }

        if (value < node->value) {
            node->left = insert(node->left, value);
        }
        else if (value > node->value) {
            node->right = insert(node->right, value);
        }
        else {
            return node;
        }

        return balance(node);
    }

    Node* findMin(Node* node) const {
        while (node->left != NULL) {
            node = node->left;
        }
        return node;
    }

    Node* removeMin(Node* node) {
        if (node->left == NULL) {
            return node->right;
        }

        node->left = removeMin(node->left);

        return balance(node);
    }

    // Functia pentru stergerea unui nod din AVL Tree
    Node* remove(Node* node, int key) {
    if (node == nullptr) {
        return nullptr;
    }

    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        // Cazul 1: nodul are cel mult un copil sau nu are niciun copil
        if (node->left == nullptr || node->right == nullptr) {
            Node* temp = node->left ? node->left : node->right;

            // Nu are niciun copil
            if (temp == nullptr) {
                temp = node;
                node = nullptr;
            }
            else { // Are un singur copil
                *node = *temp;
            }

            delete temp;
        }
        else {
            // Cazul 2: nodul are doi copii, inlocuim cu succesorul in ordine
            Node* temp = minimum(node->right);
            node->key = temp->key;
            node->right = remove(node->right, temp->key);
        }
    }

    if (node == nullptr) {
        return nullptr;
    }

    // Reechilibrare
    node->height = 1 + std::max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // Cazul stanga-stanga
    if (balance > 1 && getBalance(node->left) >= 0) {
        return rightRotate(node);
    }

    // Cazul stanga-dreapta
    if (balance > 1 && getBalance(node->left) < 0) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Cazul dreapta-dreapta
    if (balance < -1 && getBalance(node->right) <= 0) {
        return leftRotate(node);
    }

    // Cazul dreapta-stanga
    if (balance < -1 && getBalance(node->right) > 0) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

         // Functie pentru a afisa daca un anumit element exista in AVL tree
    bool AVLTree::contains(int value) const {
        Node* node = root;
        while (node != nullptr) {
            if (value == node->value) {
                return true;
            } else if (value < node->value) {
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return false;
    }

    // Functie care afiseaza cel mai mare numar Y, mai mic sau egal cu X
    int AVLTree::floor(int x) const {
        Node* node = root;
        int floor_val = INT_MIN;
        while (node != nullptr) {
            if (node->value == x) {
                return x;
            } else if (node->value < x) {
                floor_val = node->value;
                node = node->right;
            } else {
                node = node->left;
            }
        }
        return floor_val;
    }

    // Functie care afiseaza cel mai mic numar Y, mai mare sau egal cu X
    int AVLTree::ceiling(int x) const {
        Node* node = root;
        int ceil_val = INT_MAX;
        while (node != nullptr) {
            if (node->value == x) {
                return x;
            } else if (node->value > x) {
                ceil_val = node->value;
                node = node->left;
            } else {
                node = node->right;
            }
        }
        return ceil_val;
    }

    // Functie care afiseaza in ordine sortata toate numerele Z, unde X <= Z <= Y
    void AVLTree::range(int x, int y) const {
        if (x > y) {
            return;
        }
        range_helper(root, x, y);
    }

    // Functie helper pentru a afisa numerele din AVL tree intre X si Y
    void AVLTree::range_helper(Node* node, int x, int y) const {
        if (node == nullptr) {
            return;
        }
        if (node->value >= x && node->value <= y) {
            range_helper(node->left, x, y);
            cout << node->value << " ";
            range_helper(node->right, x, y);
        } else if (node->value < x) {
            range_helper(node->right, x, y);
        } else if (node->value > y) {
            range_helper(node->left, x, y);
        }
    }
};
int main()
{
AVLTree tree;
    tree.insert(8);
    tree.insert(3);
    tree.insert(10);
    tree.insert(1);
    tree.insert(6);
    tree.insert(9);
    tree.insert(14);
    tree.insert(4);
    tree.insert(7);
    tree.insert(13);

    cout << "AVL tree: ";
    tree.inorder_traversal();
    cout << endl;

    cout << "Floor of 12: " << tree.floor(12) << endl;
    cout << "Ceiling of 12: " << tree.ceiling(12) << endl;
    cout << "Range between 5 and 13: ";
    tree.range(5, 13);
    cout << endl;

    tree.remove(6);
    cout << "AVL tree after removing 6: ";
    tree.inorder_traversal();
  
  return 0;
}
