#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include "IPublicacion.h"
#include "Enums.h"

using namespace std;

class Usuario
{
    public:
        //constructor de usuario a partir de nombre y contraseña
        Usuario(string n, string p):
            nombre(move(n)), password(move(p)){}
        //función para verificar si la constraseña introducida es correcta
        bool verificarPassword(const string&p) const;
        //función para obtener el nombre del objeto Usuario
        const string& obtNombre();
        //función para publicar una publicación
        void publicarTexto(shared_ptr<IPublicacion> pub);
        //función para obtener las publicaciones del usuario
        const vector<shared_ptr<IPublicacion>>& obtPublicaciones()const;
        //función para agregar o modificar la relación del usuario con otro
        void establecerRelacion(const string&usuario, TipoRelacion tipo);
        //función para obtener el tipo de relación del usuario con otro
        bool obtRelacion(const string&usuario, TipoRelacion& resultado) const;



    private:
        const string nombre;
        const string password;
        unordered_map<string, TipoRelacion> relaciones;
        vector<shared_ptr<IPublicacion>> publicaciones;
};

#endif // USUARIO_H
