#ifndef MUNDIAL_H
#define MUNDIAL_H

#include <iostream>
#include "Equipo.h"
#include "Grupo.h"
using namespace std;

// Clase principal que coordina todo el torneo del mundial
class Mundial {
private:
    Equipo* equipos;      // arreglo dinamico con los 48 equipos cargados
    int totalEquipos;     // cantidad de equipos cargados

    Equipo* bombo1;       // 12 mejores equipos por ranking
    Equipo* bombo2;       // siguientes 12
    Equipo* bombo3;       // siguientes 12
    Equipo* bombo4;       // los 12 de menor ranking
    Grupo* grupos;        // los 12 grupos del torneo

    Equipo* clasificados[32];    // los 32 que pasan de la fase de grupos
    Equipo* terceros[12];        // los 12 terceros de cada grupo
    Equipo* ganadores32[16];     // ganadores de dieciseisavos
    Equipo* ganadores16[8];      // ganadores de octavos
    Equipo* ganadores8[4];       // ganadores de cuartos
    Equipo* finalistas[2];       // los dos equipos que juegan la final
    Equipo* perdedoresSemi[2];   // los que juegan el tercer puesto
    Equipo* campeonFinal;        // el campeon del mundial

public:
    // Constructor: crea toda la memoria dinamica necesaria
    Mundial();
    // Destructor: libera toda la memoria creada
    ~Mundial();

    // Lee los equipos desde el archivo CSV
    void cargarEquipos();
    // Muestra todos los equipos con sus datos
    void mostrarEquipos();
    // Ordena los equipos de mejor a peor ranking FIFA
    void ordenarPorRanking();
    // Divide los equipos en 4 bombos de 12
    void crearBombos();
    // Muestra los 4 bombos en consola
    void mostrarBombos();
    // Crea los 12 grupos con sus letras
    void crearGrupos();
    // Sortea los grupos respetando restricciones de confederacion
    void sortearGrupos();
    // Muestra los grupos conformados
    void mostrarGrupos();
    // Asigna fechas a los partidos de la fase de grupos
    void programarFaseGrupos();
    // Simula los 72 partidos de la fase de grupos
    void simularFaseGrupos();
    // Selecciona los 32 equipos que pasan a dieciseisavos
    void clasificarEquipos();
    // Simula los 16 partidos de dieciseisavos
    void jugarRonda32();
    // Simula los 8 partidos de octavos
    void jugarOctavos();
    // Simula los 4 partidos de cuartos
    void jugarCuartos();
    // Simula las 2 semifinales
    void jugarSemifinal();
    // Simula el tercer puesto y la final
    void jugarFinal();
    // Muestra el podio y estadisticas finales del torneo
    void mostrarEstadisticas();
};

#endif
