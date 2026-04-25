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

public:
    Grupo(char l);
    Grupo();

    void agregarEquipo(Equipo* e);
    void mostrar();
    void mostrarSimple();
    void mostrarTabla();
    void simularPartidos();
    int getCantidadEquipos();
    Equipo* getEquipo(int i);
};

#endif
