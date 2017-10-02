#include <stdio.h>
#include "mapwindow.h"
#include "stateview.h"
#include <ncurses.h>

MapWindow createMapWindow(int maxX, int maxY) {
	MapWindow mw;
	
	mw.window = newwin(maxY-3,maxX-1,2,0);
	mw.editMode = 0;
	mw.cursorX = 0;
	mw.cursorY = 0;
	mw.flagChosen = 1;
	mw.menuEdition = createMenuEdition(maxX, maxY);

	return mw;	
}

void replaceMap(MapWindow* mw, Map m) {
	mw->map = m;
}

void switchToEditMode(MapWindow* mw) {
	mw->cursorX = 1;
	mw->cursorY = 1;
	mw->editMode = 1;
	drawMapWindow(mw);
}

void switchToNormalMode(MapWindow* mw) {
	mw->cursorX = 0;
	mw->cursorY = 0;
	mw->editMode = 0;
}	

void drawMapWindow(MapWindow* mw) {
	wclear(mw->window);
	box(mw->window, 0, 0);
	displayMap(mw->map, mw->cursorX, mw->cursorY, mw->window);
	wrefresh(mw->window);
}

void updateMapWindow(MapWindow* mw, StateView* sv) {
	
	while(mw->editMode == 1) 
	{
		updateStateView(sv, "Edit Mode - e to change bloc, space to place");
		keypad(mw->window, TRUE);
		int input = wgetch(mw->window);
		keypad(mw->window, FALSE);

		switch(input) {
			case KEY_LEFT:
				mw->cursorX--;
				break;
			case KEY_RIGHT:
				mw->cursorX++;
				break;
			case KEY_UP:		
				mw->cursorY--;
				break;
			case KEY_DOWN: 
				mw->cursorY++;
				break;
			case 27:
				// Sors du mode d'édition	
				switchToNormalMode(mw);
				break;
			case 'e':	
				// Ouvre le menu pour choisir le flag de la case
				mw->menuEdition.visible = 1;
				drawMenuEdition(&mw->menuEdition);
				updateMenuEdition(&mw->menuEdition);	
				break;
			case ' ':
				// Change le flag de la case
				changeFlag(&mw->map, mw->cursorX, mw->cursorY, mw->menuEdition.validatedOption);
				break;	
			default:
				break;
		}
		
		if(mw->menuEdition.validatedOption >= 0) {
			mw->flagChosen = mw->menuEdition.validatedOption;
		}
		
	
		// Empêche le curseur de dépasser sur les bords
		if(mw->cursorX <= 0) { mw->cursorX = 1; }
		if(mw->cursorX > mw->map.width ) { mw->cursorX = mw->map.width; }
		if(mw->cursorY <= 0) { mw->cursorY = 1; }
		if(mw->cursorY > mw->map.height ) { mw->cursorY = mw->map.height; }	
		drawMapWindow(mw);
}
}
