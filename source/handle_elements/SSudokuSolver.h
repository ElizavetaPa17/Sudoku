#pragma once
#include <iostream>
#include <cmath>
#include <string>
#include <ctime>

#include "SBoard.h"

#define SIZE 9
#define MAX_K 1000
    
const int SIZE_SQUARED = SIZE*SIZE;
const int SIZE_SQRT = sqrt((double)SIZE);
const int ROW_NB = SIZE*SIZE*SIZE;
const int COL_NB = 4 * SIZE*SIZE;

struct Node {

	Node *left;
	Node *right;
	Node *up;
	Node *down;
	Node *head;
	
	int size;		
	int rowID[3];	
};

class SSudokuSolver final {
private:
    struct Node Head;
    struct Node* HeadNode = &Head;
    struct Node* solution[MAX_K];
    struct Node* orig_values[MAX_K];
    bool matrix[ROW_NB][COL_NB] = { { 0 } };
    bool isSolved = false;

    void coverColumn(Node* col);
    void uncoverColumn(Node* col);
    void search(int k);

    void BuildSparseMatrix(bool matrix[ROW_NB][COL_NB]);
    void BuildLinkedList(bool matrix[ROW_NB][COL_NB]);
    void TransformListToCurrentGrid(int Puzzle[][SIZE]);
    void MapSolutionToGrid(int Sudoku[][SIZE]);
public:
    bool SolveSudoku(int Sudoku[][SIZE]);
};
