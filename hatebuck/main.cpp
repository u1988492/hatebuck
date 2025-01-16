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
#include "PublicacionBase.h"

using namespace std;

// variables globales
shared_ptr<Usuario> usuarioActual;
map<string, shared_ptr<Usuario>> usuarios;

// declaración de funciones de la aplicación
void ejecutar();
void mostrarMenu();
void login(const map<string, shared_ptr<Usuario>>& usuarios);
void cambiarRelacion();
void modificarPublicacion();
void enviarMensaje();
void gestionarOpciones();
void procesarArchivoEntrada(map<string, shared_ptr<Usuario>>& usuarios);
void procesarPublicaciones(const string& linea, map<string, shared_ptr<Usuario>>& usuarios, ifstream& fin);
vector<shared_ptr<IPalabra>> leerSecuenciaPalabras();
shared_ptr<IPalabra> leerPalabra(const string& entrada);
vector<string> tokens(const string &s, char separador, bool cometes);
string token(const string &s, char separador, bool cometes, long &primer, long &ultim);

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
    cin.ignore();
    getline(cin, destinatario);

    // comprobar si existe el usuario
    auto it = usuarios.find(destinatario);
    if(it==usuarios.end()){
        cout << "Error: Usuario no encontrado" << endl;
        return;
    }

    cout << "Introduce el mensaje. Cada palabra será procesada indivudualmente." << endl;
    auto palabras = leerSecuenciaPalabras();

    usuarioActual->enviarMensaje(destinatario, palabras);
    cout << "Mensaje enviado correctamente" << endl;
}

// función para gestionar la interacción con el usuario en la opción 2
void modificarPublicacion(){
    string nombreUsuario;
    size_t pubIndex;
    shared_ptr<Usuario> usuarioTarget = usuarioActual;

    // si el usuario es un moderador, pedirle el usuario del cual quiere modificar la publicación
    auto moderador = dynamic_pointer_cast<Moderador>(usuarioActual);
    if(moderador){
        cout << "Introduce el nombre del usuario cuya publicación quieres modificar: ";
        cin.ignore();
        getline(cin, nombreUsuario);

        auto it = usuarios.find(nombreUsuario);
        if(it==usuarios.end()){
            cout << "Error: Usuario no encontrado" << endl;
            return;
        }
        usuarioTarget = it->second; // modificar la publicación del usuario seleccionado
    }

    // mostrar las publicaciones disponibles
    const auto& publicaciones = usuarioTarget->obtPublicaciones();
    // si es moderador, mostrar las publicaciones del usuario indicado
    // si no es moderador, mostrar las publicaciones del usuario actual

    if(publicaciones.empty()){
        cout << "No hay publicaciones disponibles" << endl;
        return;
    }

    cout << "Publicaciones disponibles: " << endl;
    for(size_t i=0; i<publicaciones.size(); i++){
        cout << i+1 << ". " << publicaciones[i]->contenido() << endl;
    }

    cout << "Introduce el índice de la publicación a modificar: ";
    cin >> pubIndex;
    cin.ignore();

    cout << "Introduce el nuevo contenido. Cada palabra será procesada individualmente." << endl;
    auto nuevaPub = leerSecuenciaPalabras();

    // editar la publicación y mostrar mensaje de confirmación
    bool exito;
    if(moderador){
        exito = moderador->editarPublicacion(pubIndex-1, nuevaPub, *usuarios[nombreUsuario]);
    }
    else{
        exito = usuarioActual->editarPublicacion(pubIndex-1, nuevaPub);
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
    int tipoRel;

    cout << "Introduce el nombre del usuario con el que deseas establecer una nueva relación: ";
    cin.ignore();
    getline(cin, nombreUsuario);

    // Verificar que el usuario existe
    auto it = usuarios.find(nombreUsuario);
    if(it == usuarios.end()){
        cout << "Error: Usuario no encontrado." << endl;
        return;
    }

    // Mostrar opciones de relación
    cout << "Selecciona el tipo de relación: \n"
         << "1. Saludado\n"
         << "2. Conocido\n"
         << "3. Amigo\n"
         << "Opción: ";
    cin >> tipoRel;
    cin.ignore();

    TipoRelacion tipo;
    if(tipoRel == 1){
        tipo == TipoRelacion::SALUDADO;
    }
    else if(tipoRel == 2){
        tipo = TipoRelacion::CONOCIDO;
    }
    else if(tipoRel == 3){
        tipo = TipoRelacion::AMIGO;
    }
    else{
        cout << "Opción no válida" << endl;
        return;
    }

    // Establecer la nueva relación
    usuarioActual->establecerRelacion(nombreUsuario, tipo);
    cout << "Relación actualizada correctamente." << endl;

    // Mostrar el estado actualizado de las relaciones del usuario
    cout << "Relaciones de " << usuarioActual->obtNombre() << ":\n";
    for (const auto& rel : usuarioActual->obtenerRelaciones()) {
        cout << "- " << rel.first << ": ";
        switch (rel.second) {
            case TipoRelacion::SALUDADO: cout << "Saludado\n"; break;
            case TipoRelacion::CONOCIDO: cout << "Conocido\n"; break;
            case TipoRelacion::AMIGO: cout << "Amigo\n"; break;
        }
    }

}

// función que ejecuta el programa. lee los datos de los usuarios del archivo de entrada, gestiona el inicio de sesión, y gestiona las opciones de menú
void ejecutar(){
    procesarArchivoEntrada(usuarios);

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

bool verificarPassword(const string& pwd, const string& nombre, const map<string, shared_ptr<Usuario>>& usuarios){
    auto it = usuarios.find(nombre);
    if(it != usuarios.end() && it->second->verificarPassword(pwd)){
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
                throw runtime_error("Error: inicio de sesión fallido. Finalizando el programa.");
            }

            cout << "Contraseña: ";
            cin >> pwd;

        }while(verificarPassword(pwd, nombre, usuarios) == false && retry=='S');
    }
}

// función para leer secuencias de palabras
vector<shared_ptr<IPalabra>> leerSecuenciaPalabras(){
    vector<shared_ptr<IPalabra>> palabras;
    string entrada;

    cout << "Introduce palabras/símbolos (escribe 'FIN' para terminar): " << endl;

    while(true){
        cout << "Nueva entrada ('FIN' para terminar): ";
        getline(cin, entrada);

        if(entrada == "FIN") break;

        auto palabra = leerPalabra(entrada);
        if(palabra){
            palabras.push_back(move(palabra));
        }
    }

    return palabras;
}

// función para leer una palabra
shared_ptr<IPalabra> leerPalabra(const string& entrada){
    cout << "Tipo de entrada: " << endl;
    cout << "1. Palabra" << endl;
    cout << "2. Símbolo" << endl;
    cout << "Selección: ";

    int tipoEntrada;
    cin >> tipoEntrada;
    cin.ignore();

    // si es un símbolo
    if(tipoEntrada == 2){
        return make_shared<Simbolo>(entrada);
    }
    // si es una palabra
    else if(tipoEntrada==1){
        cout << "Tipo de palabra:" << endl;
        cout << "1. Normal" << endl;
        cout << "2. No mostrar" << endl;
        cout << "3. Reemplazar" << endl;
        cout << "Selección: ";

        int tipoPalabra;
        cin >> tipoPalabra;
        cin.ignore();

        if(tipoPalabra == 1){
            return make_shared<Palabra>(entrada, "NORMAL");
        }
        else if(tipoPalabra == 2){
            return make_shared<NoMostrar>(entrada);
        }
        else if(tipoPalabra == 3){
            cout << "Palabra de reemplazo: ";
            string reemplazo;
            getline(cin, reemplazo);
            return make_shared<Reemplazar>(entrada, reemplazo);
        }
        else{
            cout << "Opción no válida" << endl;
            return nullptr;
        }
    }

    cout << "Opción no válida" << endl;
    return nullptr;

}

// función para leer los datos de los usuarios y las publicaciones del archivo de entrada
void procesarArchivoEntrada(map<string, shared_ptr<Usuario>>& usuarios){
    // abrir archivo
    string fichero = "datos.txt";
    ifstream fin(fichero);
    if(!fin.is_open()){
        throw runtime_error("Error: El fichero [" + fichero + "] no se pudo abrir. Repasa el nombre y los permisos.");
    }
    // leer usuarios
    string linea;
    vector<string> campos;
    bool relaciones = false;
    bool publicaciones = false;

    while(getline(fin, linea)){
        if(linea.empty()) continue;

        if(linea[0] == '='){
            relaciones = true;
            continue;
        }
        else if(linea[0] == '*'){
            publicaciones = true;
            continue;
        }

        campos = tokens(linea, ' ', true);
        if(!publicaciones){
            if(!relaciones){
                // leyendo usuarios
                if(campos[2] == "m"){
                    usuarios[campos[0]] = make_shared<Moderador>(campos[0], campos[1]); // crear moderador
                }
                else{
                    usuarios[campos[0]] = make_shared<Usuario>(campos[0], campos[1]); // crear usuario normal
                }
            }else{
                // leyendo relaciones
                TipoRelacion tipo;
                if(campos[2] == "AMIGO") tipo = TipoRelacion::AMIGO;
                else if(campos[2] == "CONOCIDO") tipo = TipoRelacion::CONOCIDO;
                else tipo = TipoRelacion::SALUDADO;

                // buscar al usuario en la lista
                auto it = usuarios.find(campos[0]);
                if( it != usuarios.end()){
                    it->second->establecerRelacion(campos[1], tipo); // crear la relación leída
                }
            }

        }
        else{
            // leyendo publicaciones
            procesarPublicaciones(linea, usuarios, fin);
        }
    }
}

// función encapsulada para procesar las publicaciones del archivo de entrada
void procesarPublicaciones(const string& linea, map<string, shared_ptr<Usuario>>& usuarios, ifstream& fin){
    vector<string> campos = tokens(linea, ' ', true);

    // buscar al autor en la lista de usuarios
    string autor = campos[0];
    auto it = usuarios.find(autor);
    if(it == usuarios.end()) return;

    // leer la linea que contiene el numero de palabras de la publicacion
    string lineaNPalabras;
    if(!getline(fin, lineaNPalabras)) return;
    size_t nPalabras = stoi(lineaNPalabras);

    // vector para guardar las palabras de la publicacion
    vector<shared_ptr<IPalabra>> palabras;
    string lineaPalabra;

    for(size_t i=0; i < nPalabras; i++){
        if(!getline(fin, lineaPalabra) || lineaPalabra.empty()) break;

        auto palabraCampos = tokens(lineaPalabra, ' ', true);
        if(palabraCampos.empty()) continue;

        if(palabraCampos[0] == "S"){
            // símbolo
            palabras.push_back(make_shared<Simbolo>(palabraCampos[1]));
        }
        else if(palabraCampos[0] == "P"){
            if(palabraCampos[1] == "NORMAL"){
                palabras.push_back(make_shared<Palabra>(palabraCampos[2], "NORMAL"));
            }
            else if(palabraCampos[1]=="NOMOSTRAR"){
                palabras.push_back(make_shared<NoMostrar>(palabraCampos[2]));
            }
            else if(palabraCampos[1]=="REEMPLAZAR"){
                palabras.push_back(make_shared<Reemplazar>(palabraCampos[2], palabraCampos[3]));
            }
        }
    }
    // crear y añadir la publicación
    if(!palabras.empty()){
        auto publicacion = make_shared<PublicacionBase>(autor);
        publicacion->editarContenido(palabras);
        it->second->publicarTexto(publicacion);
    }

    // leer hasta encontrar el separador o fin de archivo
    while(getline(fin, lineaPalabra) && lineaPalabra != "---"){
        // ignorar lineas hasta encontrar separador
    }
}

// código de eines.h para leer elementos del archivo (gracias profe)

vector<string> tokens(const string &s, char separador, bool cometes) {
    vector<string> resultat;
    if (!s.empty()) {
        long primer = 0, ultim = 0;
        while (ultim != string::npos)
            resultat.push_back(token(s, separador, cometes, primer, ultim));
    }
    return resultat;
}

string token(const string &s, char separador, bool cometes, long &primer, long &ultim) {
    string t;

    if (!cometes || s[primer] != '"') { // No volem tenir en compte les " o no comença per "
        while(s[primer]==' ' && primer<s.length()) // ens  mengem els espais inicials si no hi ha cometes
            primer++;
        ultim = s.find(separador, primer);
        if (ultim == string::npos)
            t = s.substr(primer);
        else {
            t = s.substr(primer, ultim - primer);
            primer = ultim + 1; // ens mengem la ,
        }
    } else { // comença per " i les volem tenir en compte com delimitadors
        primer++;
        ultim = s.find('"', primer);
        while (s.length()>ultim+1 && s[ultim+1]=='"') {
            ultim = s.find('"', ultim+2); //saltem "" dobles seguides
        }

        if (ultim == string::npos)
            throw ("cometes no tancades");
        else {
            t = s.substr(primer, ultim - primer);
            primer = ultim + 2; // ens mengem els ",
            if (primer > s.length())
                ultim = string::npos; //era l'últim token
        }
    }
    return t;
}
