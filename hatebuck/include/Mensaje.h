#ifndef MENSAJE_H
#define MENSAJE_H

#include <vector>
#include <string>
#include <memory>

#include "IPalabra.h"

using namespace std;

// clase mensaje: gestiona la creación de mensajes privados

class Mensaje
{
    public:
        // constructor del mensaje a partir de los datos y el contenido
        Mensaje(string emisor, string receptor, const vector<shared_ptr<IPalabra>>&contenido)
        : emisor(move(emisor)), receptor(move(receptor)), palabras(contenido){
            // obt fecha actual del mensaje
            auto now = std::chrono::system_clock::now();
            auto timeT = std::chrono::system_clock::to_time_t(now);
            fecha = std::ctime(&timeT);
        }

        // función para obtener el contenido del mensaje
        string obtContenido() const;
        // funciones para obtener los metadatos del mensaje
        const string& obtEmisor() const;
        const string& obtReceptor() const;
        const string& obtFecha() const;

    private:
        vector<shared_ptr<IPalabra>> palabras;
        string emisor;
        string receptor;
        string fecha;
};

#endif // MENSAJE_H
