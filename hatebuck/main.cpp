#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <memory>
#include <iomanip>

#include "Usuario.h"
#include "Moderador.h"
#include "Palabra.h"
#include "Mensaje.h"
#include "Enums.h"

using namespace std;

// declaración de funciones de la aplicación
void ejecutar();
map<string, shared_ptr<Usuario>> inicializarDatos();
void mostrarMenu();
void login();
void cambiarRelacion();
void crearPublicacion();
void modificarPublicacion();
void enviarMensaje();
vector<shared_ptr<IPalabra>> leerTextoEntrada();

// función principal
int main()
{
    try{
        ejecutar();
    }catch(const invalid_argument& e){
        cerr << e.what() << endl;
        return 1;
    }


    return 0;
}

// implementación de las funciones de la aplicación

// función que ejecuta el programa. lee los datos de los usuarios del archivo de entrada, gestiona el inicio de sesión, y gestiona las opciones de menú
void ejecutar(){
    map<string, shared_ptr<Usuario>> usuarios = inicializarDatos();

    login();

    mostrarMenu();

    gestionarOpciones();
}

// función para inicializar datos de usuarios de la aplicación a partir del nombre y la contraseña. Devuelve un map con los usuarios creados
map<string, shared_ptr<Usuario>> inicializarDatos(){
    map<string, shared_ptr<Usuario>> usuarios;

    // usuarios normales
    usuarios["gemmaReina"] = make_shared<Usuario>("gemmaReina", "");
    usuarios["fedeDiaz"] = make_shared<Usuario>("fedeDiaz", "");
    usuarios["cHodoroga"] = make_shared<Usuario("cHodoroga", "password123");

    // usuarios moderadores
    usuarios["jordiRegincos"] = make_shared<Moderador>("jordiRegincos", "elsPatronsGraspMolan");

    // relaciones iniciales
    usuarios["gemmaReina"]->establecerRelacion("fedeDiaz", TipoRelacion::AMIGO);
    usuarios["fedeDiaz"]->establecerRelacion("gemmaReina", TipoRelacion::AMIGO);
    usuarios["cHodoroga"]->establecerRelacion("fedeDiaz", TipoRelacion::SALUDADO);

    return usuarios;
}
