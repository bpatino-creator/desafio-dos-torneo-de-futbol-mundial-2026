#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include "Jugador.h"
using namespace std;

// Representa un equipo del mundial con sus jugadores y estadisticas
class Equipo {
private:
    string nombrePais;      // nombre del pais
    string confederacion;   // continente al que pertenece
    int ranking;            // posicion en el ranking FIFA
    int golesFavor;         // goles anotados
    int golesContra;        // goles recibidos
    int puntos;             // puntos acumulados en el torneo
    int ganados;            // partidos ganados
    int empatados;          // partidos empatados
    int perdidos;           // partidos perdidos
    Jugador* jugadores;     // arreglo dinamico de 26 jugadores
    int cantidadJugadores;  // cantidad de jugadores en la plantilla

public:
    // Constructor vacio
    Equipo();
    // Constructor solo con nombre
    Equipo(string nombre);
    // Constructor completo con todos los datos
    Equipo(string nombre, string conf, int ranking, int gf, int gc);

    // Destructor: libera la memoria de los jugadores
    ~Equipo();
    // Constructor de copia: crea un arreglo nuevo para no compartir memoria
    Equipo(const Equipo& otro);
    // Operador asignacion: libera memoria anterior y copia los datos
    Equipo& operator=(const Equipo& otro);
    // Compara dos equipos por puntos
    bool operator<(const Equipo& otro) const;
    // Compara dos equipos por nombre del pais
    bool operator==(const Equipo& otro) const;

    string getNombre();
    void setNombre(string nombre);
    // Muestra el equipo con todos sus jugadores
    void mostrar();
    // Muestra solo el nombre y ranking
    void mostrarSimple();
    // Suma 3 puntos y cuenta la victoria
    void sumarVictoria();
    // Suma 1 punto y cuenta el empate
    void sumarEmpate();
    // Solo cuenta la derrota, no suma puntos
    void sumarDerrota();
    void sumarPuntos(int p);
    void sumarGolesFavor(int g);
    void sumarGolesContra(int g);
    // Reinicia puntos y goles para la fase de grupos
    void reiniciarEstadisticas();
    int getPuntos();
    int getRanking();
    int getGolesFavor();
    int getGolesContra();
    string getConfederacion();
};

#endif
