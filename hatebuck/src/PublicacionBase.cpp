#include "PublicacionBase.h"

// Constructor de PublicacionBase
PublicacionBase::PublicacionBase(const string& autor) : autor(autor) {
    fecha = "Desconocida"; // O puedes usar la fecha actual
}

// Implementaci�n de contenido()
string PublicacionBase::contenido() const {
    string resultado;
    for (const auto& palabra : palabras) {
        resultado += palabra->mostrarContenido() + " ";  // Concatena palabras
    }
    return resultado;
}

// Implementaci�n de editarContenido()
void PublicacionBase::editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) {
    palabras = nuevoContenido;
}

// Implementaci�n de obtenerMetadata()
string PublicacionBase::obtenerMetadata() const {
    return "Autor: " + autor + "\nFecha: " + fecha;
}
