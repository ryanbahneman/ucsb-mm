#ifndef _MAZEFLOOD_H
#define	_MAZEFLOOD_H

#include "MazeDefinitions.h"

/*
Runs the floodfill algorithm on the given maze.

Floodfill starts from the goal and moves outwards until every reachable square has been processed

Stores the distance from the center in the upper bits of the maze integers

*/

void FloodFill(unsigned int maze[][16], int xGoal, int yGoal);


#endif	/* _MAZEFLOOD_H */

