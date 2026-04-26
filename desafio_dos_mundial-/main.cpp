#include <iostream>
#include "Mundial.h"
using namespace std;

int main() {
    // Crea el objeto mundial que coordina todo el torneo
    Mundial m;

    // Lee los 48 equipos desde el archivo CSV
    m.cargarEquipos();

    // Ordena los equipos de mejor a peor ranking FIFA
    m.ordenarPorRanking();

    // Divide los equipos en 4 bombos de 12 segun su ranking
    m.crearBombos();

    // Muestra los 4 bombos en consola
    m.mostrarBombos();

    // Crea los 12 grupos vacios con sus letras
    m.crearGrupos();

    // Sortea los grupos respetando restricciones de confederacion
    m.sortearGrupos();

    // Muestra los grupos conformados con sus equipos
    m.mostrarGrupos();

    // Asigna fechas a los 72 partidos de la fase de grupos
    m.programarFaseGrupos();

    // Simula los 72 partidos y actualiza estadisticas
    m.simularFaseGrupos();

    // Selecciona los 32 equipos que pasan a dieciseisavos
    m.clasificarEquipos();

    // Simula los 16 partidos de dieciseisavos
    m.jugarRonda32();

    // Simula los 8 partidos de octavos de final
    m.jugarOctavos();

    // Simula los 4 partidos de cuartos de final
    m.jugarCuartos();

    // Simula las 2 semifinales
    m.jugarSemifinal();

    // Simula el tercer puesto y la final
    m.jugarFinal();

    // Muestra el podio y estadisticas finales del torneo
    m.mostrarEstadisticas();

    return 0;
}
