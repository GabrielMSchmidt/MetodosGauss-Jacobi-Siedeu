#include <iostream>
#include <iomanip>

using namespace std;

void mostrarMatriz(int n, double *A){
    int i, j;
    i = 0;
    
    cout << endl;
    while (i < ((n*n)+n)){
        cout << "|";
        j = i;
        for (i = i; i < n+j+1; i++){
            cout << fixed << setprecision(2) << setw(5) << *(A+i) << " ";
        }
        cout << "|" << endl;
    }
    cout << endl;
}


int main(){
    int i, j, n, x;

    cout << "Digite a Ordem da Matriz: ";
    cin >> n;

    double m[n], X[n], c[n], pivo;
    double A[n][n+1];

    for (i = 0; i < n; i ++){
        cout << "- Equacao " << i+1 << " -" << endl;
        for (j = 0; j < n; j++){
            cout << "Valor do x" << j+1 << " = "; 
            cin >> A[i][j];
        }
        cout << "Valor da constante = ";
        cin >> A[i][n];
    }
    // A[0][0] = 3.0;
    // A[0][1] = -2.0;
    // A[0][2] = 5.0;
    // A[0][3] = 20.0;
    // A[1][0] = 6.0;
    // A[1][1] = -9.0;
    // A[1][2] = 12.0;
    // A[1][3] = 51.0;
    // A[2][0] = -5.0;
    // A[2][1] = 0.0;
    // A[2][2] = 2.0;
    // A[2][3] = 1.0;
    mostrarMatriz(n, *A);
    cout << "Comecando a Elimincacao de Gauss..." << endl;

    for (x = 0; x < n-1; x++){
        pivo = A[x][x];
        cout << "\nPivo: " << pivo << endl;

        for (i = x+1; i < n; i++){
            m[i] = A[i][x]/A[x][x];
            cout << "m[" << i << "] = " << m[i] << endl; 
        }
        for (j = x+1; j < n; j++){
            for (i = x+1; i < n; i++){
                A[j][i] += -(m[j] * A[x][i]);
            }
            A[j][x] = 0;
            A[j][n] += -(m[j] * A[x][n]);
        }
    }

    mostrarMatriz(n, *A);

    for (i = 0; i < n; i++){
        c[i] = A[i][n]; 
    }
    for (i = 0; i < n; i++){
        cout << "c[" << i << "] = " << c[i] << "   "; 
    }

    for (i = n-1; i >= 0; i--) {
        X[i] = c[i];
        for (j = i+1; j < n; j++) {
            X[i] = X[i] - X[j] * A[i][j];
        }
        X[i] = X[i] / A[i][i];
    }

    cout << "\n\n-- Resultado --" << endl;
    for (i = 0; i < n; i++){
        cout << "x" << i+1 << " = " << X[i] << endl;
    }
}