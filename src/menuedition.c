#include "menuedition.h"
#include "casemap.h"
#include <ncurses.h>

// Longueur et largeur du menu
#define MENUEDITION_WIDTH 15
#define MENUEDITION_HEIGHT 8

// Tableau contenant les cases plaçables par l'utilisateur
char* optionsEdition[4] = {
	"Mur     X",
	"Vide    .",
	"Depart  D",
	"Arrivee A"
};

// Crée le menu d'édition, et le centre
MenuEdition createMenuEdition(int maxX, int maxY) {
	
	MenuEdition me;

	me.window = newwin(
		MENUEDITION_HEIGHT,
		MENUEDITION_WIDTH,
		maxY/2 - MENUEDITION_HEIGHT/2,
		maxX/2 - MENUEDITION_WIDTH/2
	);
	
	me.visible = 0;
	me.chosenOption = 0;
	me.validatedOption = -1;

	return me;
}

// Affiche la fenêtre du menu d'édition
void drawMenuEdition(MenuEdition* me) {
	wclear(me->window);
	box(me->window, 0, 0);	

	// Affiche les options	
	int i;
	for(i = 0 ; i < 4 ; i++) {
		// L'option qui est choisie est highlightée
		if(i == me->chosenOption) {
			wattron(me->window, A_REVERSE);
		}		
		mvwprintw(me->window, i+1, 1, optionsEdition[i]);
		wattroff(me->window, A_REVERSE);	
	}

	wrefresh(me->window);
}

// Met à jour le menu d'édition (en fonction des input utilisateur)
void updateMenuEdition(MenuEdition* me) {
	
	while(me->visible == 1) {
		keypad(me->window, TRUE);
		int choice = wgetch(me->window);
		keypad(me->window, FALSE);
		
		switch(choice) {
			case KEY_UP:
				me->chosenOption--;
				if(me->chosenOption < 0) { me->chosenOption = 3; }
				break;
			case KEY_DOWN:
				me->chosenOption++;
				if(me->chosenOption >= 4) { me->chosenOption = 0; }
				break;
			case 27:
				// Appui sur ESC
				me->visible = 0;
				break;
			case 10:
				// Appui sur entrée
				me->validatedOption = me->chosenOption;
				me->visible = 0;	
				break;
			default: 
				break;
		}

		
		drawMenuEdition(me);
	}	
}
