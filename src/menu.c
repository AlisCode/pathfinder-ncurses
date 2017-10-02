#include "menu.h"
#include <ncurses.h>
#include <stdio.h>

char* options[5] = {
	"edit",
	"save",
	"load",
	"resolve",
	"quit"
};

// Fonction permettant de créer le menu et sa fenêtre associée
Menu createMenu(int maxX, int maxY) {
	Menu m;

	m.visible = 0;
	m.window = newwin(3, maxX, maxY-3, 0);
	m.chosenOption = 0;
	m.validatedOption = -1;

	return m;
}

// Affiche ou désaffiche le menu
void toggleMenu(Menu* m) {
	if(m->visible == 1) { m->visible = 0; }
	else { m->visible = 1; displayMenu(m); }	
}

// Affiche le menu s'il est visible
void displayMenu(Menu* m) {
	while(m->visible == 1) {

		// Affiche les bords du menu
		box(m->window, 0, 0);
				
		// Dessine les options
		int i;
		wmove(m->window, 1, 1);
		for(i = 0 ; i < 5 ; i++) {
			if(i == m->chosenOption) {
				wattron(m->window, A_REVERSE);
			}
			wprintw(m->window, options[i]);
			wattroff(m->window, A_REVERSE);
			wprintw(m->window, " ");
		}

		// Refresh pour afficher la fenêtre
		wrefresh(m->window);

		// Prend en compte l'entrée utilisateur
		keypad(m->window, TRUE);
		int choice = wgetch(m->window);
		keypad(m->window, FALSE);
		switch(choice) {
			case KEY_LEFT:
				m->chosenOption--;
				if(m->chosenOption < 0) { m->chosenOption = 4; } 
				break;
			case KEY_RIGHT:
				m->chosenOption++;
				if(m->chosenOption > 4) { m->chosenOption = 0; }
				break;
			case 'm':
				toggleMenu(m);
				break;
			case 27:
				toggleMenu(m);
				break;
			case 10:
				m->validatedOption = m->chosenOption;
				toggleMenu(m);
				break;
			default:
				break;
		}	
	}	
}

void deleteMenu(Menu m) {
	delwin(m.window);
}
