#include "Equipo.h"

Equipo::~Equipo() {
    delete[] jugadores;
    jugadores = nullptr;
}

Equipo::Equipo(const Equipo& otro) {
    nombrePais = otro.nombrePais;
    confederacion = otro.confederacion;
    ranking = otro.ranking;
    golesFavor = otro.golesFavor;
    golesContra = otro.golesContra;
    puntos = otro.puntos;
    ganados = otro.ganados;
    empatados = otro.empatados;
    perdidos = otro.perdidos;
    cantidadJugadores = otro.cantidadJugadores;

    if (cantidadJugadores > 0 && otro.jugadores != nullptr) {
        jugadores = new Jugador[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i];
    } else {
        jugadores = nullptr;
    }
}

Equipo& Equipo::operator=(const Equipo& otro) {
    if (this == &otro) return *this;

    delete[] jugadores;

    nombrePais = otro.nombrePais;
    confederacion = otro.confederacion;
    ranking = otro.ranking;
    golesFavor = otro.golesFavor;
    golesContra = otro.golesContra;
    puntos = otro.puntos;
    ganados = otro.ganados;
    empatados = otro.empatados;
    perdidos = otro.perdidos;
    cantidadJugadores = otro.cantidadJugadores;

    if (cantidadJugadores > 0 && otro.jugadores != nullptr) {
        jugadores = new Jugador[cantidadJugadores];
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i];
    } else {
        jugadores = nullptr;
    }

    return *this;
}

bool Equipo::operator<(const Equipo& otro) const {
    return puntos < otro.puntos;
}

bool Equipo::operator==(const Equipo& otro) const {
    return nombrePais == otro.nombrePais;
}

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

Equipo::Equipo(string nombre) {
    nombrePais = nombre;
    golesFavor = 0;
    golesContra = 0;
    puntos = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;
    cantidadJugadores = 26;
    jugadores = new Jugador[cantidadJugadores];

    for (int i = 0; i < cantidadJugadores; i++)
        jugadores[i] = Jugador("Jugador", i + 1);
}

Equipo::Equipo(string nombre, string conf, int rank, int gf, int gc) {
    nombrePais = nombre;
    confederacion = conf;
    ranking = rank;
    golesFavor = gf;
    golesContra = gc;
    puntos = 0;
    ganados = 0;
    empatados = 0;
    perdidos = 0;
    cantidadJugadores = 26;
    jugadores = new Jugador[cantidadJugadores];

    for (int i = 0; i < cantidadJugadores; i++)
        jugadores[i] = Jugador("Jugador", i + 1);
}

string Equipo::getNombre() {
    return nombrePais;
}

void Equipo::setNombre(string nombre) {
    nombrePais = nombre;
}

void Equipo::mostrar() {
    cout << "Equipo: " << nombrePais << endl;
    for (int i = 0; i < cantidadJugadores; i++)
        jugadores[i].mostrar();
}

void Equipo::mostrarSimple() {
    cout << nombrePais << " (Ranking: " << ranking << ")" << endl;
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

void Equipo::sumarPuntos(int p) {
    puntos += p;
}

void Equipo::sumarGolesFavor(int g) {
    golesFavor += g;
}

void Equipo::sumarGolesContra(int g) {
    golesContra += g;
}

void Equipo::reiniciarEstadisticas() {
    puntos = 0;
    golesFavor = 0;
    golesContra = 0;
}

int Equipo::getPuntos() {
    return puntos;
}

int Equipo::getRanking() {
    return ranking;
}

int Equipo::getGolesFavor() {
    return golesFavor;
}

int Equipo::getGolesContra() {
    return golesContra;
}

string Equipo::getConfederacion() {
    return confederacion;
}
