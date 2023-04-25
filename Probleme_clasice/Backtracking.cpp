//Gasiti toate combinațiile de k elemente dintr-un set dat de n elemente.

#include <iostream>
#include <vector>

using namespace std;

void backtrack(int n, int k, int start, vector<int>& combination) {
    // cazul de bază
    if (combination.size() == k) {
        for (int x : combination) {
            cout << x << " ";
        }
        cout << endl;
        return;
    }

    // încercăm toate combinațiile posibile
    for (int i = start; i <= n; i++) {
        combination.push_back(i);
        backtrack(n, k, i + 1, combination);
        combination.pop_back();
    }
}

int main() {
    int n = 5;
    int k = 3;
    vector<int> combination;
    backtrack(n, k, 1, combination);
    return 0;
}


/*
Funcția backtrack primește ca argumente n - numărul de elemente din set, k - numărul de elemente din fiecare combinație, start - index-ul de început pentru iterarea prin set și combination - vectorul în care se stochează combinația curentă.
În interiorul funcției, avem un caz de bază, în care verificăm dacă combinația curentă are k elemente și, în caz afirmativ, o afișăm.
În continuare, încercăm toate combinațiile posibile prin a adăuga fiecare element la combinația curentă și a apela recursiv funcția cu start setat la indexul următor.
Apoi, eliminăm ultimul element adăugat pentru a încerca următorul.
În funcția main, apelăm funcția backtrack cu valorile n, k și vectorul combinatii gol pentru a obține toate combinațiile de k elemente din setul de n elemente.
*/
