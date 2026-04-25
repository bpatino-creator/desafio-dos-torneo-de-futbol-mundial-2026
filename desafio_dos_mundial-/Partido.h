#ifndef PARTIDO_H
#define PARTIDO_H

#include <iostream>
#include "Equipo.h"
using namespace std;

class Partido {
private:
    Equipo* equipo1;
    Equipo* equipo2;
    int goles1;
    int goles2;

public:
    Partido(Equipo* e1, Equipo* e2);

    void simular();
    void actualizarEquipos();
    void mostrar();
    int getGoles1();
    int getGoles2();
    void setGoles1(int g);
    void setGoles2(int g);
};

#endif
