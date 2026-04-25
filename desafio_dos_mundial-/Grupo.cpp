#include "Grupo.h"
#include "Partido.h"

Grupo::Grupo(char l) {
    letra = l;
    cantidadEquipos = 0;
}

Grupo::Grupo() {
    letra = '?';
    cantidadEquipos = 0;
}

void Grupo::agregarEquipo(Equipo* e) {
    if (cantidadEquipos < 4) {
        equipos[cantidadEquipos] = e;
        cantidadEquipos++;
    }
}

void Grupo::mostrar() {
    cout << "Grupo " << letra << endl;
    for (int i = 0; i < cantidadEquipos; i++)
        equipos[i]->mostrar();
}

void Grupo::mostrarSimple() {
    cout << "Grupo " << letra << ": ";
    for (int i = 0; i < cantidadEquipos; i++) {
        cout << equipos[i]->getNombre() << "(" << equipos[i]->getConfederacion() << ")";
        if (i < cantidadEquipos - 1)
            cout << " | ";
    }
    cout << endl;
}

void Grupo::simularPartidos() {
    cout << "\n--- Grupo " << letra << " ---\n";

    Equipo* A = equipos[0];
    Equipo* B = equipos[1];
    Equipo* C = equipos[2];
    Equipo* D = equipos[3];

    cout << "\nFecha 1:\n";
    Partido p1(A, B); p1.simular(); p1.actualizarEquipos(); p1.mostrar();
    Partido p2(C, D); p2.simular(); p2.actualizarEquipos(); p2.mostrar();

    cout << "\nFecha 2:\n";
    Partido p3(A, C); p3.simular(); p3.actualizarEquipos(); p3.mostrar();
    Partido p4(B, D); p4.simular(); p4.actualizarEquipos(); p4.mostrar();

    cout << "\nFecha 3:\n";
    Partido p5(A, D); p5.simular(); p5.actualizarEquipos(); p5.mostrar();
    Partido p6(B, C); p6.simular(); p6.actualizarEquipos(); p6.mostrar();
}

void Grupo::mostrarTabla() {
    for (int i = 0; i < cantidadEquipos - 1; i++) {
        for (int j = i + 1; j < cantidadEquipos; j++) {
            int pts_i = equipos[i]->getPuntos();
            int pts_j = equipos[j]->getPuntos();
            int dg_i = equipos[i]->getGolesFavor() - equipos[i]->getGolesContra();
            int dg_j = equipos[j]->getGolesFavor() - equipos[j]->getGolesContra();
            int gf_i = equipos[i]->getGolesFavor();
            int gf_j = equipos[j]->getGolesFavor();

            if (pts_j > pts_i ||
                (pts_j == pts_i && dg_j > dg_i) ||
                (pts_j == pts_i && dg_j == dg_i && gf_j > gf_i)) {
                Equipo* temp = equipos[i];
                equipos[i] = equipos[j];
                equipos[j] = temp;
            }
        }
    }

    cout << "\nTabla Grupo " << letra << endl;
    for (int i = 0; i < cantidadEquipos; i++) {
        int dg = equipos[i]->getGolesFavor() - equipos[i]->getGolesContra();
        cout << equipos[i]->getNombre()
             << " | Pts: " << equipos[i]->getPuntos()
             << " | GF: " << equipos[i]->getGolesFavor()
             << " | GC: " << equipos[i]->getGolesContra()
             << " | DG: " << dg
             << endl;
    }
}

int Grupo::getCantidadEquipos() {
    return cantidadEquipos;
}

Equipo* Grupo::getEquipo(int i) {
    return equipos[i];
}
