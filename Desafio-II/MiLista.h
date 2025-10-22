#ifndef MILISTA_H
#define MILISTA_H

template <typename T>
class MiLista
{
private:
    T** elementos;
    int cantidad;
    int capacidad;

    void redimencionar ()
    {
        capacidad *=2;
        T** nuevo = new T*[capacidad];
        for(int i = 0; i < cantidad; i++)
        {
            nuevo[i]= elementos [i];
        }
        delete[] elementos;
        elementos = nuevo;
    }
public:
    MiLista(int capInicial = 10)
    {
        capacidad = capInicial;
        cantidad = 0;
        elementos = new T*[capacidad];
    }

    void agregar (T* element)
    {
        if (cantidad == capacidad)redimencionar();
        elementos [cantidad++] = element;
    }

    T* obtener (int i)
    {
        if (i >= 0 && i <cantidad)
            return elementos[i];
        return nullptr;
    }

    int getCantidad(){ return cantidad;}

    ~MiLista()
    {
        delete[] elementos;
    }
};

#endif // MILISTA_H
