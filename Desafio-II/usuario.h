#ifndef USUARIO_H
#define USUARIO_H

#include <string>
#include <iostream>

#include "publicidad.h"
#include "MiLista.h"
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
    MiLista<Cancion> favoritos;
    MiLista<Publicidad> anuncios;

public:
    Usuario(bool VIP, string nic, string ciu, string pa, string fecha)
        : membresia(VIP), nickname(nic), ciudad(ciu), pais(pa), fechaInscripcion(fecha), favoritos(20) {}

    bool getVIP();
    bool agregarFavorito(Cancion* C);
    bool eliminarFavorito(Cancion* C);
    string getCiudad() const{return ciudad; }
    string getPais()const {return pais; }
    string getFechaInscripcion()const{return fechaInscripcion; }
    string getNickname();
    void reproducir(Cancion* c);
    void publicidad();
    void pasarCancion();
    void propagandas();
    void regresarCancion();
    void pausarCancion();
    void misFavoritos();
    void ejecutarFavoritos(bool aleatorio, int K=5);
    void seguirFavoritosDe(Usuario* otro);
    void aleatorio();
    void leerListasUsVIP();
    void reproducirUno(Cancion* c);
    void seguir(Artista* a);
    MiLista<Cancion>& getFavoritso(){return favoritos; }

};

#endif // USUARIO_H
