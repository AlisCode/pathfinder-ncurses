#include <stdio.h>
#include "pathfinding.h"
#include "map.h"
#include "casemap.h"
#include "pathfindermath.h"
#include "stateview.h"


// Fonction permettant de trouver le chemin entre le point d'arrivée et le point de départ de la map donnée
// Retourne une PathfindingNodeList vide si aucun chemin n'a été trouvé
PathfindingNodeList findPath(Map m) {

	// Récupère le point de départ et d'arrivée
    CaseMap* startCm = getStartingPoint(m);
    CaseMap* endCm = getEndingPoint(m);
    
	// S'il en manque un
    if(startCm == NULL || endCm == NULL)
    {
        return createPathfindingNodeList();
    }

	// Crée le noeud de départ et le noeud d'arrivée
    PathfindingNode* startPn = createNodeFromCaseMap(startCm);
    PathfindingNode* endPn = createNodeFromCaseMap(endCm);

	// Crée la liste de noeuds ouverts et fermés ( A* )
    PathfindingNodeList openList = createPathfindingNodeList();
    PathfindingNodeList closedList = createPathfindingNodeList();

	// Ajoute le point de départ à la liste ouverte
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

// Fonction permettant de gérer la résolution du chemin
// Affiche le chemin en cas de succès
// Affiche l'erreur s'il y en a une  
void resolvePath(Map m, StateView* sv) {

	// Résouds le chemin
	PathfindingNodeList pnl = findPath(m);

	// Si on a trouvé une solution
    if(pnl.tailleUtilisee != 0)
	{
		int i; 
		// On parcourt tout le tableau (sauf la dernière et la première case)
		for(i = 1 ; i < pnl.tailleUtilisee-1 ; i++)
		{
			// Si on a une case après
			if(i-1 >= 0)
			{
				int dx = pnl.nodes[i]->x - pnl.nodes[i-1]->x;
				int dy = pnl.nodes[i]->y - pnl.nodes[i-1]->y;
				
				// NB : Comme le chemin est reconstruit à l'envers (en partant du point d'arrivée, on inverse le sens pour déduire le déplacement entre deux points)
				// Si on se déplace vers la droite
				if(dx < 0) {
					changeFlag(&m, pnl.nodes[i]->x, pnl.nodes[i]->y, CHEMIN_RIGHT);				
				}
				// Si on se déplace vers la gauche
				else if(dx > 0) {
					changeFlag(&m, pnl.nodes[i]->x, pnl.nodes[i]->y, CHEMIN_LEFT);				
				}
				// Si on se déplace vers le haut
				else if(dy > 0) {
					changeFlag(&m, pnl.nodes[i]->x, pnl.nodes[i]->y, CHEMIN_UP);			
				}
				// Si on se déplace vers le bas
				else if(dy < 0) {
					changeFlag(&m, pnl.nodes[i]->x, pnl.nodes[i]->y, CHEMIN_DOWN);	
				}
			}
		}

		// Met à jour la StateView
		updateStateView(sv, "Chemin trouve !");
	}
	else {
		// sinon, on affiche qu'on a eu une erreur 	
		updateStateView(sv, "Aucun chemin trouve :(");
	}
}

// Fonction permettant de reconstruire le chemin à partir du dernier PathfindingNode (en remontant dans les parents)
// Retourne une PathfindingNodeList si il n'y'a pas eu d'erreur
PathfindingNodeList constructPath(PathfindingNode* end) {

    PathfindingNodeList path = createPathfindingNodeList();

    PathfindingNode* current = end;
    while(current != NULL) {
        addToNodeList(&path, current);
        current = current->parent;
    }


    return path;
}

// Ajoute les noeuds voisin du noeud actuel dans la liste ouverte
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

// Ajoute le noeud voisin à pn dans la liste ouverte, en fonction de l'offset X/Y donné, si le noeud existe et qu'il n'est pas ni dans la liste ouverte, ni dans la liste fermée
void addNeighbour(PathfindingNodeList* openList, PathfindingNodeList* closedList, Map m, int offsetX, int offsetY, PathfindingNode* pn) {
	int nx = pn->x + offsetX; 
    	int ny = pn->y + offsetY;

    	if(nx > 0 && nx <= m.width && ny > 0 && ny <= m.height ) { 
		CaseMap ncm = getCase(m, nx, ny);
		PathfindingNode* npn = createNodeFromCaseMap(&ncm);
		if(ncm.flag != MUR && 
		nodeListContains(closedList, npn) == 0 && 
		nodeListContains(openList, npn) == 0) {
			setParent(npn, pn);
			addToNodeList(openList, npn);   
		}
   	 }
}