#include "pathfindingnode.h"
#include "pathfindermath.h"
#include <stdlib.h>

// FONCTIONS UTILITAIRES POUR LES PATHFINDINGNODE

// Calcule les coûts dont l'algorithme A* a besoin
void calcCost(PathfindingNode* pn, PathfindingNode target, PathfindingNode begin) {
	
	// Coût depuis le point de départ
	float gcost = calcDistance(pn, &begin);

	// Coût vers le point d'arrivée
	float hcost = calcDistance(pn, &target);
	
	// Produit des deux précédents
	float fcost = gcost*hcost;
	
	// Affecte les coûts calculés à la structure
	pn->gCost = gcost;
	pn->hCost = hcost;
	pn->fCost = fcost;
} 

// Permet de définir le pointeur vers le parent du noeud concerné
void setParent(PathfindingNode* pn, PathfindingNode* parent) {
	pn->parent = parent;
}

// Récupère le pointeur vers le parent du noeud concerné 
PathfindingNode* getParent(PathfindingNode pn) {
	return pn.parent;
}

// Crée un PathfindingNode depuis une CaseMap 
PathfindingNode createNodeFromCaseMap(CaseMap* cm) {
	PathfindingNode pn;

	pn.x = cm->x;
	pn.y = cm->y;
	
	pn.parent = NULL;
	pn.isAnchor = 0;
	pn.gCost = 0;
	pn.hCost = 0;
	pn.fCost = 0;

	return pn;
}

// FONCTIONS UTILITAIRES POUR LES LISTES DE PATHFINDINGNODE

// Crée une pathfindingNodeList
PathfindingNodeList createPathfindingNodeList() {
	
	// Crée la liste
	PathfindingNodeList pnl;
	
	// Initialise la liste avec une taille pouvant contenir 10 PathfindingNode
	pnl.nodes = malloc(sizeof(PathfindingNode) * 10);
	pnl.taille = 10;
	pnl.tailleUtilisee = 0;

	// Retourne la liste
	return pnl;
}

// Ajoute un noeud à une liste dont la mémoire est gérée dynamiquement
void addToNodeList(PathfindingNodeList* pnl, PathfindingNode pn) {
	
	// Si notre liste est déjà complète
	if(pnl->taille == pnl->tailleUtilisee) {
		// On ajoute de la place pour stocker 10 noeuds
		pnl->nodes = realloc(pnl->nodes, sizeof(PathfindingNode) * 10);
		pnl->taille += 10;
	}

	// Ajoute le noeud dans la liste
	pnl->nodes[pnl->tailleUtilisee] = pn;
	pnl->tailleUtilisee++;
}

// Retire un noeud à une liste dont la mémoire est gérée dynamiquement
void removeFromNodeList(PathfindingNodeList* pnl, int index) {
	// Vérifie qu'on soit bien en train d'accéder un index qui existe réellement
	if(index >= 0 && index < pnl->tailleUtilisee) {
		
		// Itère sur tous les éléments de la liste
		int i;
		for(i = index ; i < pnl->tailleUtilisee ; i++) {
			// Remplace l'élément par le suivant dans la liste
			pnl->nodes[i] = pnl->nodes[i+1];
		}

		// Notifie la liste qu'elle peut stocker un noeud en plus
		pnl->tailleUtilisee--;
	}
}

// Libère la mémoire utilisée par une PathfindingNodeList
void freeNodeList(PathfindingNodeList* pnl) {
	free(pnl->nodes);
}

int nodeListContains(PathfindingNodeList* pnl, PathfindingNode* pn) {

	int i;
	for(i = 0 ; i < pnl->taille ; i++)
	{
		if(pnl->nodes[i].x == pn->x && pnl->nodes[i].y == pn->y) {
			return 1;
		}
	}
	
	return 0;
}