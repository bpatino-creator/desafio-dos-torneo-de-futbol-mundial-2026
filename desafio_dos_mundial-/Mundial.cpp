#include "Mundial.h"
#include <fstream>
#include <cstdlib>  // para rand

Mundial::Mundial() {
    totalEquipos = 0;
    equipos = new Equipo[50];

    srand(42); // semilla fija para no utilizar ctime libreria
}

void Mundial::mostrarGrupos() {

    cout << "\n=========== GRUPOS ===========\n";

    for(int i = 0; i < 12; i++) {
        grupos[i].mostrarSimple();
    }
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

    int posUSA = -1;

    // 1. Buscar USA
    for(int i = 0; i < totalEquipos; i++) {
        if(equipos[i].getNombre() == "United States") {
            posUSA = i;
            break;
        }
    }

    int indice = 0;

    // 2. Meter USA primero en bombo 1
    if(posUSA != -1) {
        bombo1[0] = equipos[posUSA];
    }

    // 3. Llenar el resto de bombos sin repetir USA
    for(int i = 0; i < totalEquipos; i++) {

        if(i == posUSA) continue; // saltar USA

        if(indice < 11) {
            bombo1[indice + 1] = equipos[i];
        }
        else if(indice < 23) {
            bombo2[indice - 11] = equipos[i];
        }
        else if(indice < 35) {
            bombo3[indice - 23] = equipos[i];
        }
        else {
            bombo4[indice - 35] = equipos[i];
        }

        indice++;
    }

    cout << "CREANDO BOMBOS (USA en bombo 1)..." << endl;
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

bool puedeEntrar(Grupo& g, string conf) {

    int conteo = 0;
    int uefa = 0;

    for(int i = 0; i < g.getCantidadEquipos(); i++) {

        string c = g.getEquipo(i)->getConfederacion();

        if(c == conf) conteo++;
        if(c == "UEFA") uefa++;
    }

    if(conf == "UEFA") return uefa < 2;

    return conteo == 0;
}

void barajar(Equipo bombo[], int n) {
    for(int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);

        Equipo temp = bombo[i];
        bombo[i] = bombo[j];
        bombo[j] = temp;
    }
}


void Mundial::sortearGrupos() {

    bool valido = false;

    while(!valido) {

        // 🔹 limpiar grupos
        for(int i = 0; i < 12; i++) {
            grupos[i] = Grupo('A' + i);
        }

        // 🔹 mezclar bombos
        barajar(bombo1, 12);
        barajar(bombo2, 12);
        barajar(bombo3, 12);
        barajar(bombo4, 12);

        // 🔹 BOMBO 1
        for(int i = 0; i < 12; i++) {
            grupos[i].agregarEquipo(&bombo1[i]);
        }

        bool fallo = false;

        // 🔹 función interna para asignar
        auto asignar = [&](Equipo bombo[]) {

            for(int i = 0; i < 12; i++) {

                bool colocado = false;
                int intentos = 0;

                while(!colocado && intentos < 50) {

                    int g = rand() % 12;

                    if(grupos[g].getCantidadEquipos() < 4 &&
                        puedeEntrar(grupos[g], bombo[i].getConfederacion())) {

                        grupos[g].agregarEquipo(&bombo[i]);
                        colocado = true;
                    }

                    intentos++;
                }

                if(!colocado) {
                    fallo = true;
                    return;
                }
            }
        };

        // 🔹 asignar bombos
        asignar(bombo2);
        if(fallo) continue;

        asignar(bombo3);
        if(fallo) continue;

        asignar(bombo4);
        if(fallo) continue;

        // 🔹 si llegó aquí → válido
        valido = true;
    }
}

void Mundial::programarFaseGrupos() {

    cout << "\n===== PROGRAMANDO FASE DE GRUPOS =====\n";

    int partidosPorDia[30] = {0};
    int dia = 0;
    int total = 0;

    int diaInicio = 20;
    int mes = 6;

    cout << "\n";

    for(int g = 0; g < 12; g++) {

        Grupo& grupo = grupos[g];

        for(int i = 0; i < 4; i++) {
            for(int j = i + 1; j < 4; j++) {

                // 🔹 si el día está lleno → siguiente día
                if(partidosPorDia[dia] == 4) {
                    dia++;
                    diaInicio++;

                    if(diaInicio > 30 && mes == 6) {
                        diaInicio = 1;
                        mes = 7;
                    }

                    cout << "\n"; // salto de día
                }

                // 🔹 imprimir fecha si es el primer partido del día
                if(partidosPorDia[dia] == 0) {
                    cout << diaInicio << "/" << mes << ":\n";
                }

                // 🔥 imprimir partido
                cout << "  "
                     << grupo.getEquipo(i)->getNombre()
                     << " vs "
                     << grupo.getEquipo(j)->getNombre()
                     << endl;

                partidosPorDia[dia]++;
                total++;
            }
        }
    }

    cout << "\nTotal: " << total << " partidos\n";
}
