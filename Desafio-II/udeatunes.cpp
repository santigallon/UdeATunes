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

bool UdeATunes::guardarDatos(const std::string& dir) {
    auto abrir = [&](const std::string& path, std::ofstream& f) -> bool {
        f.open(path, std::ios::trunc);
        if (!f.is_open()) {
            cerr << "[ERROR] No se pudo abrir " << path << " para guardar.\n";
            return false;
        }
        return true;
    };

    std::ofstream f;

    // === USUARIOS ===
    if (abrir(dir + "/usuarios.txt", f)) {
        for (int i = 0; i < usuarios.getCantidad(); ++i) {
            Usuario* u = usuarios.obtener(i);
            f << u->getNickname() << "|" << (u->getVIP() ? 1 : 0) << "|"
              << u->getCiudad() << "|" << u->getPais() << "|"
              << u->getFechaInscripcion() << "\n";
        }
        f.close();
    }

    // === ARTISTAS ===
    if (abrir(dir + "/artistas.txt", f)) {
        for (int i = 0; i < artistas.getCantidad(); ++i) {
            Artista* a = artistas.obtener(i);
            f << a->getId() << "|" << a->getEdad() << "|"
              << a->getNombre() << "|" << a->getPaisOrigen() << "|"
              << a->getSeguidores() << "|" << a->getPosicionTendencia() << "\n";
        }
        f.close();
    }

    // === ÁLBUMES ===
    if (abrir(dir + "/albumes.txt", f)) {
        for (int i = 0; i < artistas.getCantidad(); ++i) {
            Artista* a = artistas.obtener(i);
            for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
                Album* alb = a->getAlbumes().obtener(j);
                f << alb->getId() << "|" << alb->getNombre() << "|"
                  << alb->getFechaLanzamiento() << "|" << alb->getSelloDisquero()
                  << "|" << alb->getPortadaRuta() << "|" << a->getId() << "\n";
            }
        }
        f.close();
    }

    // === CANCIONES ===
    if (abrir(dir + "/canciones.txt", f)) {
        for (int i = 0; i < artistas.getCantidad(); ++i) {
            Artista* a = artistas.obtener(i);
            for (int j = 0; j < a->getAlbumes().getCantidad(); ++j) {
                Album* alb = a->getAlbumes().obtener(j);
                for (int k = 0; k < alb->getCanciones().getCantidad(); ++k) {
                    Cancion* c = alb->getCanciones().obtener(k);
                    f << c->getId() << "|" << c->getDuracion() << "|"
                      << c->getNombre() << "|" << c->getRuta128() << "|"
                      << c->getRuta320() << "|" << alb->getId() << "\n";
                }
            }
        }
        f.close();
    }

    // === CRÉDITOS ===
    if (abrir(dir + "/creditos.txt", f)) {
        for (int i = 0; i < artistas.getCantidad(); ++i) {
            Artista* art = artistas.obtener(i);
            for (int j = 0; j < art->getAlbumes().getCantidad(); ++j) {
                Album* alb = art->getAlbumes().obtener(j);
                for (int k = 0; k < alb->getCanciones().getCantidad(); ++k) {
                    Cancion* c = alb->getCanciones().obtener(k);
                    for (int m = 0; m < c->getCreditos().getCantidad(); ++m) {
                        Creditos* cr = c->getCreditos().obtener(m);
                        f << c->getId() << "|" << cr->getNombreCompleto() << "|"
                          << cr->getTipo() << "|" << cr->getCodigo() << "\n";
                    }
                }
            }
        }
        f.close();
    }

    // === ANUNCIOS ===
    if (abrir(dir + "/anuncios.txt", f)) {
        for (int i = 0; i < anuncios.getCantidad(); ++i) {
            Publicidad* p = anuncios.obtener(i);
            f << p->getPeso() << "|" << p->getMensaje() << "\n";
        }
        f.close();
    }

    cout << "\n Datos guardados correctamente en '" << dir << "'.\n";
    return true;
}
bool UdeATunes::cargarDatos(const std::string& dir) {
    // Limpiar listas previas
    usuarios.clear();
    artistas.clear();
    anuncios.clear();

    auto abrirArchivo = [&](const std::string& path, std::ifstream& f) -> bool {
        f.open(path);
        if (!f.is_open()) {
            cerr << "[ERROR] No se pudo abrir: " << path << endl;
            return false;
        }
        return true;
    };

    std::string line, token;

    // === USUARIOS ===
    {
        std::ifstream f;
        if (abrirArchivo(dir + "/usuarios.txt", f)) {
            while (std::getline(f, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                std::string nickname, ciudad, pais, fecha;
                int vipFlag;
                std::getline(ss, nickname, '|');
                std::getline(ss, token, '|'); vipFlag = stoi(token);
                std::getline(ss, ciudad, '|');
                std::getline(ss, pais, '|');
                std::getline(ss, fecha, '|');
                Usuario* u = new Usuario(vipFlag == 1, nickname, ciudad, pais, fecha);
                usuarios.agregar(u);
            }
            f.close();
            cout << "[OK] Usuarios cargados: " << usuarios.getCantidad() << endl;
        }
    }

    // === ARTISTAS ===
    {
        std::ifstream f;
        if (abrirArchivo(dir + "/artistas.txt", f)) {
            while (std::getline(f, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                int id, edad, seguidores, tendencia;
                std::string nombre, pais;
                std::getline(ss, token, '|'); id = stoi(token);
                std::getline(ss, token, '|'); edad = stoi(token);
                std::getline(ss, nombre, '|');
                std::getline(ss, pais, '|');
                std::getline(ss, token, '|'); seguidores = stoi(token);
                std::getline(ss, token, '|'); tendencia = stoi(token);
                Artista* a = new Artista(id, edad, nombre, pais);
                for (int i = 0; i < seguidores; i++) a->agregarSeguidor();
                artistas.agregar(a);
            }
            f.close();
            cout << "[OK] Artistas cargados: " << artistas.getCantidad() << endl;
        }
    }

    // === ÁLBUMES ===
    {
        std::ifstream f;
        if (abrirArchivo(dir + "/albumes.txt", f)) {
            while (std::getline(f, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                int id, artId;
                std::string nombre, fecha, sello, portada;
                std::getline(ss, token, '|'); id = stoi(token);
                std::getline(ss, nombre, '|');
                std::getline(ss, fecha, '|');
                std::getline(ss, sello, '|');
                std::getline(ss, portada, '|');
                std::getline(ss, token, '|'); artId = stoi(token);
                Artista* a = buscarArtistaPorId(artId);
                if (a) {
                    Album* alb = new Album(id, nombre, fecha, sello, portada);
                    a->agregarAlbum(alb);
                }
            }
            f.close();
            cout << "[OK] Álbumes cargados correctamente.\n";
        }
    }

    // === CANCIONES ===
    {
        std::ifstream f;
        if (abrirArchivo(dir + "/canciones.txt", f)) {
            while (std::getline(f, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                int id, albumId;
                float duracion;
                std::string nombre, ruta128, ruta320;
                std::getline(ss, token, '|'); id = stoi(token);
                std::getline(ss, token, '|'); duracion = stof(token);
                std::getline(ss, nombre, '|');
                std::getline(ss, ruta128, '|');
                std::getline(ss, ruta320, '|');
                std::getline(ss, token, '|'); albumId = stoi(token);
                Album* alb = buscarAlbumPorId(albumId);
                if (alb) alb->agregarCancion(new Cancion(id, duracion, nombre, ruta128, ruta320));
            }
            f.close();
            cout << "[OK] Canciones cargadas.\n";
        }
    }

    // === CRÉDITOS ===
    {
        std::ifstream f;
        if (abrirArchivo(dir + "/creditos.txt", f)) {
            while (std::getline(f, line)) {
                if (line.empty()) continue;
                std::stringstream ss(line);
                int songId;
                std::string nombre, apellido, tipo, codigo;
                std::getline(ss, token, '|'); songId = stoi(token);
                std::getline(ss, nombre, '|');
                std::getline(ss, apellido, '|');
                std::getline(ss, tipo, '|');
                std::getline(ss, codigo, '|');
                Cancion* c = buscarCancionPorId(songId);
                if (c) c->agregarCreditos(new Creditos(nombre, apellido, tipo, codigo));
            }
            f.close();
            cout << "[OK] Créditos cargados.\n";
        }
    }

    // === ANUNCIOS ===
    {
        std::ifstream f;
        if (abrirArchivo(dir + "/anuncios.txt", f)) {
            while (std::getline(f, line)) {
                if (line.empty()) continue;
                size_t pos = line.find('|');
                int cat = stoi(line.substr(0, pos));
                std::string msg = line.substr(pos + 1);
                Publicidad::Categoria catEnum = Publicidad::C;
                if (cat == 2) catEnum = Publicidad::B;
                else if (cat == 3) catEnum = Publicidad::A;
                anuncios.agregar(new Publicidad(msg, catEnum));
            }
            f.close();
            cout << "[OK] Anuncios cargados.\n";
        }
    }

    cout << "\n Carga de datos finalizada correctamente.\n";
    return true;
}

void UdeATunes::iniciarKron(const std::string& rutaDatos, int segundos) {
    if (kronActivo) return; // ya está activo

    kronActivo = true;
    hiloKron = std::thread([this, rutaDatos, segundos]() {
        while (kronActivo) {
            std::this_thread::sleep_for(std::chrono::seconds(segundos));
            if (kronActivo) {
                cout << "\n [Kron] Guardando datos automáticos...\n";
                guardarDatos(rutaDatos);
            }
        }
    });
    hiloKron.detach(); // lo dejamos correr en segundo plano
    cout << "[OK] Sistema Kron iniciado. Guardado automático cada " << segundos << " segundos.\n";
}

void UdeATunes::detenerKron() {
    kronActivo = false;
    cout << "[Kron] Detenido correctamente.\n";
}
