#include "loadwindow.h"
#include <form.h>
#include <ncurses.h>

// Crée la fenêtre de chargement
LoadWindow createLoadWindow(int maxX, int maxY) {

	LoadWindow window;

	window.window = newwin(10,3,1,1);
	window.fields[0] = new_field(1,10, 1, 1, 0, 0);
	window.fields[1] = NULL;
	window.formLoading = new_form(window.fields);

	set_field_back(window.fields[0], A_UNDERLINE); 	
	field_opts_off(window.fields[0], O_AUTOSKIP);  
	
	return window;
}

// Affiche la fenêtre de chargement
void drawLoadWindow(LoadWindow* lw) {
	wclear(lw->window);
	box(lw->window, 0, 0);

	mvwprintw(lw->window, 1, 1, "Nom de la carte");
	wrefresh(lw->window);
}

// Lance la fenêtre pour le chargement de carte
void popupWindowLoading(LoadWindow* lw) {
	post_form(lw->formLoading);
	keypad(lw->window, TRUE);

	keypad(lw->window, FALSE);
	unpost_form(lw->window);
}

// Libère la mémoire prise pour la fenêtre de chargement
void freeLoadWindow(LoadWindow lw) {

	free_form(lw.formLoading);
	free_field(lw.fields[0]);
	delwin(lw.window);
}
