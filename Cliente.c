#include "Header.h"


int main (void)
{
  	char server_data[256];
  	char user[20];
  	char password[20];
  	char producto[100];
  	int connection_status;
  	int user_input = 1;
  	int test;
  	int input;
  	int ret;
  	float precio_producto;
  	long int stock_producto;
  	item product;

	///////CREAR SOCKET/////
	network_socket = socket(AF_INET, SOCK_STREAM, 0);


	///////ESPECIFICAR DIRECCION///////
	struct sockaddr_in server_address;
	server_address.sin_family = AF_INET;
	server_address.sin_port = htons(9002);
	server_address.sin_addr.s_addr = INADDR_ANY;


	///////CONECTAR AL SERVIDOR//////
	connection_status = connect(network_socket, (struct sockaddr*) &server_address, sizeof(server_address));
	if (connection_status == -1)
	{
		printf("ERROR\n");
	}


	///////SI EL SERVIDOR ACEPTA NUESTRA CONEXION PROCEDEMOS A ENVIAR/RECIBIR DATA///////

	////////RECIBIMOS INSTRUCCIONES DEL SERVIDOR////////
	recv(network_socket, &server_data, sizeof(server_data), 0);

	printf("Bienvenido!\n");

	while (1)
	{
		printf("%s\n",server_data);
		scanf("%d",&user_input);
		send(network_socket, &user_input, sizeof(user_input), 0);

		if (user_input == 0)
		{
			break;
		}


		///////INGRESAMOS USUARIO Y CONTRASEÑA PARA LOGUEARNOS O PARA CREAR UN NUEVO USUARIO///////	
		printf("Ingrese usuario y luego contraseña\n");
		scanf("%s",user);
		scanf("%s",password);
		send(network_socket, user, sizeof(user), 0);
		send(network_socket, password, sizeof(password), 0);


		///////SEGUN LO QUE HAYAMOS SELECCIONADO, EL SERVIDOR NOS DIRA SI NUESTRO LOGUEO O CREACION DE USUARIO FUE VALIDO O NO///////
		recv(network_socket, &test, sizeof(test), 0);
		input = 1;

		if (user_input == 1)
		{
			switch (test)
			{
				//////SI EL LOGUEO FUE VALIDO//////
				case 1:
				printf("Hola %s!\n\n",user);
				printf("1. Buscar producto\n0. Salir\n\n");
				scanf("%d",&input);
				send(network_socket, &input, sizeof(input), 0);
				while (input != 0)
				{
					if (input == 1)
					{
						printf("Que producto desea buscar?\n\n");
						scanf("%s",producto);			////////////PROBLEMA FUNCION FGETS/////////////
						send(network_socket, producto, sizeof(producto), 0);
						recv(network_socket, &(product.Nombre), sizeof(char[50]), 0);
						recv(network_socket, &(product.Precio), sizeof(float), 0);
						recv(network_socket, &(product.Stock), sizeof(long int), 0);

						if (product.Precio == 0.0)
						{
							printf("Producto no encontrado\n\n");
						}
						else
						{
							printf("Producto: %s\n",product.Nombre);
							printf("Precio: %f\n",product.Precio);
							printf("Stock: %ld\n\n",product.Stock);
						}
					}
					printf("1. Buscar producto\n0. Salir\n\n");
					scanf("%d",&input);
					send(network_socket, &input, sizeof(input), 0);
				}
				break;

				///////EL LOGUEO NO FUE VALIDO//////
				case 0:
				printf("ERROR: usuario o contraseña invalida\n");
				break;
			}
		}

		if (user_input == 2)
		{
			switch (test)
			{
				case 1:
				printf("Registrado correctamente!\n");
				break;

				case 0:
				printf("El nombre de usuario ingresado no se encuentra disponible\n");
				break;

				case -1:
				printf("La contraseña debe contener al menos una mayuscula, un numero y tener entre 6 y 20 caracteres\n");
				break;
			}
		}

		if (user_input == 3)
		{
			switch (test)
			{
				case 1:
				printf("Hola %s!\n",user);
				printf("1. Agregar producto\n2. Modificar producto\n3. Eliminar producto\n0. Salir\n\n");
				scanf("%d",&input);
				send(network_socket, &input, sizeof(input), 0);
				while(input != 0)
				{
					if (input == 1)
					{
						printf("Ingrese nombre del producto\n");
						scanf("%s",producto);
						printf("Ingrese el precio\n");
						scanf("%f",&precio_producto);
						printf("Ingrese stock disponible\n");
						scanf("%ld",&stock_producto);
						send(network_socket, producto, sizeof(producto), 0);
						send(network_socket, &precio_producto, sizeof(float), 0);
						send(network_socket, &stock_producto, sizeof(long int), 0);
						recv(network_socket, &ret, sizeof(int), 0);
						if (ret == 1)
						{
							printf("Producto agregado correctamente\n");
						}
					}

					if (input == 2)
					{
						printf("Ingrese nombre del producto\n");
						scanf("%s",producto);
						printf("Ingrese precio, si no desea mofidicar este campo simplemente ingrese 0\n");
						scanf("%f",&precio_producto);
						printf("Ingrese stock, si no desea mofidicar este campo simplemente ingrese 0\n");
						scanf("%ld",&stock_producto);
						send(network_socket, producto, sizeof(producto), 0);
						send(network_socket, &precio_producto, sizeof(float), 0);
						send(network_socket, &stock_producto, sizeof(long int), 0);
						recv(network_socket, &ret, sizeof(int), 0);
						if (ret == 1)
						{
							printf("Modificado correctamente\n");
						}
						else
						{
							printf("Producto no encontrado\n");
						}
					}

					if (input == 3)
					{
						printf("Ingrese el nombre del producto que desea eliminar del listado\n");
						scanf("%s",producto);
						send(network_socket, producto, sizeof(producto), 0);
						recv(network_socket, &ret, sizeof(ret), 0);
						if (ret == 1)
						{
							printf("El producto fue eliminado\n");
						}
						else
						{
							printf("El producto ingresado no se encuentra en el listado\n");
						}
					}
					printf("1. Agregar producto\n2. Modificar producto\n3. Eliminar producto\n0. Salir\n\n");
					scanf("%d",&input);
					send(network_socket, &input, sizeof(input), 0);
				}
				break;

				case 0:
				printf("ERROR: usuario o contraseña invalida\n");
				break;
			}
		}
	}


		return 0;
}
