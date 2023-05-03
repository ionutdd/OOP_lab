#include <iostream>
#include <algorithm>

template<typename T>
class SplayTree {
private:
    struct Node {
        T value;
        Node *left, *right, *parent;

        Node(T value = T{}, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr) :
            value(value), parent(parent), left(left), right(right) {}
    };

    Node* root;

    // Zig rotation
    void rotateZig(Node* node) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        Node* rightChild = node->right;

        parent->left = rightChild;
        node->right = parent;

        if (rightChild != nullptr) {
            rightChild->parent = parent;
        }

        node->parent = grandparent;
        parent->parent = node;

        if (grandparent == nullptr) {
            root = node;
        } else if (grandparent->left == parent) {
            grandparent->left = node;
        } else {
            grandparent->right = node;
        }
    }

    // Zag rotation
    void rotateZag(Node* node) {
        Node* parent = node->parent;
        Node* grandparent = parent->parent;
        Node* leftChild = node->left;

        parent->right = leftChild;
        node->left = parent;

        if (leftChild != nullptr) {
            leftChild->parent = parent;
        }

        node->parent = grandparent;
        parent->parent = node;

        if (grandparent == nullptr) {
            root = node;
        } else if (grandparent->left == parent) {
            grandparent->left = node;
        } else {
            grandparent->right = node;
        }
    }

    // Splay operation
    void splay(Node* node) {
        while (node->parent != nullptr) {
            Node* parent = node->parent;
            Node* grandparent = parent->parent;

            if (grandparent == nullptr) {
                // Zig step
                if (node == parent->left) {
                    rotateZig(node);
                } else {
                    rotateZag(node);
                }
            } else {
                // Zig-Zig step
                if (node == parent->left && parent == grandparent->left) {
                    rotateZig(parent);
                    rotateZig(node);
                }
                // Zag-Zag step
                else if (node == parent->right && parent == grandparent->right) {
                    rotateZag(parent);
                    rotateZag(node);
                }
                // Zig-Zag step
                else if (node == parent->right && parent == grandparent->left) {
                    rotateZig(node);
                    rotateZag(node);
                }
                           // Zag-Zig step
            else {
                rotateZag(node);
                rotateZig(node);
            }
        }
    }
}

// Recursive insert helper function
Node* insert(Node* node, T value, Node* parent) {
    if (node == nullptr) {
        node = new Node(value, parent);
        splay(node);
        return node;
    }

    if (value < node->value) {
        node->left = insert(node->left, value, node);
    } else if (value > node->value) {
        node->right = insert(node->right, value, node);
    } else {
        // If the value already exists in the tree, splay it to the root
        splay(node);
    }

    return node;
}

// Recursive search helper function
Node* search(Node* node, T value) {
    if (node == nullptr || value == node->value) {
        splay(node);
        return node;
    }

    if (value < node->value && node->left != nullptr) {
        return search(node->left, value);
    } else if (value > node->value && node->right != nullptr) {
        return search(node->right, value);
    } else {
        splay(node);
        return nullptr;
    }
}

// Find the node with maximum value less than or equal to the given value
Node* findFloor(Node* node, T value) {
    Node* floor = nullptr;

    while (node != nullptr) {
        if (node->value <= value) {
            if (floor == nullptr || node->value > floor->value) {
                floor = node;
            }

            node = node->right;
        } else {
            node = node->left;
        }
    }

    if (floor != nullptr) {
        splay(floor);
    }

    return floor;
}

// Find the node with minimum value greater than or equal to the given value
Node* findCeiling(Node* node, T value) {
    Node* ceiling = nullptr;

    while (node != nullptr) {
        if (node->value >= value) {
            if (ceiling == nullptr || node->value < ceiling->value) {
                ceiling = node;
            }

            node = node->left;
        } else {
            node = node->right;
        }
    }

    if (ceiling != nullptr) {
        splay(ceiling);
    }

    return ceiling;
}
public:
  SplayTree() : root(nullptr) {}
  
  // Public insert function
  void insert(T value) {
      root = insert(root, value, nullptr);
  }

  // Public search function
  bool search(T value) {
      Node* result = search(root, value);
      return (result != nullptr);
  }

  // Public floor function
  T floor(T value) {
      Node* floorNode = findFloor(root, value);

      if (floorNode != nullptr) {
          return floorNode->value;
      } else {
          return T{};
      }
  }

  // Public ceiling function
  T ceiling(T value) {
      Node* ceilingNode = findCeiling(root, value);

      if (ceilingNode != nullptr) {
          return ceilingNode->value;
      } else {
          return T{};
      }
  }

  void remove(T value) {
  Node* node = search(root, value);
  if (node == nullptr) {
      return;
  }

  splay(node);

  if (node->left == nullptr) {
      root = node->right;
      if (node->right != nullptr) {
          node->right->parent = nullptr;
      }
  } else if (node->right == nullptr) {
      root = node->left;
      if (node->left != nullptr) {
          node->left->parent = nullptr;
      }
  } else {
      Node* maxLeft = node->left;
      while (maxLeft->right != nullptr) {
          maxLeft = maxLeft->right;
      }

      if (maxLeft->parent != node) {
          maxLeft->parent->right = maxLeft->left;
          if (maxLeft->left != nullptr) {
              maxLeft->left->parent = maxLeft->parent;
          }

          maxLeft->left = node->left;
          maxLeft->left->parent = maxLeft;
      }

      maxLeft->right = node->right;
      if (maxLeft->right != nullptr) {
          maxLeft->right->parent = maxLeft;
      }

      root = maxLeft;
      maxLeft->parent = nullptr;
  }

  delete node;
}
  
  void erase(T value) {
  Node* node = search(root, value);
    if (node == nullptr) {
      return;
  }

  splay(node);

  if (node->left == nullptr) {
      root = node->right;
      if (node->right != nullptr) {
          node->right->parent = nullptr;
      }
  } else if (node->right == nullptr) {
      root = node->left;
      if (node->left != nullptr) {
          node->left->parent = nullptr;
      }
  } else {
      Node* maxLeft = node->left;
      while (maxLeft->right != nullptr) {
          maxLeft = maxLeft->right;
      }

      if (maxLeft->parent != node) {
          maxLeft->parent->right = maxLeft->left;
          if (maxLeft->left != nullptr) {
              maxLeft->left->parent = maxLeft->parent;
          }

          maxLeft->left = node->left;
          maxLeft->left->parent = maxLeft;
      }

      maxLeft->right = node->right;
      if (maxLeft->right != nullptr) {
          maxLeft->right->parent = maxLeft;
      }

      root = maxLeft;
      maxLeft->parent = nullptr;
  }

  delete node;
  }
};

int main() {

//exemplu de main

    SplayTree<int> tree;

    // inserati numarul X in multime
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);

    // afisati arborele
    cout << "Arborele este: ";
    tree.print();

    // stergeti numarul X din multime (daca acesta exista)
    tree.erase(5);

    // afisati 1 daca numarul X este in multime, alftel afisati 0
    cout << "Este 10 in arbore? " << tree.find(10) << endl;
    cout << "Este 5 in arbore? " << tree.find(5) << endl;

    // afisati cel mai mare numar Y, mai mic sau egal cu X
    cout << "Cel mai mare numar mai mic sau egal cu 12 este: " << tree.floor(12) << endl;

    // afisati cel mai mic numar Y, mai mare sau egal cu X
    cout << "Cel mai mic numar mai mare sau egal cu 12 este: " << tree.ceiling(12) << endl;

    // afisati in ordine sortata, toate numerele Z, unde X ≤ Z ≤ Y
    cout << "Numerele intre 10 si 15 sunt: ";
    tree.range(10, 15);

    return 0;
}
