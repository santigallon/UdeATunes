#include "cancion.h"

#include <iostream>

void Cancion::agregarCreditos(Creditos* c)
{
    creditos.agregar(c);
}

void Cancion::reproducir(bool altaCalidad)
{
    string ruta = altaCalidad ? ruta320 : ruta128;
    cout << "Reproduciendo: " << nombre << endl;
    cout << "Archivo: " << ruta << endl;
    reproducciones++;
}

float Cancion::getDuracion()
{
    return duracion;
}

string Cancion::getNombre()
{
    return nombre;
}

int Cancion::getReproducciones()
{
    return reproducciones;
}

void Cancion::contarReproducciones()
{
    reproducciones++;
}
