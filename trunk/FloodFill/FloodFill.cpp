#include "stdafx.h"
#include "FloodFill.h"
#include "Maze_Definitions.h"




void floodFill(unsigned int currentMazeArray[][16], unsigned int floodValues[][16], Loc goal)
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
	for(int r = 0; r <16; r++){
		for(int c = 0; c < 16; c++){
			floodValues[r][c] = 255;
		}

	}

	//set the goal in the current queue
	currentQueue[currentQueueLength] = goal;
	currentQueueLength++;

	while(!complete){

		//for all values in the current Queue
		for(int k = 0; k < currentQueueLength; k++){
			//"pull" the current value off of the queue
			tempLoc = currentQueue[k];
			//set the value = to the current distance
			floodValues[tempLoc.x][tempLoc.y] = dist;
			//find neighbors and add them to the nextQueue
			//West
				//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
			if((tempLoc.x > 0) && !(currentMazeArray[tempLoc.x][tempLoc.y] & WEST) && (floodValues[tempLoc.x - 1][tempLoc.y]) == 255){
				possibleNeighbor.x = tempLoc.x -1;
				possibleNeighbor.y = tempLoc.y;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++){
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++){
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true){
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}

			//East
				//check to see if there is a cell to the right & there is no wall to the east & the cell to the left hasn't been assigned a value
			if((tempLoc.x < 15) && !(currentMazeArray[tempLoc.x][tempLoc.y] & EAST) && (floodValues[tempLoc.x + 1][tempLoc.y]) == 255){
				possibleNeighbor.x = tempLoc.x +1;
				possibleNeighbor.y = tempLoc.y;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++){
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++){
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true){
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}

			//North
				//check to see if there is a cell to the left & there is no wall to the west & the cell to the left hasn't been assigned a value
			if((tempLoc.y > 0) && !(currentMazeArray[tempLoc.x][tempLoc.y] & NORTH) && (floodValues[tempLoc.x][tempLoc.y - 1]) == 255){
				possibleNeighbor.x = tempLoc.x;
				possibleNeighbor.y = tempLoc.y - 1;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++){
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++){
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true){
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}
			//South
				//check to see if there is a cell to the below & there is no wall to the south & the cell to the left hasn't been assigned a value
			if((tempLoc.y < 15) && !(currentMazeArray[tempLoc.x][tempLoc.y] & SOUTH) && (floodValues[tempLoc.x][tempLoc.y + 1]) == 255){
				possibleNeighbor.x = tempLoc.x;
				possibleNeighbor.y = tempLoc.y + 1;
				//check to see if the neighbor is in the current queue
				bool addToQueue = true;
				for(int l = 0; l < currentQueueLength; l++){
					//don't check yourself
					if(l == k)
						continue;
					if(currentQueue[l].x == possibleNeighbor.x && currentQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//see if it has been added to the next queue
				for(int l = 0; l < nextQueueLength; l++){
					if(nextQueue[l].x == possibleNeighbor.x && nextQueue[l].y == possibleNeighbor.y){
						addToQueue = false;
						break;
					}
				}
				//add to next queue
				if(addToQueue == true){
					nextQueue[nextQueueLength] = possibleNeighbor;
					nextQueueLength++;
				}
			}
		}//end of current queue for loop

		//check to see that the next queue isn't empty
		if(nextQueueLength != 0){
			//copy the next queue to the current queue
			for(int k = 0; k < nextQueueLength; k++){
				currentQueue[k] = nextQueue[k];
			}
			//updat queue lengths
			currentQueueLength = nextQueueLength;
			nextQueueLength = 0;

			//increment the distance
			dist++;
		}
		else{//you are done
			complete = true;
		}

	}//end while loop


	

}


