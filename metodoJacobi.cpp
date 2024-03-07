#include <iostream>
#include <iomanip>

using namespace std;

void mostrarMatriz(int n, float *A){
    int i, j;
    i = 0;

    while (i < ((n*n)+n)){
        cout << "| ";
        j = i;
        for (i = i; i < n+j+1; i++){
            cout << fixed << setprecision(2) << *(A+i) << " ";
        }
        cout << "|" << endl;
    }
}