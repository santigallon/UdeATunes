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
    int reunirTodasCanciones(Cancion*** outArray);
    int getUsuariosCount() const { return usuarios.getCantidad(); }
    int getArtistasCount() const { return artistas.getCantidad(); }
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
    void incrementIter() { contadorIteraciones++; }
    Publicidad* seleccionarPublicidad(Publicidad* ultimo);
    Usuario* getUsuarioAt(int i) { return usuarios.obtener(i); }
    Artista* getArtistaAt(int i) { return artistas.obtener(i); }
    Cancion* buscarCancionPorIdPublic(int id) { return buscarCancionPorId(id); }

    Usuario* buscarUsuarioPorNicknamePublic(const string& nick) {
        for (int i = 0; i < usuarios.getCantidad(); i++) {
            if (usuarios.obtener(i)->getNickname() == nick)
                return usuarios.obtener(i);
        }
        return nullptr;
    }

    string buscarPortadaDeCancion(Cancion* c) {
        for (int i = 0; i < artistas.getCantidad(); i++) {
            Artista* art = artistas.obtener(i);
            for (int j = 0; j < art->getAlbumes().getCantidad(); j++) {
                Album* alb = art->getAlbumes().obtener(j);
                for (int k = 0; k < alb->getCanciones().getCantidad(); k++) {
                    if (alb->getCanciones().obtener(k) == c)
                        return alb->getPortadaRuta();
                }
            }
        }
        return "[Portada no encontrada]";
    }

    int reunirTodasCancionesPublic(Cancion*** outArray) { return reunirTodasCanciones(outArray); }

};

#endif // UDEATUNES_H
