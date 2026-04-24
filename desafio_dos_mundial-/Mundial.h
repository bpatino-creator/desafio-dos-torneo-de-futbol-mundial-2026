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

    Equipo bombo1[12];
    Equipo bombo2[12];
    Equipo bombo3[12];
    Equipo bombo4[12];
    Grupo grupos[12];
    Equipo* clasificados[32];
    Equipo* terceros[12];
    Equipo* ganadores32[16];
    Equipo* ganadores16[8];
    Equipo* ganadores8[4];
    Equipo* finalistas[2];
    Equipo* perdedoresSemi[2];


    //Grupo* grupos;
    int totalGrupos;

public:
    Mundial();


    void cargarEquipos();
    void crearGrupos();
    void simular();
    void mostrarEquipos();
    void ordenarPorRanking();
    void crearBombos();
    void mostrarBombos();
    //void crearGrupos();
    void mostrarGrupos();
    void sortearGrupos();
    void programarFaseGrupos();
    void simularFaseGrupos();
    void clasificarEquipos();
    void jugarRonda32();
    void jugarOctavos();
    void jugarCuartos();
    void jugarSemifinal();
    void jugarFinal();


};

#endif
