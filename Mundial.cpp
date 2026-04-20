#include "Mundial.h"
#include <fstream>

// Constructor
Mundial::Mundial() {
    totalEquipos = 0;
    equipos = new Equipo[50];

    totalGrupos = 0;
    grupos = nullptr;
}

void Mundial::cargarEquipos() {

    ifstream archivo("selecciones_clasificadas_mundial.csv");

    if (!archivo) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    char nombre[50];
    char conf[20];
    int ranking;

    totalEquipos = 0;

    while (archivo.getline(nombre, 50, ',')) {

        archivo.getline(conf, 20, ',');
        archivo >> ranking;
        archivo.ignore();

        equipos[totalEquipos] = Equipo(nombre, conf, ranking);
        totalEquipos++;
    }

    archivo.close();
}
