El proyecto implementa los 3 casos de uso pedidos en la práctica.

Las opciones disponibles en la aplicación después de iniciar sesión son:
1. Enviar mensaje privado
	Permite enviar un mensaje a otro usuario ingresandose palabra por palabra.
2. Modificar una publicación
	Permite editar una publicación existente y, si el usuario es moderador, puede editar publicaciones de otros usuarios.
	Se selecciona la publicación por su índice y se introduce el nuevo contenido.
3. Establecer una relacion con otro usuario
	Permite modificar la relación con otro usuario.
4. Mostrar el menu.
0. Salir.

Se han definido 2 juegos de pruebas para verificar el correcto funcionamiento.
Uno representa un usuario normal (gemmaReina.txt) y el otro un moderador (jordiRegincos.txt).

Para compilar el programa es necesario especificar la ubicación de los archivos mediante:
-----
g++ -c -Iinclude main.cpp src/*.cpp
g++ -o hatebuck *.o
-----