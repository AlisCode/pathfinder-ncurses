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
        return NULL;
    }

    PathfindingNode startPn = createNodeFromCaseMap(startCm);
    PathfindingNode endPn = createNodeFromCaseMap(endCm);

    PathfindingNodeList openList = createPathfindingNodeList();
    PathfindingNodeList closedList = createPathfindingNodeList();

    addToNodeList(&openList, startPn);
    fprintf(stderr, "tout est initialise\n");
    int tourBoucle = 1;
    while(openList.tailleUtilisee > 0) {
        
        fprintf(stderr, "tour de boucle %d\n", tourBoucle);
        tourBoucle++;
        // Dépile le premier élément de la liste
        PathfindingNode pn = openList.nodes[0];
        removeFromNodeList(&openList, 0);
        
        // Si le noeud qu'on visite est le noeud d'arrivée, le chemin est trouvé
        if(nodeEquals(pn, endPn)) {
            fprintf(stderr, "construction du chemin...\n");
            // On retourne le chemin construit à partir de l'arrivée
            return constructPath(&pn);
        }

        // Ajoute les voisins
        addNeighbours(&openList, &closedList, pn, m);

        // Ajoute le noeud visité dans la closedList
        addToNodeList(&closedList, pn);

        // Et on recommence ....
    }

}

void resolvePath(Map m) {
    PathfindingNodeList* pnl = findPath(m);

    fprintf(stderr, "ended call to findPath");
    if(pnl != NULL)
    {
        fprintf(stderr, "\n path found : {\n");
        int i; 
        for(i = 0 ; i < pnl->tailleUtilisee ; i++)
        {
            fprintf(stderr, "x : %d, y : %d;\n", pnl->nodes[i].x, pnl->nodes[i].y);
        }
        fprintf(stderr, "}\n");
    }
}

PathfindingNodeList* constructPath(PathfindingNode* end) {

    PathfindingNodeList path = createPathfindingNodeList();
    addToNodeList(&path, *end);

    PathfindingNode* current = end;
    while(current != NULL) {
        addToNodeList(&path, *current);
        current = current->parent;
    }


    return &path;
}

void addNeighbours(PathfindingNodeList* openList, PathfindingNodeList* closedList, PathfindingNode pn, Map m) {

    // Ajoute le voisin gauche
    int lx = pn.x-1;
    int ly = pn.y;
    if(lx > 0 && lx <= m.width ) { 
        CaseMap lcm = getCase(m, lx, ly);
        PathfindingNode lpn = createNodeFromCaseMap(&lcm);
        if(lcm.flag != MUR && nodeListContains(closedList, lpn) == 0) {
            setParent(&lpn, &pn);
            addToNodeList(openList, lpn);   
        }
    }
    
    int rx = pn.x+1;
    int ry = pn.y;
    if(rx > 0 && rx <= m.width ) { 
        CaseMap rcm = getCase(m, rx, ry);
        PathfindingNode rpn = createNodeFromCaseMap(&rcm);
        if(rcm.flag != MUR && nodeListContains(closedList, rpn) == 0) {
            setParent(&rpn, &pn);
            addToNodeList(openList, rpn);   
        }
    }
    
    int ux = pn.x;
    int uy = pn.y-1;
    if(uy > 0 && uy <= m.height ) { 
        CaseMap ucm = getCase(m, ux, uy);
        PathfindingNode upn = createNodeFromCaseMap(&ucm);
        if(ucm.flag != MUR && nodeListContains(closedList, upn) == 0) {
            setParent(&upn, &pn);
            addToNodeList(openList, upn);   
        }
    }
    
    int dx = pn.x; 
    int dy = pn.y+1;
    if(dx > 0 && dx <= m.height ) { 
        CaseMap dcm = getCase(m, dx, dy);
        PathfindingNode dpn = createNodeFromCaseMap(&dcm);
        if(dcm.flag != MUR && nodeListContains(closedList, dpn) == 0) {
            setParent(&dpn, &pn);
            addToNodeList(openList, dpn);   
        }
    }
    
}