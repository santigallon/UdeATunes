#ifndef UDEATUNES_H
#define UDEATUNES_H

#include <string>
#include <iostream>

#include "MiLista.h"
#include "usuario.h"
#include "artista.h"

using namespace std;

class UdeATunes
{
private:
    MiLista<Usuario> usuarios;
    MiLista<Artista> artistas;

public:
    UdeATunes() {}

    void agregarUsuario(Usuario* u);
    void agregarArtista(Artista* a);
    void mostrarUsuarios();
    void memoriaUsada();
    void iniciarSesion();
};

#endif // UDEATUNES_H
