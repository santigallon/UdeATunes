#include <iostream>
#include <cstdlib>
#include <ctime>

#include "udeatunes.h"
#include "usuario.h"
#include "artista.h"
#include "album.h"
#include "cancion.h"
#include "creditos.h"
#include "publicidad.h"

using namespace std;

int main() {
    srand((unsigned)time(nullptr));

    UdeATunes app;

    cout << "==========================" << endl;
    cout << "   UdeATunes Iniciado    " << endl;
    cout << "==========================" << endl << endl;

    // ---------- Crear artistas ----------
    Artista* badBunny = new Artista(1, 29, "Bad Bunny", "Puerto Rico");
    Artista* karolG   = new Artista(2, 33, "Karol G", "Colombia");

    app.agregarArtista(badBunny);
    app.agregarArtista(karolG);

    // ---------- Crear álbumes ----------
    Album* verano = new Album(100, "Un Verano Sin Ti", "2022-05-06", "Rimas", "/users/storage/badbunny/image/verano.png");
    Album* manana = new Album(101, "Mañana Será Bonito", "2023-02-24", "Universal", "/users/storage/karolg/image/manana.png");

    badBunny->agregarAlbum(verano);
    karolG->agregarAlbum(manana);

    // ---------- Crear canciones ----------
    Cancion* ojitos = new Cancion(200, 3.45, "Ojitos Lindos", "/users/.../ojitos_128.ogg", "/users/.../ojitos_320.ogg");
    Cancion* titi   = new Cancion(201, 3.60, "Titi Me Preguntó", "/users/.../titi_128.ogg", "/users/.../titi_320.ogg");
    Cancion* provenza = new Cancion(202, 3.20, "Provenza", "/users/.../provenza_128.ogg", "/users/.../provenza_320.ogg");

    verano->agregarCancion(ojitos);
    verano->agregarCancion(titi);
    manana->agregarCancion(provenza);

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

    // ---------- Publicidad ----------
    app.agregarPublicidad(new Publicidad("Compra ya el nuevo producto X", Publicidad::C));
    app.agregarPublicidad(new Publicidad("Oferta especial - 50% hoy", Publicidad::B));
    app.agregarPublicidad(new Publicidad("Suscríbete a AAA Premium", Publicidad::A));

    // ---------- Mostrar usuarios ----------
    cout << "\n--- Lista de usuarios ---" << endl;
    app.mostrarUsuarios();

    // ---------- Reproducción aleatoria: probar para usuario estándar (Laura) y VIP (Santi) ----------
    cout << "\n--- Reproducción aleatoria (usuario estándar - Laura) ---" << endl;
    app.reproduccionAleatoria(laura, 5);

    cout << "\n--- Reproducción aleatoria (usuario VIP - Santiago) ---" << endl;
    app.reproduccionAleatoria(santi, 5);

    // ---------- Favoritos VIP ----------
    cout << "\n--- Favoritos (VIP) ---" << endl;
    santi->agregarFavorito(ojitos);
    santi->agregarFavorito(provenza); // se puede agregar canciones de otros álbumes
    santi->ejecutarFavoritos(true, 4);

    // ---------- Uso de memoria ----------
    cout << "\n--- Uso de memoria ---" << endl;
    app.memoriaUsada();

    // ---------- Liberar memoria (objetos creados con new) ----------
    // Nota: para la entrega puedes decidir si liberas todo o no. Aquí lo hacemos.
    delete badBunny;
    delete karolG;
    delete verano;
    delete manana;
    delete ojitos;
    delete titi;
    delete provenza;
    delete prod1;
    delete prod2;
    delete santi;
    delete laura;

    cout << "\n============================" << endl;
    cout << "   Programa Finalizado   " << endl;
    cout << "============================" << endl;

    return 0;
}
