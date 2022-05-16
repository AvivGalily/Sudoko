#ifndef _lists_Header
#define _lists_Header

#include "firstFuncs.h"

void makeEmptyList(cellList* lst);
cellListNode* createNewCellListNode(cellLocation location, cellListNode* next, cellListNode* prev);
void insertLocationToEndList(cellList* lst, cellLocation location);
void insertNodeToEndList(cellList* lst, cellListNode* newTail);
void freeList(cellList lst);
int isEmptyList(cellList lst);
void printList(cellList lst);
void makeCellLocationList(cellList* lst);
cellListNode* findNodeLocation(cellList lst, int cellPlace);
cellLocation removeCellLocation(cellList* lst, cellListNode* node);
short getNumberFromPoss(CellPossibilities*** possibilities, cellLocation tempLocation);
int listLen(cellList lst);
void makeEmptyPlayerList(playerList* lst);
void makeEmptywinnerList(winnerList* lst);
playerListNode* createNewPlayerListNode(playerData* player, playerListNode* next, playerListNode* prev);
winnerListNode* createNewwinnerListNode(playerData* player, winnerListNode* next, winnerListNode* prev);
bool isEmptyPlayerList(playerList lst);
bool isEmptywinnerList(winnerList lst);
void insertPlayerDataToEndList(playerList* lst, playerData* player);
void insertwinnerDataToEndList(winnerList* lst, playerData* player);
void insertPlayerNodeToEndList(playerList* lst, playerListNode* newTail);
void insertwinnerNodeToEndList(winnerList* lst, winnerListNode* newTail);
void freePlayerList(playerList lst);
void freewinnerList(winnerList lst);
void freePlayer(playerListNode* node);
void createActivePlayerList();
void printPlayerList(playerList* lst);
void freewinnerList(winnerList lst);
void printwinnerList(winnerList* lst);
playerListNode** makePointerArrToPlayerList(playerList lst, int listSize);
void sortPlayerNodes(playerListNode** arr, int size);
void merge(playerListNode** arr1, int size1, playerListNode** arr2, int size2, playerListNode** res);
int playTurn(playerData* player);
void initialBoard(short board[][SIZE], int* resInitialNum);

#endif // !_lists_Header
