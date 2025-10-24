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
    Artista(int _id, int _edad, string _nombre, string _pais)
        : id(_id), edad(_edad), seguidores(0), posicionTendencia(0), nombre(_nombre), paisOrigen(_pais) {}
    int getId()const{return id; }
    int getEdad()const{return edad;}
    int getPosicionTendencia()const{return posicionTendencia;}
    int getSeguidores();
    string getNombre();
    string getPaisOrigen()const{return paisOrigen; }
    void agregarSeguidor();
    void agregarAlbum(Album* a);
    void mostrarInfo();
    MiLista<Album>& getAlbumes(){return albumes; }
};

#endif // ARTISTA_H
