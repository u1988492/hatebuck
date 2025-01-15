#ifndef PALABRA_H
#define PALABRA_H

using namespace std;

// definición de las clases necesarias para el patrón Strategy(??) para la gestión de los diferentes tipos de palabra


// clase Palabra: implementa IPalabra, contiene el tipo y el contenido de la palabra
class Palabra
{
    protected:
        string contenido;
        string tipo;
};

// clase NoMostrar: implementa Palabra, gestiona el comportamiento de las palabras de tipo NoMostrar
class NoMostrar: public Palabra{
    public:
        string mostrarContenido() const override{ return "[REDACTADO]"; }
};

// clase Reemplazar: implementa Palabra, gestiona el comportamiento de las palabras de tipo Reemplazar
class Reemplazar: public Palabra{
    private:
        string reemplazo;
    public:
        string mostrarContenido() const override{ return reemplazo; }
};

// clase Simbolo: implementa Palabra, gestiona el comportamiendo de los símbolos
class Simbolo: public Palabra{
    public:
        string mostrarContenido() const override{ return contenido; }
};

#endif // PALABRA_H
