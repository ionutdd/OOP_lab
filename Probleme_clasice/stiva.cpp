/*
Explicații:

-Am definit clasa Stack pentru a implementa stiva. Aceasta are un array arr în care stocăm elementele stivei și un indice top pentru a ține evidența elementului din varful stivei.
-În constructorul clasei, am inițializat stiva cu 0 elemente, adică top are valoarea -1.
-Metodele is_empty și is_full verifică dacă stiva este goală, respectiv plină.
-Metoda push adaugă un element în varful stivei. Dacă stiva este deja plină, afișăm un mesaj de eroare și nu adăugăm elementul.
-Metoda pop elimină elementul din varful stivei. Dacă stiva este deja goală, afișăm un mesaj de eroare și nu eliminăm elementul.
-Metoda peek returnează elementul din varful stivei, fără a-l elimina
*/


#include <iostream>
using namespace std;

const int MAX_SIZE = 100; // dimensiunea maxima a stivei

class Stack {
private:
    int arr[MAX_SIZE]; // array-ul in care stocam elementele stivei
    int top; // indicele elementului din varful stivei
public:
    Stack() { // constructor
        top = -1; // stiva este initializata cu 0 elemente
    }

    bool is_empty() { // verificam daca stiva este goala
        return (top == -1);
    }

    bool is_full() { // verificam daca stiva este plina
        return (top == MAX_SIZE - 1);
    }

    void push(int x) { // adaugam un element in varful stivei
        if (is_full()) {
            cout << "Stiva este plina! Nu putem adauga elemente suplimentare.\n";
            return;
        }
        top++; // mutam indicele varfului stivei in sus cu o pozitie
        arr[top] = x; // adaugam elementul in varful stivei
    }

    void pop() { // eliminam elementul din varful stivei
        if (is_empty()) {
            cout << "Stiva este goala! Nu putem elimina elemente.\n";
            return;
        }
        top--; // mutam indicele varfului stivei in jos cu o pozitie
    }

    int peek() { // returnam elementul din varful stivei
        if (is_empty()) {
            cout << "Stiva este goala! Nu exista elemente in varful stivei.\n";
            return -1;
        }
        return arr[top];
    }
};

int main() {
    Stack s;

    // adaugam elemente in stiva
    s.push(1);
    s.push(2);
    s.push(3);
    s.push(4);

    // afisam elementele stivei
    cout << "Elementele stivei sunt: ";
    while (!s.is_empty()) {
        cout << s.peek() << " ";
        s.pop();
    }
    cout << endl;

    return 0;
}
