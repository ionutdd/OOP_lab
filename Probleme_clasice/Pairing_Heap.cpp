/*
Pairing Heap este o structură de date bazată pe heap care este foarte eficientă în termeni de timp de execuție. Pentru aceasta, vom crea o clasă PairingHeap cu următoarele funcții:

1.PairingHeap() - Constructor care initializează heap-ul gol.
2.bool isEmpty() - Verifică dacă heap-ul este gol.
3.void insert(int x) - Inserează elementul x în heap.
4.void merge(PairingHeap& other) - Îmbină două heap-uri și păstrează proprietatea heap.
5.int findMin() - Returnează valoarea minimă din heap.
6.int deleteMin() - Șterge valoarea minimă din heap și reface proprietatea heap.
7.void decreaseKey(int oldVal, int newVal) - Scade valoarea nodului cu valoarea oldVal la newVal.
8.void remove(int x) - Șterge nodul cu valoarea x din heap și reface proprietatea heap.
9.bool contains(int x) - Verifică dacă valoarea x se află în heap.
10.void range(int x, int y) - Afișează toate elementele din heap care se află în intervalul [x, y] în ordine sortată.
*/

#include <iostream>
#include <queue>
#include <vector>

using namespace std;

template <typename T>
class PairingHeap {
private:
    struct Node {
        T data;
        Node* child;
        Node* next;
        Node* prev;
        
        Node(const T& value) : data(value), child(nullptr), next(nullptr), prev(nullptr) {}
    };

    Node* root;

    void clear(Node* node) {
        if (node == nullptr) {
            return;
        }

        if (node->child != nullptr) {
            clear(node->child);
        }

        if (node->next != nullptr) {
            clear(node->next);
        }

        delete node;
    }

    Node* mergePairs(Node* first) {
        if (first == nullptr || first->next == nullptr) {
            return first;
        }

        Node* second = first->next;
        Node* rest = second->next;

        first->next = nullptr;
        second->next = nullptr;

        Node* merged = merge(merge(first, second), mergePairs(rest));
        return merged;
    }

public:
    PairingHeap() : root(nullptr) {}

    ~PairingHeap() {
        clear(root);
    }

    void insert(const T& value) {
        Node* node = new Node(value);
        root = merge(root, node);
    }

    T findMin() const {
        return root->data;
    }

    void deleteMin() {
        Node* oldRoot = root;
        root = mergePairs(root->child);
        delete oldRoot;
    }

    bool isEmpty() const {
        return root == nullptr;
    }

    void merge(PairingHeap& other) {
        root = merge(root, other.root);
        other.root = nullptr;
    }

    Node* merge(Node* first, Node* second) {
        if (first == nullptr) {
            return second;
        }

        if (second == nullptr) {
            return first;
        }

        if (first->data < second->data) {
            second->prev = first;
            first->next = second->child;
            if (second->child != nullptr) {
                second->child->prev = first;
            }
            first->child = second;
            return first;
        } else {
            first->prev = second;
            second->next = first->child;
            if (first->child != nullptr) {
                first->child->prev = second;
            }
            second->child = first;
            return second;
        }
    }
};

int main() {
    PairingHeap heap;

    // insert some values
    heap.insert(10);
    heap.insert(5);
    heap.insert(7);
    heap.insert(12);
    heap.insert(1);

    // print the minimum value
    cout << "Minimum value: " << heap.getMin() << endl;

    // delete the minimum value
    heap.deleteMin();

    // check if a value exists in the heap
    cout << "Value 7 exists: " << heap.exists(7) << endl;
    cout << "Value 1 exists: " << heap.exists(1) << endl;

    // print the sorted values
    cout << "Sorted values: ";
    while (!heap.isEmpty()) {
        cout << heap.getMin() << " ";
        heap.deleteMin();
    }
    cout << endl;

    return 0;
}

/*
Acesta este un exemplu simplu de implementare a Heap-ului Pairing folosind pointeri.
Clasa PairingHeap are metode pentru a insera elemente, a găsi și a șterge elementul minim, a verifica dacă heap-ul este gol, a uni două heap-uri și o metodă auxiliară pentru a uni noduri. 
Am folosit o structură nod pentru a stoca informațiile legate de elemente în heap. Pentru a șterge minimul am folosit o metodă auxiliară mergePairs, care folosește metoda merge pentru a uni nodurile de pe niveluri succesive.
*/
