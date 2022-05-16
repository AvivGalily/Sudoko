#ifndef _firstFuncs_Header
#define _firstFuncs_Header

#include "structs.h"

void sudokoPrintBoard(short board[][SIZE]);
CellPossibilities*** PossibleDigits(short sudokuBoard[][SIZE]);
int checkCol(short sudokuBoard[][SIZE], int row, int col, bool* digits);
int checkRow(short sudokuBoard[][SIZE], int row, int col, bool* digits);
CellPossibilities* countOptionsForCell(short sudokuBoard[][SIZE], int i, int j);
int checkSquares(short sudokuBoard[][SIZE], int row, int col, bool* digits);
void checkMemoryAllocation(void* ptr);
bool checkDuplication(short sudokuBoard[][SIZE]);
int FillBoard(short board[][SIZE], CellPossibilities*** possibilities);
void updatePossibilities(CellPossibilities*** possibilities, int row, int col, int num);
void updateSquares(CellPossibilities*** possibilities, int row, int col, int num);
void updateCell(CellPossibilities* arry, int num);
void updateRow(CellPossibilities*** possibilities, int row, int col, int num);
void updateCol(CellPossibilities*** possibilities, int row, int col, int num);
int OneStage(short board[][SIZE], CellPossibilities*** possibilities, int* x, int* y);
void freeArr(CellPossibilities*** possibilities);

#endif // !_firstFuncs_Header
