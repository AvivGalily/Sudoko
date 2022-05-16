#include "lists.h"
#include "trees.h"
#include "firstFuncs.h"

void createActivePlayerList()
{
    int numOfPlayers, i, j, numOfInitialCells , newSize;
    char curName[100];
    playerList lst, newActivePlayerList;
    playerListNode** pArr;
    Tree pointerTree;
 
    makeEmptyPlayerList(&lst);

    printf("how many players?\n");
    scanf("%d", &numOfPlayers);

    for (i = 0; i < numOfPlayers; i++)
    {
        playerData* currPlayer = (playerData*)malloc(sizeof(playerData));
        checkMemoryAllocation(currPlayer);
        short* currBoard = (short*)malloc(81 * sizeof(short));
        checkMemoryAllocation(currBoard);
        
        memset(currBoard, -1, 81 * sizeof(short)); // initializing temp board with (-1)

        currPlayer->board = currBoard; 

        printf("enter name: \n");
        scanf("%s", curName);
        strcpy(currPlayer->name, curName); // fill name of player

        initialBoard(currPlayer->board, &numOfInitialCells); //fill player board;
        currPlayer->numOfInitials = numOfInitialCells;
        currPlayer->possibilities = PossibleDigits(currPlayer->board); //fill player possibilities board

        insertPlayerDataToEndList(&lst, currPlayer);
        sudokoPrintBoard(currPlayer->board);

    }

    pArr = makePointerArrToPlayerList(lst, numOfPlayers);

    printf("\n\n");
    sortPlayerNodes(pArr, numOfPlayers); //merge sort
    newSize = pow(2, ceil(log2(numOfPlayers + 1))) - 1;
    pArr = realloc(pArr, sizeof(*pArr) * newSize);
    checkMemoryAllocation(pArr);
    for (j = numOfPlayers; j < newSize; j++) {
        pArr[j] = NULL;
    }
    pointerTree = BuildTreeFromArray(pArr, newSize);
    PlayInOrder(pointerTree, &lst);

    free(pArr);
    freeTree(pointerTree);



}
int playTurn(playerData* player) {
    int x = 0;
    int y = 0, i;
    int status;
    int numOfOptions, userChoice;
    status = OneStage(player->board, player->possibilities, &x, &y);
    if (status == NOT_FINISH) {
        printf("Its player %s turn\n", player->name);
        printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);
        if (player->possibilities[x][y] != NULL)
            numOfOptions = player->possibilities[x][y]->size;
        else
        {
            return status;
        }
        for (i = 0; i < numOfOptions; i++)
        {
            printf("%d. %d \n", i + 1, player->possibilities[x][y]->arr[i]);
        }
        scanf("%d", &userChoice);

        while (userChoice < 1 || userChoice > 9)
        {
            printf("Try again, please enter a valid number\n");
            scanf("%d", &userChoice);
        }

        printf("Updating cell %d with value %d\n", ((x * 9) + y), userChoice);
        player->board[x * 9 + y] = userChoice;
        free(player->possibilities[x][y]->arr);
        free(player->possibilities[x][y]);
        player->possibilities[x][y] = NULL;
        updatePossibilities(player->possibilities, x, y, userChoice);
        printf("******\n"); sudokoPrintBoard(player->board); printf("******\n");
    }
    return status;
}
void sortPlayerNodes(playerListNode** arr, int size)
{
    playerListNode** temp;
    int i;

    if (size == 1)
        return;
    else
    {
        sortPlayerNodes(arr, size / 2);
        sortPlayerNodes(arr + size / 2, size - size / 2);
        temp = (playerListNode**)malloc(sizeof(playerListNode*) * size);
        checkMemoryAllocation(temp);
        merge(arr, size / 2, arr + size / 2, size - size / 2, temp);

        for (i = 0; i < size; i++)
        {
            arr[i] = temp[i];
        }

        free(temp);
    }
};
void merge(playerListNode** arr1, int size1, playerListNode** arr2, int size2, playerListNode** res)
{
    int i = 0, j = 0, k = 0;

    while (i < size1 && j < size2)
    {
        if (arr1[i]->player->numOfInitials < arr2[j]->player->numOfInitials)
        {
            res[k++] = arr1[i++];
        }
        else if (arr1[i]->player->numOfInitials > arr2[j]->player->numOfInitials)
        {
            res[k++] = arr2[j++];
        }
        else
        {
            if (strcmp(arr1[i]->player->name, arr2[j]->player->name) < 0)
                res[k++] = arr1[i++];
            else
            {
                res[k++] = arr2[j++];
            }
        }
    }

    while (i < size1)
    {
        res[k++] = arr1[i++];
    }

    while (j < size2)
    {
        res[k++] = arr2[j++];
    }
}
playerListNode** makePointerArrToPlayerList(playerList lst, int listSize)
{
    playerListNode** pArr = (playerListNode**)malloc(sizeof(playerListNode*) * listSize);
    checkMemoryAllocation(pArr);
    int i;
    playerListNode* curr = lst.head;
    for (i = 0; i < listSize; i++)
    {
        pArr[i] = curr;
        curr = curr->next;
    }
    return pArr;
}
void makeEmptyList(cellList* lst)
{
    lst->head = lst->tail = NULL;
}
cellListNode* createNewCellListNode(cellLocation location, cellListNode* next, cellListNode* prev)
{
    cellListNode* result = (cellListNode*)malloc(sizeof(cellListNode));
    checkMemoryAllocation(result);
    result->location = location;
    result->next = next;
    result->prev = prev;

    return result;
}
void insertLocationToEndList(cellList* lst, cellLocation location)
{
    cellListNode* result = createNewCellListNode(location, NULL, NULL);

    insertNodeToEndList(lst, result);
}
void insertNodeToEndList(cellList* lst, cellListNode* newTail)
{
    if (isEmptyList(*lst))
    {
        newTail->next = newTail->prev = NULL;
        lst->head = lst->tail = newTail;
    }
    else
    {
        newTail->prev = lst->tail;
        newTail->next = NULL;
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}
int isEmptyList(cellList lst)
{
    return (lst.head == NULL);
}
void printList(cellList lst)
{
    cellListNode* curr;

    curr = lst.head;

    while (curr != NULL)
    {
        printf("(%d , %d) ", curr->location.row, curr->location.col);
        curr = curr->next;
    }

    printf("\n");
}
void initialBoard(short board[][SIZE], int* resInitialNum)
{
    int i;


    srand(time(NULL));
    int numberOfInitialCells = 1 + rand() % 20; // gets a number between 1 to 20
    *resInitialNum = numberOfInitialCells;
    int cellPlace;
    cellList lst;
    cellListNode* currCell;

    makeEmptyList(&lst);
    makeCellLocationList(&lst);

    CellPossibilities*** possibilities = PossibleDigits(board); // updates possibilities arr

    int sizeOfList = 80;

    for (i = 0; i < numberOfInitialCells; i++)
    {
        short newNumber;
        int row, col;
        cellPlace = 1 + rand() % sizeOfList; // gets a num between 1 to 80
        sizeOfList--;                        // each iteration size of list reduced by one
        currCell = findNodeLocation(lst, cellPlace); // finds the node in the list
        cellLocation tempLocation = removeCellLocation(&lst, currCell); // retrieve the data from the node while removing from the list
        row = tempLocation.row;
        col = tempLocation.col;
        newNumber = getNumberFromPoss(possibilities, tempLocation); // gets a random number from the options arr
        board[row][col] = newNumber;                                // fills the board with this number
        updatePossibilities(possibilities, row, col, newNumber);
    }
    freeList(lst);

}
short getNumberFromPoss(CellPossibilities*** possibilities, cellLocation tempLocation)
{
    int row, col, size;
    row = tempLocation.row;
    col = tempLocation.col;
    size = possibilities[row][col]->size;
    short randomIdx = rand() % size;
    return possibilities[row][col]->arr[randomIdx];
}
cellListNode* findNodeLocation(cellList lst, int cellPlace)
{
    cellListNode* curr = lst.head;
    int idx;

    for (idx = 1; idx < cellPlace; idx++)
    {
        curr = curr->next;
    }
    return curr;
}
cellLocation removeCellLocation(cellList* lst, cellListNode* node)
{
    cellLocation location = node->location;

    if (lst->head == lst->tail)
        lst->head = lst->tail = NULL;
    else if (lst->head == node)
    {
        lst->head = lst->head->next;
        lst->head->prev = NULL;
    }
    else if (lst->tail == node)
    {
        lst->tail = lst->tail->prev;
        lst->tail->next = NULL;
    }
    else
    {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }

    free(node);

    return location;
}
void removeplayerfromlist(playerList* lst, playerListNode* node) {
    //node->next
    if (lst->head == lst->tail)
    {
        lst->head = NULL;
        lst->tail = NULL;
    }
    else if (lst->head == node)
    {
        lst->head = node->next;
        lst->head->prev = NULL;
    }
    else if (lst->tail == node)
    {
        node->prev->next = node->next;
        lst->tail = node->prev;
        lst->tail->next = NULL;
    }
    else {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    }


    free(node);
}
void makeCellLocationList(cellList* lst)
{
    int row, col;
    cellLocation curr;


    for (row = 0; row < 9; row++)
    {
        for (col = 0; col < 9; col++)
        {
            curr.row = row;
            curr.col = col;
            insertLocationToEndList(lst, curr);
        }
    }
}
int listLen(cellList lst)
{
    int count = 0;
    cellListNode* curr;
    curr = lst.head;
    while (curr != NULL)
    {
        count++;
        curr = curr->next;
    }
    return count;
}
void makeEmptyPlayerList(playerList* lst)
{
    lst->head = lst->tail = NULL;
}
void makeEmptywinnerList(winnerList* lst)
{
    lst->head = lst->tail = NULL;
}
playerListNode* createNewPlayerListNode(playerData* player, playerListNode* next, playerListNode* prev)
{
    playerListNode* result;

    result = (playerListNode*)malloc(sizeof(playerListNode));
    checkMemoryAllocation(result);
    result->player = player;
    result->next = next;
    result->prev = prev;

    return result;
}
winnerListNode* createNewwinnerListNode(playerData* player, winnerListNode* next, winnerListNode* prev)
{
    winnerListNode* result;

    result = (winnerListNode*)malloc(sizeof(winnerListNode));
    checkMemoryAllocation(result);
    result->player = player;
    result->next = next;
    result->prev = prev;

    return result;
}
bool isEmptyPlayerList(playerList lst)
{
    if (lst.head == NULL) {
        return true;
    }
    return false;
}
bool isEmptywinnerList(winnerList lst)
{
    if (lst.head == NULL) {
        return true;
    }
    return false;
}
void insertwinnerDataToEndList(winnerList* lst, playerData* player)
{
    winnerListNode* result = createNewwinnerListNode(player, NULL, NULL);

    insertwinnerNodeToEndList(lst, result);
}
void insertPlayerDataToEndList(playerList* lst, playerData* player)
{
    playerListNode* result = createNewPlayerListNode(player, NULL, NULL);

    insertPlayerNodeToEndList(lst, result);
}
void insertPlayerNodeToEndList(playerList* lst, playerListNode* newTail)
{
    if (isEmptyPlayerList(*lst) == true)
    {
        newTail->next = newTail->prev = NULL;
        lst->head = lst->tail = newTail;
    }
    else
    {
        newTail->prev = lst->tail;
        newTail->next = NULL;
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}
void insertwinnerNodeToEndList(winnerList* lst, winnerListNode* newTail)
{
    if (isEmptywinnerList(*lst) == true)
    {
        newTail->next = newTail->prev = NULL;
        lst->head = lst->tail = newTail;
    }
    else
    {
        newTail->prev = lst->tail;
        newTail->next = NULL;
        lst->tail->next = newTail;
        lst->tail = newTail;
    }
}
void freePlayerList(playerList lst)
{
    playerListNode* curr = lst.head, * next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}
void freewinnerList(winnerList lst)
{
    winnerListNode* curr = lst.head, * next;

    while (curr != NULL)
    {
        next = curr->next;


        freeArr(curr->player->possibilities);
        free(curr);
        curr = next;
    }
}
void freeList(cellList lst)
{
    cellListNode* curr = lst.head, * next;

    while (curr != NULL)
    {
        next = curr->next;
        free(curr);
        curr = next;
    }
}
void freePlayer(playerListNode* node)
{
    free(node->player->board);
    freeArr(node->player->possibilities);
}
void printPlayerList(playerList* lst)
{
    playerListNode* curr;

    curr = lst->head;

    while (curr != NULL)
    {
        printf("%s\n", curr->player->name);
        sudokoPrintBoard(curr->player->board);
        curr = curr->next;
    }

    printf("\n");
}
void printwinnerList(winnerList* lst)
{
    winnerListNode* curr;

    curr = lst->head;

    while (curr != NULL)
    {
        printf("%s\n", curr->player->name);
        sudokoPrintBoard(curr->player->board);
        curr = curr->next;
    }

    printf("\n");
}