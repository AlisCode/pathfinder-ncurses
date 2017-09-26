#include <stdio.h>
#include "pathfinding.h"
#include "map.h"
#include "casemap.h"
#include "pathfindermath.h"

PathfindingNodeList findPath(Map m) {

    CaseMap* startCm = getStartingPoint(m);
    CaseMap* endCm = getEndingPoint(m);
    
    if(startCm == NULL || endCm == NULL)
    {
        fprintf(stderr, "Erreur : pas de point d'arrivée et de départ trouvé !");
        return createPathfindingNodeList();
    }

    PathfindingNode* startPn = createNodeFromCaseMap(startCm);
    PathfindingNode* endPn = createNodeFromCaseMap(endCm);

    PathfindingNodeList openList = createPathfindingNodeList();
    PathfindingNodeList closedList = createPathfindingNodeList();

    addToNodeList(&openList, startPn);
    int tourBoucle = 1;
    while(openList.tailleUtilisee > 0) {
        
        tourBoucle++;
        
	// Dépile le premier élément de la liste et l'ajoute dans la ClosedList
        PathfindingNode* pn = openList.nodes[0];
        removeFromNodeList(&openList, 0);
        addToNodeList(&closedList, pn);
        
	// Si le noeud qu'on visite est le noeud d'arrivée, le chemin est trouvé
        if(nodeEquals(pn, endPn)) {
            fprintf(stderr, "construction du chemin...\n");
            // On retourne le chemin construit à partir de l'arrivée
                PathfindingNodeList path = constructPath(pn);
		freeNodeList(&openList);
            	freeNodeList(&closedList);
		return path;
	 }

        // Ajoute les voisins
        addNeighbours(&openList, &closedList, pn, m);

        // Et on recommence ....
    }


    // Si on n'a pas trouvé de chemin à la fin, retourne une liste vide 
    return createPathfindingNodeList();

}

void resolvePath(Map m) {
    PathfindingNodeList pnl = findPath(m);

    fprintf(stderr, "ended call to findPath");
    if(pnl.taille != 0)
    {
        fprintf(stderr, "\n path found : {\n");
        int i; 
        for(i = 0 ; i < pnl.tailleUtilisee ; i++)
        {
            fprintf(stderr, "x : %d, y : %d;\n", pnl.nodes[i]->x, pnl.nodes[i]->y);
        }
        fprintf(stderr, "}\n");
    }
}

PathfindingNodeList constructPath(PathfindingNode* end) {

    PathfindingNodeList path = createPathfindingNodeList();

    PathfindingNode* current = end;
    while(current != NULL) {
        addToNodeList(&path, current);
        current = current->parent;
    }


    return path;
}

void addNeighbours(PathfindingNodeList* openList, PathfindingNodeList* closedList, PathfindingNode* pn, Map m) {

    	// Ajoute le voisin gauche
	addNeighbour(openList, closedList, m, -1, 0, pn);  
 
	// Ajoute le voisin droit
	addNeighbour(openList, closedList, m, 1, 0, pn);  
   
    	// Ajoute le voisin du dessus
	addNeighbour(openList, closedList, m, 0, -1, pn);  
   	
	// Ajoute le voisin du dessous
	addNeighbour(openList, closedList, m, 0, 1, pn);   
    
}


void addNeighbour(PathfindingNodeList* openList, PathfindingNodeList* closedList, Map m, int offsetX, int offsetY, PathfindingNode* pn) {
	//fprintf(stderr,"1\n");
	int nx = pn->x + offsetX; 
    	int ny = pn->y + offsetY;
	//fprintf(stderr,"2\n");

    	if(nx > 0 && nx <= m.width && ny > 0 && ny <= m.height ) { 
        	//fprintf(stderr,"3\n");
		CaseMap ncm = getCase(m, nx, ny);
	        //fprintf(stderr,"4\n");	
		PathfindingNode* npn = createNodeFromCaseMap(&ncm);
        	//fprintf(stderr,"5\n");
		if(ncm.flag != MUR && 
		nodeListContains(closedList, npn) == 0 && 
		nodeListContains(openList, npn) == 0) {
		    //fprintf(stderr,"6\n");
			setParent(npn, pn);
		    //fprintf(stderr,"7\n");
			addToNodeList(openList, npn);   
		}
   	 }
	//fprintf(stderr,"8\n");
}

