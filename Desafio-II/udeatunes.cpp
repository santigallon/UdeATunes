#include "udeatunes.h"
#include "usuario.h"
#include "album.h"

#include <iostream>
#include <thread>
#include <chrono>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <iomanip>


using namespace std;

int UdeATunes::reunirTodasCanciones(Cancion*** outArray) {

    int total = 0;
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        Artista* art = artistas.obtener(i);
        for (int j = 0; j < art->getAlbumes().getCantidad(); ++j) {
            Album* alb = art->getAlbumes().obtener(j);
            total += alb->getCanciones().getCantidad();
        }
    }
    if (total == 0) { *outArray = nullptr; return 0; }

    Cancion** arr = new Cancion*[total];
    int idx = 0;
    for (int i = 0; i < artistas.getCantidad(); ++i)
    {
        Artista* art = artistas.obtener(i);
        for (int j = 0; j < art->getAlbumes().getCantidad(); ++j)
        {
            Album* alb = art->getAlbumes().obtener(j);
            for (int k = 0; k < alb->getCanciones().getCantidad(); ++k)
            {
                arr[idx++] = alb->getCanciones().obtener(k);
            }
        }
    }
    *outArray = arr;
    return total;
}


Publicidad* seleccionarPublicidad(Publicidad** anuncios, int n, Publicidad* ultimo)
{
    int totalPeso = 0;
    for (int i = 0; i < n; ++i)
    {
        totalPeso += anuncios[i]->getPeso();
    }
    if (totalPeso==0)return nullptr;

    int r = rand () % totalPeso +1;
    int acumulado = 0;
    for (int i = 0; i < n; i++)
    {
        acumulado += anuncios[i]->getPeso();
        if (r <= acumulado)
        {
            if (ultimo != nullptr && anuncios[i] == ultimo)
            {
                int idx = (i+1) % n;
                return anuncios[idx];
            }
            return anuncios[i];
        }
    }
    return anuncios[n+1];
}

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


void UdeATunes::agregarPublicidad(Publicidad* p)
{
    anuncios.agregar(p);
}

Publicidad* UdeATunes::seleccionarPublicidad(Publicidad* ultimo)
{
    int n = anuncios.getCantidad();
    if (n == 0) return nullptr;
    int totalPeso = 0;
    for (int i = 0; i < n; ++i) totalPeso += anuncios.obtener(i)->getPeso();
    if (totalPeso == 0) return anuncios.obtener(0);

    int r = rand() % totalPeso + 1;
    int acumulado = 0;
    for (int i = 0; i < n; ++i) {
        acumulado += anuncios.obtener(i)->getPeso();
        if (r <= acumulado) {
            // evitar repetición consecutiva
            if (ultimo != nullptr && anuncios.obtener(i) == ultimo) {
                int idx = (i + 1) % n;
                return anuncios.obtener(idx);
            }
            return anuncios.obtener(i);
        }
    }
    return anuncios.obtener(n-1);
}

void UdeATunes::reproduccionAleatoria(Usuario* u, int K)
{
    long long iteraciones = 0;
    Cancion** todas = nullptr;
    int total = reunirTodasCanciones(&todas);
    iteraciones += total; // cuenta la recolección como iteraciones

    if (total == 0) {
        cout << "No hay canciones en la plataforma." << endl;
        return;
    }

    int reproducidas = 0;
    int lastIndex = -1;
    int standardAdCounter = 0;
    Publicidad* ultimoAd = nullptr;

    while (reproducidas < K && reproducidas < total) {
        int idx = rand() % total;
        if (idx == lastIndex) idx = (idx + 1) % total; // evitar repetición inmediata
        Cancion* c = todas[idx];

        // Mostrar portada si está disponible: buscamos su álbum para portada (simple búsqueda)
        string portada = "(portada no disponible)";
        bool encontrada = false;
        for (int i = 0; i < artistas.getCantidad() && !encontrada; ++i) {
            Artista* art = artistas.obtener(i);
            for (int j = 0; j < art->getAlbumes().getCantidad() && !encontrada; ++j) {
                Album* alb = art->getAlbumes().obtener(j);
                for (int k = 0; k < alb->getCanciones().getCantidad(); ++k) {
                    if (alb->getCanciones().obtener(k) == c) {
                        portada = alb->getPortadaRuta();
                        encontrada = true;
                        break;
                    }
                }
            }
        }
        cout << "Portada: " << portada << endl;
        c->reproducir(u->getVIP());
        iteraciones++;
        std::this_thread::sleep_for(std::chrono::seconds(3));
        reproducidas++;
        lastIndex = idx;

        if (!u->getVIP()) {
            standardAdCounter++;
            if (standardAdCounter == 2) {
                Publicidad* ad = seleccionarPublicidad(ultimoAd);
                if (ad) {
                    cout << "[Publicidad] " << ad->getMensaje() << endl;
                    ultimoAd = ad;
                }
                standardAdCounter = 0;
            }
        }
    }

    delete[] todas;

    cout << "Iteraciones realizadas (estimadas): " << iteraciones << endl;
    memoriaUsada();
}

void UdeATunes::memoriaUsada() {
    size_t memoria = 0;
    memoria += sizeof(*this);

    // estructura MiLista (usuarios y artistas)
    memoria += sizeof(usuarios);
    memoria += usuarios.getCapacidad() * sizeof(Usuario*);
    memoria += usuarios.getCantidad() * sizeof(Usuario);

    memoria += sizeof(artistas);
    memoria += artistas.getCapacidad() * sizeof(Artista*);
    memoria += artistas.getCantidad() * sizeof(Artista);

    // anuncios
    memoria += sizeof(anuncios);
    memoria += anuncios.getCapacidad() * sizeof(Publicidad*);
    memoria += anuncios.getCantidad() * sizeof(Publicidad);

    // recorrer artistas -> albumes -> canciones
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        Artista* a = artistas.obtener(i);
        memoria += sizeof(*a);
        memoria += a->getAlbumes().getCapacidad() * sizeof(Album*);
        memoria += a->getAlbumes().getCantidad() * sizeof(Album);
        for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
            Album* alb = a->getAlbumes().obtener(j);
            memoria += sizeof(*alb);
            memoria += alb->getCanciones().getCapacidad() * sizeof(Cancion*);
            memoria += alb->getCanciones().getCantidad() * sizeof(Cancion);
        }
    }

    cout << "Memoria estimada usada por el sistema (aprox): " << memoria << " bytes." << endl;
    cout << "Nota: estimación que incluye sizeof de objetos y arrays dinámicos (no incluye overhead interno de std::string)." << endl;
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
// helper: busca artista por id (incrementa contadorIteraciones por comparación)
Artista* UdeATunes::buscarArtistaPorId(int id) {
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        contadorIteraciones++; // comparación
        Artista* a = artistas.obtener(i);
        if (a->getId() == id) return a;
    }
    return nullptr;
}

// busca album por id (recorre todos los albums)
Album* UdeATunes::buscarAlbumPorId(int id) {
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        contadorIteraciones++;
        Artista* a = artistas.obtener(i);
        for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
            contadorIteraciones++;
            Album* alb = a->getAlbumes().obtener(j);
            if (alb->getId() == id) return alb;
        }
    }
    return nullptr;
}

// busca cancion por id (recorre todo)
Cancion* UdeATunes::buscarCancionPorId(int id) {
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        contadorIteraciones++;
        Artista* a = artistas.obtener(i);
        for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
            contadorIteraciones++;
            Album* alb = a->getAlbumes().obtener(j);
            for (int k = 0; k < alb->getCanciones().getCantidad(); ++k) {
                contadorIteraciones++;
                Cancion* c = alb->getCanciones().obtener(k);
                if (c->getId() == id) return c;
            }
        }
    }
    return nullptr;
}

// Formatos de archivo usados:
//
// usuarios.txt: nickname|VIP(0/1)|ciudad|pais|fecha|favId1,favId2,...
// artistas.txt: id|edad|nombre|pais|seguidores|posicionTendencia
// albumes.txt: albumId|nombre|fecha|sello|portadaRuta|artistaId
// canciones.txt: cancionId|duracion|nombre|ruta128|ruta320|albumId
// creditos.txt: cancionId|nombre|apellido|tipo|codigoAfiliacion
// anuncios.txt: categoria(1=C,2=B,3=A)|mensaje\n
//
// NOTA: El directorio 'dir' debe existir (por ejemplo "data/"). Los archivos se crean/reescriben ahí.

bool UdeATunes::guardarDatos(const std::string& dir) {
    // ---- usuarios ----
    std::ofstream fusers(dir + "/usuarios.txt");
    if (!fusers.is_open()) {
        std::cerr << "No se pudo abrir usuarios.txt para guardar\n";
        return false;
    }

    for (int i = 0; i < usuarios.getCantidad(); ++i) {
        Usuario* u = usuarios.obtener(i);
        fusers << u->getNickname() << "|"
               << (u->getVIP() ? "1" : "0") << "|"
               << u->getCiudad() << "|"
               << u->getPais() << "|"
               << u->getFechaInscripcion() << "\n";
    }
    fusers.close();

    // ---- artistas ----
    std::ofstream fart(dir + "/artistas.txt");
    if (!fart.is_open()) {
        std::cerr << "No se pudo abrir artistas.txt para guardar\n";
        return false;
    }
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        Artista* a = artistas.obtener(i);
        fart << a->getId() << "|"
             << a->getEdad() << "|"
             << a->getNombre() << "|"
             << a->getPaisOrigen() << "|"
             << a->getSeguidores() << "|"
             << a->getPosicionTendencia() << "\n";
    }
    fart.close();

    // ---- álbumes ----
    std::ofstream falb(dir + "/albumes.txt");
    if (!falb.is_open()) {
        std::cerr << "No se pudo abrir albumes.txt para guardar\n";
        return false;
    }
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        Artista* a = artistas.obtener(i);
        for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
            Album* alb = a->getAlbumes().obtener(j);
            falb << alb->getId() << "|"
                 << alb->getNombre() << "|"
                 << alb->getFechaLanzamiento() << "|"
                 << alb->getSelloDisquero() << "|"
                 << alb->getPortadaRuta() << "|"
                 << a->getId() << "\n";
        }
    }
    falb.close();

    // ---- canciones ----
    std::ofstream fcanc(dir + "/canciones.txt");
    if (!fcanc.is_open()) {
        std::cerr << "No se pudo abrir canciones.txt para guardar\n";
        return false;
    }
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        Artista* a = artistas.obtener(i);
        for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
            Album* alb = a->getAlbumes().obtener(j);
            for (int k = 0; k < alb->getCanciones().getCantidad(); ++k) {
                Cancion* c = alb->getCanciones().obtener(k);
                fcanc << c->getId() << "|"
                      << c->getDuracion() << "|"
                      << c->getNombre() << "|"
                      << c->getRuta128() << "|"
                      << c->getRuta320() << "|"
                      << alb->getId() << "\n";
            }
        }
    }
    fcanc.close();

    // ---- créditos ----
    std::ofstream fcred(dir + "/creditos.txt");
    if (!fcred.is_open()) {
        std::cerr << "No se pudo abrir creditos.txt para guardar\n";
        return false;
    }
    for (int i = 0; i < artistas.getCantidad(); ++i) {
        Artista* art = artistas.obtener(i);
        for (int j = 0; j < art->getAlbumes().getCantidad(); ++j) {
            Album* alb = art->getAlbumes().obtener(j);
            for (int k = 0; k < alb->getCanciones().getCantidad(); ++k) {
                Cancion* c = alb->getCanciones().obtener(k);
                // Para acceder a los créditos, asumimos que tienes getCreditos() en Cancion
                // Si no lo tienes, agrégalo: MiLista<Creditos>& getCreditos(){ return creditos; }
                for (int m = 0; m < c->getCreditos().getCantidad(); ++m) {
                    Creditos* cr = c->getCreditos().obtener(m);
                    fcred << c->getId() << "|"
                          << cr->getNombreCompleto() << "|"
                          << cr->getTipo() << "|"
                          << cr->getCodigo() << "\n";
                }
            }
        }
    }
    fcred.close();

    // ---- anuncios ----
    std::ofstream fans(dir + "/anuncios.txt");
    if (!fans.is_open()) {
        std::cerr << "No se pudo abrir anuncios.txt para guardar\n";
        return false;
    }
    for (int i = 0; i < anuncios.getCantidad(); ++i) {
        Publicidad* p = anuncios.obtener(i);
        fans << p->getPeso() << "|" << p->getMensaje() << "\n";
    }
    fans.close();

    return true;
}

bool UdeATunes::cargarDatos(const std::string& dir) {
    // ---- artistas ----
    std::ifstream fart(dir + "/artistas.txt");
    if (fart.is_open()) {
        std::string line;
        while (std::getline(fart, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string token;
            std::getline(ss, token, '|'); int id = std::stoi(token);
            std::getline(ss, token, '|'); int edad = std::stoi(token);
            std::string nombre, pais;
            std::getline(ss, nombre, '|');
            std::getline(ss, pais, '|');
            std::getline(ss, token, '|'); int seguidores = std::stoi(token);
            Artista* a = new Artista(id, edad, nombre, pais);
            for (int i = 0; i < seguidores; ++i) a->agregarSeguidor();
            artistas.agregar(a);
        }
        fart.close();
    }

    // ---- álbumes ----
    std::ifstream falb(dir + "/albumes.txt");
    if (falb.is_open()) {
        std::string line;
        while (std::getline(falb, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string token;
            std::getline(ss, token, '|'); int albumId = std::stoi(token);
            std::string nombre, fecha, sello, portada;
            std::getline(ss, nombre, '|');
            std::getline(ss, fecha, '|');
            std::getline(ss, sello, '|');
            std::getline(ss, portada, '|');
            std::getline(ss, token, '|'); int artId = std::stoi(token);
            Album* alb = new Album(albumId, nombre, fecha, sello, portada);
            Artista* a = buscarArtistaPorId(artId);
            if (a) a->agregarAlbum(alb);
        }
        falb.close();
    }

    // ---- canciones ----
    std::ifstream fcanc(dir + "/canciones.txt");
    if (fcanc.is_open()) {
        std::string line;
        while (std::getline(fcanc, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string token;
            std::getline(ss, token, '|'); int id = std::stoi(token);
            std::getline(ss, token, '|'); float dur = std::stof(token);
            std::string nombre, ruta128, ruta320;
            std::getline(ss, nombre, '|');
            std::getline(ss, ruta128, '|');
            std::getline(ss, ruta320, '|');
            std::getline(ss, token, '|'); int albumId = std::stoi(token);
            Cancion* c = new Cancion(id, dur, nombre, ruta128, ruta320);
            Album* alb = buscarAlbumPorId(albumId);
            if (alb) alb->agregarCancion(c);
        }
        fcanc.close();
    }

    // ---- créditos ----
    std::ifstream fcred(dir + "/creditos.txt");
    if (fcred.is_open()) {
        std::string line;
        while (std::getline(fcred, line)) {
            if (line.empty()) continue;
            std::stringstream ss(line);
            std::string token;
            std::getline(ss, token, '|'); int cid = std::stoi(token);
            std::string nom, ape, tipo, cod;
            std::getline(ss, nom, '|');
            std::getline(ss, ape, '|');
            std::getline(ss, tipo, '|');
            std::getline(ss, cod, '|');
            Cancion* c = buscarCancionPorId(cid);
            if (c) {
                Creditos* cr = new Creditos(nom, ape, tipo, cod);
                c->agregarCreditos(cr);
            }
        }
        fcred.close();
    }

    // ---- anuncios ----
    std::ifstream fans(dir + "/anuncios.txt");
    if (fans.is_open()) {
        std::string line;
        while (std::getline(fans, line)) {
            if (line.empty()) continue;
            size_t pos = line.find('|');
            int cat = std::stoi(line.substr(0, pos));
            std::string msg = line.substr(pos + 1);
            Publicidad::Categoria pc = Publicidad::C;
            if (cat == 2) pc = Publicidad::B;
            else if (cat == 3) pc = Publicidad::A;
            Publicidad* p = new Publicidad(msg, pc);
            anuncios.agregar(p);
        }
        fans.close();
    }

    return true;
}
