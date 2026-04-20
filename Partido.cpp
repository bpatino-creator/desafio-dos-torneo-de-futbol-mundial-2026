#include "Partido.h"
#include <cstdlib> // para rand()

// Constructor
Partido::Partido(Equipo* e1, Equipo* e2) {
    equipo1 = e1;
    equipo2 = e2;
    goles1 = 0;
    goles2 = 0;
}

// Simular partido
void Partido::simular() {
    goles1 = rand() % 5;
    goles2 = rand() % 5;
}

// Mostrar resultado
void Partido::mostrar() {
    cout << equipo1->getNombre() << " " << goles1
         << " vs "
         << goles2 << " " << equipo2->getNombre() << endl;
}

void Partido::actualizarEquipos() {

    if (goles1 > goles2) {
        equipo1->sumarVictoria();
        equipo2->sumarDerrota();
    }
    else if (goles2 > goles1) {
        equipo2->sumarVictoria();
        equipo1->sumarDerrota();
    }
    else {
        equipo1->sumarEmpate();
        equipo2->sumarEmpate();
    }
}
