#include "Header.h"

int main (void)
{   
	char server_message[256] = "1. LogIn\n2. Crear usuario\n3. Admin Panel\n0. Salir\n\n";
	char user[20];
	char password[20];
	char producto[100];
	char *usr,*pass,*prod;

	int server_socket;
	int client_socket;
	int client_input;
	int test;
	int input;
	int ret;
	
	float precio_producto;

	long int stock_producto;


	item* p_producto;
	usr = user;
	pass = password;
	prod = producto;

	////////CREAR SOCKET////////
	server_socket = socket(AF_INET, SOCK_STREAM, 0);



	/////////DEFINIR DIRECCION DEL SERVIDOR//////////
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	////////ASOCIAR LA DIRECCION DIFINIDA, AL SOCKET//////////
	bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address));


	/////////ESPERAR CONEXIONES DE ADMINISTRADORES O CLIENTES/////////
	listen(server_socket,10);

	while(1)
	{

		////////ACEPTAR LA CONEXION/////////
	 	client_socket = accept(server_socket,NULL,NULL);

	 	if(!fork())
	 	{
		 	//////ENVIAR/RECIBIR DATA///////
		 	send(client_socket, server_message, sizeof(server_message), 0);
		 	recv(client_socket, &client_input, sizeof(client_input), 0);

		 	while (client_input != 0)
		 	{
			 	switch (client_input)
			 	{
			 		///////LOGUEO DE CLIENTE COMUN///////
			 		case 1:
			 		recv(client_socket, &user, sizeof(user), 0);
			 		recv(client_socket, &password, sizeof(password), 0);
			 		test = Log_In(usr,pass,1);
			 		send(client_socket, &test, sizeof(test), 0); ////test = 1 -> OK, test = 0 -> ERROR////

			 		if (test == 1)
			 		{
				 		//////SI EL LOGUEO FUE VALIDO, VEO QUE QUIERE HACER EL CLIENTE//////
				 		recv(client_socket, &input , sizeof(input), 0);
				 		while (input != 0)
				 		{
					 		if (input == 1)
					 		{
					 			recv(client_socket, producto, sizeof(producto), 0);
					 			p_producto = Buscar_Producto(prod);
					 			if (p_producto == NULL)
					 			{
					 				send(client_socket, &p_producto, sizeof(p_producto), 0);
					 			}
					 			send(client_socket, &(p_producto -> Nombre), sizeof(char[50]), 0);
					 			send(client_socket, &(p_producto -> Precio), sizeof(float), 0);
					   			send(client_socket, &(p_producto -> Stock), sizeof(long int), 0);
					 		}
					 		recv(client_socket, &input , sizeof(input), 0);
						}
					}
			 		break;

			 		///////CREACION NUEVA CUENTA CLIENTE//////
			 		case 2:
			 		recv(client_socket, &user, sizeof(user), 0);
			 		recv(client_socket, &password, sizeof(password), 0);
			 		test = Create_User(usr,pass);
			 		send(client_socket, &test, sizeof(test), 0);
			 		break;

			 		///////LOGUEO DE ADMIN///////
			 		case 3:
			 		recv(client_socket, &user, sizeof(user), 0);
			 		recv(client_socket, &password, sizeof(password), 0);
			 		test = Log_In(usr,pass,2);
			 		send(client_socket, &test, sizeof(test), 0);

			 		///////SI EL LOGUEO FUE CORRECTO///////
			 		if (test == 1)
			 		{
			 			recv(client_socket, &input, sizeof(int), 0);
			 			while(input != 0)
			 			{
			 				////////AGREGAR PRODUCTO/////////
			 				if (input == 1)
			 				{
			 					recv(client_socket, producto, sizeof(producto), 0);
			 					recv(client_socket, &precio_producto, sizeof(float), 0);
			 					recv(client_socket, &stock_producto, sizeof(long int), 0);
			 					ret = Agregar_Producto(prod,precio_producto,stock_producto);
			 					send(client_socket, &ret, sizeof(int), 0);
			 				}

			 				///////MODIFICAR PRODUCTO////////
			 				if (input == 2)
			 				{
			 					recv(client_socket, producto, sizeof(producto), 0);
			 					recv(client_socket, &precio_producto, sizeof(float), 0);
			 					recv(client_socket, &stock_producto, sizeof(long int), 0);
			 					ret = Modificar_Producto(prod,precio_producto,stock_producto);
			 					send(client_socket, &ret, sizeof(ret), 0);
			 				}

			 				///////ELIMINAR PRODUCTO////////
			 				if (input == 3)
			 				{
			 					recv(client_socket, producto, sizeof(producto), 0);
			 					ret = Eliminar_Producto(prod);
			 					send(client_socket, &ret, sizeof(ret), 0);
			 				}
			 				recv(client_socket, &input, sizeof(int), 0);
			 			}
			 		}
			 		break;
			 	}
			 	recv(client_socket, &client_input, sizeof(client_input), 0);
			 }
			 	 	//////CERRAR LA CONEXION, CERRAR EL SOCKET//////
	 	close(client_socket);
	 	exit(0);
}
}
	return 0;
}