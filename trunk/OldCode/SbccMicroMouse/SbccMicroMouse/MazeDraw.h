#ifndef _MAZEDRAW_H
#define	_MAZEDRAW_H

/*
Draws the given maze to the screen
*/

void DrawMaze(unsigned int map[][16], unsigned int maze[][16], int mouseX, int mouseY, int goalX, int goalY);

#include "MazeDefinitions.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#endif	/* _MAZEDRAW_H */

