#include "Partido.h"

// Calcula la potencia de forma manual sin usar la libreria math
// se usa para aplicar la formula lambda del enunciado
double potencia(double base, double exponente) {
    double resultado = 1.0;
    int pasos = (int)(exponente * 10);
    for (int i = 0; i < pasos; i++)
        resultado *= base;
    return resultado;
}

// Constructor: guarda los punteros de los dos equipos e inicializa goles en cero
Partido::Partido(Equipo* e1, Equipo* e2) {
    equipo1 = e1;
    equipo2 = e2;
    goles1 = 0;
    goles2 = 0;
}

// Calcula los goles esperados de cada equipo usando la formula del enunciado
void Partido::simular() {
    double mu = 1.35;   // promedio general de goles
    double alpha = 0.6; // peso del ataque
    double beta  = 0.4; // peso de la defensa rival

    // Obtiene los goles historicos de cada equipo
    double gfA = equipo1->getGolesFavor();
    double gcA = equipo1->getGolesContra();
    double gfB = equipo2->getGolesFavor();
    double gcB = equipo2->getGolesContra();

    // Evita dividir por cero si algun valor es cero
    if (gfA == 0) gfA = 1;
    if (gcA == 0) gcA = 1;
    if (gfB == 0) gfB = 1;
    if (gcB == 0) gcB = 1;

    // Aplica la formula lambda para cada equipo
    double lambdaA = mu * potencia(gfA / mu, alpha) * potencia(gcB / mu, beta);
    double lambdaB = mu * potencia(gfB / mu, alpha) * potencia(gcA / mu, beta);

    // Limita los goles esperados a un rango razonable
    if (lambdaA < 0.5) lambdaA = 0.5;
    if (lambdaB < 0.5) lambdaB = 0.5;
    if (lambdaA > 5) lambdaA = 5;
    if (lambdaB > 5) lambdaB = 5;

    // Genera los goles de forma aleatoria dentro del rango calculado
    goles1 = rand() % ((int)(lambdaA + 3));
    goles2 = rand() % ((int)(lambdaB + 3));
}

// Actualiza puntos y goles de cada equipo segun el resultado del partido
void Partido::actualizarEquipos() {
    // Suma puntos segun el resultado
    if (goles1 > goles2)
        equipo1->sumarPuntos(3);       // gana equipo 1
    else if (goles2 > goles1)
        equipo2->sumarPuntos(3);       // gana equipo 2
    else {
        equipo1->sumarPuntos(1);       // empate
        equipo2->sumarPuntos(1);
    }

    // Actualiza goles a favor y en contra de cada equipo
    equipo1->sumarGolesFavor(goles1);
    equipo1->sumarGolesContra(goles2);
    equipo2->sumarGolesFavor(goles2);
    equipo2->sumarGolesContra(goles1);
}

// Muestra el resultado del partido en consola
void Partido::mostrar() {
    cout << equipo1->getNombre()
         << " " << goles1
         << " - " << goles2 << " "
         << equipo2->getNombre()
         << endl;
}

int Partido::getGoles1() { return goles1; }
int Partido::getGoles2() { return goles2; }
void Partido::setGoles1(int g) { goles1 = g; }
void Partido::setGoles2(int g) { goles2 = g; }
