#include "usuario.h"

#include <iostream>

using namespace std;

bool Usuario::getVIP()
{
    return membresia;
}

string Usuario::getNickname()
{
    return nickname;
}

void  Usuario::reproducir(Cancion* c)
{
    cout << "Usuario: " << nickname << endl;
    c->reproducir(membresia);
}

void Usuario::propagandas()
{
    if (!membresia)
        cout << "[Publicidad] ¡Hazte VIP para escuchar sin anuncios!" << endl;
}

void Usuario::pasarCancion()
{
    cout << nickname << " pasó a la siguiente canción." << endl;
}

void Usuario::regresarCancion()
{
    cout << nickname << " regresó a la canción anterior." << endl;
}

void Usuario::pausarCancion()
{
    cout << nickname << " pausó la canción." << endl;
}

void Usuario::misFavoritos()
{
    cout << nickname << " abrió su lista de favoritos." << endl;
}

void Usuario::leerListasUsVIP()
{
    if (membresia)
        cout << nickname << " accedió a sus listas personalizadas VIP." << endl;
    else
        cout << "Solo usuarios VIP pueden acceder a listas personalizadas." << endl;
}

void Usuario::aleatorio()
{
    cout << nickname << " está reproduciendo en modo aleatorio." << endl;
}

void Usuario::reproducirUno(Cancion* c)
{
    cout << nickname << " eligió reproducir solo una canción." << endl;
    c->reproducir(membresia);
}

void Usuario::seguir(Artista* a)
{
    cout << nickname << " ahora sigue a " << a->getNombre() << endl;
    a->agregarSeguidor();
}
