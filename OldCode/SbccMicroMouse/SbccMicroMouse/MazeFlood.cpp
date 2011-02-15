#include "MazeFlood.h"

void FloodFill(unsigned int maze[][16], int xGoal, int yGoal){

	//pre-processing of the maze
	int i, j;
	for( i = 0; i < SIDE; i++){//for every row
		for( j = 0; j < SIDE; j++){//for every collumn
			// set the the upper byte to 255. This is used to tell if a cell has been traveled to before and also will 
			maze[i][j] |= (255<<8);// eventually be where the distance from the center will be stored
		}
	}

	//initialize variables
	int level = 0;//distance from center
	const int MAX = 16*16-1;// maximum needed buffer size also used to check if the level is unvisited
	int currentLevel[MAX][2];// cells being explored on the current level
	int nextLevel[MAX][2];// cells to be explored on the next level
	int count;
	int endY = yGoal; //goal location
	int endX = xGoal;
	int current; //used to load the new level info into the maze integer

	//set up the first array with the goal location
	currentLevel[0][0] = endY;
	currentLevel[0][1] = endX;
	int currentLevelSize = 1;
	int nextLevelSize = 0;
	
	do {//until all the cells have been visited
    	count = 0;// keeps track of where in the array a new cell will go
        nextLevelSize=0;//reset the next level size

        for( i=0;i<currentLevelSize;i++) {//every cell in the level
			if (((maze[currentLevel[i][0]][currentLevel[i][1]] & 65280) >> 8) == MAX) {// the cell is unvisited
                current = level<<8; //set current equal to the level, shifted to be put into the integer 
                maze[currentLevel[i][0]][currentLevel[i][1]] &=255;//clear the upper byte
                maze[currentLevel[i][0]][currentLevel[i][1]] |= current;//load the level info into the upper byte
                        
				//add the neighbors that are unvisited to the next level array
				if((maze[currentLevel[i][0]][currentLevel[i][1]] & NORTH) != NORTH) { //no wall inbetween neighbors
                        nextLevel[count][0] = currentLevel[i][0] - 1;// add the neighbor to the next level array
                        nextLevel[count][1] = currentLevel[i][1];
                        count++;//increment the position that the next neighbor will be stored in the array
                        nextLevelSize++;//increment the next level size
                }
                if((maze[currentLevel[i][0]][currentLevel[i][1]] & EAST) != EAST) {
                        nextLevel[count][0] = currentLevel[i][0];
                        nextLevel[count][1] = currentLevel[i][1]+1;
                        count++;
                        nextLevelSize++;
                }
                if((maze[currentLevel[i][0]][currentLevel[i][1]] & SOUTH) != SOUTH) {
                        nextLevel[count][0] = currentLevel[i][0]+1;
                        nextLevel[count][1] = currentLevel[i][1];
                        count++;
                        nextLevelSize++;
                }
                if((maze[currentLevel[i][0]][currentLevel[i][1]] & WEST) != WEST) {
                        nextLevel[count][0] = currentLevel[i][0];
                        nextLevel[count][1] = currentLevel[i][1] - 1;
                        count++;
                        nextLevelSize++;
                }
            }
        }
		//copy the next level array into the current level array
        for( i =0;i<nextLevelSize;i++) {
                currentLevel[i][0] = nextLevel[i][0];
                currentLevel[i][1] = nextLevel[i][1];
        }
        currentLevelSize=nextLevelSize; //update the new current level size
        level++;// increment the level
	} while (nextLevelSize != 0);

}
