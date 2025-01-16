#ifndef IPALABRA_H
#define IPALABRA_H

#include <string>

using namespace std;

// clase IPalabra: clase abstracta para implementar el patrón Strategy (??) para la gestión dinámica de los diferentes tipos de palabra

class IPalabra
{
    public:
        // Constructor por defecto explícito
        IPalabra() = default;
        // destructor por defecto
        virtual ~IPalabra() = default;
        // función para mostrar el contenido de la palabra
        virtual string mostrarContenido() const = 0;
        // función para obtener el tipo de palabra
        virtual string obtTipo() const = 0;
};

#endif // IPALABRA_H
