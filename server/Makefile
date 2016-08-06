all: server

server: configure_context.o main.o create_context.o verify_callback.o cmd.o accept_conn_cb.o ssl_read_cb.o ssl_event_cb.o update_prog.o
	gcc configure_context.o main.o create_context.o verify_callback.o cmd.o accept_conn_cb.o ssl_read_cb.o ssl_event_cb.o update_prog.o `pkg-config --libs openssl libevent libevent_openssl` -o$@

configure_context.o: configure_context.c
	gcc -c configure_context.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

main.o: main.c config.h
	gcc -c main.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

#create_socket.o: create_socket.c
#	gcc -c create_socket.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

accept_conn_cb.o: accept_conn_cb.c
	gcc -c accept_conn_cb.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

create_context.o: create_context.c
	gcc -c create_context.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

verify_callback.o: verify_callback.c
	gcc -c verify_callback.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

cmd.o: cmd.c
	gcc -c cmd.c -o$@

ssl_read_cb.o: ssl_read_cb.c
	gcc -c ssl_read_cb.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

ssl_event_cb.o: ssl_event_cb.c
	gcc -c ssl_event_cb.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

update_prog.o: update_prog.c
	gcc -c update_prog.c `pkg-config --cflags openssl libevent libevent_openssl` -o$@

clean:
	/bin/rm server *.o
