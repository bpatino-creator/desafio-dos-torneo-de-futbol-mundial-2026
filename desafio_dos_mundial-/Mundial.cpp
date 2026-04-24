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

    // días por jornada
    int dias[3][6] = {
        {20,21,22,23,24,25},   // junio
        {27,28,29,30,1,2},     // mezcla junio/julio
        {4,5,6,7,8,9}          // julio
    };

    // meses correspondientes
    int meses[3][6] = {
        {6,6,6,6,6,6},
        {6,6,6,6,7,7},
        {7,7,7,7,7,7}
    };

    // 🔹 recorrer jornadas
    for(int fecha = 0; fecha < 3; fecha++) {

        cout << "\n===== FECHA " << fecha + 1 << " =====\n";

        int diaIdx = 0;
        int partidosHoy = 0;

        for(int g = 0; g < 12; g++) {

            Grupo& grupo = grupos[g];

            Equipo* A = grupo.getEquipo(0);
            Equipo* B = grupo.getEquipo(1);
            Equipo* C = grupo.getEquipo(2);
            Equipo* D = grupo.getEquipo(3);

            Equipo *e1, *e2, *e3, *e4;

            // fixture correcto
            if(fecha == 0) {
                e1 = A; e2 = B;
                e3 = C; e4 = D;
            }
            else if(fecha == 1) {
                e1 = A; e2 = C;
                e3 = B; e4 = D;
            }
            else {
                e1 = A; e2 = D;
                e3 = B; e4 = C;
            }

            int d = dias[fecha][diaIdx];
            int m = meses[fecha][diaIdx];

            // ---- Partido 1 ----
            if(partidosHoy == 0) {
                cout << "\n" << d << "/" << m << ":\n";
            }

            cout << "  " << e1->getNombre() << " vs " << e2->getNombre() << endl;
            partidosHoy++;

            if(partidosHoy == 4) {
                partidosHoy = 0;
                diaIdx++;
            }

            // actualizar día si cambió
            d = dias[fecha][diaIdx];
            m = meses[fecha][diaIdx];

            // ---- Partido 2 ----
            if(partidosHoy == 0) {
                cout << "\n" << d << "/" << m << ":\n";
            }

            cout << "  " << e3->getNombre() << " vs " << e4->getNombre() << endl;
            partidosHoy++;

            if(partidosHoy == 4) {
                partidosHoy = 0;
                diaIdx++;
            }
        }
    }
}

void Mundial::simularFaseGrupos() {

    // 🔥 REINICIAR ANTES
    for(int i = 0; i < 12; i++) {
        for(int j = 0; j < 4; j++) {
            grupos[i].getEquipo(j)->reiniciarEstadisticas();
        }
    }

    // 🔹 SIMULAR
    for(int i = 0; i < 12; i++) {
        grupos[i].simularPartidos();
        grupos[i].mostrarTabla();
    }
}

void Mundial::clasificarEquipos() {

    cout << "\n===== CLASIFICADOS A OCTAVOS =====\n";

    for(int i = 0; i < 12; i++) {

        cout << "Grupo " << char('A' + i) << ": ";

        Equipo* primero = grupos[i].getEquipo(0);
        Equipo* segundo = grupos[i].getEquipo(1);

        cout << primero->getNombre()
             << " y "
             << segundo->getNombre()
             << endl;
    }
}
