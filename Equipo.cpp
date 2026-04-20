#include "Equipo.h"

// Constructor vacío
Equipo::Equipo() {
    nombrePais = "";
    golesFavor = 0;
    golesContra = 0;

    puntos = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;

    cantidadJugadores = 0;
    jugadores = nullptr;
}

// Constructor con nombre
Equipo::Equipo(string nombre) {
    nombrePais = nombre;
    golesFavor = 0;
    golesContra = 0;

    puntos = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;

    //
    cantidadJugadores = 26;
    jugadores = new Jugador[cantidadJugadores];

    for(int i = 0; i < cantidadJugadores; i++) {
        jugadores[i] = Jugador("Jugador", i + 1);
    }
}

// Getter
string Equipo::getNombre() {
    return nombrePais;
}

// Setter
void Equipo::setNombre(string nombre) {
    nombrePais = nombre;
}

// Mostrar
void Equipo::mostrar() {
    cout << "Equipo: " << nombrePais << endl;

    for(int i = 0; i < cantidadJugadores; i++) {
        jugadores[i].mostrar();
    }
}

void Equipo::sumarVictoria() {
    ganados++;
    puntos += 3;
}

void Equipo::sumarEmpate() {
    empatados++;
    puntos += 1;
}

void Equipo::sumarDerrota() {
    perdidos++;
}

int Equipo::getPuntos() {
    return puntos;
}
