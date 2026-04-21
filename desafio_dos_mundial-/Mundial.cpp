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

    ifstream archivo("datos.csv.csv");

    if (!archivo) {
        cout << "Error al abrir archivo" << endl;
        return;
    }

    char nombre[50];
    char conf[20];
    int ranking;
    int gf;
    int gc;

    while (archivo.getline(nombre, 50, ',')) {

        archivo.getline(conf, 20, ',');
        archivo >> ranking;
        archivo.ignore();

        archivo >> gf;
        archivo.ignore();

        archivo >> gc;
        archivo.ignore();

        equipos[totalEquipos] = Equipo(nombre, conf, ranking, gf, gc);
        totalEquipos++;
    }
}
void Mundial::mostrarEquipos() {
    for(int i = 0; i < totalEquipos; i++) {
        equipos[i].mostrar();
    }
}

void Mundial::ordenarPorRanking() {

    for(int i = 0; i < totalEquipos - 1; i++) {
        for(int j = 0; j < totalEquipos - 1 - i; j++) {

            if(equipos[j].getRanking() > equipos[j + 1].getRanking()) {

                // intercambio
                Equipo temp = equipos[j];
                equipos[j] = equipos[j + 1];
                equipos[j + 1] = temp;
            }
        }
    }
}

void Mundial::crearBombos() {

    for(int i = 0; i < 12; i++) {
        bombo1[i] = equipos[i];
    }

    for(int i = 0; i < 12; i++) {
        bombo2[i] = equipos[i + 12];
    }

    for(int i = 0; i < 12; i++) {
        bombo3[i] = equipos[i + 24];
    }

    for(int i = 0; i < 12; i++) {
        bombo4[i] = equipos[i + 36];
    }
    cout << "CREANDO BOMBOS..." << endl;
}
void Mundial::mostrarBombos() {

    cout << "\n=========== BOMBOS ===========\n";

    cout << "\nBOMBO 1\n";
    for(int i = 0; i < 12; i++)
        bombo1[i].mostrarSimple();

    cout << "\nBOMBO 2\n";
    for(int i = 0; i < 12; i++)
        bombo2[i].mostrarSimple();

    cout << "\nBOMBO 3\n";
    for(int i = 0; i < 12; i++)
        bombo3[i].mostrarSimple();

    cout << "\nBOMBO 4\n";
    for(int i = 0; i < 12; i++)
        bombo4[i].mostrarSimple();
}

void Mundial::crearGrupos() {

    char letra = 'A';

    for(int i = 0; i < 12; i++) {
        grupos[i] = Grupo(letra);
        letra++;
    }
}

