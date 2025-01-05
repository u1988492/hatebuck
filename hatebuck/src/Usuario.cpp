#include "Usuario.h"

bool Usuario::verificarPassword(const string& p) const{
    return password == p;
}

const string& Usuario::obtNombre(){
    return nombre;
}

void Usuario::publicarTexto(shared_ptr<IPublicacion> pub){
    publicaciones.push_back(move(pub));
}

const vector<shared_ptr<IPublicacion>>& Usuario::obtPublicaciones() const{
    return publicaciones;
}

void Usuario::establecerRelacion(const string& usuario, TipoRelacion tipo){
    relaciones[usuario] = tipo;
}

bool Usuario::obtRelacion(const string& usuario, TipoRelacion& resultado) const{
    auto it = relaciones.find(usuario);
    if(it!=relaciones.end()){
        resultado = it->second;
        return true;
    }
    return false;
}
