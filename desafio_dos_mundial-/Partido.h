#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include "Equipo.h"
using namespace std;

// Representa un partido entre dos equipos
class Partido {
private:
    Equipo* equipo1;  // puntero al primer equipo
    Equipo* equipo2;  // puntero al segundo equipo
    int goles1;       // goles del equipo 1
    int goles2;       // goles del equipo 2

public:
    // Constructor: recibe punteros para no copiar los equipos
    Partido(Equipo* e1, Equipo* e2);

    // Calcula los goles de cada equipo usando la formula del enunciado
    void simular();
    // Actualiza puntos y goles de cada equipo segun el resultado
    void actualizarEquipos();
    // Muestra el resultado del partido en consola
    void mostrar();
    int getGoles1();
    int getGoles2();
    void setGoles1(int g);
    void setGoles2(int g);
};

#endif
