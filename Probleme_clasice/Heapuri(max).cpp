/*

Explicații:

Clasa `MaxHeap` are un membru privat `vector<int> heap`, care este vectorul utilizat pentru a stoca elementele heap-ului. Constructorul implicit și constructorul cu parametri sunt utilizați pentru a inițializa vectorul.
Metoda privată `heapify` este utilizată pentru a rearanja elementele heap-ului după ce un element a fost eliminat din vârful heap-ului sau a fost adăugat în vector. Metoda primește ca argument index-ul elementului care trebuie să fie rearanjat și compară elementul cu cei doi copii ai săi, determinând care este cel mai mare dintre cei trei. Dacă elementul nu este cel mai mare dintre cei trei, el este schimbat cu cel mai mare element și recursiv apelat pentru noul index al elementului.
Metoda publică `push` este utilizată pentru a adăuga un element în heap. Elementul este adăugat la sfârșitul vectorului heap-ului, iar apoi este rearanjat astfel încât heap-ul să rămână valid.
Metoda publică `pop` este utilizată pentru a elimina elementul din vârful heap-ului și a returna valoarea sa. Pentru a elimina elementul, valoarea din vârful heap-ului este înlocuită cu ultimul element din vector, care este apoi eliminat din vector. Apoi, heap-ul este rearanjat astfel încât să rămână valid.
Metoda publică `top` este utilizată pentru a obține valoarea din vârful heap-ului, fără a-l elimina.
Metodele publice `empty` și `size` sunt utilizate pentru a verifica dacă heap-ul este gol și, respectiv, pentru a obține dimensiunea heap-ului.
Metoda publică `print` este utilizată pentru a afișa elementele heap-ului în ordinea în care sunt stocate în vector.

*/

#include <iostream>
#include <vector>

using namespace std;

class MaxHeap {
private:
    vector<int> heap;

    void heapify(int i) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < heap.size() && heap[left] > heap[largest]) {
            largest = left;
        }

        if (right < heap.size() && heap[right] > heap[largest]) {
            largest = right;
        }

        if (largest != i) {
            swap(heap[i], heap[largest]);
            heapify(largest);
        }
    }

public:
    MaxHeap() {}

    MaxHeap(vector<int> v) {
        heap = v;
        for (int i = heap.size() / 2 - 1; i >= 0; i--) {
            heapify(i);
        }
    }

    void push(int value) {
        heap.push_back(value);
        int i = heap.size() - 1;
        while (i > 0 && heap[(i - 1) / 2] < heap[i]) {
            swap(heap[(i - 1) / 2], heap[i]);
            i = (i - 1) / 2;
        }
    }
    
    int pop() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }

    int root = heap[0];
    heap[0] = heap.back();
    heap.pop_back();
    heapify(0);

    return root;
}

int top() {
    if (heap.empty()) {
        throw runtime_error("Heap is empty");
    }

    return heap[0];
}

bool empty() {
    return heap.empty();
}

int size() {
    return heap.size();
}

void print() {
    for (int i = 0; i < heap.size(); i++) {
        cout << heap[i] << " ";
    }
    cout << endl;
}
};

int main() {
MaxHeap heap({10, 20, 15, 30, 40});
heap.print();
cout << heap.pop() << endl;
heap.print();
cout << heap.top() << endl;
heap.push(50);
heap.print();

retrun 0;
}
