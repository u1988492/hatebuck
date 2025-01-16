#ifndef PUBLICACIONEDITADA_H
#define PUBLICACIONEDITADA_H

#include <string>
#include <vector>
#include <IPalabra.h>

using namespace std::chrono;

// clase PublicacionEditada: contiene los datos de una publicación que ha sido editada, y las funciones para consultar o modificar su contenido

class PublicacionEditada : public PublicacionDecorator
{
    public:
        PublicacionEditada(shared_ptr<IPublicacion> pub, string editor, string contenidoOrig)
            : PublicacionDecorator(move(pub)), editorUsuario(move(editor)), contenidoOriginal(move(contenidoOrg)) {
                auto now = std::chrono::system_clock::now();
                auto timeT = std::chrono::system_clock::to_time_t(now);
                fechaEdicion = std::ctime(&timeT);
        }
        // función para mostrar el contenido de la publicación
        string contenido() const override{
            return PublicacionDecorator::contenido();
        }
        // función para modificar el contenido de la publicación
        void editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) override;

        // función para obtener los datos de la publicación
        string obtenerMetadata() const override{
            return PublicacionDecorator::obtenerMetadata() +
                "\nEditado por: " + editorUsuario + "\Fecha de edición: " + fechaEdicion;
        }

    private:
        // metadata de una publicación editada
        string editorUsuario;
        string fechaEdicion;
        string contenidoOriginal;
};

#endif // PUBLICACIONEDITADA_H
