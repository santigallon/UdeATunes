#ifndef PUBLICIDAD_H
#define PUBLICIDAD_H

#include <string>

using namespace std;

class Publicidad
{
private:
    char categoria;
    string mensaje;

public:
    Publicidad(string m, char c)
        : mensaje(m), categoria(c) {}

    int getPrioridad();
    string getMensaje();
};

#endif // PUBLICIDAD_H
