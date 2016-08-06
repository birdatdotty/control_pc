#test: main.c config.h
#	gcc main.c `pkg-config --libs --cflags openssl` -o$@

all: client

client: configure_context.o main.o create_socket.o create_context.o verify_callback.o
	gcc -g configure_context.o main.o create_socket.o create_context.o verify_callback.o `pkg-config --libs openssl` -o$@ -std=c99

configure_context.o: configure_context.c
	gcc -c -g configure_context.c `pkg-config --cflags openssl` -o$@ -std=c99

main.o: main.c config.h
	gcc -c -g main.c `pkg-config --cflags openssl` -o$@ -std=c99

create_socket.o: create_socket.c
	gcc -c -g create_socket.c `pkg-config --cflags openssl` -o$@ -std=c99

create_context.o: create_context.c
	gcc -c -g create_context.c `pkg-config --cflags openssl` -o$@ -std=c99

verify_callback.o: verify_callback.c
	gcc -c -g verify_callback.c `pkg-config --cflags openssl` -o$@ -std=c99
