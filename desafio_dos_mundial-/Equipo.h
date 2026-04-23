#ifndef EQUIPO_H
#define EQUIPO_H

#include <iostream>
#include "Jugador.h"
using namespace std;

class Equipo {
private:
    string nombrePais;

    string confederacion;
    int ranking;

    int golesFavor;
    int golesContra;

    int puntos;
    int ganados;
    int empatados;
    int perdidos;

    Jugador* jugadores;
    int cantidadJugadores;

public:
    Equipo();
    Equipo(string nombre);
    Equipo(string nombre, string conf, int ranking, int gf, int gc);

    string getNombre();
    void setNombre(string nombre);
    void mostrar();
    void sumarVictoria();
    void sumarEmpate();
    void sumarDerrota();
    int getPuntos();
    int getRanking();
    void mostrarSimple();
    string getConfederacion();
};

#endif
