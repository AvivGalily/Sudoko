#ifndef _structs_Header
#define _structs_Header

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

#define SIZE 9
#define FINISH_SUCCESS 0
#define NOT_FINISH 1
#define FINISH_FAILURE -1
#define FILLED 1
#define FAIL -1




typedef struct _Array
{
    short* arr;
    unsigned short size;
} CellPossibilities;

typedef CellPossibilities CellPossibilities;

typedef struct _cellLocation
{
    unsigned short row;
    unsigned short col;
}cellLocation;

typedef struct cellListNode_ {
    cellLocation location;
    struct cellListNode_* next;
    struct cellListNode_* prev;
}cellListNode;

typedef struct cellList_ {
    cellListNode* head;
    cellListNode* tail;
}cellList;

typedef struct playerData_ {
    char name[100];
    short* board;
    CellPossibilities*** possibilities;
    int numOfInitials;
}playerData;

typedef struct playerListNode_ {
    playerData* player;
    struct playerListNode_* next;
    struct playerListNode_* prev;
}playerListNode;

typedef struct playerList_ {
    playerListNode* head;
    playerListNode* tail;
}playerList;

typedef struct winnerListNode_ {
    playerData* player;
    struct winnerListNode_* next;
    struct winnerListNode_* prev;
}winnerListNode;
typedef struct winnerList_ {
    winnerListNode* head;
    winnerListNode* tail;
}winnerList;
typedef struct treeNode
{
    playerListNode** data;
    struct treeNode* left;
    struct treeNode* right;
} TreeNode;
typedef struct tree
{
    TreeNode* root;
} Tree;




#endif // !_structs_Header
