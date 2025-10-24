#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <thread>
#include <fstream>

#include "udeatunes.h"
#include "usuario.h"
#include "cancion.h"

using namespace std;

// Helper: buscar usuario por nickname (simple)
Usuario* buscarUsuarioPorNickname(UdeATunes& app, const string& nick) {
    for (int i = 0; i < app.getUsuariosCount(); ++i) {
        Usuario* u = app.getUsuarioAt(i);
        if (u->getNickname() == nick) return u;
    }
    return nullptr;
}

// NOTE: The helper functions app.getUsuariosCount() and app.getUsuarioAt(i)
// must exist. If in your implementation they have other names, reemplaza por los getters
// que tienes. Si no existen, puedo añadirlos. Si prefieres, usa app.iniciarSesion()
// que ya tenías (pero aquí queremos el puntero Usuario* para operar).

int menuPrincipal() {
    cout << "\n===== UdeATunes =====\n";
    cout << "1. Iniciar sesión\n";
    cout << "2. Salir\n";
    cout << "Seleccione una opción: ";
    int opc; cin >> opc;
    return opc;
}

int menuPremium() {
    cout << "\n=== Menú Premium ===\n";
    cout << "1. Reproducción aleatoria (K=5)\n";
    cout << "2. Mis favoritos (editar / seguir / ejecutar)\n";
    cout << "3. Mostrar métricas actuales\n";
    cout << "4. Cerrar sesión\n";
    cout << "Seleccione una opción: ";
    int opc; cin >> opc;
    return opc;
}

int menuEstandar() {
    cout << "\n=== Menú Estándar ===\n";
    cout << "1. Reproducción aleatoria (K=5)\n";
    cout << "2. Mostrar métricas actuales\n";
    cout << "3. Cerrar sesión\n";
    cout << "Seleccione una opción: ";
    int opc; cin >> opc;
    return opc;
}

int menuFavoritos() {
    cout << "\n--- Menú Favoritos (VIP) ---\n";
    cout << "1. Agregar canción a favoritos (por ID)\n";
    cout << "2. Eliminar canción de favoritos (por ID)\n";
    cout << "3. Seguir lista de favoritos de otro usuario\n";
    cout << "4. Ejecutar mis favoritos (orden original)\n";
    cout << "5. Ejecutar mis favoritos (aleatorio)\n";
    cout << "6. Volver\n";
    cout << "Seleccione una opción: ";
    int opc; cin >> opc;
    return opc;
}

// Función que implementa interacción simplificada de reproducción para premium
// usando reproduccionAleatoria del app cuando se quiere simplemente testear K canciones.
// Para control más fino (prev/next/repeat) implementamos aquí un bucle que
// simula K reproducciones con prompt entre canciones.
void reproduccionPremiumInteractiva(UdeATunes& app, Usuario* u, int K = 5) {
    cout << "\nIniciando reproducción aleatoria interactiva (Premium). K = " << K << "\n";
    app.resetContadorIter();

    // Reunir todas las canciones (reutilizamos la función interna)
    Cancion** all = nullptr;
    int total = app.reunirTodasCancionesPublic(&all); // necesito versión pública; si no existe usa reproducirAleatoria
    if (total == 0) {
        cout << "No hay canciones en la plataforma.\n";
        return;
    }

    // historial circular para retroceder hasta 4 canciones
    int historySize = 10; // suficiente
    Cancion** history = new Cancion*[historySize];
    int historyPos = 0;
    int historyCount = 0;

    bool repetir = false;
    int reproducidas = 0;
    int lastIdx = -1;

    while (reproducidas < K) {
        int idx = rand() % total;
        if (idx == lastIdx) idx = (idx + 1) % total;
        Cancion* c = all[idx];

        // Mostrar interfaz solicitado
        string portada = app.buscarPortadaDeCancion(c); // helper que deberías tener; si no, mostramos portada del album al buscar
        cout << "\n-------------------------------\n";
        cout << "Cantante / Album / Portada: " << portada << "\n";
        cout << "Título: " << c->getNombre() << "\n";
        cout << "Ruta del archivo (320 kbps): " << c->getRuta320() << "\n";
        cout << "Duración (simulada): " << c->getDuracion() << " minutos\n";
        cout << "Opciones: 1-Reproducir  2-Detener  3-Siguiente  4-Previo  5-Repetir on/off\n";
        cout << "Comando (si no ingresa nada en 3s, avanza automáticamente): ";

        // Reproducir y esperar 3 segundos (chronos)
        c->reproducir(true); // premium -> alta calidad
        app.incrementIter(); // si tienes contador interno, incrementa
        std::this_thread::sleep_for(std::chrono::seconds(3));

        // Guardar en historial
        history[historyPos] = c;
        historyPos = (historyPos + 1) % historySize;
        if (historyCount < historySize) historyCount++;

        reproducidas++;
        lastIdx = idx;

        // Tras reproducción, preguntar acción (pero sin bloquear demasiado)
        cout << "\nIngrese comando (0 para continuar): ";
        int cmd;
        // intentar leer con tiempo limitado no es trivial sin threads; para simplicidad leemos normalmente
        cin >> cmd;
        if (cmd == 2) { // detener
            cout << "Reproducción detenida por el usuario.\n";
            break;
        } else if (cmd == 3) {
            continue; // siguiente
        } else if (cmd == 4) {
            // volver hasta 4
            if (historyCount >= 2) {
                int retroIdx = (historyPos - 2 + historySize) % historySize; // la canción anterior
                Cancion* prev = history[retroIdx];
                cout << "Volviendo a: " << prev->getNombre() << "\n";
                prev->reproducir(true);
                std::this_thread::sleep_for(std::chrono::seconds(3));
            } else {
                cout << "No hay canción previa disponible.\n";
            }
        } else if (cmd == 5) {
            repetir = !repetir;
            cout << "Modo repetir " << (repetir ? "activado" : "desactivado") << "\n";
            if (repetir) {
                // repetir la misma canción una vez inmediatamente
                c->reproducir(true);
                std::this_thread::sleep_for(std::chrono::seconds(3));
            }
        } else {
            // 0 u otro -> continuar (automático)
            continue;
        }
    } // while

    delete[] history;
    delete[] all;

    cout << "\nReproducción finalizada. Iteraciones: " << app.getContadorIter() << "\n";
    app.memoriaUsada();
}

// Función de reproducción estándar delegada (usa app.reproduccionAleatoria que maneja anuncios)
void reproduccionEstandar(UdeATunes& app, Usuario* u, int K = 5) {
    cout << "\nIniciando reproducción aleatoria (Estándar). K = " << K << "\n";
    app.resetContadorIter();
    app.reproduccionAleatoria(u, K);
    cout << "\nReproducción finalizada. Iteraciones: " << app.getContadorIter() << "\n";
    app.memoriaUsada();
}

int main() {
    srand((unsigned)time(nullptr));

    UdeATunes app;

    cout << "Ingrese la carpeta donde se encuentran los datos (por defecto: data): ";
    string carpeta;
    getline(cin >> ws, carpeta);
    if (carpeta.empty()) carpeta = "data";
    cout << "Cargando datos desde '" << carpeta << "/' ...\n";

    bool cargado = app.cargarDatos(carpeta);
    if (!cargado) {
        cout << "No se encontraron datos o hubo problemas cargando.\n";
        cout << "¿Desea crear archivos de prueba automáticamente? (s/n): ";
        char resp;
        cin >> resp;
        if (resp == 's' || resp == 'S') {
            system(("mkdir " + carpeta).c_str());
            ofstream fUsuarios(carpeta + "/usuarios.txt");
            fUsuarios << "1|Carlos Perez|carlitos|1234|1\n";
            fUsuarios << "2|Ana Gomez|anita|abcd|0\n";
            fUsuarios << "3|Santiago Gallon|santig|4321|1\n";
            fUsuarios.close();

            ofstream fArtistas(carpeta + "/artistas.txt");
            fArtistas << "10001|Shakira|46|Colombia|1500000|1\n";
            fArtistas << "10002|Juanes|50|Colombia|800000|2\n";
            fArtistas.close();

            ofstream fAlbumes(carpeta + "/albumes.txt");
            fAlbumes << "10001|01|Sale el Sol|Pop|2010|3600|Sony|/users/storage/shakira/image/sale_el_sol.png|9\n";
            fAlbumes << "10002|01|Un dia normal|Rock|2002|3000|Universal|/users/storage/juanes/image/un_dia_normal.png|8\n";
            fAlbumes.close();

            ofstream fCanciones(carpeta + "/canciones.txt");
            fCanciones << "1000101|Loca|180|/users/storage/shakira/audio/loca_128.ogg|/users/storage/shakira/audio/loca_320.ogg|0\n";
            fCanciones << "1000201|A Dios le Pido|200|/users/storage/juanes/audio/adioslepido_128.ogg|/users/storage/juanes/audio/adioslepido_320.ogg|0\n";
            fCanciones.close();

            ofstream fPubli(carpeta + "/publicidad.txt");
            fPubli << "Promo1|C|Disfruta café colombiano premium\n";
            fPubli << "Promo2|B|Compra guitarras con 20% de descuento\n";
            fPubli << "Promo3|AAA|Viaja con descuento exclusivo a Medellín\n";
            fPubli.close();

            cout << "Archivos de ejemplo creados en '" << carpeta << "/'. Ejecute nuevamente el programa.\n";
            return 0;
        }
    }
    if (!cargado) {
        cout << "No se encontraron datos o hubo problemas cargando. Continúe y los cambios se guardarán al salir.\n";
    } else {
        cout << "Datos cargados correctamente.\n";
    }

    while (true) {
        int opc = menuPrincipal();
        if (opc == 1) {
            cout << "Ingrese nickname: ";
            string nick; cin >> nick;

            // Buscar usuario
            Usuario* user = app.buscarUsuarioPorNicknamePublic(nick); // esta función debe existir; si no, la agregamos
            if (!user) {
                cout << "Usuario no encontrado. Intente de nuevo.\n";
                continue;
            }

            cout << "Bienvenido, " << user->getNickname() << "!\n";
            if (user->getVIP()) {
                // Menú Premium
                bool session = true;
                while (session) {
                    int op = menuPremium();
                    if (op == 1) {
                        // reproducción aleatoria con interacción premium
                        reproduccionPremiumInteractiva(app, user, 5);
                    } else if (op == 2) {
                        // Favoritos
                        bool favBack = false;
                        while (!favBack) {
                            int fop = menuFavoritos();
                            if (fop == 1) {
                                cout << "Ingrese ID de canción a agregar: ";
                                int id; cin >> id;
                                Cancion* c = app.buscarCancionPorIdPublic(id);
                                if (!c) { cout << "Canción no encontrada.\n"; }
                                else user->agregarFavorito(c);
                            } else if (fop == 2) {
                                cout << "Ingrese ID de canción a eliminar: ";
                                int id; cin >> id;
                                Cancion* c = app.buscarCancionPorIdPublic(id);
                                if (!c) { cout << "Canción no encontrada.\n"; }
                                else user->eliminarFavorito(c);
                            } else if (fop == 3) {
                                cout << "Ingrese nickname del usuario a seguir: ";
                                string otro; cin >> otro;
                                Usuario* u2 = app.buscarUsuarioPorNicknamePublic(otro);
                                if (!u2) cout << "Usuario a seguir no encontrado.\n";
                                else user->seguirFavoritosDe(u2);
                            } else if (fop == 4) {
                                app.resetContadorIter();
                                user->ejecutarFavoritos(false, 6); // orden original, M=6
                                cout << "Iteraciones (ejecutarFavoritos): " << app.getContadorIter() << "\n";
                                app.memoriaUsada();
                            } else if (fop == 5) {
                                app.resetContadorIter();
                                user->ejecutarFavoritos(true, 6);
                                cout << "Iteraciones (ejecutarFavoritos aleatorio): " << app.getContadorIter() << "\n";
                                app.memoriaUsada();
                            } else {
                                favBack = true;
                            }
                        }
                    } else if (op == 3) {
                        // Mostrar métricas (global)
                        cout << "Iteraciones actuales (acumuladas): " << app.getContadorIter() << "\n";
                        app.memoriaUsada();
                    } else {
                        session = false;
                        cout << "Cerrando sesión de " << user->getNickname() << "\n";
                    }
                }
            } else {
                // Menú Estándar
                bool session = true;
                while (session) {
                    int op = menuEstandar();
                    if (op == 1) {
                        app.resetContadorIter();
                        reproduccionEstandar(app, user, 5);
                    } else if (op == 2) {
                        cout << "Iteraciones actuales (acumuladas): " << app.getContadorIter() << "\n";
                        app.memoriaUsada();
                    } else {
                        session = false;
                        cout << "Cerrando sesión de " << user->getNickname() << "\n";
                    }
                }
            }

        } else {
            // SALIR: guardar datos y terminar
            cout << "Guardando datos en 'data/' ...\n";
            bool ok = app.guardarDatos("data");
            if (!ok) cout << "Advertencia: no se pudieron guardar algunos archivos.\n";
            else cout << "Datos guardados correctamente.\n";
            cout << "Saliendo. ¡Hasta luego!\n";
            break;
        }
    } // while true

    return 0;
}
