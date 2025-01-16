#ifndef PUBLICACIONBASE_H
#define PUBLICACIONBASE_H

#include <string>
#include <vector>
#include <memory>
#include "IPalabra.h"
#include "IPublicacion.h"
using namespace std;

// clase PublicacionBase: implementa IPublicacion, contiene los métodos necesarios para visualizar y modificar el contenido de una publicación

class PublicacionBase : public IPublicacion
{
    public:
            // Constructor explícito
        PublicacionBase(const string& autor);
        // función para mostrar el contenido de la publicación
        string contenido() const override;
        // función para modificar el contenido de la publicación
        void editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) override;
        // función para obtener los datos de la publicación
        string obtenerMetadata() const override;

    protected:
        vector<shared_ptr<IPalabra>> palabras; // palabras que componen la publicación
        // metadata de la publicación
        string autor;
        string fecha;
        vector<string> multimedia;
};

#endif // PUBLICACIONBASE_H
