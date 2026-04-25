#include <iostream>
#include "Mundial.h"
using namespace std;

int main() {
    Mundial m;

    m.cargarEquipos();
    m.ordenarPorRanking();
    m.crearBombos();
    m.mostrarBombos();
    m.crearGrupos();
    m.sortearGrupos();
    m.mostrarGrupos();
    m.programarFaseGrupos();
    m.simularFaseGrupos();
    m.clasificarEquipos();
    m.jugarRonda32();
    m.jugarOctavos();
    m.jugarCuartos();
    m.jugarSemifinal();
    m.jugarFinal();
    m.mostrarEstadisticas();

    return 0;
}
