#include <stdio.h>
#include <stdlib.h>

#include "Maze_Definitions.h"
#include "floodFill.h"

void init(unsigned int maze[][16], unsigned int floodValues[][16], Loc goal)
{
	floodFill(maze,floodValues,goal); // initializes the initial flood values

	// sets the edge of the maze
	int i = 0;
	for (i = 0; i < 16; i++)
		maze[i][0] |= WEST;
	for (i = 0; i < 16; i++)
		maze[i][15] |= EAST;
	for (i = 0; i < 16; i++)
		maze[0][i] |= NORTH;
	for (i = 0; i < 16; i++)
		maze[15][i] |= SOUTH;
}

int main(void)
{
	//initializes individual variables needed throughout the program

	unsigned int maze[NUM_ROWS][NUM_COLS];			// maze hodling the walls
	unsigned int floodValues[NUM_ROWS][NUM_COLS];	// flood values
	unsigned int currentDirection = WEST;			// direction mouse is facing
	unsigned int newDirection = 0;
	unsigned int wallInfo = 0;

	unsigned int numSteps = 0;

	Loc goal;
	goal.row = GOALR; goal.col = GOALC;					// goal

	Loc currentLocation;							// currentPosition
	currentLocation.row = STARTR;
	currentLocation.col = STARTC;

	Loc currentGoal;								// current Goal
	currentGoal.row = GOALR;
	currentGoal.col = GOALC;

	Loc start;
	start.row = STARTR; start.col = STARTC;

	init(maze,floodValues,currentGoal);				// initializes the maze

	bool mazeMapped = false;
	bool goalReached = false;

	while (mazeMapped == false)
	{
		wallInfo = measureWalls(currentDirection);			  				// NOT DONE
		updateWalls(wallInfo,maze,currentLocation);							// DONE
		modifiedFloodfill(floodValues,maze,currentLocation);				// NOT DONE
		newDirection = getNewDirection(currentLocation,maze,floodValues); 	// DONE
		//the less turning the better
		//turn(&currentDirection,newDirection);								// NOT DONE
		//move1cell();														// NOT DONE
		numSteps++;
		updateCurrentLocation(&currentLocation,newDirection);				// DONE
		goalReached = (currentLocation.row == currentGoal.row &&
					   currentLocation.col == currentGoal.col);

		if (goalReached == true)
		{
			if (currentGoal.row == goal.row && currentGoal.col == goal.col)
			{
				currentGoal = start;
			}
			else
			{
				if (numSteps == maze[currentLocation.row][currentLocation.col])
				{
					mazeMapped = true;
				}
				else
				{
					currentGoal = goal;

				}
			}
			numSteps = 0;
			floodFill(maze,floodValues,currentGoal);
		}
	}
	return 0;
}
