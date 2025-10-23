#include "udeatunes.h"

#include <iostream>

using namespace std;

void UdeATunes::agregarUsuario(Usuario* u) {
    usuarios.agregar(u);
}

void UdeATunes::agregarArtista(Artista* a) {
    artistas.agregar(a);
}

void UdeATunes::mostrarUsuarios() {
    for (int i = 0; i < usuarios.getCantidad(); i++) {
        cout << "Usuario: " << usuarios.obtener(i)->getNickname() << endl;
    }
}

void UdeATunes::memoriaUsada() {
    int memoria = 0;
    memoria += usuarios.getCantidad() * sizeof(Usuario);
    memoria += artistas.getCantidad() * sizeof(Artista);
    cout << "Memoria estimada usada por el sistema: " << memoria << " bytes." << endl;
}


void UdeATunes::iniciarSesion() {
    string nombre;
    cout << "Ingrese su nombre de usuario: ";
    cin >> nombre;

    for (int i = 0; i < usuarios.getCantidad(); i++) {
        if (usuarios.obtener(i)->getNickname() == nombre) {
            cout << "Bienvenido de nuevo, " << nombre << "!" << endl;
            return;
        }
    }
    cout << "Usuario no encontrado." << endl;
}
