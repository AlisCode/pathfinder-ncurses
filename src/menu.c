#include "menu.h"
#include <ncurses.h>

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
	m.window = newwin(3, maxX, 0, 0);
	m.validatedOption = 0;

	return m;
}

// Affiche ou désaffiche le menu
void toggleMenu(Menu* m) {
	if(m->visible == 1) { m->visible = 0; }
	else { m->visible = 1; }	
}

// Affiche le menu s'il est visible
void displayMenu(Menu* m) {
	if(m->visible == 1) {

		// Affichage les bords du menu
		box(&m->window, 0, 0);
		keypad(&m->window, true);
		wrefresh(&m->window);

		// Affiche les options
		int i;
		wmove(&m->window, 1, 1);
		for(i = 0 ; i < 5 ; i++) {
			if(i == chosenOption) {
				wattron(&m->window, A_REVERSE);
			}
			wprintw(&m->window, options[i]);
			wattroff(&m->window, A_REVERSE);
			wprintw(&m->window, " ");
		}
		wrefresh(&m->window);
		int choice = wgetch(&m->window);
		switch(choice) {
			case KEY_LEFT:
				chosenOption--;
				if(chosenOption < 0) { chosenOption = 4; } 
				break;
			case KEY_RIGHT:
				chosenOption++;
				if(chosenOption > 4) { chosenOption = 0; }
				break;
			case 27:
				toggleMenu(&m);
				break;
			default:
				break;
		}

		if(choice == 10) {
			// Le choix a été fait	
			m->validatedOption = chosenOption;
		}	
	}
	else {
		keypad(&m->window, false);
	}
}

void deleteMenu(Menu m) {
	delwin(&m.window);
}
