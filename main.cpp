#include <iostream>
using namespace std;


int main() {

    int** matritwo;
    int filas = 0;
    int columnas = 0;

    cout << "filas: " << endl;
    cin >> filas;
    cout << "columnas: " << endl;
    cin >> columnas;

    matritwo = new int*[filas];

    for(int fila=0; fila<filas; fila++){
        matritwo[fila] = new int[columnas];
    }
    for(int fila=0; fila<filas; fila++){
        cout << "|";
        for(int columna = 0;columna<columnas;columna++){
            matritwo[fila][columna] = 0;
            cout << matritwo[fila][columna]<< " ";
        }
        cout << "|";
        cout << endl;
    }
    for(int fila=0; fila<filas; fila++){
        delete [] matritwo[fila];
    }
    delete [] matritwo;
}
