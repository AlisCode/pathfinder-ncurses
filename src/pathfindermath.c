#include "pathfindermath.h"

// Retourne la position dans le tableau de la case aux coordonnées (x,y)
int getArrayIndexFromXYPos(int x, int y, int arrayW) {
	return ((y-1)*arrayW + x) -1;
}
