#include "Usuario.h"

bool Usuario::verificarPassword(const string& p) const{
    return password == p;
}

const string& Usuario::obtNombre(){
    return nombre;
}

bool Usuario::verificarPassword(const string& p) const{
    return password == p;
}

void Usuario::publicarTexto(shared_ptr<IPublicacion> pub){
    publicaciones.push_back(move(pub)); // añadir publicación a estructura de publicaciones del usuario
}

bool Usuario::editarPublicacion(size_t pubIndex, const vector<shared_ptr<IPalabra>>& nuevoContenido){
    // usuarios no moderadores solo pueden editar sus propias publicaciones
    if(pubIndex >= publicaciones.size()){
        return false; // la publicación no existe
    }

    publicaciones[pubIndex]->editarContenido(nuevoContenido); // pasar el contenido nuevo a la función de edicón de la publicación
    return true; // confirmar que se ha editado correctamente;
}

const vector<shared_ptr<IPublicacion>>& Usuario::obtPublicaciones() const{
    return publicaciones; // obtener las publicaciones del usuario
}

void Usuario::establecerRelacion(const string& usuario, TipoRelacion tipo){
    // modificar el tipo de relación de la estructura de relaciones del usuario al tipo seleccionado
    relaciones[usuario] = tipo; // si no existe la relación con el usuario indicado, se creará una nueva
}

bool Usuario::obtRelacion(const string& usuario, TipoRelacion& resultado) const{
    // buscar la relación con el usuario indicado
    auto it = relaciones.find(usuario);
    if(it!=relaciones.end()){
        resultado = it->second; // devolver el contenido de la relación con el usuario indicado
        return true; // confirmar que se ha encontrado correctamente
    }
    return false; // no existe una relación con el usuario indicado
}
