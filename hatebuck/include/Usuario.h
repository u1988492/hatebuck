#ifndef USUARIO_H
#define USUARIO_H

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <sstream>
#include <string>
#include <memory>
#include <vector>
#include "IPublicacion.h"
#include "Enums.h"

using namespace std;

// clase usuario: almacena los datos de un usuario y gestiona las funciones básicas del usuario, de publicación de textos, y modificación de relaciones

class Usuario
{
    public:
        // constructor de usuario a partir de nombre y contraseña
        Usuario(string n, string p):
            nombre(move(n)), password(move(p)){}
        // destructor por defecto
        virtual ~Usuario() = default;

        // función para verificar si la constraseña introducida es correcta
        bool verificarPassword(const string&p) const;
        // función para obtener el nombre del objeto Usuario
        const string& obtNombre();

        // función para publicar una publicación
        void publicarTexto(shared_ptr<IPublicacion> pub);
        // función para obtener las publicaciones del usuario
        const vector<shared_ptr<IPublicacion>>& obtPublicaciones()const;
        // función para editar una publicación, diferentes implementaciones para usuario o moderador
        virtual bool editarPublicacion(size_t index, const vector<shared_ptr<IPalabra>>& nuevoContenido);

        // función para enviar un mensaje privado a un usuario
        void enviarMensaje(const string& usuario, const vector<shared_ptr<IPalabra>>& contenido);

        // función para agregar o modificar la relación del usuario con otro
        void establecerRelacion(const string&usuario, TipoRelacion tipo);
        // función para obtener el tipo de relación del usuario con otro
        bool obtRelacion(const string&usuario, TipoRelacion& resultado) const;




    // protected para permitir la herencia con la clase moderador
    protected:
        const string nombre;
        const string password;
        unordered_map<string, TipoRelacion> relaciones;
        vector<shared_ptr<IPublicacion>> publicaciones;
        // aquí irían las preferencias de mensajes y visibilidad pero quizás no hace falta implementarlo para la práctica
        // map<TipoRelacion, bool> preferenciasMensajes;
        // map<TipoRelacion, bool> preferenciasVisibilidad;
};

#endif // USUARIO_H
