#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
#include "map.h"
#include "casemap.h"
#include "pathfindermath.h"
#include "stateview.h"

// Crée une carte à partir de son nom, sa taille (Width, Height)
Map createMap(char* name, int w, int h) {
	
	Map m;
	
	m.name = name;
	m.width = w;
	m.height = h;
	
	CaseMap *cases = malloc(w*h*sizeof(CaseMap));
	m.cases = cases;
	m.nbCases = w*h;

	// Instancie les cases dans le tableau
	int i;
	for(i = 0 ; i < m.nbCases ; i++) {
		CaseMap cm;
		cm.x = (i % w)+1;
		cm.y = (i / w)+1;
		cm.flag = VIDE;
		addCase(&m, cm);	
	}

	return m;
}

// Libère la mémoire allouée pour créer le tableau 
void freeMap(Map* m) {
	free(m->cases);
}

// Récupère la case aux coordonnées (X,Y)
CaseMap getCase(Map m, int x, int y) {
	int index = getArrayIndexFromXYPos(x,y,m.width);
	return m.cases[index];
}

// Change la case aux coordonnées (X,Y)
void setCase(Map* m, CaseMap cm) {
	int index = getArrayIndexFromXYPos(cm.x,cm.y, m->width);
	m->cases[index] = cm;
}

// Change le contenu de la case aux coordonnées (X,Y)
void changeFlag(Map* m, int x, int y, CaseFlags flag) {
	int index = getArrayIndexFromXYPos(x,y,m->width);
	m->cases[index].flag = flag;
}

// Sauvegarde la carte dans un fichier portant son nom
void saveMap(Map m) {
	
	FILE* fichier = fopen(m.name, "w");
	if(fichier == NULL) {
		fprintf(stderr, "Erreur lors de l'ouverture du fichier pour la sauvegarde");
		exit(1);
	}
	
	fprintf( fichier, "%d\n", m.width);
	fprintf( fichier, "%d\n", m.height);

	int i;
	for(i = 0 ; i < m.nbCases ; i++) {
		if(i != 0 && i % m.width == 0) { fprintf( fichier, "\n"); }
		fprintf( fichier, "%d", m.cases[i].flag);
	}

	fclose(fichier);
}

// Charge une carte dans l'application
Map loadMap(char* filename, StateView* sv) {
	FILE* fichier = fopen(filename, "r");
	if(fichier == NULL) {
		updateStateView(sv, "No map found, starting from scratch");
		Map m = createMap(filename, 10,10);

		return m;
	}

	int width;
	int height;
	fscanf(fichier, "%d\n", &width);
	fscanf(fichier, "%d\n", &height);

	Map m = createMap(filename, width, height);	

	int nbCases = width*height;
	int i;
	for(i = 0 ; i < nbCases ; i++) {
		int flag;
		char buffer[2];
		// Evite le problème avec les retours à la ligne
		if( i % width == 0 && i != 0) { 
			fscanf(fichier, "%c", &buffer[0]);
		}
		fscanf(fichier, "%c", &buffer[0]);
		sscanf(buffer, "%d", &flag); 
		int x = (i%width)+1;
		int y = (i/width)+1;
		changeFlag(&m,x,y,flag);
	}

	fclose(fichier);
	return m;
}

// Affiche une carte sur l'écran
void displayMap(Map m, int cursorX, int cursorY, WINDOW* win) {
	int i;
	int indexCursor = getArrayIndexFromXYPos(cursorX, cursorY, m.width);
	start_color();
	for(i = 0 ; i < m.nbCases ; i++) {
		if(i == indexCursor) { wattron( win, A_REVERSE); }
		drawCase(m.cases[i], win);	
		if(i == indexCursor) { wattroff( win, A_REVERSE); }
	}
}


// Ajoute une case dans une carte
void addCase(Map* m, CaseMap cm) {

	int index = getArrayIndexFromXYPos(cm.x,cm.y,m->width);	
	m->cases[index] = cm;
}

void normalizeMap(Map* m) {
	int x, y;
	for(x = 1 ; x <= m->width ; x++) 
	{
		for(y = 1 ; y <= m->height ; y++)
		{	
			
			int flag = getCase(*m, x,y).flag;
			if(flag == CHEMIN_LEFT 
			|| flag == CHEMIN_RIGHT
			|| flag == CHEMIN_UP
			|| flag == CHEMIN_DOWN) {
				changeFlag(m, x, y, VIDE);
			}
		}	
	}
}


// Récupère la case "point de départ" d'une carte
CaseMap* getStartingPoint(Map m) {
	
	int i;
	for(i = 0 ; i < m.nbCases ; i++) {
		if(m.cases[i].flag == DEPART) {
			return &m.cases[i];
		}
	}

	return NULL;
}

// Récupère la case "point d'arrivée" d'une carte
CaseMap* getEndingPoint(Map m) {

	int i;
	for(i = 0 ; i < m.nbCases ; i++) {
		if(m.cases[i].flag == ARRIVEE) {
			return &m.cases[i];
		}
	}

	return NULL;
}
