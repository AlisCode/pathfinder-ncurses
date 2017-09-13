#include <stdio.h>
#include "pathfinding.h"
#include "map.h"
#include "casemap.h"
#include "pathfindermath.h"

PathfindingNodeList* findPath(Map m) {

    CaseMap* startCm = getStartingPoint(m);
    CaseMap* endCm = getEndingPoint(m);

    if(startCm == NULL || endCm == NULL)
    {
        fprintf(stderr, "Erreur : pas de point d'arrivée et de départ trouvé !");
        return;
    }

    PathfindingNodeList openList = createPathfindingNodeList();
    PathfindingNodeList closedList = createPathfindingNodeList();

}

void resolvePath(Map m) {
    PathfindingNodeList* pnl = findPath(m);

    if(pnl != NULL)
    {

    }
}