#include <stdio.h>
#include <ncurses.h>
#include "casemap.h"
#include "map.h"
#include "menu.h"

int main(void) {

	int maxX = 0;
	int maxY = 0;

	initscr();
	noecho();
	curs_set(FALSE);
	getmaxyx(stdscr, maxY, maxX);

	Map map = createMap("test.map", 10, 10);
	changeFlag(&map, 5, 5, VIDE);
	changeFlag(&map, 5, 6, VIDE);
	changeFlag(&map, 5, 7, VIDE);
	changeFlag(&map, 4, 2, VIDE);
	changeFlag(&map, 1, 1, VIDE);
	
	Menu menu = createMenu(maxX, maxY);

	int running = 1;
	while(running == 1) {
		clear();
		displayMap(map);
		displayMenu(&menu);
		refresh();

		int userInput = getch();

		switch(userInput) {
			case 27:
				toggleMenu(&menu);
				break;
			case 'q':	
				running = 0;
				break;
			case 's':
				saveMap(map);
				break;
			case 'o':	
				map = loadMap("test.map");
				break;
			default: 
				fprintf(stderr, "unhandled %d", userInput);	
				break;	
		} 

	}
	
	// Quitte le programme de façon propre
	deleteMenu(menu);
	endwin();	
	freeMap(&map);

	return 0;
}
