SVR_OBJECT_FILES = Server_Main.o Funciones.o
CLT_OBJECT_FILES = Cliente.o

LDFLAGS = -Wall
CFLAGS = -o -Wall 
CC = gcc 


all: client/clt server/svr
client/clt: $(CLT_OBJECT_FILES) 
server/svr: $(SVR_OBJECT_FILES)


$(CC) -o $@ $(SVR_OBJECT_FILES) $(CLT_OBJECT_FILES) $(LDFLAGS)



%.o: %.c Makefile
$(CC) $(CFLAGS) $< -o $@ 




clean: 
     rm -f *.o 
     rm -f SVR_OBJECT_FILES CLT_OBJECT_FILES
