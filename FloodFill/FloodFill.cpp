#include "stdafx.h"
#include "FloodFill.h"
#include "Maze_Definitions.h"
#include <stack>
#include <GL/glut.h>


void sleep2(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}

void mapSurroundings(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int x, int y)
{
	if ((actualMaze[x][y] & NORTH) == NORTH)
	{
		unmappedMaze[x][y] |= NORTH;
		if (x-1 >= 0)
		unmappedMaze[x-1][y] |= SOUTH;
	}
	if ((actualMaze[x][y] & SOUTH) == SOUTH)
	{
		unmappedMaze[x][y] |= SOUTH;
		if (x+1 <= 15)
		unmappedMaze[x+1][y] |= NORTH;
	}		
	if ((actualMaze[x][y] & WEST) == WEST)
	{
		unmappedMaze[x][y] |= WEST;
		if (y- 1 >= 0)
		unmappedMaze[x][y-1] |= EAST;
	}		
	if ((actualMaze[x][y] & EAST) == EAST)
	{
		unmappedMaze[x][y] |= EAST;
		if (y+1 >= 0)
		unmappedMaze[x][y+1] |= WEST;
	}
}

void solveMaze(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], unsigned int emptyMazeArray[][16], 
	Loc* current, int* found)
{
	int x = current->x;
	int y = current->y;
	cout << emptyMazeArray[current->x][current->y];
	int min = 1000;

	if((current->y > 0) && ((emptyMazeArray[current->x][current->y] & WEST) != WEST)) 
	{
			
		cout << "!!!!!!!!!!!" << endl;
		if (min > floodValues[current->x][current->y-1])
		{
			min = floodValues[current->x][current->y-1];
			x = current->x;
			y = current->y-1;
		}	
	}
	if((current->y < 15) && ((emptyMazeArray[current->x][current->y] & EAST) != EAST)) 
	{
		if (min > floodValues[current->x][current->y+1])
		{
			
			min = floodValues[current->x][current->y+1];
			x = current->x;
			y = current->y+1;
		}	
	}
	if((current->x < 15) && ((emptyMazeArray[current->x][current->y] & SOUTH) != SOUTH)) 
	{
		if (min > floodValues[current->x+1][current->y])
		{
			min = floodValues[current->x+1][current->y];
			x = current->x+1;
			y = current->y;
		}	
	}
	if((current->x > 0) && ((emptyMazeArray[current->x][current->y] & NORTH) != NORTH)) 
	{
		if (min > floodValues[current->x-1][current->y])
		{
			min = floodValues[current->x-1][current->y];
			x = current->x-1;
			y = current->y;
		}	
	}
	if (*found == 1)
	{
		if (floodValues[x][y] == 0)
		{
				*found = 0;
				for(int r = 0; r <16; r++)
				{
					for(int c = 0; c < 16; c++)
					{
						//emptyMazeArray[r][c] = 256;
					}
				}
		}
	}
	current->x = x;
	current->y = y;

	cout << current->x << " " << current->y << endl;

	
	//if (emptyMazeArray
}

//===================================FLOOD FILL==========================================//
void floodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc, Loc goal)
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

	unsigned int visitedOrNot[16][16];


	//set all the flood values to 256
	for(int r = 0; r < 16; r++)
	{
		for(int c = 0; c < 16; c++)
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
		for (int k = 0; k < currentQueueLength; k++)
		{
			//"pull" the current value off of the queue
			tempLoc = currentQueue[k];
			//set the value = to the current distance
			floodValues[tempLoc.x][tempLoc.y] = dist;			
			//find neighbors and add them to the nextQueue
			
			//West
			//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
			if((tempLoc.y > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & WEST) != WEST) && (floodValues[tempLoc.x ][tempLoc.y-1] & 128) == 128)
			{
				possibleNeighbor.x = tempLoc.x;
				possibleNeighbor.y = tempLoc.y - 1;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y)
					{
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y)
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
			if((tempLoc.y < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & EAST) != EAST) && (floodValues[tempLoc.x ][tempLoc.y+1] & 128) == 128)
			{
				possibleNeighbor.x = tempLoc.x;
				possibleNeighbor.y = tempLoc.y+1;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y)
					{
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for (int l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y)
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
			if((tempLoc.x > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & NORTH) != NORTH) && (floodValues[tempLoc.x-1][tempLoc.y] & 128) == 128)
			{
				possibleNeighbor.x = tempLoc.x-1;
				possibleNeighbor.y = tempLoc.y;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y)
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
			if((tempLoc.x < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & SOUTH) != SOUTH) && (floodValues[tempLoc.x+1][tempLoc.y] & 128) == 128){
				possibleNeighbor.x = tempLoc.x+1;
				possibleNeighbor.y = tempLoc.y;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++)
				{
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y)
					{
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++)
				{
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y)
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
			for(int k = 0; k < nextQueueLength; k++)
			{
				currentQueue[k] = nextQueue[k];
			}
			//updat queue lengths
			currentQueueLength = nextQueueLength;
			nextQueueLength = 0;

			//increment the distance
			dist++;
		}
		else
		{
			complete = true;
		}

	}//end while loop
	//===========================================================================================================
	
}
void modifiedFloodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc)
{
	bool complete = false;
	unsigned int dist = 0;
	Loc tempLoc;
	Loc possibleNeighbor;	

	int count = 0;
	//set up the queues
	Loc currentQueue[256];
	int currentQueueLength = 0;
	
	Loc nextQueue[256];
	int nextQueueLength = 0;	
	
	currentQueue[currentQueueLength] = currentLoc;
	currentQueueLength++;

	// MODIFIED FLOODFILL

	stack<Loc> s;
	s.push(currentLoc);

	while(!s.empty())
	{
		count++;
		Loc location = s.top();
		tempLoc = location;
		s.pop();

		int currentDistance = floodValues[tempLoc.x][tempLoc.y];
		int result = checkIfMazeNeedsToBeReflooded(currentMazeArray, floodValues, tempLoc);
		//cout << result;

		if (result == -1)
		{
			continue;
		}
		else
		{
			floodValues[tempLoc.x][tempLoc.y] = result + 1;
			int tempVal = floodValues[tempLoc.x][tempLoc.y];
			if((tempLoc.y > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & WEST) != WEST))
			{
				possibleNeighbor.x = tempLoc.x;
				possibleNeighbor.y = tempLoc.y - 1;	
				s.push(possibleNeighbor);								
			}

			//East
			//check to see if there is a cell to the right & there is no wall to the east & the cell to the left hasn't been assigned a value
			if((tempLoc.y < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & EAST) != EAST))
			{
				possibleNeighbor.x = tempLoc.x;
				possibleNeighbor.y = tempLoc.y+1;
				s.push(possibleNeighbor);	
				
			}

			//North
				//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
			if((tempLoc.x > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & NORTH) != NORTH))
			{
				possibleNeighbor.x = tempLoc.x-1;
				possibleNeighbor.y = tempLoc.y;				
				s.push(possibleNeighbor);	
				
			}
			//South			
			if((tempLoc.x < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & SOUTH) != SOUTH))
			{
				possibleNeighbor.x = tempLoc.x+1;
				possibleNeighbor.y = tempLoc.y;
				s.push(possibleNeighbor);				
			}
		}
	}
	//cout << endl;
		//for (int k = 0; k < currentQueueLength; k++)
		//{
		//	tempLoc = currentQueue[k];		
		//	int currentDistance = floodValues[tempLoc.x][tempLoc.y];

		//	int result = checkIfMazeNeedsToBeReflooded(currentMazeArray, floodValues, currentLoc);
		//	//cout << result;

		//	if (result == -1)
		//	{
		//		continue;
		//	}
		//	else
		//	{
		//		floodValues[tempLoc.x][tempLoc.y] = result + 1;
		//		if((tempLoc.y > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & WEST) != WEST))
		//		{
		//			possibleNeighbor.x = tempLoc.x;
		//			possibleNeighbor.y = tempLoc.y - 1;				
		//			
		//			nextQueue[nextQueueLength] = possibleNeighbor;
		//			nextQueueLength++;						
		//							
		//		}

		//		//East
		//		//check to see if there is a cell to the right & there is no wall to the east & the cell to the left hasn't been assigned a value
		//		if((tempLoc.y < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & EAST) != EAST))
		//		{
		//			possibleNeighbor.x = tempLoc.x;
		//			possibleNeighbor.y = tempLoc.y+1;
		//			//check to see if the neighbor is in the current queue
		//			nextQueue[nextQueueLength] = possibleNeighbor;
		//			nextQueueLength++;	
		//		
		//		}

		//		//North
		//			//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
		//		if((tempLoc.x > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & NORTH) != NORTH))
		//		{
		//			possibleNeighbor.x = tempLoc.x-1;
		//			possibleNeighbor.y = tempLoc.y;				
		//	
		//			nextQueue[nextQueueLength] = possibleNeighbor;
		//			nextQueueLength++;	
		//		
		//		}
		//		//South			
		//		if((tempLoc.x < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & SOUTH) != SOUTH))
		//		{
		//			possibleNeighbor.x = tempLoc.x+1;
		//			possibleNeighbor.y = tempLoc.y;
		//		
		//			nextQueue[nextQueueLength] = possibleNeighbor;
		//			nextQueueLength++;	
		//		
		//		}
		//	}

		//	
		//}//end of current queue for loop

		////check to see that the next queue isn't empty
		//if(nextQueueLength != 0)
		//{
		//	//copy the next queue to the current queue
		//	for(int k = 0; k < nextQueueLength; k++)
		//	{
		//		currentQueue[k] = nextQueue[k];
		//	}
		//	//updat queue lengths
		//	currentQueueLength = nextQueueLength;
		//	nextQueueLength = 0;			
		//}
		//else
		//{
		//	complete = true;
		//}		
		
}

int checkIfMazeNeedsToBeReflooded(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc currentLoc)
{
	Loc tempLoc = currentLoc;

	//dont need to check the goal location
	if (floodValues[tempLoc.x][tempLoc.y] == 0)
		return (-1);

	//find the minimum value of the neighbors
	unsigned int minNeighbor;
	minNeighbor = 255;


	//West
	if((tempLoc.y > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & WEST) != WEST))
	{
		if (floodValues[tempLoc.x][tempLoc.y-1] < minNeighbor)
			minNeighbor = floodValues[tempLoc.x][tempLoc.y-1];
	}	
	//North
	if((tempLoc.x > 0) && ((currentMazeArray[tempLoc.x][tempLoc.y] & NORTH) != NORTH))
	{
		if (floodValues[tempLoc.x-1][tempLoc.y] < minNeighbor)
			minNeighbor = floodValues[tempLoc.x-1][tempLoc.y];
	}
	//East
	if((tempLoc.y < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & EAST) != EAST))
	{
		if (floodValues[tempLoc.x][tempLoc.y+1] < minNeighbor)
			minNeighbor = floodValues[tempLoc.x][tempLoc.y+1];
	}
	//South
	if((tempLoc.x < 15) && ((currentMazeArray[tempLoc.x][tempLoc.y] & SOUTH) != SOUTH))
	{
		if (floodValues[tempLoc.x+1][tempLoc.y] < minNeighbor)
			minNeighbor = floodValues[tempLoc.x+1][tempLoc.y];
	}
	
	//the current cell values
	unsigned int currentFloodValue = floodValues[tempLoc.x][tempLoc.y];

	//cout << minNeighbor << endl;

	//if the cell value isn't equal to 1 + the min neighbor, return the value of the minimum neighbor
	if (currentFloodValue != 1 + minNeighbor)
		return (minNeighbor);
	else //cell does not need to be updated
		return (-1);

}


