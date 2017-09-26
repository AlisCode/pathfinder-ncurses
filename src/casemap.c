#include "casemap.h"
#include <ncurses.h>

// Tableau permettant de stocker la représentation graphique des cases dans la map
char charRepresentation[8] = {
	'X',
	'.',
	'D',
	'A',
	'<',
	'>',
	'^',
	'v'
}; 


// Tableau permettant de stocker la couleur d'une case dans la map
int charColor[8] = {
	2,
	1,
	3,
	3,
	4,
	4,
	4,
	4	
};

// Affiche la case passée en paramètre dans la fenêtre ncurses
void drawCase(CaseMap cm, WINDOW* win) {
	
	// Crée un string affichable à partir du char dans le tableau
	char c[2];
	c[0] = getCharRepresentation(cm);
	c[1] = '\0'; 
	
	wattron(win, COLOR_PAIR(charColor[cm.flag]));
	mvwprintw(win, cm.y, cm.x, c);
	wattroff(win, COLOR_PAIR(charColor[cm.flag]));
}

// Obtient la représentation sous forme de char de la case donnée
char getCharRepresentation(CaseMap cm) {
	return charRepresentation[cm.flag];
}
