CFLAGS = -Wall -Wextra -g
LDLIBS = -L/lib/x86_64-linux-gnu/ -lncurses

all: src/main

src/main: src/main.o src/casemap.o src/map.o src/pathfindermath.o src/menu.o
src/main.o:src/main.c src/map.h src/casemap.h src/menu.h
src/pathfindermath.o: src/pathfindermath.c src/pathfindermath.h
src/map.o: src/map.c src/map.h
src/casemap.o: src/casemap.c src/casemap.h
src/menu.o: src/menu.c src/menu.h

clean:
	rm -rf src/main src/*.o
