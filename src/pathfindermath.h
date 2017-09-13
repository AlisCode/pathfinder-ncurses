#ifndef PATHFINDERMATH_H
#define PATHFINDERMATH_H

#include "pathfindingnode.h"

int getArrayIndexFromXYPos(int x, int y, int arrayW);
float calcDistance(PathfindingNode* depart, PathfindingNode* arrivee);

#endif
