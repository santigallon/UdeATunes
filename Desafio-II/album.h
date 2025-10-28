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
        :   id(_id), duracionTotal(0.0), nombre(_nombre), fechaLanzamiento(_fecha),
        selloDisquero(_sello), portadaRuta(_portada){}
    int getId()const{return id; }
    float getDuracion();
    string getNombre();
    string getFechaLanzamiento()const{return fechaLanzamiento; }
    string getSelloDisquero()const{return selloDisquero; }
    string getPortadaRuta()const{return portadaRuta; }
    void agregarCancion(Cancion* c);
    void mostrarCanciones();
    MiLista<Cancion>& getCanciones(){return canciones; }

};

#endif // ALBUM_H
