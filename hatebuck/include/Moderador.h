#ifndef MODERADOR_H
#define MODERADOR_H

#pragma once
#include "Usuario.h"

using namespace std;

// clase moderador: subclase de usuario, gestiona las funciones específicas a los moderadores

class Moderador : public Usuario
{
    public:
        // hereda el constructor de Usuario
        using Usuario::Usuario;

        // función para editar publicaciones, con el permiso de editar las de otros usuarios
        bool editarPublicacion(size_t pubIndex, const vector<shared_ptr<IPalabra>>& nuevoContenido, Usuario& usuario);
};

#endif // MODERADOR_H
