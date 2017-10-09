#ifndef LOADWINDOW_H
#define LOADWINDOW_H

#include <form.h>
#include <ncurses.h>

typedef struct loadWindow LoadWindow;

struct loadWindow {

	char* mapName;

	WINDOW* window;	
	FIELD** fields;
	FORM* formLoading;

	int x;
	int y;
	int width;
	int height;
};

LoadWindow createLoadWindow(int maxX, int maxY);
void freeLoadWindow(LoadWindow lw);
void drawLoadWindow(LoadWindow* lw);
void popupWindowLoading(LoadWindow* lw);
char* trimwhitespace(char* str);

#endif
