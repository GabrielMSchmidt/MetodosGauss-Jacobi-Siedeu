#include <iostream>
#include <cmath>

using namespace std;

void imprimirMatriz(float *a, int lin);
float* escreverMatriz(int lin);
bool testarConvergencia(float *a, int lin);
void permutarLinhas(float *a, int lin, int linha1, int linha2);
void gaussSeidel(float *A, int lin, float epsilon, float* x_inicial);

bool testarConvergencia(float *a, int lin) {
    for (int i = 0; i < lin; i++) {
        float soma = 0.0;
        for (int j = 0; j < lin; j++) {
            if (j != i) {
                soma += abs(a[i * (lin + 1) + j]);
            }
        }
        if (abs(a[i * (lin + 1) + i]) < soma) {
            return false;
        }
    }
    return true;
}

void permutarLinhas(float *a, int lin, int linha1, int linha2) {
    for (int i = 0; i < lin + 1; ++i) {
        float temp = a[linha1 * (lin + 1) + i];
        a[linha1 * (lin + 1) + i] = a[linha2 * (lin + 1) + i];
        a[linha2 * (lin + 1) + i] = temp;
    }
}

void gaussSeidel(float *A, int lin, float epsilon, float* x_inicial) {
    float *a = A;
    int n = lin;

    if (!testarConvergencia(a, n)) {
        cout << "A matriz nao eh diagonalmente dominante" << endl;
        bool convergente = false;
        for (int i = 0; i < n; ++i) {
            for (int j = i + 1; j < n; ++j) {
                permutarLinhas(a, n, i, j);
                if (testarConvergencia(a, n)) {
                    cout << "Linhas permutadas" << endl;
                    convergente = true;
                    break;
                }
                permutarLinhas(a, n, j, i); 
            }
            if (convergente) {
                break;
            }
        }
        if (!convergente) {
            cout << "Falha ao encontrar uma permutacao de linhas que torne a matriz diagonalmente dominante. O metodo de Gauss-Seidel pode nao convergir." << endl;
            exit(-1);
        }
    }

    float x[n];
    float x_ant[n];
    float erro;
    int iteracao = 0;

    for (int i = 0; i < n; i++) {
        x[i] = x_inicial[i];
    }

    cout << "Iteracao 0:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }

    do {
        iteracao++;

        for (int i = 0; i < n; i++) {
            x_ant[i] = x[i];
        }

        for (int i = 0; i < n; i++) {
            float sum = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sum += a[i * (n + 1) + j] * x[j];
                }
            }
            x[i] = (a[i * (n + 1) + n] - sum) / a[i * (n + 1) + i];
        }

        cout << "Iteracao " << iteracao << ":" << endl;
        for (int i = 0; i < n; i++) {
            cout << "x[" << i << "] = " << x[i] << endl;
        }

        erro = 0.0;
        for (int i = 0; i < n; i++) {
            erro += pow(x[i] - x_ant[i], 2);
        }
        erro = sqrt(erro);

    } while (erro > epsilon);

    cout << "---resultado---" << endl;
    for(int i = 0; i < n; i++) {
        cout << "x[" << i << "] = " << x[i] << endl;
    }
    cout << endl;
}

void imprimirMatriz(float *a, int lin) {
    int n = lin;
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n + 1; j++) {
            if(j < n)
                cout << a[i * (n + 1) + j] << "x[" << j << "] ";
            else
                cout << " = " << a[i * (n + 1) + j];
        }
        cout << endl;
    }
}

float* escreverMatriz(int lin) {
    float *a = new float[lin * (lin + 1)];
    for(int i = 0; i < lin; i++) {
        for(int j = 0; j < lin + 1; j++) {
            cin >> a[i * (lin + 1) + j];
        }
    }
    return a;
}

int main() {
    cout << "Bem-vindo ao metodo de Gauss-Seidel" << endl;
    cout << "Qual eh a ordem da matriz? ";

    int n;
    cin >> n;
    cout << "Sua matriz eh " << n << "x" << n << "!" << endl;

    cout << "----equacao inicial---" << endl;
    float *a = escreverMatriz(n);
    
    float epsilon;
    cout << "Digite a tolerancia para o criterio de parada: ";
    cin >> epsilon;

    float x_inicial[n];
    cout << "Digite os valores iniciais de x:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x[" << i << "] = ";
        cin >> x_inicial[i];
    }

    gaussSeidel(a, n, epsilon, x_inicial);

    delete[] a;

    return 0;
}
