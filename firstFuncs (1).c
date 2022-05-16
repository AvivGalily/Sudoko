#include "firstFuncs.h"

void sudokoPrintBoard(short board[][SIZE])
{
    int i, j;

    printf("  ");
    for (int i = 0; i < SIZE; i++)
    {
        if (i % 3 == 0)
            printf("|");
        printf("%2d", i);
    }
    printf("\n");
    for (i = 0; i < SIZE; i++) // print the the board
    {
        if (i % 3 == 0)
            printf("-----------------------\n");
        printf("%2d", i);


        for (j = 0; j < SIZE; j++)
        {
            if (j % 3 == 0)  // finds start of cube
                printf("|");

            if (board[i][j] == -1) // empty cell
                printf("  ");

            else
                printf("%2d", board[i][j]); // not empty cell
        }
        printf("\n");
    }

    printf("-----------------------\n");
}
CellPossibilities*** PossibleDigits(short sudokuBoard[][SIZE])
{
    CellPossibilities*** possibilitiesArr = (CellPossibilities***)malloc(SIZE * sizeof(CellPossibilities**));
    checkMemoryAllocation(possibilitiesArr);
    for (int ind = 0; ind < SIZE; ind++) {
        possibilitiesArr[ind] = (CellPossibilities**)malloc(SIZE * sizeof(CellPossibilities*));
        checkMemoryAllocation(possibilitiesArr[ind]);
    }


    //check all cells with (-1)
    //count how many digits for a single cell 
    for (int i = 0; i < SIZE; i++)
    {
        for (int j = 0; j < SIZE; j++) {
            if (sudokuBoard[i][j] != -1)
            {
                possibilitiesArr[i][j] = NULL;
            }
            else
            {
                possibilitiesArr[i][j] = countOptionsForCell(sudokuBoard, i, j);

            }
        }

    }
    return possibilitiesArr;

}
CellPossibilities* countOptionsForCell(short sudokuBoard[][SIZE], int i, int j) {
    CellPossibilities* optionsForCell;
    optionsForCell = (CellPossibilities*)malloc(sizeof(CellPossibilities));
    checkMemoryAllocation(optionsForCell);
    int countTrue = 0;
    int k = 0;
    bool digits[SIZE] = { true, true, true, true, true, true, true, true, true }; // "switches ON/OFF for used cells"

    //find square
    //check digits in square
    checkRow(sudokuBoard, i, j, digits);
    checkCol(sudokuBoard, i, j, digits);
    checkSquares(sudokuBoard, i, j, digits);
    for (int ind = 0; ind < SIZE; ind++) {   //counts the options array for the cell
        if (digits[ind] == true) {
            countTrue++;
        }
    }

    optionsForCell->size = countTrue;
    optionsForCell->arr = (short*)malloc(sizeof(short) * countTrue);
    checkMemoryAllocation(optionsForCell->arr);

    for (int indx = 0; indx < SIZE; indx++) {   // fills the options arr
        if (digits[indx] == true) {
            optionsForCell->arr[k] = indx + 1;
            k++;
        }
    }

    return optionsForCell;
}
int checkCol(short sudokuBoard[][SIZE], int row, int col, bool* digits)
{
    int res = 0;
    for (row = 0; row < SIZE; row++)
    {
        if (sudokuBoard[row][col] >= 1 && sudokuBoard[row][col] <= SIZE)
        {

            if (digits[sudokuBoard[row][col] - 1] == false)
            {
                res = -1;
            }
            else
            {
                digits[sudokuBoard[row][col] - 1] = false;
            }

        }
    }
    return res;

}
int checkRow(short sudokuBoard[][SIZE], int row, int col, bool* digits)
{
    int res = 0;
    for (col = 0; col < SIZE; col++)
    {
        if (sudokuBoard[row][col] >= 1 && sudokuBoard[row][col] <= SIZE)
        {
            if (digits[sudokuBoard[row][col] - 1] == false)
            {
                res = -1;
            }
            else
            {
                digits[sudokuBoard[row][col] - 1] = false;
            }

        }

    }
    return res;
}
int checkSquares(short sudokuBoard[][SIZE], int row, int col, bool* digits)
{
    int res = 0;
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (sudokuBoard[i][j] >= 1 && sudokuBoard[i][j] <= 9) {
                if (digits[sudokuBoard[i][j] - 1] == false)
                {
                    res = -1;
                }
                else
                {
                    digits[sudokuBoard[i][j] - 1] = false;
                }

            }
        }
    }
    return res;
}
int OneStage(short board[][SIZE], CellPossibilities*** possibilities, int* x, int* y) {
    int row, col;
    bool flag = true, nextMove;
    int getNum, minFinder = SIZE;
    while (flag)
    {
        flag = nextMove = false;
        for (row = 0; row < SIZE; row++)
        {
            for (col = 0; col < SIZE; col++)
            {
                if (possibilities[row][col] != NULL)
                {
                    if (possibilities[row][col]->size == 1) //finds the cells with minimum number of possible values
                    {
                        flag = true;
                        getNum = possibilities[row][col]->arr[0];  // get the num from the 1 sized arr
                        free(possibilities[row][col]->arr);
                        free(possibilities[row][col]);
                        possibilities[row][col] = NULL;           
                        board[row][col] = getNum;            // fills board 
                        updatePossibilities(possibilities, row, col, getNum);  // updating the possibilities arr , new options were made
                        if (checkDuplication(board) == false) {
                            return FINISH_FAILURE;
                        }
                    }
                    else
                    {
                        if (possibilities[row][col]->size < minFinder) { // updates the coordinates of the new cell with min number of possible values
                            minFinder = possibilities[row][col]->size;
                            *x = row;
                            *y = col;
                        }
                        nextMove = true;
                    }
                }
            }
        }
    }

    if (!nextMove) // finished board
        return FINISH_SUCCESS;


    if (checkDuplication(board) == false) //duplication , thus failed and lost
        return FINISH_FAILURE;

    sudokoPrintBoard(board);

    return NOT_FINISH; // not finished and not failed
}
bool checkDuplication(short sudokuBoard[][SIZE]) {
    int row, col; int checkSquareRes, checkRowRes, checkColRes;
    bool digits[SIZE] = { true };
    memset(digits, true, sizeof(digits));
    for (row = 0; row < SIZE; row++) {
        for (col = 0; col < 9; col++) {
            checkSquareRes = checkSquares(sudokuBoard, row, col, digits);
            memset(digits, true, sizeof(digits));
            checkRowRes = checkRow(sudokuBoard, row, col, digits);
            memset(digits, true, sizeof(digits));
            checkColRes = checkCol(sudokuBoard, row, col, digits);
            memset(digits, true, sizeof(digits));
            if (checkSquareRes == -1 || checkRowRes == -1 || checkColRes == -1)
            {
                return false;
            }
        }
    }
    return true;
}
int FillBoard(short board[][SIZE], CellPossibilities*** possibilities)
{
    int x, y, i;
    int userChoice;
    unsigned short numOfOptions;
    int status = NOT_FINISH;
    while (status == NOT_FINISH)
    {
        status = OneStage(board, possibilities, &x, &y);
        if (status == FINISH_FAILURE)
        {
            break;
        }
        else if (status == FINISH_SUCCESS)
            break;
        printf("Cell number [%d,%d] currently holds the minimum number of possible values, select one of the below:\n", x, y);
        if (possibilities[x][y] != NULL)
            numOfOptions = possibilities[x][y]->size;
        else
        {
            continue;
        }
        for (i = 0; i < numOfOptions; i++)
        {
            printf("%d. %d \n", i + 1, possibilities[x][y]->arr[i]);
        }
        scanf("%d", &userChoice);

        while (userChoice < 1 || userChoice > SIZE)
        {
            printf("Try again, please enter a valid number\n");
            scanf("%d", &userChoice);
        }

        printf("Updating cell %d with value %d\n", ((x * SIZE) + y), userChoice);
        board[x][y] = userChoice;
        free(possibilities[x][y]->arr);
        free(possibilities[x][y]);
        possibilities[x][y] = NULL;
        updatePossibilities(possibilities, x, y, userChoice);
    }
    return status;
}
void checkMemoryAllocation(void* ptr)
{
    if (ptr == NULL)
    {
        printf("Memory Allocation failed!!");
        exit(1);
    }
}
void updatePossibilities(CellPossibilities*** possibilities, int row, int col, int num)
{
    updateSquares(possibilities, row, col, num);
    updateRow(possibilities, row, col, num);
    updateCol(possibilities, row, col, num);
}
void updateSquares(CellPossibilities*** possibilities, int row, int col, int num)
{
    int startRow = (row / 3) * 3;
    int startCol = (col / 3) * 3;

    for (int i = startRow; i < startRow + 3; i++) {
        for (int j = startCol; j < startCol + 3; j++) {
            if (possibilities[i][j] != NULL)
                updateCell(possibilities[i][j], num);
        }
    }
}
void  updateCell(CellPossibilities* arry, int num)
{
    int size, i; bool numfinder = false; int place;
    if (arry->size == 0) {
        return;
    }
    else if (arry->size == 1)
    {
        arry = NULL;
    }
    else if (arry->size > 1)
    {
        size = arry->size;
        for (i = 0; i < size; i++) {
            if (arry->arr[i] == num) {
                numfinder = true;
                place = i;
            }
        }
        if (numfinder == true)
        {
            for (i = place; i < size - 1; i++) {
                arry->arr[i] = arry->arr[i + 1];

            }
            arry->arr = (short*)realloc(arry->arr, sizeof(short) * (size - 1));
            checkMemoryAllocation(arry->arr);
            arry->size = (size - 1);
        }
    }
    else return;
}
void updateRow(CellPossibilities*** possibilities, int row, int col, int num) {

    int i = row, j = col;
    for (j = 0; j < SIZE; j++)
    {
        if (possibilities[i][j] != NULL)
            updateCell(possibilities[i][j], num);
    }
}
void updateCol(CellPossibilities*** possibilities, int row, int col, int num) {

    int i = row, j = col;
    for (i = 0; i < SIZE; i++)
    {
        if (possibilities[i][j] != NULL)
            updateCell(possibilities[i][j], num);
    }
}
void freeArr(CellPossibilities*** possibilities)
{
    int i, j;
    for (i = 0; i < SIZE; i++)
    {
        for (j = 0; j < SIZE; j++)
        {
            if (possibilities[i][j] != NULL)
            {
                free(possibilities[i][j]->arr);
                free(possibilities[i][j]);
            }
        }
    }
    for (i = 0; i < SIZE; i++)
    {
        free(possibilities[i]);
    }
    free(possibilities); 
}