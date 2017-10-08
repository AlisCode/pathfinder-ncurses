#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "map.h"
#include "casemap.h"
#include "pathfindingnode.h"
#include "stateview.h"

PathfindingNodeList constructPath(PathfindingNode* end);
PathfindingNodeList findPath(Map m);
void addNeighbours(PathfindingNodeList* openList, PathfindingNodeList* closedList, PathfindingNode* pn, Map m);
void addNeighbour(PathfindingNodeList* openList, PathfindingNodeList* closedList, Map m, int offsetX, int offsetY, PathfindingNode* pn);
void resolvePath(Map m, StateView* sv);

#endif
