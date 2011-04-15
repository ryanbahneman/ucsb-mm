#include "floodFill.h"


#include "Maze_Definitions.h"

void floodFill(unsigned int currentMazeArray[][NUM_COLS], unsigned int floodValues[][NUM_COLS], struct Loc goal)
{
	bool complete = false;
	unsigned int dist = 0;
	Loc tempLoc;
	Loc possibleNeighbor;

	//set up the queues
	Loc currentQueue[256];
	int currentQueueLength = 0;

	Loc nextQueue[256];
	int nextQueueLength = 0;

	//set all the flood values to 256
	int r = 0;
	int c = 0;
	int k = 0;
	int l = 0;

	for(r = 0; r < 16; r++)
	{
		for(c = 0; c < 16; c++)
		{
			floodValues[r][c] = 128;
			//visitedOrNot[r][c] =
		}
	}

	//set the goal in the current queue
	currentQueue[currentQueueLength] = goal;
	currentQueueLength++;

	while(!complete)
	{
		//for all values in the current Queue
		for (k = 0; k < currentQueueLength; k++)
		{
			//"pull" the current value off of the queue
			tempLoc = currentQueue[k];
			//set the value = to the current distance
			floodValues[tempLoc.row][tempLoc.col] = dist;
			//find neighbors and add them to the nextQueue

			//West
			//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
			if((tempLoc.col > 0) && ((currentMazeArray[tempLoc.row][tempLoc.col] & WEST) != WEST) && (floodValues[tempLoc.row ][tempLoc.col-1] & 128) == 128)
			{
				possibleNeighbor.row = tempLoc.row;
				possibleNeighbor.col = tempLoc.col - 1;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].row == possibleNeighbor.row && currentQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for( l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].row == possibleNeighbor.row && nextQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true)
				{
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}

			//East
			//check to see if there is a cell to the right & there is no wall to the east & the cell to the left hasn't been assigned a value
			if((tempLoc.col < 15) && ((currentMazeArray[tempLoc.row][tempLoc.col] & EAST) != EAST) && (floodValues[tempLoc.row ][tempLoc.col+1] & 128) == 128)
			{
				possibleNeighbor.row = tempLoc.row;
				possibleNeighbor.col = tempLoc.col+1;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for( l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].row == possibleNeighbor.row && currentQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for ( l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].row == possibleNeighbor.row && nextQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true)
				{
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}

			//North
				//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
			if((tempLoc.row > 0) && ((currentMazeArray[tempLoc.row][tempLoc.col] & NORTH) != NORTH) && (floodValues[tempLoc.row-1][tempLoc.col] & 128) == 128)
			{
				possibleNeighbor.row = tempLoc.row-1;
				possibleNeighbor.col = tempLoc.col;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for( l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].row == possibleNeighbor.row && currentQueue[l].col == possibleNeighbor.col){
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for( l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].row == possibleNeighbor.row && nextQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true)
				{
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}
			//South
				//check to see if there is a cell to the below & there is no wall to the south & the cell to the left hasn't been assigned a value
			if((tempLoc.row < 15) && ((currentMazeArray[tempLoc.row][tempLoc.col] & SOUTH) != SOUTH) && (floodValues[tempLoc.row+1][tempLoc.col] & 128) == 128){
				possibleNeighbor.row = tempLoc.row+1;
				possibleNeighbor.col = tempLoc.col;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for( l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].row == possibleNeighbor.row && currentQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for( l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].row == possibleNeighbor.row && nextQueue[l].col == possibleNeighbor.col)
					{
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true)
				{
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}
		}//end of current queue for loop

		//check to see that the next queue isn't empty
		if(nextQueueLength != 0)
		{
			//copy the next queue to the current queue
			for( k = 0; k < nextQueueLength; k++)
			{
				currentQueue[k] = nextQueue[k];
			}
			//update queue lengths
			currentQueueLength = nextQueueLength;
			nextQueueLength = 0;

			//increment the distance
			dist++;
		}
		else
		{
			complete = true;
		}

	}
}

unsigned int getNewDirection(Loc currentPosition, unsigned int maze[][NUM_COLS], unsigned int floodValues[][NUM_COLS])
{
	// Currently chooses the smallest value. Will be re implemented later.
	// Possible ideas: Think three moves ahead which will help make smoother curves

	int currentRow = currentPosition.row;
	int currentCol = currentPosition.col;

	unsigned int newDirection = 0;

	int min = 512;

	if((currentCol > 0) && ((maze[currentRow][currentCol] & WEST) != WEST))
	{
		if (min > floodValues[currentRow][currentCol-1])
		{
			min = floodValues[currentRow][currentCol-1];
			newDirection = WEST;
		}
	}
	if((currentCol < 15) && ((maze[currentRow][currentCol] & EAST) != EAST))
	{
		if (min > floodValues[currentRow][currentCol+1])
		{
			min = floodValues[currentRow][currentCol+1];
			newDirection = EAST;
		}
	}
	if((currentRow < 15) && ((maze[currentRow][currentCol] & SOUTH) != SOUTH))
	{
		if (min > floodValues[currentRow+1][currentCol])
		{
			min = floodValues[currentRow+1][currentCol];
			newDirection = SOUTH;
		}
	}
	if((currentRow > 0) && ((maze[currentRow][currentCol] & NORTH) != NORTH))
	{
		if (min > floodValues[currentRow-1][currentCol])
		{
			min = floodValues[currentRow-1][currentCol];
			newDirection = NORTH;
		}
	}
	return newDirection;
}

void updateWalls(unsigned int newWalls, unsigned int maze[][NUM_COLS], Loc currentPosition)
{

	unsigned int x = currentPosition.row;
	unsigned int y = currentPosition.col;

	if ((newWalls & NORTH) == NORTH)
	{
		maze[x][y] |= NORTH;
		if (x-1 >= 0)
			maze[x-1][y] |= SOUTH;
	}
	if ((newWalls & SOUTH) == SOUTH)
	{
		maze[x][y] |= SOUTH;
		if (x+1 <= 15)
			maze[x+1][y] |= NORTH;
	}
	if ((newWalls & WEST) == WEST)
	{
		maze[x][y] |= WEST;
		if (y- 1 >= 0)
			maze[x][y-1] |= EAST;
	}
	if ((newWalls & EAST) == EAST)
	{
		maze[x][y] |= EAST;
		if (y+1 >= 0)
			maze[x][y+1] |= WEST;
	}

}

unsigned int measureWalls (unsigned int currentDirection)
{

}

void modifiedFloodfill(unsigned int maze[][NUM_COLS], unsigned int floodValues[][NUM_COLS], Loc goal)
{

}

void updateCurrentLocation(Loc* currentLocation, unsigned int newDirection)
{
	int currentRow = currentLocation->row;
	int currentCol = currentLocation->col;

	if (newDirection == WEST)
	{
		currentLocation->col = currentCol - 1;
	}
	else if (newDirection == EAST)
	{
		currentLocation->col = currentCol + 1;
	}
	else if (newDirection == NORTH)
	{
		currentLocation->row = currentRow - 1;
	}
	else if (newDirection == SOUTH)
	{
		currentLocation->row = currentRow + 1;
	}
}
