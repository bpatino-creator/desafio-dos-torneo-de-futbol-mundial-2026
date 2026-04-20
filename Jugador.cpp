#include "Jugador.h"

Jugador::Jugador() {
    nombre = "";
    numero = 0;
}

Jugador::Jugador(string n, int num) {
    nombre = n;
    numero = num;
}

void Jugador::mostrar() {
    cout << "Jugador: " << nombre << " #" << numero << endl;
}
