
#ifndef _SOLVE_H
#define	_SOLVE_H


#include "MazeDefinitions.h"
#include "MazeBuild.h"
#include "MazeFlood.h"
#include "MazeDraw.h"

/* 
The core of our maze solving algorithms. 
Moves from Start to Goal by calling the floodfill algorithm each time it enters a new cell.
It then moves from its current location to the neighboring cell with the lowest floodfill value.
It assumes it only knows the wall locations that it has previously seen when computing floodfill.
It updates its 'mental map' using vaules from the actual maze each time it enters a new cell.

Returns the number of steps taken to reach the goal location
 */

int GoFFtoCellConfigurable(unsigned int map[][16], unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal, bool print);

/*

Calls GoFFtoCellConfigurable with print set to false

*/

int GoFFtoCell(unsigned int map[][16], unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal);

/* 
This is a simple solution to find the fastest route
It uses floodfill everytime it moves to a new cell and updates a wall.
when it finds the center it retraces it's steps (not acutally coded here [I simply
multiplied the number of steps to the center by 2 and reset the starting location
to 0,0])
This is extremely inefficient and was only created as a benchmark
 
Returns the number of steps taken
 */

int SolveWithFF0(unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal);


/* 
This solution is slightly more elegant than FF0.
Once it reaches the center it switches the goal and start location and tries to
get back to the center in as few steps as possible.

Returns the number of steps taken
*/
int SolveWithFF1(unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal, bool print);

#endif	/* _SOLVE_H */

