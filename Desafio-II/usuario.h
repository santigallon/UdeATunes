#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

#include "cancion.h"
#include "artista.h"

using namespace std;

class Usuario
{
private:
    bool membresia;
    string nickname;
    string ciudad;
    string pais;
    string fechaInscripcion;

public:
    Usuario(bool VIP, string nic, string ciu, string pa, string fecha)
        : membresia(VIP), nickname(nic), ciudad(ciu), pais(pa), fechaInscripcion(fecha) {}

    bool getVIP();
    string getNickname();
    void reproducir(Cancion* c);
    void propagandas();         // anuncios* anun  → se agregará más adelante
    void pasarCancion();
    void regresarCancion();
    void pausarCancion();
    void misFavoritos();
    void leerListasUsVIP();
    void aleatorio();
    void reproducirUno(Cancion* c);
    void seguir(Artista* a);
};

#endif // USUARIO_H
