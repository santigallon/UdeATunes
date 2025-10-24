#include "usuario.h"
#include <thread>
#include <chrono>
#include <cstdlib>

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

// NUEVOS

bool Usuario::agregarFavorito(Cancion* c)
{
    if (!membresia) {
        cout << "Solo usuarios VIP pueden tener lista de favoritos." << endl;
        return false;
    }
    if (favoritos.getCantidad() >= 10000) {
        cout << "Lista de favoritos llena (10000)." << endl;
        return false;
    }
    if (favoritos.contiene(c)) {
        cout << "La canción ya está en favoritos." << endl;
        return false;
    }
    favoritos.agregar(c);
    cout << "Canción " << c->getNombre() << " agregada a favoritos de " << nickname << endl;
    return true;
}

bool Usuario::eliminarFavorito(Cancion* c)
{
    if (!membresia) {
        cout << "Solo usuarios VIP pueden tener lista de favoritos." << endl;
        return false;
    }
    if (favoritos.eliminar(c)) {
        cout << "Canción " << c->getNombre() << " eliminada de favoritos de " << nickname << endl;
        return true;
    }
    cout << "La canción no está en la lista de favoritos." << endl;
    return false;
}

void Usuario::seguirFavoritosDe(Usuario* otro)
{
    if (!membresia) {
        cout << "Solo usuarios VIP pueden seguir listas de otros." << endl;
        return;
    }
    for (int i = 0; i < otro->favoritos.getCantidad(); ++i) {
        Cancion* c = otro->favoritos.obtener(i);
        if (!favoritos.contiene(c)) {
            favoritos.agregar(c);
        }
    }
    cout << nickname << " ahora sigue la lista de " << otro->getNickname() << endl;
}

void Usuario::ejecutarFavoritos(bool aleatorio, int K)
{
    if (!membresia) {
        cout << "Solo usuarios VIP pueden ejecutar favoritos." << endl;
        return;
    }
    int total = favoritos.getCantidad();
    if (total == 0) { cout << "Lista de favoritos vacía." << endl; return; }

    int reproducidas = 0;
    int idx = 0;
    int lastIdx = -1;

    while (reproducidas < K && reproducidas < total) {
        if (aleatorio) {
            idx = rand() % total;
            if (idx == lastIdx) { idx = (idx + 1) % total; } // evitar repetición inmediata
        } else {
            idx = reproducidas % total;
        }
        Cancion* c = favoritos.obtener(idx);
        // Mostrar portada y ruta (si tu Album lo relaciona, podrías mostrar la portada real aquí)
        cout << "[Favoritos] Mostrando portada: (ruta simulada)" << endl;
        c->reproducir(true); // VIP -> alta calidad
        std::this_thread::sleep_for(std::chrono::seconds(3));
        reproducidas++;
        lastIdx = idx;
    }
    cout << "Se reprodujeron " << reproducidas << " canciones de favoritos." << endl;
}
