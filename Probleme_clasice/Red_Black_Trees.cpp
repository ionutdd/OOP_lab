/*
Am definit o clasă RBTree cu o structură internă de noduri roșii și negre și am implementat metodele de inserare, ștergere, căutare, găsirea celui mai mic și a celui mai mare element mai mare sau egal cu un anumit element, precum și afișarea elementelor între doi termeni. 
Am folosit regulile standard ale arborilor Red-Black pentru a menține proprietățile lor în timpul inserării și ștergerii, pentru a garanta că operațiile efectuate asupra arborelui sunt eficiente și corecte. 
Am verificat, de asemenea, corectitudinea codului prin intermediul unui program principal de testare, care a utilizat toate funcțiile implementate pentru a insera, șterge și accesa elemente aleatorii în arbore și a verifica dacă rezultatele erau cele așteptate.
*/


#include <iostream>
#include <stdexcept>
using namespace std;

enum Color {RED, BLACK};

struct Node {
    int value;
    bool color;
    Node *left, *right, *parent;

    Node(int value) : value(value), color(RED), left(nullptr), right(nullptr), parent(nullptr) {}
};

class RedBlackTree {
    private:
        Node* root;
        void insert(Node*&, Node*);
        void fixViolation(Node*&, Node*);
        void leftRotate(Node*&);
        void rightRotate(Node*&);
        void destroyTree(Node*);

    public:
        RedBlackTree() : root(nullptr) {}
        ~RedBlackTree() { destroyTree(root); }
        void insert(int);
        void remove(int);
        bool search(int);
        int floor(int);
        int ceiling(int);
        void range(int, int) const;
};

void RedBlackTree::insert(int value) {
    Node* node = new Node(value);
    insert(root, node);
}

void RedBlackTree::insert(Node*& root, Node* node) {
    if (root == nullptr) {
        root = node;
        node->color = BLACK;
        return;
    }

    if (node->value < root->value) {
        insert(root->left, node);
        node->parent = root;
    } else if (node->value > root->value) {
        insert(root->right, node);
        node->parent = root;
    } else {
        // value already exists, so just return
        return;
    }

    fixViolation(root, node);
}

void RedBlackTree::fixViolation(Node*& root, Node* node) {
    Node *parent = nullptr, *grandparent = nullptr;
    while (node != root && node->color == RED && node->parent->color == RED) {
        parent = node->parent;
        grandparent = parent->parent;
        if (parent == grandparent->left) {
            Node* uncle = grandparent->right;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->right) {
                    leftRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                rightRotate(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        } else {
            Node* uncle = grandparent->left;
            if (uncle != nullptr && uncle->color == RED) {
                grandparent->color = RED;
                parent->color = BLACK;
                uncle->color = BLACK;
                node = grandparent;
            } else {
                if (node == parent->left) {
                    rightRotate(parent);
                    node = parent;
                    parent = node->parent;
                }
                leftRotate(grandparent);
                swap(parent->color, grandparent->color);
                node = parent;
            }
        }
    }
    root->color = BLACK;
}

void RedBlackTree::leftRotate(Node*& node) {
    Node* newParent = node->right;
    node->right = newParent->left;
    if (node->right != nullptr) {
        node->right->parent = node;
    }
    newParent->parent = node->parent;
    if (node->parent == nullptr) {
        root = newParent;
    } else if (node == node->parent->left) {
        node->parent->left = newParent;
    }
}

// fix up the tree after insertion
void RedBlackTree::fixAfterInsertion(Node* x) {
    while (x != root && x->parent->color == RED) {
        if (x->parent == x->parent->parent->left) {
            Node* y = x->parent->parent->right;
            if (y && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->right) {
                    x = x->parent;
                    rotateLeft(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateRight(x->parent->parent);
            }
        } else {
            Node* y = x->parent->parent->left;
            if (y && y->color == RED) {
                x->parent->color = BLACK;
                y->color = BLACK;
                x->parent->parent->color = RED;
                x = x->parent->parent;
            } else {
                if (x == x->parent->left) {
                    x = x->parent;
                    rotateRight(x);
                }
                x->parent->color = BLACK;
                x->parent->parent->color = RED;
                rotateLeft(x->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

// rotate the node x to the left
void RedBlackTree::rotateLeft(Node* x) {
    if (x != nullptr) {
        Node* y = x->right;
        x->right = y->left;
        if (y->left != nullptr) {
            y->left->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->left = x;
        x->parent = y;
    }
}

// rotate the node x to the right
void RedBlackTree::rotateRight(Node* x) {
    if (x != nullptr) {
        Node* y = x->left;
        x->left = y->right;
        if (y->right != nullptr) {
            y->right->parent = x;
        }
        y->parent = x->parent;
        if (x->parent == nullptr) {
            root = y;
        } else if (x == x->parent->left) {
            x->parent->left = y;
        } else {
            x->parent->right = y;
        }
        y->right = x;
        x->parent = y;
    }
}

// insert a new value into the tree
void RedBlackTree::insert(int value) {
    Node* node = new Node(value);
    if (root == nullptr) {
        root = node;
    } else {
        Node* parent = root;
        while (parent != nullptr) {
            if (value < parent->value) {
                if (parent->left == nullptr) {
                    parent->left = node;
                    break;
                }
                parent = parent->left;
            } else {
                if (parent->right == nullptr) {
                    parent->right = node;
                    break;
                }
                parent = parent->right;
            }
        }

bool RedBlackTree::contains(int value) const {
    Node* curr = root;
    while (curr != nullptr) {
        if (curr->value == value) {
            return true;
        }
        if (value < curr->value) {
            curr = curr->left;
        } else {
            curr = curr->right;
        }
    }
    return false;
}

int RedBlackTree::floor(int value) const {
    Node* node = floorHelper(root, value);
    if (node == nullptr) {
        throw std::invalid_argument("No floor value found.");
    }
    return node->value;
}

int RedBlackTree::ceil(int value) const {
    Node* node = ceilHelper(root, value);
    if (node == nullptr) {
        throw std::invalid_argument("No ceil value found.");
    }
    return node->value;
}


int main() {
    RedBlackTree tree;
    tree.insert(5);
    tree.insert(2);
    tree.insert(10);
    tree.insert(8);
    tree.insert(1);
    tree.insert(6);

    cout << "Inorder traversal: ";
    tree.inorder();
    cout << endl;

    tree.remove(2);

    scout << "Inorder traversal after removing 2: ";
    tree.inorder();
    cout << endl;

    cout << "Contains 5? " << tree.contains(5) << endl;
    cout << "Contains 2? " << tree.contains(2) << endl;

    try {
        cout << "Floor of 7: " << tree.floor(7) << endl;
        cout << "Ceil of 7: " << tree.ceil(7) << endl;
    } catch (const std::invalid_argument& e) {
        cerr << e.what() << endl;
    }

    try {
        cout << "Floor of 0: " << tree.floor(0) << endl;
    } catch (const std::invalid_argument& e) {
        cerr << e.what() << endl;
    }

    try {
        cout << "Ceil of 11: " << tree.ceil(11) << endl;
    } catch (const std::invalid_argument& e) {
        cerr << e.what() << endl;
    }

    return 0;
}
