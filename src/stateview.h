#ifndef STATEVIEW_H
#define STATEVIEW_H

#include <ncurses.h>

typedef struct stateView StateView;

struct stateView {
	WINDOW* window;
	
	char* text;
	int textLength;	
	
	int xText; 

	int x;
	int y; 
	int w;
	int h;

};

StateView createStateView(int maxX, int maxY);
void updateStateView(StateView* sv, char* newText);
void displayState(StateView sv);



#endif
