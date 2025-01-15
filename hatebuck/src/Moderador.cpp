#include "Moderador.h"

bool Moderador::editarPublicacion(size_t pubIndex, const vector<shared_ptr<IPalabra>>& nuevoContenido, Usuario& usuario){
    // los moderadores pueden editar el contenido de las publicaciones de cualquier usuario
    if(pubIndex >= usuario.obtPublicaciones().size()){
        return false; // no existe la publicación indicada
    }

    // encontrar la publicación indicada
    auto& publicaciones = usuario.obtPublicaciones();
    publicaciones[pubIndex]->editarContenido(nuevoContenido); // modificar el contenido de la publicación indicada
    return true; // confirmar que se ha realizado la operación correctamente
}
