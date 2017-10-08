#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <form.h>
#include <ncurses.h>

typedef struct loadWindow LoadWindow;

struct loadWindow {

	char mapName[15];

	WINDOW* window;	
	FIELD* fields[2];
	FORM* formLoading;

	int x;
	int y;
	int width;
	int height;
};

LoadWindow createLoadWindow(int maxX, int maxY);
void freeLoadWindow(LoadWindow lw);

#endif
