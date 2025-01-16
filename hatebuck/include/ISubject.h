#ifndef ISUBJECT_H
#define ISUBJECT_H

#include <memory>
#include "IObserver.h"

// clase ISubject: interfaz de Sujeto para la implementación del patrón Observer

using namespace std;

class ISubject
{
    public:
        virtual ~ISubject() = default;
        virtual void agregarObservador(const shared_ptr<IObserver>& observador) = 0;
        virtual void eliminarObservador(const shared_ptr<IObserver>& observador) = 0;
        virtual void notificar(const shared_ptr<Mensaje>& mensaje) = 0;
};

#endif // ISUBJECT_H
