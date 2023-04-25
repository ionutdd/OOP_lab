/*
Range Minimum Query (RMQ) este o problemă de interogare a unui interval într-un șir de numere întregi pentru a găsi valoarea minimă din acest interval. 
Există mai multe soluții posibile la această problemă, iar una dintre cele mai eficiente este soluția cu segment tree.
Un segment tree este un arbore binar de intervale, unde fiecare nod reprezintă un interval și are doi copii, care reprezintă jumătățile din acest interval. 
În plus, fiecare nod are o valoare asociată care este calculată pe baza valorilor fiilor săi. În cazul RMQ, valoarea asociată unui nod este minimul valorilor din intervalul reprezentat de acel nod.
Pentru a efectua o interogare RMQ pe un interval dat [L, R], traversăm segment tree-ul pornind de la rădăcină. La fiecare pas, verificăm dacă intervalul corespunzător nodului curent se intersectează cu intervalul [L, R]. 
Dacă nu se intersectează, atunci întoarcem o valoare mare (de exemplu, INF), deoarece nu ne interesează minimul din acel interval. 
Dacă se intersectează, atunci luăm minimul dintre valoarea asociată a nodului curent și minimul dintre subarborii săi care se intersectează cu intervalul [L, R].
La final, vom avea minimul intervalului [L, R].
*/


#include <iostream>
#include <vector>
#include <climits>

using namespace std;

const int INF = INT_MAX; // valoarea mare pentru intervalul neintersectat

// clasa pentru un nod din segment tree
class Node {
public:
    int start; // începutul intervalului
    int end; // sfârșitul intervalului
    int value; // valoarea minimă din intervalul [start, end]

    Node(int s, int e, int v) : start(s), end(e), value(v) {}
};

// clasa pentru segment tree
class SegmentTree {
public:
    vector<Node> tree; // vectorul cu nodurile din segment tree

    // constructor care creează segment tree-ul
    SegmentTree(const vector<int>& a) {
        int n = a.size();
        tree.resize(4 * n);
        build_tree(1, 0, n - 1, a);
    }

    // metoda care construiește segment tree-ul
    void build_tree(int node, int start, int end, const vector<int>& a) {
        if (start == end) {
            tree[node] = Node(start, end, a[start]); // frunza
        } else {
            int mid = (start + end) / 2;
            build_tree(2 * node, start, mid, a); // construim subarborele stâng
            build_tree(2 * node + 1, mid + 1, end, a); // construim subarborele drept
            int min_left = tree[2 * node].value;
            int min_right = tree[2 * node + 1].value;
            tree[node] = Node(start, end, min(min_left))
}

// metoda care face o interogare RMQ
int query(int node, int start, int end, int L, int R) {
    if (R < start || end < L) {
        return INF; // intervalul nu se intersectează
    } else if (L <= start && end <= R) {
        return tree[node].value; // intervalul este inclus în [L, R]
    } else {
        int mid = (start + end) / 2;
        int min_left = query(2 * node, start, mid, L, R); // interogăm subarborele stâng
        int min_right = query(2 * node + 1, mid + 1, end, L, R); // interogăm subarborele drept
        return min(min_left, min_right); // întoarcem minimul dintre cele două interogări
    }
}
};

int main() {
vector<int> a = {4, 1, 5, 2, 7, 3}; // șirul de numere
SegmentTree st(a); // construim segment tree-ul
cout << st.query(1, 0, a.size() - 1, 1, 4) << endl; // interogăm intervalul [1, 4]
return 0;
}
