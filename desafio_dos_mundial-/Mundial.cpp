#include "Mundial.h"
#include <fstream>
#include <cstdlib>  // para rand
#include "Partido.h"

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

/*void Mundial::programarFaseGrupos() {

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
}*/

void Mundial::programarFaseGrupos() {

    cout << "\n===== PROGRAMANDO FASE DE GRUPOS =====\n";

    // 🔥 DIAS CORRECTOS
    int dias[3][6] = {
        {20,21,22,23,24,25},   // Fecha 1
        {23,24,25,26,27,28},   // Fecha 2
        {26,27,28,29,30,1}     // Fecha 3 (ya pasa a julio)
    };

    // 🔥 MESES CORRECTOS
    int meses[3][6] = {
        {6,6,6,6,6,6},
        {6,6,6,6,6,6},
        {6,6,6,6,6,7}   // 👈 este 7 arregla TODO
    };

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

            // Partido 1
            if(partidosHoy == 0) {
                cout << "\n" << d << "/" << m << ":\n";
            }

            cout << "  " << e1->getNombre() << " vs " << e2->getNombre() << endl;
            partidosHoy++;

            if(partidosHoy == 4) {
                partidosHoy = 0;
                diaIdx++;
            }

            d = dias[fecha][diaIdx];
            m = meses[fecha][diaIdx];

            // Partido 2
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

    int k = 0;

    for(int i = 0; i < 12; i++) {
        clasificados[k++] = grupos[i].getEquipo(0);
        clasificados[k++] = grupos[i].getEquipo(1);
        terceros[i] = grupos[i].getEquipo(2);
    }

    // ordenar terceros
    for(int i = 0; i < 11; i++) {
        for(int j = i + 1; j < 12; j++) {

            int pts_i = terceros[i]->getPuntos();
            int pts_j = terceros[j]->getPuntos();

            int dg_i = terceros[i]->getGolesFavor() - terceros[i]->getGolesContra();
            int dg_j = terceros[j]->getGolesFavor() - terceros[j]->getGolesContra();

            int gf_i = terceros[i]->getGolesFavor();
            int gf_j = terceros[j]->getGolesFavor();

            if(pts_j > pts_i ||
                (pts_j == pts_i && dg_j > dg_i) ||
                (pts_j == pts_i && dg_j == dg_i && gf_j > gf_i)) {

                Equipo* temp = terceros[i];
                terceros[i] = terceros[j];
                terceros[j] = temp;
            }
        }
    }

    // mejores 8 terceros
    for(int i = 0; i < 8; i++) {
        clasificados[k++] = terceros[i];
    }

    cout << "\n===== CLASIFICADOS (32) =====\n";
    for(int i = 0; i < 32; i++) {
        cout << clasificados[i]->getNombre() << endl;
    }
}

void Mundial::jugarRonda32() {

    cout << "\n===== RONDA DE 32 =====\n";

    int k = 0;
    int dia = 4;   // 🔥 EMPIEZA DESPUÉS DEL DESCANSO
    int mes = 7;
    int partidosHoy = 0;

    for(int i = 0; i < 32; i += 2) {

        // 🔹 imprimir fecha
        if(partidosHoy == 0) {
            cout << "\n" << dia << "/" << mes << ":\n";
        }

        Partido p(clasificados[i], clasificados[i+1]);
        p.simular();

        // 🔥 penales
        if(p.getGoles1() == p.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand()%2 == 0)
                p.setGoles1(p.getGoles1()+1);
            else
                p.setGoles2(p.getGoles2()+1);
        }

        p.mostrar();

        // 🔹 guardar ganador
        if(p.getGoles1() > p.getGoles2())
            ganadores32[k++] = clasificados[i];
        else
            ganadores32[k++] = clasificados[i+1];

        partidosHoy++;

        // 🔹 cada 4 partidos → nuevo día
        if(partidosHoy == 4) {
            partidosHoy = 0;
            dia++;
        }
    }
}


void Mundial::jugarOctavos() {

    cout << "\n===== OCTAVOS DE FINAL =====\n";

    int k = 0;
    int dia = 8;   // 🔥 DESPUÉS DEL DESCANSO
    int mes = 7;
    int partidosHoy = 0;

    for(int i = 0; i < 16; i += 2) {

        // 🔹 imprimir fecha
        if(partidosHoy == 0) {
            cout << "\n" << dia << "/" << mes << ":\n";
        }

        Partido p(ganadores32[i], ganadores32[i+1]);
        p.simular();

        // 🔥 penales
        if(p.getGoles1() == p.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand()%2 == 0)
                p.setGoles1(p.getGoles1()+1);
            else
                p.setGoles2(p.getGoles2()+1);
        }

        p.mostrar();

        // 🔹 guardar ganador
        if(p.getGoles1() > p.getGoles2())
            ganadores16[k++] = ganadores32[i];
        else
            ganadores16[k++] = ganadores32[i+1];

        partidosHoy++;

        // 🔹 2 partidos por día
        if(partidosHoy == 2) {
            partidosHoy = 0;
            dia++;
        }
    }
}

/*void Mundial::jugarOctavos() {

    cout << "\n===== OCTAVOS DE FINAL =====\n";

    int dia = 10;
    int mes = 7;
    int k = 0;

    for(int i = 0; i < 12; i += 2) {

        cout << "\n" << dia << "/" << mes << ":\n";

        Equipo* A1 = grupos[i].getEquipo(0);
        Equipo* A2 = grupos[i].getEquipo(1);

        Equipo* B1 = grupos[i+1].getEquipo(0);
        Equipo* B2 = grupos[i+1].getEquipo(1);

        // 🔹 Partido 1
        Partido p1(A1, B2);
        p1.simular();

        if(p1.getGoles1() == p1.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand() % 2 == 0)
                p1.setGoles1(p1.getGoles1() + 1);
            else
                p1.setGoles2(p1.getGoles2() + 1);
        }

        p1.mostrar();

        // guardar ganador
        if(p1.getGoles1() > p1.getGoles2())
            ganadoresOctavos[k++] = A1;
        else
            ganadoresOctavos[k++] = B2;

        // 🔹 Partido 2
        Partido p2(B1, A2);
        p2.simular();

        if(p2.getGoles1() == p2.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand() % 2 == 0)
                p2.setGoles1(p2.getGoles1() + 1);
            else
                p2.setGoles2(p2.getGoles2() + 1);
        }

        p2.mostrar();

        // guardar ganador
        if(p2.getGoles1() > p2.getGoles2())
            ganadoresOctavos[k++] = B1;
        else
            ganadoresOctavos[k++] = A2;

        dia++;
    }
}*/

void Mundial::jugarCuartos() {

    cout << "\n===== CUARTOS DE FINAL =====\n";

    int k = 0;
    int dia = 13;   // 🔥 CORREGIDO
    int mes = 7;
    int partidosHoy = 0;

    for(int i = 0; i < 8; i += 2) {

        if(partidosHoy == 0) {
            cout << "\n" << dia << "/" << mes << ":\n";
        }

        Partido p(ganadores16[i], ganadores16[i+1]);
        p.simular();

        if(p.getGoles1() == p.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand()%2 == 0) p.setGoles1(p.getGoles1()+1);
            else p.setGoles2(p.getGoles2()+1);
        }

        p.mostrar();

        if(p.getGoles1() > p.getGoles2())
            ganadores8[k++] = ganadores16[i];
        else
            ganadores8[k++] = ganadores16[i+1];

        partidosHoy++;

        if(partidosHoy == 2) {
            partidosHoy = 0;
            dia++;
        }
    }
}

void Mundial::jugarSemifinal() {

    cout << "\n===== SEMIFINAL =====\n";

    int dia = 16;
    int mes = 7;

    int k = 0;

    for(int i = 0; i < 4; i += 2) {

        cout << "\n" << dia++ << "/" << mes << ":\n";

        Partido p(ganadores8[i], ganadores8[i+1]);
        p.simular();

        if(p.getGoles1() == p.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand()%2 == 0) p.setGoles1(p.getGoles1()+1);
            else p.setGoles2(p.getGoles2()+1);
        }

        p.mostrar();

        if(p.getGoles1() > p.getGoles2()) {
            finalistas[k] = ganadores8[i];
            perdedoresSemi[k] = ganadores8[i+1];
        } else {
            finalistas[k] = ganadores8[i+1];
            perdedoresSemi[k] = ganadores8[i];
        }

        k++;
    }
}

void Mundial::jugarFinal() {

    int mes = 7;

    cout << "\n===== TERCER PUESTO =====\n";
    cout << "\n20/" << mes << ":\n";

    Partido tercer(perdedoresSemi[0], perdedoresSemi[1]);
    tercer.simular();

    if(tercer.getGoles1() == tercer.getGoles2()) {
        if(rand()%2 == 0) tercer.setGoles1(tercer.getGoles1()+1);
        else tercer.setGoles2(tercer.getGoles2()+1);
    }

    tercer.mostrar();

    cout << "\n===== FINAL =====\n";
    cout << "\n21/" << mes << ":\n";

    Partido final(finalistas[0], finalistas[1]);
    final.simular();

    if(final.getGoles1() == final.getGoles2()) {
        if(rand()%2 == 0) final.setGoles1(final.getGoles1()+1);
        else final.setGoles2(final.getGoles2()+1);
    }

    final.mostrar();

    if(final.getGoles1() > final.getGoles2())
        cout << "\n🏆 CAMPEON: " << finalistas[0]->getNombre() << endl;
    else
        cout << "\n🏆 CAMPEON: " << finalistas[1]->getNombre() << endl;
}

/*void Mundial::jugarCuartos() {

    cout << "\n===== CUARTOS DE FINAL =====\n";

    int dia = 16;  // 🔥 empieza justo después de octavos
    int mes = 7;

    int partidosEnDia = 0;

    for(int i = 0; i < 12; i += 2) {

        if(partidosEnDia == 0) {
            cout << "\n" << dia << "/" << mes << ":\n";
        }

        Partido p(ganadoresOctavos[i], ganadoresOctavos[i+1]);
        p.simular();

        if(p.getGoles1() == p.getGoles2()) {
            cout << "  (Empate -> penales)\n";
            if(rand() % 2 == 0)
                p.setGoles1(p.getGoles1() + 1);
            else
                p.setGoles2(p.getGoles2() + 1);
        }

        p.mostrar();

        partidosEnDia++;

        if(partidosEnDia == 2) {
            partidosEnDia = 0;
            dia++;
        }
    }
}*/
