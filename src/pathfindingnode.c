#include "pathfindingnode.h"
#include "pathfindermath.h"


// FONCTIONS UTILITAIRES POUR LES PATHFINDINGNODE

float calcCost(PathfindingNode* pn, PathfindingNode target, PathfindingNode begin) {
	
	float gcost = calcDistance(pn, begin);
	float hcost = calcDistance(pn, target);
	float fcost = gcost*hcost;
	
	pn->gCost = gcost;
	pn->hCost = hcost;
	pn->fCost = fcost;
} 

void setParent(PathfindingNode* pn, PathfindingNode* parent) {
	pn->parent = parent;
}

PathfindingNode* getParent(PathfindingNode pn) {
	return pn.parent;
}

// FONCTIONS UTILITAIRES POUR LES LISTES DE PATHFINDINGNODE
PathfindingNodeList createPathfindigNodeList() {
	PathfindingNodeList pnl;
	
	pnl.nodes = NULL;
	pnl.taille = 0;
	pnl.tailleUtilisee = 0;
}

void addToNodeList(PathfindingNodeList* pnl, PathfindingNode* pn) {
	// TODO
}

void removeFromNodeList(PathfindingNodeList* pnl, int index) {
	// TODO
}	

