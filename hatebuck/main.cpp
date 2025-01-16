#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <memory>
#include <iomanip>

#include "Usuario.h"
#include "Moderador.h"
#include "Palabra.h"
#include "IPalabra.h"
#include "Mensaje.h"
#include "Enums.h"

using namespace std;

// variables globales
shared_ptr<Usuario> usuarioActual;
map<string, shared_ptr<Usuario>> usuarios;

// declaración de funciones de la aplicación
void ejecutar();
map<string, shared_ptr<Usuario>> inicializarDatos();
void mostrarMenu();
void login(const map<string, shared_ptr<Usuario>>& usuarios);
void cambiarRelacion();
void modificarPublicacion();
void enviarMensaje();
void gestionarOpciones();
vector<shared_ptr<IPalabra>> leerSecuenciaPalabra();

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

// función que gestiona la selección de opciones del menú
void gestionarOpciones(){
    int opcion;
    do{
        cout << "Introduce una opción (4 para mostrar menú): ";
        cin >> opcion;

        if(opcion==0){
            cout << "Finalizando programa..." << endl;
        }
        else if(opcion==1){
            enviarMensaje();
        }
        else if(opcion==2){
            modificarPublicacion();
        }
        else if(opcion==3){
            cambiarRelacion();
        }
        else if(opcion==4){
            mostrarMenu();
        }
        else{
            cout << "Opción no válida" << endl;
        }
    }while(opcion != 0);
}

// función para gestionar la interacción con el usuario en la opción 1
void enviarMensaje(){
    string destinatario;
    cout << "Introduce el nombre del destinatario: ";
    getline(cin, destinatario);

    // comprobar si existe el usuario
    auto it = usuarios.find(destinatario);
    if(it==usuarios.end()){
        cout << "Error: Usuario no encontrado" << endl;
        return;
    }

    cout << "Introduce el mensaje. Cada palabra será procesada indivudualmente." << endl;
    auto palabras = leerSecuenciaPalabra();

    usuarioActual->enviarMensaje(destinatario, palabras);
    cout << "Mensaje enviado correctamente" << endl;
}

// función para gestionar la interacción con el usuario en la opción 2
void modificarPublicacion(){
    string nombreUsuario;
    size_t pubIndex;

    // si el usuario es un moderador, pedirle el usuario del cual quiere modificar la publicación
    auto moderador = dynamic_pointer_cast<Moderador>(usuarioActual);
    if(moderador){
        cout << "Introduce el nombre del usuario cuya publicación quieres modificar: ";
        getline(cin, nombreUsuario);

        auto it = usuarios.find(nombreUsuario);
        if(it==usuarios.end()){
            cout << "Error: Usuario no encontrado" << endl;
            return;
        }
    }

    // mostrar las publicaciones disponibles
    const auto& publicaciones = moderador ?
        usuarios[nombreUsuario]->obtPublicaciones() : // si es moderador, mostrar las publicaciones del usuario indicado
        usuarioActual->obtPublicaciones(); // si no es moderador, mostrar las publicaciones del usuario actual

    cout << "Publicaciones disponibles: " << endl;
    for(size_t i=0; i<publicaciones.size(); i++){
        cout << i << ". " << publicaciones[i]->contenido() << endl;
    }

    cout << "Introduce el índice de la publicación a modificar: ";
    cin >> pubIndex;
    cin.ignore();

    cout << "Introduce el nuevo contenido. Cada palabra será procesada individualmente." << endl;
    auto nuevaPub = leerSecuenciaPalabras();

    // editar la publicación y mostrar mensaje de confirmación
    bool exito;
    if(moderador){
        exito = moderador->editarPublicacion(pubIndex, nuevaPub, *usuarios[nombreUsuario]);
    }
    else{
        exito = usuarioActual->editarPublicacion(pubIndex, nuevaPub); //
    }

    if(exito){
        cout << "Publicación modificada correctamente." << endl;
    }
    else{
        cout << "Error al modificar la publicación" << endl;
    }
}

// función para gestionar la interacción con el usuario en la opción 3
void cambiarRelacion(){
    string nombreUsuario;
    cout << "";
}

// función que ejecuta el programa. lee los datos de los usuarios del archivo de entrada, gestiona el inicio de sesión, y gestiona las opciones de menú
void ejecutar(){
    map<string, shared_ptr<Usuario>> usuarios = inicializarDatos();

    login(usuarios);

    mostrarMenu();

    gestionarOpciones();
}

void mostrarMenu(){
    cout << "OPCIONES:" << endl;
    cout << "0. Finalizar el programa" << endl;
    cout << "1. Enviar mensaje a un usuario" << endl;
    cout << "2. Modificar una publicación" << endl;
    cout << "3. Establecer una relación con un usuario" << endl;
    cout << "4. Mostrar menú" << endl;
    cout << endl;
}

// función para inicializar datos de usuarios de la aplicación a partir del nombre y la contraseña. Devuelve un map con los usuarios creados
map<string, shared_ptr<Usuario>> inicializarDatos(){
    map<string, shared_ptr<Usuario>> usuarios;

    // usuarios normales
    usuarios["gemmaReina"] = make_shared<Usuario>("gemmaReina", "contrasenyaImposibleDeAdivinar");
    usuarios["fedeDiaz"] = make_shared<Usuario>("fedeDiaz", "noSeQuePoner.!#    ");
    usuarios["cHodoroga"] = make_shared<Usuario("cHodoroga", "password123");

    // usuarios moderadores
    usuarios["jordiRegincos"] = make_shared<Moderador>("jordiRegincos", "elsPatronsGraspMolan");

    // relaciones iniciales
    usuarios["gemmaReina"]->establecerRelacion("fedeDiaz", TipoRelacion::AMIGO);
    usuarios["fedeDiaz"]->establecerRelacion("gemmaReina", TipoRelacion::AMIGO);
    usuarios["cHodoroga"]->establecerRelacion("fedeDiaz", TipoRelacion::SALUDADO);

    return usuarios;
}

bool verificarPassword(const string& pwd, const string& nombre, const map<string, shared_ptr<Usuario>>& usuarios){
    auto it = usuarios.find(nombre);
    if(it != usuarios.end() && it->second == pwd){
        usuarioActual = it->second;
        return true; // contraseña correcta
    }
    return false; // contraseña incorrecta
}

// función para iniciar sesión; pide al usuario su nombre de usuario y contraseña, y comprueba si existen en la base de datos
void login(const map<string, shared_ptr<Usuario>>& usuarios){
    string nombre, pwd;
    cout << "Usuario: ";
    cin >> nombre;
    cout << "Contraseña: ";
    cin >> pwd;

    char retry = 'N';

    if(verificarPassword(pwd, nombre, usuarios) == false){
        do{
            cout << "Contraseña incorrecta. ¿Desea volver a intentarlo? (S/N)" << endl;
            cin >> retry;

            if(retry == 'N'){
                cout << "Inicio de sesión fallido" << endl;
                break;
            }

            cout << "Contraseña: ";
            cin >> pwd;

        }while(verificarPassword(pwd, nombre, usuarios) == false && retry=='S');
    }
}
