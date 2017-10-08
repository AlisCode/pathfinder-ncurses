#include "loadwindow.h"
#include <form.h>
#include <ncurses.h>
#include <string.h>

// Crée la fenêtre de chargement
LoadWindow createLoadWindow(int maxX, int maxY) {

	LoadWindow lwindow;

	lwindow.window = newwin(5,25,1,1);
	lwindow.fields[0] = new_field(1,15, 3, 2, 0, 0);
	lwindow.fields[1] = NULL;

	set_field_back(lwindow.fields[0], A_UNDERLINE); 	
	field_opts_off(lwindow.fields[0], O_AUTOSKIP);  
	
	lwindow.formLoading = new_form(lwindow.fields);
	set_form_win(lwindow.formLoading, stdscr);
	set_form_sub(lwindow.formLoading, lwindow.window);
	
	post_form(lwindow.formLoading);
	unpost_form(lwindow.formLoading);

	return lwindow;
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
	
	drawLoadWindow(lw);
	
	int ch;
	// Tourne tant qu'on a pas appuyé sur entrée
	while((ch = getch()) != 10) {
		switch(ch) {
			case KEY_BACKSPACE:
			case 8:
				form_driver(lw->formLoading, REQ_DEL_PREV);
			break;
			default: 
				form_driver(lw->formLoading, ch);
			break;
		}

		wrefresh(lw->window);
	}

	form_driver(lw->formLoading, REQ_NEXT_FIELD);
	
	char* buf = field_buffer(lw->fields[0], 0);
	strcpy(lw->mapName, buf);
}

// Libère la mémoire prise pour la fenêtre de chargement
void freeLoadWindow(LoadWindow lw) {

	free_form(lw.formLoading);
	free_field(lw.fields[0]);
	delwin(lw.window);
}