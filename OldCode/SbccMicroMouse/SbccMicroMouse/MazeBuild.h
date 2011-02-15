
#ifndef _MAZEBUILD_H
#define	_MAZEBUILD_H

#include "MazeDefinitions.h"
#include "MazeFlood.h"

#include <stdlib.h>

/*
Used to generate a random maze. 

The maze generation algorithm doesn't inherently have loops, so they must be added post-generation. 
The loops are created by randomly knocking down walls. 

To conform with the official maze, the four middle squares are connected and only one path to theses squares. 
This is done post-generation and usually makes the maze unsolvable. Knocking down walls greatly increases the 
likely hood that a maze will be solvable.

returns 0 if the maze is solvable, 1 otherwise
*/

int MakeMaze(unsigned int maze[][16], int loops);

/*
do NOT call this function

This is used by MakeMaze to do the initial generation
*/

void BuildMaze(unsigned int maze[][16], int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum);

/*

Takes a maze and adds walls around the perimiter.
While not stricly necessary, it makes the display nicer.

*/
void InitializeMap(unsigned int map[][16]);



#endif	/* _MAZEBUILD_H */

