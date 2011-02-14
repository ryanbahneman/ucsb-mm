#include <queue>
#include "Maze_Definitions.h"

void floodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc goal);
void solveMaze(unsigned int currentMazeArray[][16], unsigned int floodvalues[][16], unsigned int emptyMazeArray[][16], 
	Loc start, Loc* current);
void mapSurroundings(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int r, int c);