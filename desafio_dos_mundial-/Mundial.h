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

    Equipo* bombo1;
    Equipo* bombo2;
    Equipo* bombo3;
    Equipo* bombo4;
    Grupo* grupos;

    Equipo* clasificados[32];
    Equipo* terceros[12];
    Equipo* ganadores32[16];
    Equipo* ganadores16[8];
    Equipo* ganadores8[4];
    Equipo* finalistas[2];
    Equipo* perdedoresSemi[2];
    Equipo* campeonFinal;

public:
    Mundial();
    ~Mundial();

    void cargarEquipos();
    void mostrarEquipos();
    void ordenarPorRanking();
    void crearBombos();
    void mostrarBombos();
    void crearGrupos();
    void sortearGrupos();
    void mostrarGrupos();
    void programarFaseGrupos();
    void simularFaseGrupos();
    void clasificarEquipos();
    void jugarRonda32();
    void jugarOctavos();
    void jugarCuartos();
    void jugarSemifinal();
    void jugarFinal();
    void mostrarEstadisticas();
};

#endif
