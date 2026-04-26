#include "Equipo.h"

// Libera el arreglo de jugadores al destruir el equipo
Equipo::~Equipo() {
    delete[] jugadores;
    jugadores = nullptr; // evita que el puntero quede apuntando a memoria liberada
}

// Crea un arreglo nuevo para no compartir memoria con el otro equipo
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
        jugadores = new Jugador[cantidadJugadores]; // crea arreglo nuevo
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i]; // copia jugador por jugador
    } else {
        jugadores = nullptr;
    }
}

Equipo& Equipo::operator=(const Equipo& otro) {
    // Verifica que no se este asignando el mismo objeto
    if (this == &otro) return *this;

    // Libera la memoria anterior antes de crear una nueva
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
        jugadores = new Jugador[cantidadJugadores]; // crea arreglo nuevo
        for (int i = 0; i < cantidadJugadores; i++)
            jugadores[i] = otro.jugadores[i]; // copia jugador por jugador
    } else {
        jugadores = nullptr;
    }

    return *this; // retorna el objeto actual para poder encadenar asignaciones
}

// Retorna true si este equipo tiene menos puntos que el otro
bool Equipo::operator<(const Equipo& otro) const {
    return puntos < otro.puntos;
}

// Retorna true si los dos equipos son del mismo pais
bool Equipo::operator==(const Equipo& otro) const {
    return nombrePais == otro.nombrePais;
}

// Constructor vacio: deja todo en cero y sin jugadores
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

// Constructor con nombre: crea los 26 jugadores con nombres genericos
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
        jugadores[i] = Jugador("Jugador", i + 1); // asigna numero de camiseta
}

// Constructor completo: recibe los datos historicos del CSV
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
        jugadores[i] = Jugador("Jugador", i + 1); // asigna numero de camiseta
}

string Equipo::getNombre() {
    return nombrePais;
}

void Equipo::setNombre(string nombre) {
    nombrePais = nombre;
}

// Muestra el equipo con la lista completa de jugadores
void Equipo::mostrar() {
    cout << "Equipo: " << nombrePais << endl;
    for (int i = 0; i < cantidadJugadores; i++)
        jugadores[i].mostrar();
}

// Muestra solo el nombre y el ranking del equipo
void Equipo::mostrarSimple() {
    cout << nombrePais << " (Ranking: " << ranking << ")" << endl;
}

// Suma 3 puntos y registra la victoria
void Equipo::sumarVictoria() {
    ganados++;
    puntos += 3;
}

// Suma 1 punto y registra el empate
void Equipo::sumarEmpate() {
    empatados++;
    puntos += 1;
}

// Registra la derrota sin sumar puntos
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

// Reinicia puntos y goles antes de simular la fase de grupos
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
