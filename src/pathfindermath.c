#include "pathfindermath.h"
#include "pathfindingnode.h"
#include <math.h>

// Retourne la position dans le tableau de la case aux coordonnées (x,y)
int getArrayIndexFromXYPos(int x, int y, int arrayW) {
	return ((y-1)*arrayW + x) -1;
}


// Retourne la distance entre deux points (PathfindingNode)
float calcDistance(PathfindingNode* depart, PathfindingNode* arrivee) {
	int dx = arrivee->x - depart->x;
	int dy = arrivee->y - depart->y;

	return sqrtf(dx*dx + dy*dy);
}
