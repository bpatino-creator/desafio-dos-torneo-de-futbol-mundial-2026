#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Equipo.h"

using namespace std;

class Grupo {
private:
    char letra;
    Equipo* equipos[4];
    int cantidadEquipos;
    int puntos;
    int ganados;
    int empatados;
    int perdidos;

public:
    Grupo(char l);
    Grupo();

    void agregarEquipo(Equipo* e);
    void mostrar();
    void jugarPartidos();
    void mostrarTabla();
    int getCantidadEquipos();
    Equipo* getEquipo(int i);
    void mostrarSimple();
    void simularPartidos();

};

#endif
