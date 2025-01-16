#ifndef IPUBLICACION_H
#define IPUBLICACION_H

#include "IPalabra.h"

using namespace std;

// clase interfaz IPublicación: clase abstracta para implementar el patrón Decorator en la gestión de las publicaciones

class IPublicacion
{
    public:
        // destructor por defecto
        virtual ~IPublicacion() = default;
        // función para mostrar el contenido de la publicación
        virtual string contenido() const = 0;
        // función para editar el contenido de la publicación
        virtual void editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) = 0;
        // función para obtener los datos de la publicación
        virtual string obtenerMetadata() const = 0;


};

#endif // IPUBLICACION_H
