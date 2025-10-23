#include "artista.h"

#include <iostream>

using namespace std;

void Artista::agregarAlbum(Album* a)
{
    albumes.agregar(a);
}

string Artista::getNombre()
{
    return nombre;
}

void Artista::agregarSeguidor()
{
    seguidores++;
}

int Artista::getSeguidores()
{
    return seguidores;
}

void Artista::mostrarInfo()
{
    cout << "Artista: " << nombre << " (" << paisOrigen << ")" << endl;
    cout << "Edad: " << edad << " | Seguidores: " << seguidores
         << " | Tendencia: " << posicionTendencia << endl;
    cout << "Álbumes publicados: " << albumes.getCantidad() << endl;
}
