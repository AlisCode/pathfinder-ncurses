#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <form.h>
#include "casemap.h"
#include "map.h"
#include "menu.h"
#include "mapwindow.h"
#include "pathfinding.h"
#include "stateview.h"
#include "loadwindow.h"

void actionMenu(int opt);

// Variables globales
// Si l'application est lancée ou non
int running = 0;

// Si l'on doit mettre à jour la stateview
int dontUpdateStateView = 0;

// Map "buffer" - peut être retirée (à refactoriser ...)
Map newMap;

// Fenêtres globales
MapWindow mapWindow;
StateView stateView;
LoadWindow loadWindow;

// Point d'entrée du programme
int main(int argc, char* argv[]) {
	
	// Nombre de lignes et colonnes du terminal
	int maxX = 0;
	int maxY = 0;
	
	// Initialise ncurses
	initscr();
	noecho();
	cbreak();
	curs_set(FALSE);
	getmaxyx(stdscr, maxY, maxX);
	refresh();

	// Crée la map	
	Map map;
	if(argc > 2) {
		fprintf(stderr,"Trop d'arguments donnés.\nusage: pathfinder file.map");
		exit(1);
	}
	
	if(argc == 2) {	
		map = loadMap(argv[1], &stateView);		
	} 
	else if(argc == 1) {
		map = createMap("default.map", 10, 10);
	}

	// Crée la StateView
	stateView = createStateView(maxX);

	// Initialise les couleurs
	start_color();
	init_pair(1, COLOR_BLACK, COLOR_WHITE);
	init_pair(2, COLOR_BLACK, COLOR_RED);
	init_pair(3, COLOR_BLACK, COLOR_YELLOW);
	init_pair(4, COLOR_BLACK, COLOR_GREEN);

	// Crée la fenêtre pour la map
	mapWindow = createMapWindow(maxX, maxY);
	replaceMap(&mapWindow, map);
	
	// Crée le menu
	Menu menu = createMenu(maxX, maxY);

	// Crée la LoadWindow
	loadWindow = createLoadWindow(maxX, maxY);

	// Boucle principale
	running = 1;
	while(running == 1) {
		clear();
		refresh();
		drawMapWindow(&mapWindow);
		updateMapWindow(&mapWindow, &stateView);	

		if(dontUpdateStateView == 1)
		{
			displayState(stateView);
			dontUpdateStateView = 0;
		}
		else {
			updateStateView(&stateView, "VISUAL - m to open menu");	
		}
		int userInput = getch();
		switch(userInput) {
			case 'm':
			updateStateView(&stateView, "ESC to close");
			toggleMenu(&menu);
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
	freeLoadWindow(loadWindow);

	return 0;
}

// Gère les actions du menu après choix de l'utilisateur
void actionMenu(int opt) {

	switch(opt) {
		// Edit
		case 0:
			mapWindow.editMode = 1;
			break;
		// Save	
		case 1:
			normalizeMap(&mapWindow.map);
			saveMap(mapWindow.map);
			break;
		// Load 
		case 2:
			popupWindowLoading(&loadWindow);
			newMap = loadMap(loadWindow.mapName, &stateView);
			replaceMap(&mapWindow, newMap);
			dontUpdateStateView = 1;
			break;
		// Resolve
		case 3:
			normalizeMap(&mapWindow.map);
			resolvePath(mapWindow.map, &stateView);
			dontUpdateStateView = 1;
			break;
		// Quit
		case 4:
			// Coupe la boucle pour quitter le programme proprement
			running = 0; 
			break;
	}
}
