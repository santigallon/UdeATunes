#ifndef ARTISTA_H
#define ARTISTA_H

#include <string>

#include "MiLista.h"
#include "album.h"

using namespace std;

class Artista
{
private:
    int id;
    int edad;
    int seguidores;
    int posicionTendencia;
    string nombre;
    string paisOrigen;
    MiLista<Album> albumes;
public:
    Artista(int _id, int _edad, string _nombre, string _pais):
        id (_id) , edad(_edad), seguidores(0), posicionTendencia(0), nombre(_nombre), paisOrigen(_pais){}

    void agregarAlbum(Album* a)
    {
        albumes.agregar(a);
    }

    string getNombre(){return nombre;}
};

#endif // ARTISTA_H
