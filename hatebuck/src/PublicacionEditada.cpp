#include "PublicacionEditada.h"

void PublicacionEditada::editarContenido(const vector<shared_ptr<IPalabra>>& nuevoContenido) {
    PublicacionDecorator::editarContenido(nuevoContenido);
}
