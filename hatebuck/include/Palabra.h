#ifndef PALABRA_H
#define PALABRA_H

#include <string>
#include "IPalabra.h"

using namespace std;

// definición de las clases necesarias para el patrón Strategy(??) para la gestión de los diferentes tipos de palabra


// clase Palabra: implementa IPalabra, contiene el tipo y el contenido de la palabra
class Palabra: public IPalabra
{
    public:
        // constructor de palabra base con contenido y tipo
        Palabra(string contenido, string tipo)
            : contenido(move(contenido)), tipo(move(tipo)){}

        string obtTipo() const override{ return tipo; }

    protected:
        string contenido;
        string tipo;
};

// clase NoMostrar: implementa Palabra, gestiona el comportamiento de las palabras de tipo NoMostrar
class NoMostrar: public Palabra{
    public:
        // constructor de palabra de tipo no mostrar a partir del constructor de la palabra base
        NoMostrar(string contenido)
            : Palabra(move(contenido), "NOMOSTRAR") {}
        // función de mostrar contenido de la palabra; para este caso, el contenido será oculto
        string mostrarContenido() const override{ return "[OCULTO]"; }
};

// clase Reemplazar: implementa Palabra, gestiona el comportamiento de las palabras de tipo Reemplazar
class Reemplazar: public Palabra{
    private:
        string reemplazo;
    public:
        Reemplazar(string contenido, string reemplazo)
            : Palabra(move(contenido), "REEMPLAZAR"), reemplazo(move(reemplazo)) {}
        string mostrarContenido() const override{ return reemplazo; }
};

// clase Simbolo: implementa Palabra, gestiona el comportamiendo de los símbolos
class Simbolo: public Palabra{
    public:
        // constructor de objeto símbolo a partir del constructor de la palabra base
        Simbolo(string contenido)
            : Palabra(move(contenido), "SIMBOLO") {}
        string mostrarContenido() const override{ return contenido; }
};

#endif // PALABRA_H
