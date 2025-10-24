#include "album.h"


#include <iostream>

using namespace std;

float Album::getDuracion()
{
    return duracionTotal;
}

string Album::getNombre()
{
    return nombre;
}


void Album::agregarCancion(Cancion* c)
{
    canciones.agregar(c);
    duracionTotal += c->getDuracion();
}

void Album::mostrarCanciones()
{
    cout << "Álbum: " << nombre << " (" << fechaLanzamiento << ")" << endl;
    cout << "Sello: " << selloDisquero << endl;
    for (int i = 0; i < canciones.getCantidad(); i++) {
        cout << "  - " << canciones.obtener(i)->getNombre() << endl;
    }
}
