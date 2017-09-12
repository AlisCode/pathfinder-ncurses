#ifndef MAPWINDOW_H
#define MAPWINDOW_H

#include <ncurses.h>
#include "map.h"
#include "menuedition.h"

typedef struct mapWindow MapWindow;

struct mapWindow {
	WINDOW* window;
	MenuEdition menuEdition;
	Map map;
	int editMode;
	int cursorX;
	int cursorY;
	int flagChosen;
};

MapWindow createMapWindow(int maxX, int maxY);
void replaceMap(MapWindow* mw, Map m);
void switchToEditMode(MapWindow* mw);
void drawMapWindow(MapWindow* mw);
void updateMapWindow(MapWindow* mw);

#endif
