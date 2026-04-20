#include <iostream>
#include "Equipo.h"
#include "Partido.h"
#include "Grupo.h"
#include "Mundial.h"

using namespace std;

int main() {

    Mundial m;

    m.cargarEquipos();
    // 🔥 lo que ya tenías
    Equipo e1("Colombia");
    Equipo e2("Brasil");

    Partido p(&e1, &e2);

    p.simular();
    p.mostrar();

    cout << "---------------------" << endl;

    // 🔥 lo nuevo (grupo)
    Equipo e3("España");
    Equipo e4("Alemania");

    Grupo g('A');

    g.agregarEquipo(&e1);
    g.agregarEquipo(&e2);
    g.agregarEquipo(&e3);
    g.agregarEquipo(&e4);

    g.mostrar();

    cout << "---------------------" << endl;

    g.jugarPartidos();

    cout << "---------------------" << endl;

    g.mostrarTabla();

    return 0;
}
