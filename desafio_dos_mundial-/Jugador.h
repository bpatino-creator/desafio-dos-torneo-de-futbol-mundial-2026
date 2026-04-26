#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
using namespace std;

// Representa un jugador de un equipo del mundial
class Jugador {
private:
    string nombre;  // nombre del jugador
    int numero;     // numero de camiseta

public:
    // Constructor vacio
    Jugador();
    // Constructor con nombre y numero de camiseta
    Jugador(string nombre, int numero);
    // Muestra el nombre y numero del jugador
    void mostrar();
};

#endif
