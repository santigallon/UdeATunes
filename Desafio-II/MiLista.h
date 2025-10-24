#ifndef MILISTA_H
#define MILISTA_H

template <typename T>
class MiLista
{
private:
    T** elementos;
    int cantidad;
    int capacidad;

    void redimensionar ()
    {
        capacidad *= 2;
        T** nuevo = new T*[capacidad];
        for(int i = 0; i < cantidad; i++)
        {
            nuevo[i] = elementos[i];
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
        if (cantidad == capacidad) redimensionar();
        elementos[cantidad++] = element;
    }

    bool contiene(T* element)
    {
        for (int i = 0; i < cantidad; ++i)
            if (elementos[i] == element) return true;
        return false;
    }

    bool eliminar(T* element)
    {
        for (int i = 0; i < cantidad; ++i) {
            if (elementos[i] == element) {
                for (int j = i; j + 1 < cantidad; ++j)
                    elementos[j] = elementos[j+1];
                cantidad--;
                return true;
            }
        }
        return false;
    }

    T* obtener (int i)
    {
        if (i >= 0 && i < cantidad)
            return elementos[i];
        return nullptr;
    }

    int getCantidad(){ return cantidad;}
    int getCapacidad(){ return capacidad; }

    void clear()
    {
        cantidad = 0;
    }

    ~MiLista()
    {
        delete[] elementos;
    }
};

#endif // MILISTA_H
