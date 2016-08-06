test: my_prog

my_prog: main.o
	gcc main.o `pkg-config --libs sqlite3` -o$@

main.o: main.c
	gcc -c main.c `pkg-config --cflags sqlite3` -o$@

clean:
	/bin/rm config.sql main.o
