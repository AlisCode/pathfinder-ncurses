#include <stdio.h>
#include <ncurses.h>
#include "casemap.h"
#include "map.h"

int main(void) {

	int max_x = 0;
	int max_y = 0;

	initscr();
	noecho();
	curs_set(FALSE);
	getmaxyx(stdscr, max_y, max_x);

	Map map = createMap("test.map", 10, 10);
	changeFlag(&map, 5, 5, VIDE);
	changeFlag(&map, 5, 6, VIDE);
	changeFlag(&map, 5, 7, VIDE);
	changeFlag(&map, 4, 2, VIDE);
	changeFlag(&map, 1, 1, VIDE);
	
	int running = 1;
	while(running == 1) {
		clear();
		displayMap(map);
		refresh();

		int userInput = getch();

		switch(userInput) {
			case 27:
				running = 0;
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
	endwin();	
	freeMap(&map);

	return 0;
}
