#ifndef CANCION_H
#define CANCION_H

#include <iostream>
#include <string>

#include "MiLista.h"
#include "creditos.h"

using namespace std;

class Cancion
{
private:
    int id;
    int reproducciones;
    float duracion;
    string nombre;
    string ruta128;
    string ruta320;
    MiLista<Creditos> creditos;

public:
    Cancion(int _id, float _duracion, string _nombre, string _ruta128, string _ruta320)
        : id(_id), reproducciones(0), duracion(_duracion),nombre(_nombre), ruta128(_ruta128), ruta320(_ruta320), creditos(5) {}
    int getId() const{return id; }
    int getReproducciones();
    float getDuracion();
    string getNombre();
    string getRuta128()const{return ruta128; }
    string getRuta320()const{return ruta320; }
    void agregarCreditos(Creditos* c);
    void reproducir(bool altaCalidad);
    void contarReproducciones();
};

#endif // CANCION_H
