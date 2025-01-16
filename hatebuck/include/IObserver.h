#ifndef IOBSERVER_H
#define IOBSERVER_H

#include <string>
#include <memory>

// clase IObsever: interfaz de Observador para la implementación del patrón Observer

using namespace std;

class Mensaje;

class IObserver
{
    public:
        virtual ~IObserver() = default;
        virtual void actualizar(const shared_ptr<Mensaje>& mensaje) = 0;
};

#endif // IOBSERVER_H
