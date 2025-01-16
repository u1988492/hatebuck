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

    auto publicacionEditada = make_shared<PublicacionEditada>(
        publicaciones[pubIndex],
        nombre,
        publicaciones[pubIndex]->contenido()
    ); // crear
    publicaciones[pubIndex]->editarContenido(nuevoContenido); // pasar el contenido nuevo a la función de edicón de la publicación
    return true; // confirmar que se ha editado correctamente;
}

void Usuario::reemplazarPublicacion(size_t pubIndex, shared_ptr<IPublicacion> nuevaPublicacion){
    if(pubIndex < publicaciones.size()){
        publicaciones[pubIndex] = move(nuevaPublicacion);
    }
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

vector<shared_ptr<Mensaje>> Usuario::obtMensajesRecibidos() const{
    return mensajesRecibidos;
}

vector<shared_ptr<Mensaje>> Usuario::obtMensajesEnviados() const{
    return mensajesEnviados;
}

void Usuario::enviarMensaje(const string& destinatario, const vector<shared_ptr<IPalabra>>& contenido){
    auto mensaje = make_shared<Mensaje>(nombre, destinatario, contenido);
    mensajesEnviados.push_back(mensaje);
    notificar(mensaje);
}

void Usuario::agregarObservador(const shared_ptr<IObserver>& observador){
    // añadir observador a la lista si no existe ya
    if(find(observadores.begin(), observadores.end(), observador) == observadores.end()){
        observadores.push_back(observador);
    }
}

void Usuario::eliminarObservador(const shared_ptr<IObserver>& observador){
    // quitar al observador de la lista
    observadores.erase(remove(observadores.begin(), observadores.end(), observador), observadores.end());
}

void Usuario::notificar(const shared_ptr<Mensaje>& mensaje){
    // notificar a los posibles destinatarios del nuevo mensaje
    for(const auto& observador : observadores){
        // comprobar si el receptor es el correcto
        auto receptor = dynamic_pointer_cast<Usuario>(observador);
        if(receptor && receptor->obtNombre() == mensaje->obtReceptor()){
            observador->actualizar(mensaje);
            break;
        }
    }
}


void Usuario::actualizar(const shared_ptr<Mensaje>& mensaje){
    // verificar que el usuario es el destinatario correcto
    if(mensaje->obtReceptor() == nombre){
        mensajesRecibidos.push_back(mensaje);
    }
}


