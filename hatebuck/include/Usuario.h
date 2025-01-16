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
#include "ISubject.h"
#include "IObserver.h"
#include "Mensaje.h"

class Moderador;

using namespace std;

// clase usuario: almacena los datos de un usuario y gestiona las funciones básicas del usuario, de publicación de textos, y modificación de relaciones

class Usuario : public ISubject, public IObserver{
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
        // función para reemplazar una publicación al editarla
        void reemplazarPublicacion(size_t index, shared_ptr<IPublicacion> nuevaPublicacion);
        //para acceder a las relaciones (encapsulamiento)
        vector<pair<string, TipoRelacion>> obtenerRelaciones() const {
            vector<pair<string, TipoRelacion>> lista;
            for (const auto& rel : relaciones) {
                lista.push_back(rel);
            }
            return lista;
        }
        // función para enviar un mensaje privado a un usuario
        void enviarMensaje(const string& usuario, const vector<shared_ptr<IPalabra>>& contenido);
        // función para obtener los mensajes recibidos del usuario
        vector<shared_ptr<Mensaje>> obtMensajesRecibidos() const;
        // función para obtener los mensajes enviados por el usuario
        vector<shared_ptr<Mensaje>> obtMensajesEnviados() const;

        // función para agregar o modificar la relación del usuario con otro
        void establecerRelacion(const string&usuario, TipoRelacion tipo);
        // función para obtener el tipo de relación del usuario con otro
        bool obtRelacion(const string&usuario, TipoRelacion& resultado) const;

        // métodos de patrón observer para gestionar el envío de mensajes
        void agregarObservador(const shared_ptr<IObserver>& observador) override;
        void eliminarObservador(const shared_ptr<IObserver>& observador) override;
        void notificar(const shared_ptr<Mensaje>& mensaje) override;
        void actualizar(const shared_ptr<Mensaje>& mensaje) override;


    // protected para permitir la herencia con la clase moderador
    protected:
        const string nombre;
        const string password;
        unordered_map<string, TipoRelacion> relaciones;
        vector<shared_ptr<IPublicacion>> publicaciones;
        vector<shared_ptr<IObserver>> observadores;
        vector<shared_ptr<Mensaje>> mensajesEnviados;
        vector<shared_ptr<Mensaje>> mensajesRecibidos;
        // aquí irían las preferencias de mensajes y visibilidad pero quizás no hace falta implementarlo para la práctica
        // map<TipoRelacion, bool> preferenciasMensajes;
        // map<TipoRelacion, bool> preferenciasVisibilidad;
};

#endif // USUARIO_H
