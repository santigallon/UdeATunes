#ifndef CANCION_H
#define CANCION_H

#include <MiLista.h>
#include <creditos.h>

#include <string>
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
    MyLista <creditos> productores;

public:
    Cancion(int _id, float _duracion, string _nombre, string _ruta128, string _ruta320)
        :id(_id), reproducciones(0), duracion(_duracion), nombre(_nombre), ruta128(_ruta128), ruta320(_ruta320){}

    void agregarCreditos(Creditos* C)
    {creditos.agregar(c); }

    void reproducir(bool altaCalidad)
    {
        string ruta = altaCalidad ? ruta320 : ruta128;
        cout << "reproducionedo: " << nombre <<endl;
        cout << "archivo: " << ruta <<endl;
    }
};

#endif // CANCION_H
