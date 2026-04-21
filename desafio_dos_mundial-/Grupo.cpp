#include "Grupo.h"
#include "Partido.h"

// Constructor
Grupo::Grupo(char l) {
    letra = l;
    cantidadEquipos = 0;
}

// Agregar equipo
void Grupo::agregarEquipo(Equipo* e) {
    if (cantidadEquipos < 4) {
        equipos[cantidadEquipos] = e;
        cantidadEquipos++;
    }
}

// Mostrar grupo
void Grupo::mostrar() {
    cout << "Grupo " << letra << endl;

    for(int i = 0; i < cantidadEquipos; i++) {
        equipos[i]->mostrar();
    }
}

//jugar partidos
void Grupo::jugarPartidos() {
    cout << "Partidos del Grupo " << letra << endl;

    for(int i = 0; i < cantidadEquipos; i++) {
        for(int j = i + 1; j < cantidadEquipos; j++) {

            Partido p(equipos[i], equipos[j]);

            p.simular();
            p.actualizarEquipos(); // 🔥 importante
            p.mostrar();
        }
    }
}
/*void Grupo::jugarPartidos() {
    cout << "Partidos del Grupo " << letra << endl;

    Partido p(equipos[i], equipos[j]);

    p.simular();
    p.actualizarEquipos();  // 🔥 clave
    p.mostrar();

    for(int i = 0; i < cantidadEquipos; i++) {
        for(int j = i + 1; j < cantidadEquipos; j++) {

            Partido p(equipos[i], equipos[j]);

            p.simular();
            p.mostrar();
        }
    }
}*/

void mostrarTabla();

void Grupo::mostrarTabla() {
    cout << "Tabla del Grupo " << letra << endl;

    for(int i = 0; i < cantidadEquipos; i++) {
        cout << equipos[i]->getNombre()
        << " - Puntos: " << equipos[i]->getPuntos()
        << endl;
    }
}

int Equipo::getRanking() {
    return ranking;
}

