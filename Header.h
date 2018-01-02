#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <netinet/in.h>

#include <unistd.h>



/**
 * estructura con los atributos principales del producto
 * sera declarada como "item"
 */
typedef struct Producto 
{
	char Nombre[50];	/**< Nombre del producto */
	float Precio;	    /**< Precio del producto */
	long int Stock;		/**< stock disponible */
}item;



/**
 * estructura para el manejo de una lista simplemente enlazada
 */
typedef struct Node
{
	item prod_list;		/**< Se incluyen los atributos del producto dentro de los nodos */
	struct Node *next;	/**< Nodo que apunta hacia la siguiente direccion de memoria */
}nodo;



/**
 * Logueo de usuario
 * @param u: contiene el nombre de usuario
 * @param p: contiene la contraseña
 * @param flag: 1. usuario  2. admin
 * @return: 1. encontro usuario  0. no encontro usuario
 */

int Log_In (char*,char*,int);




/**
 * Crear nuevo usuario (no administrador)
 * @param u: nombre de usuario elegido
 * @param p: contraseña
 * @return: 0. El usuario ya existe
 * 		   -1. La clave tiene memos de 6 caracteres o no tiene letra mayuscula y algun numero
 * 			1. Usuario creado
 */

int Create_User (char*,char*);




/**
 * Compara dos strings
 * @param s1: primer string a comparar
 * @param s2: segunda string a comparar
 * @return: 1.Iguales
 * 			0.Distintas
 */
int String_Compare (char*,char*);





/**
 * Tamaño de string
 * @param str: string
 * @return: el tamaño de la string
 */
int String_Lenght (char*);





/**
 * Copiar string en otra string
 * @param Str_Inicio: string a copiar
 * @param Str_Destino: buffer donde se copiara string Inicio
 */
void String_Copy (char* Str_Inicio,char *Str_Destino);





/**
 * Busca un producto por nombre en el archivo de listado de productos
 * @param nombre: nombre del producto
 * @return: devuelve el precio y el stock disponible del prodcuto dentro de una estructura del tipo "item"
 */
item* Buscar_Producto(char*);




/**
 * Agregar nuevo producto al archivo de listado de productos
 * @param nombre: nombre del nuevo producto
 * @param precio: precio
 * @param stock: stock disponible
 * @return: 1.Se agrego el producto
 */
int Agregar_Producto (char*,float,long int);





/**
 * Modifica el precio o el stock de un producto en el archivo de listado de productos
 * @param nombre: nombre del producto a modificar
 * @param precio: nuevo precio
 * @param stock: nuevo stock
 * @return: 1.Se modifico
 * 			0.Error, no existe el producto
 */

int Modificar_Producto (char*,float,long int);





/**
 * Elimina un producto del archivo de listado de productos
 * @param nombre: nombre del producto a eliminar
 * @return: 1.Se eliminó
 */
int Eliminar_Producto (char*);





/**
 * Crear nuevo nodo de una lista simplemente enlazada
 * @param auxiliar: direccion de comienzo de la lista
 */

void Nuevo_Nodo (nodo*);
