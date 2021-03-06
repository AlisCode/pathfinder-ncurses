CFLAGS = -Wall -Wextra -g
LDLIBS = -L/lib/x86_64-linux-gnu/ -lform -lncurses -lm

all: src/main

src/main: src/main.o src/casemap.o src/map.o src/pathfindermath.o src/menu.o src/mapwindow.o src/menuedition.o src/pathfindingnode.o src/pathfinding.o src/stateview.o src/loadwindow.o
src/main.o:src/main.c src/map.h src/casemap.h src/menu.h src/mapwindow.h src/pathfinding.h src/stateview.h src/loadwindow.h
src/pathfindermath.o: src/pathfindermath.c src/pathfindermath.h src/pathfindingnode.h
src/map.o: src/map.c src/map.h
src/casemap.o: src/casemap.c src/casemap.h
src/menu.o: src/menu.c src/menu.h
src/mapwindow.o: src/mapwindow.c src/mapwindow.h src/map.h src/menuedition.h src/stateview.h
src/menuedition.o: src/menuedition.c src/menuedition.h
src/pathfindingnode.o: src/pathfindingnode.c src/pathfindingnode.h src/pathfindermath.h
src/pathfinding.o: src/pathfinding.c src/pathfinding.h src/map.h src/pathfindingnode.h src/pathfindermath.h src/stateview.h
src/stateview.o: src/stateview.c src/stateview.h
src/loadwindow.o: src/loadwindow.c src/loadwindow.h

clean:
	rm -rf src/main src/*.o out
