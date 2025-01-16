#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include "IPalabra.h"

using namespace std;

// Clase Palabra: implementa IPalabra, contiene el tipo y el contenido de la palabra
class Palabra: public IPalabra
{
    public:
        // Constructor de palabra base con contenido y tipo
        Palabra(string contenido, string tipo)
            : contenido(move(contenido)), tipo(move(tipo)) {}

        string obtTipo() const override { return tipo; }
        string mostrarContenido() const override { return contenido; }  // ✅ Agregada implementación

    protected:
        string contenido;
        string tipo;
};

// Clase NoMostrar: implementa Palabra, gestiona el comportamiento de las palabras de tipo NoMostrar
class NoMostrar: public Palabra {
    public:
        NoMostrar(string contenido)
            : Palabra(move(contenido), "NOMOSTRAR") {}
        string mostrarContenido() const override { return "[OCULTO]"; }
};

// Clase Reemplazar: implementa Palabra, gestiona el comportamiento de las palabras de tipo Reemplazar
class Reemplazar: public Palabra {
    private:
        string reemplazo;
    public:
        Reemplazar(string contenido, string reemplazo)
            : Palabra(move(contenido), "REEMPLAZAR"), reemplazo(move(reemplazo)) {}
        string mostrarContenido() const override { return reemplazo; }
};

// Clase Simbolo: implementa Palabra, gestiona el comportamiento de los símbolos
class Simbolo: public Palabra {
    public:
        Simbolo(string contenido)
            : Palabra(move(contenido), "SIMBOLO") {}
        string mostrarContenido() const override { return contenido; }
};

#endif // PALABRA_H
