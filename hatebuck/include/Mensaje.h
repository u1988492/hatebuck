#ifndef MENSAJE_H
#define MENSAJE_H


class Mensaje
{
    public:
        // función para agregar una palabra al mensaje
        void agregarPalabra(const Palabra& palabra);
        // función para obtener el contenido del mensaje
        string obtContenido() const;

    private:
        vector<Palabra> palabras;
        string emisor;
        string fecha;
};

#endif // MENSAJE_H
