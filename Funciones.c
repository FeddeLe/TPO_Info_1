#include "Header.h"


/**
 * logueo de usuario
 * @param u: contiene el nombre de usuario
 * @param p: contiene la contraseña
 * @param flag: 1. usurio  2. admin
 * @return: 1. encontro usuario  0. no encontro usuario
 */

int Log_In (char *u,char *p,int flag)
{
	char User[20];	/**< String para usuario */
	char Pass[20];	/**< String para contraseña */

	FILE *database;	/**< FD para el archivo */

	if (flag == 1)
	{
		database = fopen("Registered_Users","r");	/** Abre archivo "Registered_Users" en modo lectura */
	}

	if (flag == 2)
	{
		database = fopen("Registered_Admins","r");	/** Abre archivo "Registered_admins" en modo lectura */
	}



	/**
	 * Leemos el archivo que abrimos anteriormente almacenando lo leido en las variables antes declaradas
	 * Las comparamos con los parametros pasados
	 * Leemos el archivo hasta encontrar el EOF (End Of File)
	 */
	while(fscanf(database,"%s %s",User,Pass) != EOF)
	{
		if (String_Compare(u,User) == 1 && String_Compare(p,Pass) == 1)
		{
			fclose(database);
			return 1;
		}
	}

	fclose(database);
	return 0;
}



/**
 * Crear nuevo usuario (no administrador)
 * @param u: nombre de usuario elegido
 * @param p: contraseña
 * @return: 0. El usuario ya existe
 * 		   -1. La clave tiene memos de 6 caracteres o no tiene letra mayuscula y algun numero
 * 			1. Usuario creado
 */

int Create_User (char *u,char *p)
{
	int counter;	/**< variable para contador */
	int flag_upper;	/**< cantidad de mayusculas */
	int flag_lower;	/**< cantidad de minusculas */
	int flag_num;	/**< cantidad de numeros */
	counter = flag_upper = flag_lower = flag_num = 0;

	char User[20];
	char Pass[20];

	FILE *database;
	database = fopen("Registered_Users","r");	/** abrimos archivo de usuarios en modo lectura */



	/**
	 * Leemos el archivo (hasta EOF) y vamos comparando con el usuario y contraseña pasados como parametros
	 */
	while(fscanf(database,"%s %s",User,Pass) != EOF)
	{
		if (String_Compare(u,User) == 1)
		{
			fclose(database);
			return 0;
		}
	}



	/**
	 * Vemos si el string de contraseña tiene menos de 6 caracteres
	 */
	if (String_Lenght(p) < 6)
	{
		return (-1);
	}



	/**
	 * Contamos cuantas mayusculas minusculas y numeros hay en la string de contraseña parametro
	 * comparando por ASCII
	 */
	while(p[counter] != '\0')
	{
		if (p[counter] >= 'A' && p[counter] <= 'Z')
		{
			flag_upper++;
		}
		if (p[counter] >= 'a' && p[counter] <= 'z')
		{
			flag_lower++;
		}
		if (p[counter] >= '0' && p[counter] <= '9')
		{
			flag_num++;
		}
		counter++;
	}


	/**
	 * Si se encontraron mayusculas minusculas y numeros se registrara el nuevo user en el archivo
	 */
	if (flag_upper != 0 && flag_lower != 0 && flag_num != 0)
	{
		fclose(database);
		database = fopen("Registered_Users","a");
		fprintf(database,"%s\n%s\n\n",u,p);
		fclose(database);
		return 1;
	}

	else
	{
		return (-1);
	}
}



/**
 * Compara dos strings
 * @param s1: primer string a comparar
 * @param s2: segunda string a comparar
 * @return: 1.Iguales
 * 			0.Distintas
 */

int String_Compare (char *s1,char *s2)
{
    int count = 0;
    int cont = 0;


    /** "Medimos" el tamaño de la primer string parametro y luego la segunda
     * 	Sabremos primero si difieren en tamaño
     * 	Luego si coinciden en tamaño procedemos a comparar caracter por caracter
     */
    while(s1[count] != '\0')
    {
        count++;
    }

    while(s2[cont] != '\0')
    {
        cont++;
    }

    if (count != cont)
    {
        return 0;
    }

    count = 0;

    while(count < cont)
    {
        if (s1[count] != s2[count])
        {
            return 0;
        }
        count++;
    }

    return 1;
}



/**
 * Tamaño de string
 * @param str: string
 * @return: el tamaño de la string
 */

int String_Lenght(char *str)
{
	int counter = 0;


	/**
	 * Recorremos la string pasada como parametro hasta encontrar el caracter del NULL ('\0')
	 */
	while(str[counter] != '\0')
	{
		counter++;
	}

	return counter;
}




/**
 * Copiar string en otra string
 * @param Str_Inicio: string a copiar
 * @param Str_Destino: buffer donde se copiara string Inicio
 */

void String_Copy (char* Str_Inicio,char *Str_Destino)
{
	int i = 0;

	/**
	 * Copiamos caracter a caracter hasta encontrar el NULL en la string de inicio
	 */
	while (Str_Inicio[i] != '\0')
	{
		Str_Destino[i] = Str_Inicio[i];
		i++;
	}
}




/**
 * Busca un producto por nombre en el archivo de listado de productos
 * @param nombre: nombre del producto
 * @return: devuelve el precio y el stock disponible del prodcuto dentro de una estructura del tipo "item"
 */

item* Buscar_Producto (char* nombre)
{
	FILE* listado;
	item* pointer;
	char name[50];
	float precio;
	long int stock;

	pointer = (item*) malloc (sizeof(item));

	listado = fopen("Listado_Productos","r");

	while(fscanf(listado,"%s %f %ld",name,&precio,&stock) != EOF)
	{
		if (String_Compare(name,nombre) == 1)
		{
			String_Copy(name,pointer -> Nombre);
			pointer -> Precio = precio;
			pointer -> Stock = stock;
			fclose(listado);
			return pointer;
		}
	}

	fclose(listado);
	pointer -> Precio = 0.0;
	return pointer;
}





/**
 * Agregar nuevo producto al archivo de listado de productos
 * @param nombre: nombre del nuevo producto
 * @param precio: precio
 * @param stock: stock disponible
 * @return: 1.Se agrego el producto
 */

int Agregar_Producto (char* nombre,float precio,long int stock)
{
	FILE* listado;

	listado = fopen("Listado_Productos","a");

	fprintf(listado,"%s\n%f\n%ld\n",nombre,precio,stock);

	fclose(listado);

	return 1;
}





/**
 * Modifica el precio o el stock de un producto en el archivo de listado de productos
 * @param nombre: nombre del producto a modificar
 * @param precio: nuevo precio
 * @param stock: nuevo stock
 * @return: 1.Se modifico
 * 			0.Error, no existe el producto
 */

int Modificar_Producto (char* nombre,float precio, long int stock)
{
	char nom[100];
	float pre;
	long int sto;
	int tam;
	FILE* listado;

	listado = fopen("Listado_Productos","r+");

	while(fscanf(listado,"%s %f %ld",nom,&pre,&sto) != EOF)
	{
		if (String_Compare(nombre,nom) == 1)
		{
			if (precio == 0)
			{
				precio = pre;
			}
			if (stock == 0)
			{
				stock = sto;
			}

			tam = sizeof(nombre) + sizeof(precio) + sizeof(stock);
			fseek(listado,-tam,SEEK_CUR);

			fprintf(listado,"%s\n%f\n%ld\n",nombre,precio,stock);

			return 1;
		}
	}
	return 0;
}





/**
 * Elimina un producto del archivo de listado de productos
 * @param nombre: nombre del producto a eliminar
 * @return: 1.Se eliminó
 */

int Eliminar_Producto (char* nombre)
{
	FILE* listado;
	nodo *lista,*aux, *temp;
	lista = (nodo*) malloc(sizeof(nodo));
	listado = fopen("Listado_Productos","r+");
	lista -> next = NULL;
	aux = lista;
	temp = lista;

	while(fscanf(listado,"%s %f %ld",aux -> prod_list.Nombre,&aux -> prod_list.Precio,&aux -> prod_list.Stock) != EOF)
	{
		Nuevo_Nodo(aux);
		aux = aux -> next;
	}
	temp = lista;

	aux = lista;

	while(aux != NULL)
	{
		if (String_Compare(aux -> prod_list.Nombre,nombre) == 1)
		{
			temp -> next = aux -> next;
			free(aux);
			break;
		}
		temp = aux;
		aux = aux -> next;
	}

	temp = lista;
	rewind(listado);

	while(temp != NULL)
	{
		fprintf(listado,"%s\n%f\n%ld\n",temp -> prod_list.Nombre,temp -> prod_list.Precio,temp -> prod_list.Stock);
		temp = temp -> next;
	}

	free(lista);
	return 1;
}





/**
 * Crear nuevo nodo de una lista simplemente enlazada
 * @param auxiliar: direccion de comienzo de la lista
 */

void Nuevo_Nodo (nodo* auxiliar)
{
	nodo* nuevo;

	nuevo = (nodo*) malloc(sizeof(nodo));

	auxiliar -> next = nuevo;

	nuevo -> next = NULL;
}
