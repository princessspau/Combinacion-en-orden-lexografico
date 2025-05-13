#include <iostream>
#include <limits>
#include <fstream>

#define MAX_N 30

using namespace std;

void ImprimirCombinacion(int p[], int tam);
void CapturaSegura(int &n, string mensaje);

int main() {
    cout << "Programa que genera combinaciones en orden lexicografico.\n\n";

    int n, r;

    // Captura de n
    do {
        CapturaSegura(n, "Introduce el tama\244o del arreglo (n) [1," + to_string(MAX_N) + "]: ");
        if (n < 1 || n > MAX_N) {
            cout << "\nEl taman\244o debe estar entre 1 y " << MAX_N << ".\n";
        }
    } while (n < 1 || n > MAX_N);

    // Captura de r
    do {
        CapturaSegura(r, "Introduce el taman\244o de la combinacion (r) [0," + to_string(n) + "]: ");
        if (r < 0 || r > n) {
            cout << "\nEl tama\244o debe estar entre [0," << n << "].\n";
        }
    } while (r < 0 || r > n);

    // Si r == 0, combinación vacía
    if (r == 0) {
        cout << "\nNo hay elementos en la combinacion (combinacion vacia).\n";

        ofstream combinaciones("Combinaciones.txt");
        if (!combinaciones.is_open()) {
            cerr << "Error al abrir el archivo.\n";
            return 1;
        }

        combinaciones << "C(" << n << ",0):\n\n";
        combinaciones << "(combinacion vacia)\n";
        combinaciones.close();

        cout << "La combinacion vacia ha sido guardada en 'Combinaciones.txt'\n";

        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cin.get();
        return 0;
    }

    cout << "\nCombinaciones en r generadas:\n\n";

    int *p = new int[r];

    // Inicializar combinación inicial
    for (int i = 0; i < r; ++i) {
        p[i] = i + 1;
        cout << p[i] << "  ";
    }
    cout << endl;

    // Abrir archivo
    ofstream combinaciones;
    combinaciones.open("Combinaciones.txt");
    if (!combinaciones.is_open()) {
        cerr << "Error al abrir el archivo.\n";
        delete[] p;
        return 1;
    }

    combinaciones << "C(" << n << "," << r << "):\n\n";
    for (int i = 0; i < r; ++i) {
        combinaciones << p[i] << "  ";
    }
    combinaciones << endl;

    // Generar combinaciones
    while (true) {
        int m = r - 1;
        int val_max = n;

        while (m >= 0 && p[m] == val_max) {
            --m;
            --val_max;
        }

        if (m < 0) break;

        ++p[m];

        for (int j = m + 1; j < r; ++j) {
            p[j] = p[j - 1] + 1;
        }

        // Imprimir en consola
        for (int i = 0; i < r; ++i) {
            cout << p[i] << "  ";
        }
        cout << endl;

        // Escribir en archivo
        for (int i = 0; i < r; ++i) {
            combinaciones << p[i] << "  ";
        }
        combinaciones << endl;
    }

    combinaciones.close(); // Cerrar archivo
    cout << "\nLas combinaciones han sido guardadas en 'Combinaciones.txt'\n";

    delete[] p;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();

    return 0;
}

// Funciones
void ImprimirCombinacion(int s[], int tam) {
    for (int i = 0; i < tam; ++i) {
        cout << s[i] << "  ";
    }
    cout << endl;
}

void CapturaSegura(int &n, string mensaje) {
    while (true) {
        cout << mensaje;
        cin >> n;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<int>::max(), '\n');
            cout << "Entrada invalida. Intente de nuevo.\n";
        } else {
            break;
        }
    }
}

