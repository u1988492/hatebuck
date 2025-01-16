#ifndef PUBLICACIONDECORATOR_H
#define PUBLICACIONDECORATOR_H

#include <memory>
#include "IPublicacion.h"

// clase PublicacionDecorator: implementa la interfaz IPublicacion, gestiona la implementación del patrón Decorator para los tipos de publicaciones

class PublicacionDecorator : public IPublicacion
{
    public:
        explicit PublicacionDecorator(shared_ptr<IPublicacion> pub)
            : publicacion(move(pub)) {}

        string contenido() const override{
            return publicacion->contenido();
        }

        void editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) override{
            publicacion->editarContenido(nuevoContenido);
        }

        string obtenerMetadata() const override{
            return publicacion->obtenerMetadata();
        }

    protected:
        shared_ptr<IPublicacion> publicacion;
};

#endif // PUBLICACIONDECORATOR_H
