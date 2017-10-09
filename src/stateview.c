#include "stateview.h"
#include <ncurses.h>

// Crée la StateView
StateView createStateView(int maxX) {
	
	StateView sv;

	sv.w = (maxX * 7)/10;
	sv.h = 3;
	sv.x = maxX/2 - sv.w/2;
	sv.y = 0;

	sv.window = newwin(
		sv.h,
		sv.w,
		sv.y,
		sv.x	
	);	

	fprintf(stderr, "fenetre crée ! %d %d %d %d", sv.h, sv.w, sv.y, sv.x);
	return sv;
}

// Change le texte présent dans la stateView
void updateStateView(StateView* sv, char* newText) {

	// Détermine la taille du texte pour le centrer de façon adéquate
	int length = 0;
	int i = 0;
	
	for(i = 0; newText[i] != '\0'; i++);	
	length = i;
	
	int xText = sv->w/2 - length/2;
	sv->xText = xText;	
	sv->text = newText;

	// Si le texte est trop long, on affiche '...' à la fin
	if(length > sv->w) {
		sv->text[sv->w-3] = '.';
		sv->text[sv->w-2] = '.';
		sv->text[sv->w-1] = '.';
		sv->text[sv->w] = '\0';
		for(i = 0 ; i < length ; i++) { 
			sv->text[i] = '\0';
		}
	}
	
	displayState(*sv);
}

// Affiche la nouvelle stateView
void displayState(StateView sv) {
	wclear(sv.window);
	box(sv.window, 0 , 0);
	mvwprintw(sv.window, 1, sv.xText, sv.text);
	wrefresh(sv.window);
}
