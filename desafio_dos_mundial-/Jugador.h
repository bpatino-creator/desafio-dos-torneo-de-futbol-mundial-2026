#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

class Jugador {
private:
    string nombre;
    int numero;

public:
    Jugador();
    Jugador(string nombre, int numero);
    void mostrar();
};

#endif
