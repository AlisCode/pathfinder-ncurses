#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "casemap.h"
#include "map.h"
#include "menu.h"
#include "mapwindow.h"
#include "pathfinding.h"

void actionMenu(int opt);

int running = 0;
MapWindow mapWindow;

int main(int argc, char* argv[]) {
	
	// Nombre de lignes et colonnes du terminal
	int maxX = 0;
	int maxY = 0;

	// Crée la map	
	Map map;
	if(argc > 2) {
		fprintf(stderr,"Trop d'arguments donnés.\nusage: pathfinder file.map");
		exit(1);
	}
	
	if(argc == 2) {	
		map = loadMap(argv[1]);		
	} 
	else if(argc == 1) {
		map = createMap("default.map", 10, 10);
	}
	
	// Initialise ncurses
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	getmaxyx(stdscr, maxY, maxX);
	refresh();
		
	// Crée la fenêtre pour la map
	mapWindow = createMapWindow(maxX, maxY);
	replaceMap(&mapWindow, map);
	
	// Crée le menu
	Menu menu = createMenu(maxX, maxY);

	// Boucle principale
	running = 1;
	while(running == 1) {
		clear();
		refresh();
		drawMapWindow(&mapWindow);
		updateMapWindow(&mapWindow);	
	
		int userInput = getch();
		switch(userInput) {
			case 'm':
				toggleMenu(&menu);
				break;
			case 'o':	
				map = loadMap("test.map");
				break;
			default: 
				// Appui sur une touche non gérée
				break;	
		}

		actionMenu(menu.validatedOption); 
		menu.validatedOption = -1;
	}
	
	// Quitte le programme de façon propre
	deleteMenu(menu);
	endwin();	
	freeMap(&map);

	return 0;
}

void actionMenu(int opt) {

	switch(opt) {
		// Edit
		case 0:
			mapWindow.editMode = 1;
			break;
		// Save	
		case 1:
			saveMap(mapWindow.map);
			break;
		// Load 
		case 2:
			break;
		// Resolve
		case 3:
			resolvePath(mapWindow.map);
			break;
		// Quit
		case 4:
			// Coupe la boucle pour quitter le programme proprement
			running = 0; 
			break;
	}
}
