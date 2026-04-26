#ifndef GRUPO_H
#define GRUPO_H

#include <iostream>
#include "Equipo.h"
using namespace std;

// Representa un grupo del mundial con sus 4 equipos
class Grupo {
private:
    char letra;             // letra que identifica el grupo (A, B, C...)
    Equipo* equipos[4];     // arreglo de punteros a los 4 equipos del grupo
    int cantidadEquipos;    // cuantos equipos se han agregado hasta ahora

public:
    // Constructor con letra del grupo
    Grupo(char l);
    // Constructor vacio
    Grupo();

    // Agrega un equipo al grupo si hay espacio
    void agregarEquipo(Equipo* e);
    // Muestra el grupo con todos los datos de cada equipo
    void mostrar();
    // Muestra el grupo en una sola linea con nombre y confederacion
    void mostrarSimple();
    // Ordena y muestra la tabla de posiciones del grupo
    void mostrarTabla();
    // Simula los 6 partidos del grupo (todos contra todos)
    void simularPartidos();
    int getCantidadEquipos();
    Equipo* getEquipo(int i);
};

#endif
