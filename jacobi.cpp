#include <iostream>
#include <cmath>
#include <locale>
using namespace std;

void imprimirMatriz(float **a, int lin);
float** scanearMatriz(int lin);
void gaussJacobi(float **A, int lin, float epsilon, float* x_inicial);

void gaussJacobi(float **A, int lin, float epsilon, float* x_inicial) {
    float **a = A;
    int n = lin;

    if(a[lin - 1][lin - 1] == 0.0) {
        exit (-1);
    }

    float x[n];
    float x_ant[n];
    float error;
    int iteracao = 0;

    // Inicialize as variáveis com os valores iniciais
    for (int i = 0; i < n; i++) {
        x[i] = x_inicial[i];
    }

    // Faça iterações até que o critério de parada seja atingido
    do {
        iteracao++;
        // Salve os valores anteriores de x
        for (int i = 0; i < n; i++) {
            x_ant[i] = x[i];
        }

        // Calcule os novos valores de x
        cout << "Iteração " << iteracao << ":" << endl;
        for (int i = 0; i < n; i++) {
            float sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += a[i][j] * x_ant[j];
                }
            }
            x[i] = (a[i][n] - sum) / a[i][i];
            cout << "x[" << char('a' + i) << "] = " << x[i] << endl;
        }

        // Calcule o erro
        error = 0.0;
        for (int i = 0; i < n; i++) {
            error += pow(x[i] - x_ant[i], 2);
        }
        error = sqrt(error);

        cout << "Erro: " << error << endl << endl;

    } while (error > epsilon);

    // Imprima a solução
    cout << "---resultado---" << endl;
    for(int i = 0; i < n ; i++) {
        cout << (char)(i + 'a') << " = " << x[i] << endl;
    }
    cout << endl;
}

void imprimirMatriz(float **a, int lin) {
    int n = lin;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n + 1; j++) {
            if(j < n)
                cout << a[i][j] << char('a' + j) <<  " ";
            else
                cout << " = " << a[i][j];
        }
        cout << endl;
    }
}

float** scanearMatriz(int lin) {
    float **a = new float*[lin];
    for(int i = 0; i < lin; i++) {
        a[i] = new float[lin + 1];
    }
    for(int i = 0; i < lin; i++) {
        for(int j = 0; j < lin + 1; j++) {
            cin >> a[i][j];
        }
    }
    return a;
}

int main() {
    setlocale(LC_CTYPE, "");

    cout << "Bem-vindo ao metodo de Gauss-Jacobi" << endl;
    cout << "Qual eh a ordem da matriz? ";

    int n;
    cin >> n;
    cout << "Sua matriz eh " << n << "x" << n << "!" << endl;

    cout << "----equacao inicial---" << endl;
    float **a = scanearMatriz(n);
    
    // Defina um valor de tolerância para o critério de parada
    float epsilon;
    cout << "Digite a tolerancia para o criterio de parada: ";
    cin >> epsilon;

    // Defina os valores iniciais de x
    float x_inicial[n];
    cout << "Digite os valores iniciais de x:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << char('a' + i) << "] = ";
        cin >> x_inicial[i];
    }

    gaussJacobi(a, n, epsilon, x_inicial);

    return 0;
}
