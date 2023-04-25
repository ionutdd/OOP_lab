/*
În acest exemplu, am definit o clasă `Deque` cu funcționalitatea necesară pentru a adăuga, elimina și accesa elemente la început și la sfârșitul deque-ului. 

- Constructorul inițializează deque-ul cu `front` și `rear` la -1, indicând că deque-ul este gol.
- Metoda `is_empty` verifică dacă deque-ul este gol.
- Metoda `is_full` verifică dacă deque-ul este plin.
- Metodele `add_front` și `add_rear` adaugă elemente la începutul, respectiv sfârșitul deque-ului.
- Metodele `remove_front` și `remove_rear` elimină elemente de la începutul, respectiv sfârșitul deque-ului.
- Metodele `get_front` și `get_rear` returnează elementul de la începutul, respectiv sfârșitul deque-ului, fără să îl elimine.

În funcția `main`, am creat o instanță a clasei `Deque` și am adăugat câteva elemente la început și la sfârșitul deque-ului cu ajutorul metodelor `add_front` și `add_rear`. Am afișat apoi elementele de la început și sfârsit.
*/


#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // dimensiunea maxima a deque-ului

class Deque {
private:
    int arr[MAX_SIZE]; // array-ul in care stocam elementele deque-ului
    int front; // indicele primului element din deque
    int rear; // indicele ultimului element din deque
public:
    Deque() { // constructor
        front = -1; // deque-ul este initializat cu 0 elemente
        rear = -1;
    }

    bool is_empty() { // verificam daca deque-ul este gol
        return (front == -1 && rear == -1);
    }

    bool is_full() { // verificam daca deque-ul este plin
        return ((rear + 1) % MAX_SIZE == front);
    }

    void add_front(int x) { // adaugam un element la inceputul deque-ului
        if (is_full()) {
            cout << "Deque-ul este plin! Nu putem adauga elemente suplimentare.\n";
            return;
        }
        if (is_empty()) { // daca deque-ul este gol, initializam front si rear cu 0
            front = 0;
            rear = 0;
        } else if (front == 0) { // daca front este la inceputul deque-ului, adaugam elementul la sfarsitul deque-ului
            front = MAX_SIZE - 1;
        } else {
            front--; // mutam indicele front in jos cu o pozitie
        }
        arr[front] = x; // adaugam elementul la inceputul deque-ului
    }

    void add_rear(int x) { // adaugam un element la sfarsitul deque-ului
        if (is_full()) {
            cout << "Deque-ul este plin! Nu putem adauga elemente suplimentare.\n";
            return;
        }
        if (is_empty()) { // daca deque-ul este gol, initializam front si rear cu 0
            front = 0;
            rear = 0;
        } else if (rear == MAX_SIZE - 1) { // daca rear este la sfarsitul deque-ului, adaugam elementul la inceputul deque-ului
            rear = 0;
        } else {
            rear++; // mutam indicele rear in sus cu o pozitie
        }
        arr[rear] = x; // adaugam elementul la sfarsitul deque-ului
    }

    void remove_front() { // eliminam elementul din fata deque-ului
        if (is_empty()) {
            cout << "Deque-ul este gol! Nu putem elimina elemente.\n";
            return;
        }
        if (front == rear) { // daca deque-ul are doar un element, resetam front si rear la -1
            front = -1;
            rear = -1;
        } else if (front == MAX_SIZE - 1) { // daca front este la sfarsitul deque-ului, il mutam la inceputul deque-ului
            front = 0;
        } else {
            front++; // mutam indicele front in sus cu o pozitie
        }
    }

    void remove_rear() { // eliminam element
    if (is_empty()) {
        cout << "Deque-ul este gol! Nu putem elimina elemente.\n";
        return;
    }
    if (front == rear) { // daca deque-ul are doar un element, resetam front si rear la -1
        front = -1;
        rear = -1;
    } else if (rear == 0) { // daca rear este la inceputul deque-ului, il mutam la sfarsitul deque-ului
        rear = MAX_SIZE - 1;
    } else {
        rear--; // mutam indicele rear in jos cu o pozitie
    }
}

int get_front() { // returneaza primul element din deque, fara sa il elimine
    if (is_empty()) {
        cout << "Deque-ul este gol! Nu putem returna elemente.\n";
        return -1;
    }
    return arr[front];
}

int get_rear() { // returneaza ultimul element din deque, fara sa il elimine
    if (is_empty()) {
        cout << "Deque-ul este gol! Nu putem returna elemente.\n";
        return -1;
    }
    return arr[rear];
}
};

int main() {
Deque dq; // cream o instanta a clasei Deque
dq.add_rear(10);
dq.add_rear(20);
dq.add_front(5);
dq.add_front(15);
cout << "Elementul din fata deque-ului: " << dq.get_front() << "\n";
dq.remove_front();
cout << "Elementul din fata deque-ului dupa eliminare: " << dq.get_front() << "\n";
cout << "Elementul din spatele deque-ului: " << dq.get_rear() << "\n";
dq.remove_rear();
cout << "Elementul din spatele deque-ului dupa eliminare: " << dq.get_rear() << "\n";

return 0;
}
