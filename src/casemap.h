#ifndef CASEMAP_H
#define CASEMAP_H

#include <ncurses.h>

typedef enum caseflags CaseFlags;
enum caseflags {
	MUR = 0,
	VIDE = 1,
	DEPART = 2,
	ARRIVEE = 3,
	CHEMIN_LEFT = 4,
	CHEMIN_RIGHT = 5,
	CHEMIN_UP = 6,
	CHEMIN_DOWN = 7
};

typedef struct caseMap CaseMap;
struct caseMap {
	int x;
	int y;
	enum caseflags flag;
};

void drawCase(CaseMap cm, WINDOW* win);
char getCharRepresentation(CaseMap cm);
#endif
