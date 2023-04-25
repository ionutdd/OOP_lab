/*
Explicații:
- În clasa `Node` definim un nod al listei care conține două câmpuri: `data`, care reprezintă valoarea nodului, și `next`, care este un pointer la următorul nod din listă.
- În clasa `LinkedList` definim lista propriu-zisă, cu un câmp privat `head`, care este un pointer la primul nod al listei. Avem și câteva metode pentru a manipula lista:
  - `add_front` - adaugă un nod la începutul listei.
  - `add_back` - adaugă un nod la sfârșitul listei.
  - `remove_front` - elimină primul nod al listei.
  - `remove_back` - elimină ultimul nod al listei.
  - `is_empty` - verifică dacă lista e goală.
  - `print` - afișează elementele listei.
- În `main` cream o instanță a clasei `LinkedList` și adăugăm câteva noduri la începutul și sfârșitul listei. Apoi afișăm lista și eliminăm primul și ultimul nod. La final afișăm lista din nou.
*/

#include <iostream>

using namespace std;

// clasa care defineste un nod al listei
class Node {
public:
    int data; // campul de date al nodului
    Node *next; // pointer la urmatorul nod

    Node(int data) { // constructor
        this->data = data;
        this->next = NULL;
    }
};

// clasa care defineste lista propriu-zisa
class LinkedList {
private:
    Node *head; // pointer la primul nod al listei
public:
    LinkedList() { // constructor, lista incepe cu NULL
        head = NULL;
    }

    void add_front(int data) { // adauga un nod la inceputul listei
        Node *new_node = new Node(data); // creeaza un nou nod
        new_node->next = head; // lega noul nod de lista existenta
        head = new_node; // seteaza noul nod ca fiind primul nod
    }

    void add_back(int data) { // adauga un nod la sfarsitul listei
        Node *new_node = new Node(data); // creeaza un nou nod
        if (head == NULL) { // daca lista e goala, noul nod va fi si primul nod
            head = new_node;
            return;
        }
        Node *curr = head;
        while (curr->next != NULL) { // gaseste ultimul nod al listei
            curr = curr->next;
        }
        curr->next = new_node; // lega noul nod de ultimul nod al listei
    }

    void remove_front() { // elimina primul nod al listei
        if (head == NULL) { // daca lista e goala, nu se poate elimina nimic
            cout << "Lista e goala! Nu putem elimina noduri." << endl;
            return;
        }
        Node *temp = head; // pastram pointer-ul catre primul nod
        head = head->next; // primul nod devine al doilea nod
        delete temp; // eliberam memoria ocupata de primul nod
    }

    void remove_back() { // elimina ultimul nod al listei
        if (head == NULL) { // daca lista e goala, nu se poate elimina nimic
            cout << "Lista e goala! Nu putem elimina noduri." << endl;
            return;
        }
        if (head->next == NULL) { // daca lista are doar un nod, il eliminam
            delete head;
            head = NULL;
            return;
        }
        Node *curr = head;
        while (curr->next->next != NULL) { // gaseste penultimul nod al listei
            curr = curr->next;
        }
        delete curr->next; // elimina ultimul nod al listei
        curr->next = NULL; // penultimul nod devine ultimul nod
    }

    bool is_empty() { // verifica daca lista e goala
        return head == NULL;
    }

    void print() { // afiseaza elementele listei
        if (head == NULL) { // daca lista e goala, nu avem ce afisa
            cout << "Lista e goala";    
        } 
        else {
        Node *curr = head;
        while (curr != NULL) { // parcurgem lista si afisam fiecare nod
            cout << curr->data << " ";
            curr = curr->next;
        }
        cout << endl;
    }
}
};

int main() {
LinkedList lista; // cream o instanta a clasei LinkedList
lista.add_front(10); // adaugam un nod la inceputul listei
lista.add_front(5); // adaugam un nod la inceputul listei
lista.add_back(20); // adaugam un nod la sfarsitul listei

lista.print(); // afisam elementele listei: 5 10 20

lista.remove_front(); // eliminam primul nod al listei
lista.remove_back(); // eliminam ultimul nod al listei

lista.print(); // afisam elementele listei: 10
return 0;
}
