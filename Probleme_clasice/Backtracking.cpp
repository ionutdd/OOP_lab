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
