#ifndef ALBUM_H
#define ALBUM_H

#include <string>

#include "MiLista.h"
#include "cancion.h"

using namespace std;

class Album
{
private:
    int id;
    float duracionTotal;
    string nombre;
    string fechaLanzamiento;
    string selloDisquero;
    string portadaRuta;
    MiLista<Cancion> canciones;
public:
    Album(int _id, string _nombre, string _fecha, string _sello, string _portada)
        :   id(_id), duracionTotal(0.0), nombre(_nombre), fechaLanzamiento(_fecha), selloDisquero(_sello), portadaRuta(_portada){}

    float getDuracion();
    string getNombre();
    void agregarCancion(Cancion* c);
    void mostrarCanciones();

};

#endif // ALBUM_H
