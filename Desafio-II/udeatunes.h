#ifndef UDEATUNES_H
#define UDEATUNES_H

#include <string>
#include <iostream>

#include "MiLista.h"
#include "usuario.h"
#include "artista.h"

class UdeATunes
{
private:
    MiLista<Usuario> usuarios;
    MiLista<Artista> artistas;
public:
    UdeATunes(){};

    void agregarUsuario(Usuario* u)
    {usuarios.agregar(u);}

    void agregarArtista(Artista* a)
    {artista.agregar(a);}
    void mostrarUsuarios()
    {
        for (int i = 0; i < usuarios.getCantidad(); i++)
        {
            cout<<usuarios.obtener(i)->getNickname()>>endl;
        }
    }
};

#endif // UDEATUNES_H
