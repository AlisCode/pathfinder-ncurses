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
	'|',
	'|'
}; 

// Affiche la case passée en paramètre dans la fenêtre ncurses
void drawCase(CaseMap cm) {
	
	// Crée un string affichable à partir du char dans le tableau
	char c[2];
	c[0] = getCharRepresentation(cm);
	c[1] = '\0'; 
	mvprintw(cm.x, cm.y, c);
}

// Obtient la représentation sous forme de char de la case donnée
char getCharRepresentation(CaseMap cm) {
	return charRepresentation[cm.flag];
}
