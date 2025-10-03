// LogicaLab2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <cmath>
using namespace std;

//  FUNCIONES

// 1. Promedio anual por departamento
double promedioAnual(double temperaturas[], int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma = suma + temperaturas[i];
    }
    return suma / n;
}

// 2. Promedio nacional (36 datos en total)
double promedioNacional(double santander[], double guajira[], double narino[], int n) {
    double suma = 0;
    for (int i = 0; i < n; i++) suma = suma + santander[i];
    for (int i = 0; i < n; i++) suma = suma + guajira[i];
    for (int i = 0; i < n; i++) suma = suma + narino[i];
    return suma / (3 * n);
}

// 3. Mes más caliente de un departamento
int mesMasCaliente(double temperaturas[], int n) {
    int indiceMax = 0;
    for (int i = 1; i < n; i++) {
        if (temperaturas[i] > temperaturas[indiceMax]) {
            indiceMax = i;
        }
    }
    return indiceMax; // devuelve índice (0=enero, 11=diciembre)
}

// 4. Promedio de los picos
double promedioPicos(double santander[], double guajira[], double narino[], int n) {
    int maxSantander = mesMasCaliente(santander, n);
    int maxGuajira = mesMasCaliente(guajira, n);
    int maxNarino = mesMasCaliente(narino, n);

    double picoSantander = santander[maxSantander];
    double picoGuajira = guajira[maxGuajira];
    double picoNarino = narino[maxNarino];

    return (picoSantander + picoGuajira + picoNarino) / 3.0;
}

// 5. Departamento con mayor promedio anual
string mayorPromedio(double promS, double promG, double promN) {
    if (promS >= promG && promS >= promN) return "Santander";
    else if (promG >= promS && promG >= promN) return "Guajira";
    else return "Nariño";
}

// 6. Temperatura máxima global
void maximoGlobal(double santander[], double guajira[], double narino[], int n,
    double& maxTemp, string& departamento, int& mes) {
    maxTemp = santander[0];
    departamento = "Santander";
    mes = 0;

    for (int i = 0; i < n; i++) {
        if (santander[i] > maxTemp) {
            maxTemp = santander[i];
            departamento = "Santander";
            mes = i;
        }
        if (guajira[i] > maxTemp) {
            maxTemp = guajira[i];
            departamento = "Guajira";
            mes = i;
        }
        if (narino[i] > maxTemp) {
            maxTemp = narino[i];
            departamento = "Nariño";
            mes = i;
        }
    }
}

// 7. Desviación estándar poblacional por departamento
double desviacionEstandar(double temperaturas[], int n) {
    double prom = promedioAnual(temperaturas, n);
    double suma = 0;
    for (int i = 0; i < n; i++) {
        suma += pow(temperaturas[i] - prom, 2);
    }
    return sqrt(suma / n);
}

// ------------------- MAIN ------------------------
int main() {
    const int MESES = 12;
    double santander[MESES], guajira[MESES], narino[MESES];

    // --- Ingreso de datos ---
    cout << "Ingrese las 12 temperaturas promedio mensuales de Santander:" << endl;
    for (int i = 0; i < MESES; i++) {
        cout << "Mes " << (i + 1) << ": ";
        cin >> santander[i];
    }

    cout << "\nIngrese las 12 temperaturas promedio mensuales de Guajira:" << endl;
    for (int i = 0; i < MESES; i++) {
        cout << "Mes " << (i + 1) << ": ";
        cin >> guajira[i];
    }

    cout << "\nIngrese las 12 temperaturas promedio mensuales de Nariño:" << endl;
    for (int i = 0; i < MESES; i++) {
        cout << "Mes " << (i + 1) << ": ";
        cin >> narino[i];
    }

    // --- Cálculos ---
    double promedioSantander = promedioAnual(santander, MESES);
    double promedioGuajira = promedioAnual(guajira, MESES);
    double promedioNarino = promedioAnual(narino, MESES);

    double promedioPais = promedioNacional(santander, guajira, narino, MESES);

    int mesSantander = mesMasCaliente(santander, MESES);
    int mesGuajira = mesMasCaliente(guajira, MESES);
    int mesNarino = mesMasCaliente(narino, MESES);

    double promedioDePicos = promedioPicos(santander, guajira, narino, MESES);

    string deptoMayor = mayorPromedio(promedioSantander, promedioGuajira, promedioNarino);

    double maxTemp;
    string deptoMax;
    int mesMax;
    maximoGlobal(santander, guajira, narino, MESES, maxTemp, deptoMax, mesMax);

    double desvSantander = desviacionEstandar(santander, MESES);
    double desvGuajira = desviacionEstandar(guajira, MESES);
    double desvNarino = desviacionEstandar(narino, MESES);

    // --- Resultados ---
    cout << "\n----- PROMEDIOS ANUALES -----" << endl;
    cout << "Santander: " << promedioSantander << " °C" << endl;
    cout << "Guajira:   " << promedioGuajira << " °C" << endl;
    cout << "Nariño:    " << promedioNarino << " °C" << endl;

    cout << "\n----- PROMEDIO NACIONAL -----" << endl;
    cout << "Promedio Nacional: " << promedioPais << " °C" << endl;

    cout << "\n----- MESES MÁS CALIENTES -----" << endl;
    cout << "Santander: Mes " << (mesSantander + 1) << " con " << santander[mesSantander] << " °C" << endl;
    cout << "Guajira:   Mes " << (mesGuajira + 1) << " con " << guajira[mesGuajira] << " °C" << endl;
    cout << "Nariño:    Mes " << (mesNarino + 1) << " con " << narino[mesNarino] << " °C" << endl;

    cout << "\n----- PROMEDIO DE LOS PICOS -----" << endl;
    cout << "Promedio de los máximos de los tres departamentos: " << promedioDePicos << " °C" << endl;

    cout << "\n----- DEPARTAMENTO CON MAYOR PROMEDIO -----" << endl;
    cout << "Departamento con mayor promedio anual: " << deptoMayor << endl;

    cout << "\n----- TEMPERATURA MÁXIMA GLOBAL -----" << endl;
    cout << "Máxima: " << maxTemp << " °C en " << deptoMax << ", mes " << (mesMax + 1) << endl;

    cout << "\n----- DESVIACIÓN ESTÁNDAR -----" << endl;
    cout << "Santander: " << desvSantander << endl;
    cout << "Guajira:   " << desvGuajira << endl;
    cout << "Nariño:    " << desvNarino << endl;

    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
