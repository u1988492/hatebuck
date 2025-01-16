#include "Mensaje.h"

string Mensaje::obtContenido() const{
    string resultado;
    for(const auto& palabra : palabras){
        resultado += palabra->mostrarContenido() + " ";
    }
    return resultado;
}

const string& Mensaje::obtEmisor() const{ return emisor; }
const string& Mensaje::obtReceptor() const{ return receptor; }
const string& Mensaje::obtFecha() const{ return fecha; }
