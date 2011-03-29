#include <queue>
#include "Maze_Definitions.h"

void floodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc, Loc goal);
void modifiedFloodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc);
bool checkIfMazeNeedsToBeReflooded(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc);

bool checkIfMazeNeedsToBeReflooded(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc);


void solveMaze(unsigned int currentMazeArray[][16], unsigned int floodvalues[][16], unsigned int emptyMazeArray[][16], 
	Loc* current, int* found);
void mapSurroundings(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int r, int c);
//int chooseSideToExplore(