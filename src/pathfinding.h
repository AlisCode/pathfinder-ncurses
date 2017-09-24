#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "map.h"
#include "casemap.h"
#include "pathfindingnode.h"


PathfindingNodeList constructPath(PathfindingNode* end);
PathfindingNodeList findPath(Map m);
void addNeighbours(PathfindingNodeList* openList, PathfindingNodeList* closedList, PathfindingNode pn, Map m);
void resolvePath(Map m);

#endif