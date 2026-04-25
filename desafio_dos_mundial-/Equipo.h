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
    ~Equipo();
    Equipo(const Equipo& otro);
    Equipo& operator=(const Equipo& otro);
    bool operator<(const Equipo& otro) const;
    bool operator==(const Equipo& otro) const;

    string getNombre();
    void setNombre(string nombre);
    void mostrar();
    void mostrarSimple();
    void sumarVictoria();
    void sumarEmpate();
    void sumarDerrota();
    void sumarPuntos(int p);
    void sumarGolesFavor(int g);
    void sumarGolesContra(int g);
    void reiniciarEstadisticas();
    int getPuntos();
    int getRanking();
    int getGolesFavor();
    int getGolesContra();
    string getConfederacion();
};

#endif
