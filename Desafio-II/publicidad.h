#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

#include <string>
using namespace std;

class Publicidad {
public:
    enum Categoria { C = 1, B = 2, A = 3 };

private:
    string mensaje;
    Categoria categoria;

public:
    Publicidad(string msg, Categoria cat)
        : mensaje(msg), categoria(cat) {}

    string getMensaje() const { return mensaje; }
    Categoria getCategoria() const { return categoria; }

    int getPeso() const { return static_cast<int>(categoria); }
};

#endif // PUBLICIDAD_H
