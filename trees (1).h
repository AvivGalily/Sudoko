#ifndef _trees_Header
#define _tress_Header

#include "lists.h"

Tree BuildTreeFromArray(playerListNode** pArr, int  numOfPlayers);
//void printTreeLDRHelper(TreeNode* root);
//void printTreeLDR(TreeNode* root);
void removeplayerfromlist(playerList* lst, playerListNode* node);
void PlayInOrderHelper(TreeNode* root, playerList* ActivePlayerlist, winnerList* Winnerlist);
void PlayInOrder(Tree tr, playerList* ActivePlayerlist);
void makeActivePlayerListFromTree(TreeNode* root, playerList* activePlayerList);
void freeTree(Tree tr);
void freeTreeRec(TreeNode* root);

#endif // !_trees_Header
