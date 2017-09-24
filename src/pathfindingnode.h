#ifndef PATHFINDINGNODE_H
#define PATHFINDINGNODE_H

#include "casemap.h"

typedef struct pathfindingNode PathfindingNode;
typedef struct pathfindingNodeList PathfindingNodeList;

struct pathfindingNode {
	int x;
	int y;

	PathfindingNode* parent;
	
	float gCost;
	float hCost;
	float fCost;
};

PathfindingNode createNodeFromCaseMap(CaseMap* cm);
void calcCost(PathfindingNode* pn, PathfindingNode target, PathfindingNode begin);
void setParent(PathfindingNode* pn, PathfindingNode* parent);
PathfindingNode* getParent(PathfindingNode pn);
int nodeEquals(PathfindingNode n1, PathfindingNode n2);
int compareNodes(PathfindingNode n1, PathfindingNode n2);

struct pathfindingNodeList {
	PathfindingNode* nodes;
	int taille;
	int tailleUtilisee;
};

PathfindingNodeList createPathfindingNodeList();
void addToNodeList(PathfindingNodeList* pnl, PathfindingNode pn);
void removeFromNodeList(PathfindingNodeList* pnl, int index);
void freeNodeList(PathfindingNodeList* pnl);
int nodeListContains(PathfindingNodeList* pnl, PathfindingNode pn);

#endif
