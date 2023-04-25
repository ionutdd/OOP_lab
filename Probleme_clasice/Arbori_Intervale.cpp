#include <iostream>
#include <vector>

using namespace std;

// Implementarea structurii nodului arborelui
struct Node {
    int left;  // Intervalul din stânga
    int right;  // Intervalul din dreapta
    int min_value;  // Valoarea minimă în intervalul acoperit de acest nod
};

// Implementarea arborelui de intervale
class IntervalTree {
public:
    // Constructorul pentru arborele de intervale
    IntervalTree(const vector<int>& values) {
        n = values.size();
        tree.resize(4 * n);
        build_tree(values, 0, n-1, 0);
    }

    // Funcția pentru a găsi minimul dintr-un interval dat
    int query(int left, int right) {
        return query_tree(left, right, 0);
    }

    // Funcția pentru a actualiza valoarea unui element în arbore
    void update(int index, int value) {
        update_tree(index, value, 0);
    }

private:
    int n;  // Numărul de elemente din vectorul inițial
    vector<Node> tree;  // Vectorul care reprezintă arborele de intervale

    // Funcția pentru a construi arborele de intervale
    void build_tree(const vector<int>& values, int left, int right, int index) {
        if (left == right) {
            // Nodul este frunză, deci este asociat unui singur element
            tree[index].left = left;
            tree[index].right = right;
            tree[index].min_value = values[left];
            return;
        }

        // Calculăm mijlocul intervalului și construim subarborii stâng și drept
        int mid = (left + right) / 2;
        build_tree(values, left, mid, 2*index+1);
        build_tree(values, mid+1, right, 2*index+2);

        // Actualizăm minimul din acest nod, folosind minimul din subarborii stâng și drept
        tree[index].left = left;
        tree[index].right = right;
        tree[index].min_value = min(tree[2*index+1].min_value, tree[2*index+2].min_value);
    }

    // Funcția recursivă pentru a găsi minimul într-un interval dat
    int query_tree(int left, int right, int index) {
        if (left <= tree[index].left && right >= tree[index].right) {
            // Intervalul cerut este inclus în intervalul acoperit de nodul curent
            return tree[index].min_value;
        }

        if (left > tree[index].right || right < tree[index].left) {
            // Intervalul cerut nu se suprapune cu intervalul acoperit de nodul curent
            return numeric_limits<int>::max();
        }

        // Intervalul cerut se suprapune parțial cu intervalul acoperit de nodul curent, deci căutăm în subarborii stâng și drept
        return min(query_tree(left, right, 2*index+1), query_tree(left, right, 2*index+2));
    }

    // Funcția recursivă pentru a actualiza valoarea unui
    void update_tree(int index, int value, int node_index) {
    if (tree[node_index].left == tree[node_index].right) {
        // Nodul este frunză, deci a găsit elementul care trebuie actualizat
        tree[node_index].min_value = value;
        return;
    }

    // Cautăm elementul în subarborele stâng sau drept, în funcție de poziția acestuia
    int mid = (tree[node_index].left + tree[node_index].right) / 2;
    if (index <= mid) {
        update_tree(index, value, 2*node_index+1);
    } else {
        update_tree(index, value, 2*node_index+2);
    }

    // Actualizăm minimul din acest nod, folosind minimul din subarborii stâng și drept
    tree[node_index].min_value = min(tree[2*node_index+1].min_value, tree[2*node_index+2].min_value);
}
};

// Exemplu de utilizare a arborelui de intervale
int main() {
vector<int> values = {5, 3, 8, 1, 2, 6, 9, 4, 7};
IntervalTree tree(values);
cout << "Minimul din intervalul [1, 4] este: " << tree.query(1, 4) << endl;  // Afiseaza 1

tree.update(2, 0);  // Actualizam valoarea elementului de pe pozitia 2 la 0

cout << "Minimul din intervalul [1, 4] dupa actualizare este: " << tree.query(1, 4) << endl;  // Afiseaza 0

return 0;
}
