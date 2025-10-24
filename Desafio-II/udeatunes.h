#ifndef UDEATUNES_H
#define UDEATUNES_H

#include <string>
#include <iostream>

#include "MiLista.h"
#include "usuario.h"
#include "artista.h"
#include "publicidad.h"
#include "cancion.h"

using namespace std;

class UdeATunes
{
private:
    long long contadorIteraciones = 0;
    Artista* buscarArtistaPorId(int id);
    Album*   buscarAlbumPorId(int id);
    Cancion* buscarCancionPorId(int id);
    MiLista<Usuario> usuarios;
    MiLista<Artista> artistas;
    MiLista<Publicidad> anuncios;

public:
    UdeATunes() : usuarios(10), artistas(10), anuncios(10) {}
    int  reunirTodasCanciones(Cancion*** outArray);
    long long getContadorIter() const { return contadorIteraciones; }
    bool guardarDatos(const std::string& dir);
    bool cargarDatos(const std::string& dir);
    void agregarUsuario(Usuario* u);
    void agregarArtista(Artista* a);
    void mostrarUsuarios();
    void memoriaUsada();
    void iniciarSesion();
    void reproduccionAleatoria(Usuario* u, int K = 5);
    void agregarPublicidad(Publicidad* p);
    void resetContadorIter() { contadorIteraciones = 0; }
    Publicidad* seleccionarPublicidad(Publicidad* ultimo);

};

#endif // UDEATUNES_H
