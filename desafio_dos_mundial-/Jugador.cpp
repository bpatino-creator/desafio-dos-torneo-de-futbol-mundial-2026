#include "Jugador.h"

// Constructor vacio: deja el nombre vacio y el numero en cero
Jugador::Jugador() {
    nombre = "";
    numero = 0;
}

// Constructor con datos: asigna nombre y numero de camiseta
Jugador::Jugador(string n, int num) {
    nombre = n;
    numero = num;
}

// Muestra el nombre y numero del jugador en consola
void Jugador::mostrar() {
    cout << "Jugador: " << nombre << " #" << numero << endl;
}
