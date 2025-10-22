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

    void agregarUsuario(Usuario* u) {
        usuarios.agregar(u);
    }

    void agregarArtista(Artista* a) {
        artistas.agregar(a);
    }

    void mostrarUsuarios() {
        for (int i = 0; i < usuarios.getCantidad(); i++) {
            cout << "Usuario: " << usuarios.obtener(i)->getNickname() << endl;
        }
    }

    // Métodos aún no implementados (solo declarados)
    void memoriaUsada();
    void iniciarSesion();
};

#endif // UDEATUNES_H
