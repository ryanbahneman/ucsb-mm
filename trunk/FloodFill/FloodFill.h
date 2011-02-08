#include <queue>
#include "Maze_Definitions.h"

void floodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc goal);
void solveMaze(unsigned int currentMazeArray[][16], unsigned int emptyMazeArray[][16],  Loc nextStack[256], Loc start);
void mapSurroundings(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int r, int c);