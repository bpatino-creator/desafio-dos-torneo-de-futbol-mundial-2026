#ifndef MUNDIAL_H
#define MUNDIAL_H

#include <iostream>
#include "Equipo.h"
#include "Grupo.h"

using namespace std;

class Mundial {
private:
    Equipo* equipos;
    int totalEquipos;

    Grupo* grupos;
    int totalGrupos;

public:
    Mundial();

    void cargarEquipos();
    void crearGrupos();
    void simular();
};

#endif
