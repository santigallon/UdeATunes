#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include <string>


using namespace std;
class Estudiante
{

    //atributos (caracteristicas)
    string nombre;
    string apellido;
    string email;
    string programa;
    float promedio;
    int documento;
public:
    //metodos (Comportamientos)

    Estudiante();  //constructor por defecto
    //constructores con parametros
    Estudiante(string nombre, string apellido);
    Estudiante(string nombre, string apellido, float promedio);
    Estudiante(string nombre, string apellido, int documento);
    Estudiante(string nombre, string apellido, int documento, string email);
    Estudiante(string nombre, string apellido, int documento, string email, float promedio);
    bool InciarSesion(string email, int documento);
    void ActualizarInfo();

    float getPromedio() const;
    void setPromedio(float newPromedio);
    string getNombre() const;
    string getApellido() const;
    string getPrograma() const;
    void setPrograma(const string &newPrograma);
};

#endif // ESTUDIANTE_H
