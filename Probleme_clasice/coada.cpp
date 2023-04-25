/*
Explicații:

-Am definit clasa Queue pentru a implementa coada. Aceasta are un array arr în care stocăm elementele cozii și doi indici front și rear pentru a ține evidența primului și ultimului element din coadă.
-În constructorul clasei, am inițializat coada cu 0 elemente, adică front și rear au valoarea -1.
-Metodele is_empty și is_full verifică dacă coada este goală, respectiv plină.
-Metoda enqueue adaugă un element în coadă. Dacă coada este plină și încercăm să adăugăm un element nou, se va afișa un mesaj de eroare.
-Dacă coada este goală și încercăm să eliminăm un element din ea, se va afișa un mesaj de eroare.
-Metoda peek returnează primul element din coadă, fără să îl elimine din coadă.
-În funcția main am creat o instanță a clasei Queue și am adăugat câteva elemente în coadă cu metoda enqueue.
-Apoi am afișat elementele cozii cu ajutorul metodei peek, eliminându-le în același timp cu metoda dequeue.

*/


#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // dimensiunea maxima a cozii

class Queue {
private:
    int arr[MAX_SIZE]; // array-ul in care stocam elementele cozii
    int front; // indicele primului element din coada
    int rear; // indicele ultimului element din coada
public:
    Queue() { // constructor
        front = -1; // coada este initializata cu 0 elemente
        rear = -1;
    }

    bool is_empty() { // verificam daca coada este goala
        return (front == -1 && rear == -1);
    }

    bool is_full() { // verificam daca coada este plina
        return (rear == MAX_SIZE - 1);
    }

    void enqueue(int x) { // adaugam un element in coada
        if (is_full()) {
            cout << "Coada este plina! Nu putem adauga elemente suplimentare.\n";
            return;
        }
        if (is_empty()) { // daca coada este goala, initializam front si rear cu 0
            front = 0;
            rear = 0;
        } else {
            rear++; // mutam indicele rear in sus cu o pozitie
        }
        arr[rear] = x; // adaugam elementul in coada
    }

    void dequeue() { // eliminam elementul din fata cozii
        if (is_empty()) {
            cout << "Coada este goala! Nu putem elimina elemente.\n";
            return;
        }
        if (front == rear) { // daca coada are doar un element, resetam front si rear la -1
            front = -1;
            rear = -1;
        } else {
            front++; // mutam indicele front in sus cu o pozitie
        }
    }

    int peek() { // returnam primul element din coada
        if (is_empty()) {
            cout << "Coada este goala! Nu exista elemente.\n";
            return -1;
        }
        return arr[front];
    }
};

int main() {
    Queue q;

    // adaugam elemente in coada
    q.enqueue(1);
    q.enqueue(2);
    q.enqueue(3);
    q.enqueue(4);

    // afisam elementele cozii
    cout << "Elementele cozii sunt: ";
    while (!q.is_empty()) {
        cout << q.peek() << " ";
        q.dequeue();
    }
    cout << endl;

    return 0;
}
