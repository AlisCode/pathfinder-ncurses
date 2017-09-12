#ifndef MENU_H
#define MENU_H
#include <ncurses.h>

typedef struct menu Menu;

struct menu {
	WINDOW* window;
	int visible;
	int validatedOption;
	int chosenOption;
};

Menu createMenu(int maxX, int maxY);
void displayMenu(Menu* m);
void toggleMenu(Menu* m);
void deleteMenu(Menu m);
#endif
