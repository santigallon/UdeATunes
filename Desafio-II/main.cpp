#include <iostream>
#include "udeatunes.h"
#include "usuario.h"
#include "artista.h"
#include "album.h"
#include "cancion.h"
#include "creditos.h"

using namespace std;

int main() {
    // Creamos la aplicación
    UdeATunes app;

    cout << "==========================" << endl;
    cout << "   UdeATunes Iniciado 🎶   " << endl;
    cout << "==========================" << endl << endl;

    // ---------- Crear artistas ----------
    Artista* badBunny = new Artista(1, 29, "Bad Bunny", "Puerto Rico");
    Artista* karolG   = new Artista(2, 33, "Karol G", "Colombia");

    app.agregarArtista(badBunny);
    app.agregarArtista(karolG);

    // ---------- Crear álbumes ----------
    Album* verano = new Album(100, "Un Verano Sin Ti", "2022-05-06", "Rimas", "portada_verano.jpg");
    Album* mañana = new Album(101, "Mañana Será Bonito", "2023-02-24", "Universal", "portada_manana.jpg");

    badBunny->agregarAlbum(verano);
    karolG->agregarAlbum(mañana);

    // ---------- Crear canciones ----------
    Cancion* ojitos = new Cancion(200, 3.45, "Ojitos Lindos", "ojitos128.mp3", "ojitos320.mp3");
    Cancion* titi   = new Cancion(201, 3.60, "Titi Me Preguntó", "titi128.mp3", "titi320.mp3");
    Cancion* provenza = new Cancion(202, 3.20, "Provenza", "provenza128.mp3", "provenza320.mp3");

    verano->agregarCancion(ojitos);
    verano->agregarCancion(titi);
    mañana->agregarCancion(provenza);

    // ---------- Crear créditos ----------
    Creditos* prod1 = new Creditos("Noah", "Assad", "Productor", "RIM001");
    Creditos* prod2 = new Creditos("Ovy", "On The Drums", "Productor", "UNI002");
    ojitos->agregarCreditos(prod1);
    provenza->agregarCreditos(prod2);

    // ---------- Crear usuarios ----------
    Usuario* santi = new Usuario(true, "Santiago", "Medellín", "Colombia", "2025-10-22");
    Usuario* laura = new Usuario(false, "Laura", "Bogotá", "Colombia", "2025-10-21");

    app.agregarUsuario(santi);
    app.agregarUsuario(laura);

    // ---------- Mostrar usuarios ----------
    cout << "\n--- Lista de usuarios ---" << endl;
    app.mostrarUsuarios();

    // ---------- Simular sesión ----------
    cout << "\n--- Inicio de sesión ---" << endl;
    app.iniciarSesion();

    // ---------- Mostrar artistas ----------
    cout << "\n--- Artistas ---" << endl;
    badBunny->mostrarInfo();
    karolG->mostrarInfo();

    // ---------- Mostrar álbumes ----------
    cout << "\n--- Canciones de 'Un Verano Sin Ti' ---" << endl;
    verano->mostrarCanciones();

    cout << "\n--- Canciones de 'Mañana Será Bonito' ---" << endl;
    mañana->mostrarCanciones();

    // ---------- Reproducir canciones ----------
    cout << "\n--- Reproducción ---" << endl;
    santi->reproducir(ojitos);
    laura->reproducir(provenza);

    // ---------- Simular acciones del usuario ----------
    santi->pasarCancion();
    laura->pausarCancion();
    santi->seguir(badBunny);
    laura->seguir(karolG);

    // ---------- Mostrar memoria usada ----------
    cout << "\n--- Uso de memoria ---" << endl;
    app.memoriaUsada();

    // ---------- Liberar memoria ----------
    delete badBunny;
    delete karolG;
    delete verano;
    delete mañana;
    delete ojitos;
    delete titi;
    delete provenza;
    delete prod1;
    delete prod2;
    delete santi;
    delete laura;

    cout << "\n============================" << endl;
    cout << "   Programa Finalizado ✅   " << endl;
    cout << "============================" << endl;

    return 0;
}
