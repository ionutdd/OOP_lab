/*
SQRT DECOMPOSITION este o tehnica de preprocesare si de raspuns la intrebari (query-uri) rapide pe secvente de date, cum ar fi cautarea maximului sau minimului, sau calcularea sumei. Aceasta tehnica consta in impartirea secventei in blocuri de dimensiune fixa, urmand apoi sa se calculeze o solutie optima pentru fiecare bloc si sa se memoreze aceasta solutie. Aceasta permite efectuarea rapid a operatiilor asupra intregii secvente, folosind doar valorile stocate pentru fiecare bloc.

Pentru a implementa SQRT DECOMPOSITION, trebuie sa urmati urmatorii pasi:

1.Impartiti secventa in blocuri de dimensiune fixa (de obicei, radacina patrata a dimensiunii secventei).
2.Calculeaza si memoreaza solutia optima pentru fiecare bloc. Aceasta poate fi, de exemplu, minimul sau maximul din bloc sau suma elementelor din bloc.
3.Raspunde la intrebari (query-uri) rapide folosind valorile stocate pentru fiecare bloc.
*/

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class SqrtDecomposition {
private:
    vector<int> block; // stores the result of the operation for each block
    vector<int> array; // stores the actual elements of the array
    int block_size; // size of each block
    int num_blocks; // number of blocks
public:
    SqrtDecomposition(const vector<int>& arr) {
        array = arr;
        int n = array.size();
        block_size = sqrt(n);
        num_blocks = (n + block_size - 1) / block_size;
        block.resize(num_blocks);
        for (int i = 0; i < n; i++) {
            block[i / block_size] += array[i];
        }
    }

    void update(int idx, int val) {
        int block_idx = idx / block_size;
        block[block_idx] += val - array[idx];
        array[idx] = val;
    }

    int query(int l, int r) {
        int sum = 0;
        int start_block = l / block_size;
        int end_block = r / block_size;

        if (start_block == end_block) {
            for (int i = l; i <= r; i++) {
                sum += array[i];
            }
            return sum;
        }

        for (int i = l; i < (start_block + 1) * block_size; i++) {
            sum += array[i];
        }

        for (int i = start_block + 1; i < end_block; i++) {
            sum += block[i];
        }

        for (int i = end_block * block_size; i <= r; i++) {
            sum += array[i];
        }

        return sum;
    }
};

int main() {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    SqrtDecomposition sd(arr);
    cout << sd.query(0, 9) << endl; // Output: 55
    sd.update(3, 0);
    cout << sd.query(0, 9) << endl; // Output: 51
    return 0;
}


/*
In acest exemplu, clasa SqrtDecomposition implementeaza sqrt decomposition pentru range query si update a unei secvente de numere intregi stocate intr-un vector. 
Constructorul initializeaza variabilele de baza si calculeaza suma pentru fiecare bloc.
Metoda update actualizeaza valoarea unui element in vector si recalculeaza suma blocului corespunzator. 
Metoda query calculeaza suma pe intreaga secventa utilizand valorile de bloc si valorile individuale.
*/
