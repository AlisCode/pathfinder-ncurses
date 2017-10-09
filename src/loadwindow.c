#include "loadwindow.h"
#include <form.h>
#include <ncurses.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define LONGUEUR_NOM_CARTE 15

// Crée la fenêtre de chargement
LoadWindow createLoadWindow(int maxX, int maxY) {

	LoadWindow lwindow;

	lwindow.window = newwin(5,LONGUEUR_NOM_CARTE+10, maxY/2 - 2, maxX/2 - (LONGUEUR_NOM_CARTE+10)/2);
	lwindow.mapName = malloc(sizeof(char) * LONGUEUR_NOM_CARTE + 4);
	
	lwindow.x = 0;
	lwindow.y = 0;
	lwindow.width = 0;
	lwindow.height = 0;

	lwindow.fields = calloc(2,sizeof(FIELD *));
	lwindow.fields[0] = new_field(1, LONGUEUR_NOM_CARTE, 3, 2, 0, 0);
	lwindow.fields[1] = NULL;

	set_field_back(lwindow.fields[0], A_UNDERLINE); 	
	field_opts_off(lwindow.fields[0], O_AUTOSKIP);  
	
	lwindow.formLoading = new_form(lwindow.fields);
	set_form_win(lwindow.formLoading, stdscr);
	set_form_sub(lwindow.formLoading, lwindow.window);
	
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

	post_form(lw->formLoading);	
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
	trimwhitespace(buf);
	strcpy(lw->mapName, buf);
	strcat(lw->mapName, ".map");

	fprintf(stderr, "%s", lw->mapName);
	
	unpost_form(lw->formLoading);
}


// Libère la mémoire prise pour la fenêtre de chargement
void freeLoadWindow(LoadWindow lw) {

	free_form(lw.formLoading);
	free_field(lw.fields[0]);
	delwin(lw.window);
}

// Fonction utilitaire qui retire les espaces d'une chaîne de caractère modifiable
// (Oui, c'est copié sur internet)
// Source : https://stackoverflow.com/questions/122616/how-do-i-trim-leading-trailing-whitespace-in-a-standard-way
char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator
  *(end+1) = 0;

  return str;
}
