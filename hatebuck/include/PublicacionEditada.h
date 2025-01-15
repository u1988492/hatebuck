#ifndef PUBLICACIONEDITADA_H
#define PUBLICACIONEDITADA_H

using namespace std;

// clase PublicacionEditada: contiene los datos de una publicación que ha sido editada, y las funciones para consultar o modificar su contenido

class PublicacionEditada
{
    public:
        // función para mostrar el contenido de la publicación
        string contenido() const override;
        // función para modificar el contenido de la publicación
        void editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) override;
        // función para obtener los datos de la publicación
        string obtenerMetadata() const override;

    private:
        // metadata de una publicación editada
        string editorUsuario;
        string fechaEdicion;
        string contenidoOriginal;
};

#endif // PUBLICACIONEDITADA_H
