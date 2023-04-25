/*
Pentru a implementa operațiile 1 și 2, vom căuta nodul corespunzător valorii X, iar dacă îl găsim vom efectua inserarea/ștergerea nodului respectiv și vom actualiza nivelurile în care se găsește nodul.
Pentru a implementa operația 3, vom căuta nodul corespunzător valorii X și vom verifica dacă acesta există. Dacă da, vom returna 1, altfel vom returna 0.
Pentru a implementa operația 4, vom căuta nodul corespunzător valorii X, iar dacă acesta nu există vom lua nodul precedent (cel mai mare nod mai mic decât X) de pe nivelul maxim. De asemenea, vom verifica dacă nodul precedent există și dacă este mai mic decât X. Dacă da, vom returna valoarea stocată în nodul precedent, altfel vom returna -1 (pentru a indica că nu există un astfel de nod).
Pentru a implementa operația 5, vom căuta nodul corespunzător valorii X, iar dacă acesta există vom returna valoarea stocată în nodul respectiv. Altfel, vom căuta primul nod mai mare decât X pe nivelul maxim și vom returna valoarea stocată în nodul precedent (cel mai mic nod mai mare sau egal decât X). Dacă nodul precedent există și este mai mare sau egal decât X, vom returna valoarea stocată în acesta, altfel vom returna -1 (pentru a indica că nu există un astfel de nod).
Pentru a implementa operația 6, vom căuta nodul corespunzător valorii X și vom începe să parcurgem lista de la acest nod către dreapta, adăugând valorile întâlnite într-un vector. Vom întrerupe parcurgerea când vom ajunge la un nod cu valoarea mai mare decât Y sau la sfârșitul listei. Apoi vom sorta vectorul și îl vom returna.
*/

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <climits>

using namespace std;

// definim nivelul maxim al skip listei
const int MAX_LEVEL = 16;

// structura nodului din skip listă
struct Node {
    int value;
    int level;
    Node **next;

    Node(int v, int l) : value(v), level(l) {
        next = new Node*[l + 1];
        for (int i = 0; i <= l; i++) {
            next[i] = nullptr;
        }
    }

    ~Node() {
        delete[] next;
    }
};

// clasa skip listă
class SkipList {
private:
    Node *head;
    int level;
    int count;

public:
    SkipList() {
        // inițializăm capul skip listei cu un nod invalid
        head = new Node(INT_MIN, MAX_LEVEL);
        level = 0;
        count = 0;
    }

    ~SkipList() {
        // eliberăm toți nodurile din skip listă
        Node *curr = head->next[0];
        while (curr != nullptr) {
            Node *tmp = curr;
            curr = curr->next[0];
            delete tmp;
        }

        // eliberăm și capul
        delete head;
    }

    // adăugăm un nod cu valoarea value în skip listă
    void insert(int value) {
        // căutăm poziția unde ar trebui să inserăm nodul
        Node *curr = head;
        Node *update[MAX_LEVEL + 1];
        for (int i = level; i >= 0; i--) {
            while (curr->next[i] != nullptr && curr->next[i]->value < value) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        curr = curr->next[0];

        // verificăm dacă nodul există deja în skip listă
        if (curr != nullptr && curr->value == value) {
            return;
        }

        // creăm un nou nod cu un nivel aleatoriu
        int newLevel = randomLevel();
        Node *newNode = new Node(value, newLevel);

        // actualizăm nivelul skip listei dacă este cazul
        if (newLevel > level) {
            for (int i = level + 1; i <= newLevel; i++) {
                update[i] = head;
            }
            level = newLevel;
        }

        // inserăm noul nod în skip listă
        for (int i = 0; i <= newLevel; i++) {
            newNode->next[i] = update[i]->next[i];
            update[i]->next[i] = newNode;
        }

        count++;
    }

    // ștergem nodul cu valoarea value din skip listă (dacă există)
    void remove(int value) {
        // căutăm poziția nodului de șters
        Node *curr = head;
        Node *update[MAX_LEVEL + 1];
        for (int i = level; i >= 0; i--) {
            while (curr->next[i] != nullptr && curr->next[i]->value < value) {
                curr = curr->next[i];
            }
            update[i] = curr;
        }
        curr = curr->next[0];

                // insert the new node
        Node* newNode = new Node(level, value);
        for (int i = 0; i <= level; i++) {
            newNode->forward[i] = update[i]->forward[i];
            update[i]->forward[i] = newNode;
        }
        
        // increase size of the skip list
        size++;
    }
}
    void SkipList::remove(int value) {
    Node* update[maxLevel + 1];
    Node* x = head;
 
    // find the node to be removed and update the update vector
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->value < value) {
            x = x->forward[i];
        }
        update[i] = x;
    }
    x = x->forward[0];
 
    // if the node is found, remove it
    if (x != NULL && x->value == value) {
        for (int i = 0; i <= level; i++) {
            if (update[i]->forward[i] != x) {
                break;
            }
            update[i]->forward[i] = x->forward[i];
        }
        delete x;
 
        // update level if necessary
        while (level > 0 && head->forward[level] == NULL) {
            level--;
        }
        size--;
    }
}
    
    bool SkipList::contains(int value) const {
    Node* x = head;
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->value < value) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    return (x != NULL && x->value == value);
}

    int SkipList::floor(int value) const {
    Node* x = head;
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->value < value) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x != NULL && x->value <= value) {
        return x->value;
    } else {
        return INT_MIN;
    }
}

    int SkipList::ceiling(int value) const {
    Node* x = head;
    for (int i = level; i >= 0; i--) {
        while (x->forward[i] != NULL && x->forward[i]->value < value) {
            x = x->forward[i];
        }
    }
    x = x->forward[0];
    if (x != NULL && x->value >= value) {
        return x->value;
    } else {
        return INT_MAX;
    }
}

    void SkipList::range(int x, int y) const {
    if (x > y) {
        return;
    }
    Node* curr = head->forward[0];
    while (curr != NULL && curr->value <= y)
    {
      if (curr->value >= x) {
    cout << curr->value << " ";
    }
    curr = curr->forward[0];
    }
    cout << endl;
    } 
};

void testSkipList() {
    SkipList sl;
    assert(sl.contains(5) == false);
    assert(sl.remove(5) == false);
    sl.insert(5);
    assert(sl.contains(5) == true);
    sl.insert(10);
    sl.insert(15);
    sl.insert(20);
    sl.insert(25);
    sl.insert(30);
    assert(sl.contains(10) == true);
    assert(sl.contains(13) == false);
    sl.remove(10);
    assert(sl.contains(10) == false);
    assert(sl.contains(15) == true);
    assert(sl.floor(13) == 10);
    assert(sl.ceiling(13) == 15);
    sl.range(12, 27);
}

int main()
{
    int main() {
    SkipList sl;

    // inserăm elemente în skip list
    sl.insert(5);
    sl.insert(7);
    sl.insert(1);
    sl.insert(10);

    // afișăm toate elementele din skip list
    sl.print();

    // testăm dacă un element există în skip list
    cout << "Elementul 7 este in multime? " << sl.search(7) << endl;
    cout << "Elementul 3 este in multime? " << sl.search(3) << endl;

    // ștergem un element din skip list
    sl.remove(5);

    // afișăm elementele din skip list după ce am șters un element
    sl.print();

    // găsim cel mai mare element mai mic sau egal cu 7
    cout << "Cel mai mare element mai mic sau egal cu 7 este: " << sl.floor(7) << endl;

    // găsim cel mai mic element mai mare sau egal cu 7
    cout << "Cel mai mic element mai mare sau egal cu 7 este: " << sl.ceiling(7) << endl;

    // afișăm elementele între 1 și 7 în ordine sortată
    cout << "Elementele între 1 și 7 sunt: ";
    sl.range(1, 7);
    cout << endl;

    return 0;
}

       
