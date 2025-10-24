#include "creditos.h"

string Creditos::getNombreCompleto()
{
    return nombre + " " + apellido + " (" + tipo + ")";
}

string Creditos::getTipo()const {return tipo;}
string Creditos::getCodigo()const{return codigoAfiliacion;};
