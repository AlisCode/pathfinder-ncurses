#ifndef MENUEDITION_H
#define MENUEDITION_H

#include <ncurses.h>

typedef struct menuEdition MenuEdition;

struct menuEdition {
	WINDOW* window;
	int visible;
	int validatedOption;
	int chosenOption;
};

MenuEdition createMenuEdition(int maxX, int maxY);
void drawMenuEdition(MenuEdition* me);
void updateMenuEdition(MenuEdition* me);

#endif
