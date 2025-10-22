#ifndef CREDITOS_H
#define CREDITOS_H

#include <string>

using namespace std;

class Creditos
{
private:
    string nombre;
    string apellido;
    string tipo;
    string codigoAfiliacion;


public:
    Creditos(    string nom, string ape, string tip, string cod)
        :nombre(nom), apellido(ape), tipo(tip), codigoAfiliacion(cod) {}
    string getNombreCompleto()
    {
        return nombre + " " + apellido;
    }
};

#endif // CREDITOS_H
