#ifndef MAP_H
#define MAP_H
#include "casemap.h"
#include <ncurses.h>

typedef struct map Map;
struct map {
	char* name;
	int width;
	int height;
	int nbCases;
	CaseMap *cases;
};

Map createMap(char* name, int w, int h);
void saveMap(Map m);
Map loadMap(char* filename);
void displayMap(Map m, int cursorX, int cursorY, WINDOW* win);
void addCase(Map* m, CaseMap cm);
void normalizeMap(Map* m);
void freeMap(Map* m);
CaseMap getCase(Map m, int x, int y);
void setCase(Map* m, CaseMap cm);
void changeFlag(Map* m,int x, int y, CaseFlags flag);
CaseMap* getStartingPoint(Map m);
CaseMap* getEndingPoint(Map m);

#endif
