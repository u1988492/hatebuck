#include "Moderador.h"

bool Moderador::editarPublicacion(size_t pubIndex, const vector<shared_ptr<IPalabra>>& nuevoContenido, Usuario& usuario){
    // los moderadores pueden editar el contenido de las publicaciones de cualquier usuario
    const auto& publicaciones = usuario.obtPublicaciones();

    if(pubIndex >= publicaciones.size()){
        return false; // no existe la publicación indicada
    }

    // crear wrapper de publicación editada y actualizar el contenido
    auto original = publicaciones[pubIndex];
    auto publicacionEditada = make_shared<PublicacionEditada>(
        original, // publicacion original
        this->obtNombre(), // nombre del editor
        original->contenido() // contenido de la publicacion original
    );

    publicacionEditada->editarContenido(nuevoContenido);

    usuario.reemplazarPublicacion(pubIndex, publicacionEditada);
    return true;  // confirmar que se ha editado correctamente
}
