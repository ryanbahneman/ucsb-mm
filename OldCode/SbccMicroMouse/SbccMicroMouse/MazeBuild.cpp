#include "MazeBuild.h"



int MakeMaze(unsigned int maze[][16], int loops){

	//Initialize variables
	int xCurrent = 0, yCurrent = 0;
	int xStack[256], yStack[256], stackNum = 0;
	
	// populate the maze using the lowest four bits; bits (high -> low): WSEN
	//	(1 - wall, 0 - open)
    int i, j;
	for(i = 0; i < SIDE; i++){
		for(j = 0; j < SIDE; j++){
			maze[i][j] = ALLWALLS;
		}
	}

	//knocks down walls to create a maze
	BuildMaze(maze, xCurrent, yCurrent, xStack, yStack, stackNum);

	//Removes all but the wall information
	for(i = 0; i < SIDE; i++){
		for(j = 0; j < SIDE; j++){
				maze[i][j] &= ALLWALLS;
		}
	}

	// knock down walls to make loops
	while(loops > 0){

		//pick a random cell
		int randx = rand()%(SIDE-2) +1;
		int randy = rand()%(SIDE-2) +1;
		//pick side to knock down wall
		int randdir = rand()%4;
		int exit = 0;

		do{
			// make sure the cell has a wall to be knocked down
			if(maze[randy][randx] & (1<<((randdir)%4))){ 
				// If it does, then remove the appropriate walls
				if (randdir%4 == 0){
					maze[randy][randx] &= ~NORTH;
					maze[randy-1][randx] &= ~SOUTH;
					exit = 1;
				}
				else if (randdir%4 == 1){
					maze[randy][randx] &= ~EAST;
					maze[randy][randx+1] &= ~WEST;
					exit = 1;
				}
				else if (randdir%4 == 2){
					maze[randy][randx] &= ~SOUTH;
					maze[randy+1][randx] &= ~NORTH;
						exit = 1;
					}
				else if (randdir%4 == 3){
					maze[randy][randx] &= ~WEST;
					maze[randy][randx-1] &= ~EAST;
					exit = 1;
				}
			}
			else{// no wall to knock down
				if (randdir < 10)// termination condition
					randdir += 1;// try a different direction
				else{ //the cell has no walls to knock down
					exit = 1;// pretend it worked
					loops++;// this prevents infinite loops
				}

			}
		}while(exit == 0);
		loops -= 1;
	}

	//make a wall around the center
    maze[7][7] = (NORTH | WEST);
    maze[6][7] |= SOUTH;
    maze[7][6] |= EAST;
    maze[7][8] = (NORTH | EAST);
    maze[6][8] |= SOUTH;
    maze[7][9] |= WEST;
    maze[8][7] = (SOUTH | WEST);
    maze[8][6] |= EAST;
    maze[9][7] |= NORTH;
    maze[8][8] = (SOUTH | EAST);
    maze[8][9] |= WEST;
    maze[9][8] |= NORTH;

	// make one exit out of the center
	int hole = rand()%8;

	if (hole == 0){
	maze[7][7] &= ~NORTH;
	maze[6][7] &= ~SOUTH;
	}
	else if (hole == 1){
	maze[7][8] &= ~NORTH;
	maze[6][8] &= ~SOUTH;
	}
	else if (hole == 2){
	maze[7][8] &= ~EAST;
	maze[7][9] &= ~WEST;
	}
	else if (hole == 3){
	maze[8][8] &= ~EAST;
	maze[8][9] &= ~WEST;
	}
	else if (hole == 4){
	maze[8][8] &= ~SOUTH;
	maze[9][8] &= ~NORTH;
	}
	else if (hole == 5){
	maze[8][7] &= ~SOUTH;
	maze[9][7] &= ~NORTH;
	}
	else if (hole == 6){
	maze[8][7] &= ~WEST;
	maze[8][6] &= ~EAST;
	}
	else if (hole == 7){
	maze[7][7] &= ~WEST;
	maze[7][6] &= ~EAST;
	}

	// check to see if the maze is solveable
	FloodFill(maze, GOALX, GOALY);
	if((maze[STARTY][STARTX] >> 8) < 255)// a path to the start was found
		return(EXIT_SUCCESS); //0
	else
		return(EXIT_FAILURE); //1
}

void BuildMaze(unsigned int maze[][16], int xCurrent, int yCurrent, int xStack[], int yStack[], int stackNum){

	//set the current cell as haveing been traveled
	maze[yCurrent][xCurrent] |= TRAVELED;

	int i = 0, dir = 0;

	//check to see what possible directions it can expand

	if (yCurrent - 1 >= 0){// if there are cells above the current location
		if((maze[yCurrent - 1][xCurrent] & TRAVELED) == 0){// if the cell hasn't been traveled
			dir |= NORTH;// add it to possible directions
			i+=1;// increment the number of possilbe directions found 
		}
	}
	if (xCurrent + 1 < SIDE){
		if((maze[yCurrent][xCurrent + 1] & TRAVELED) == 0){
			dir |= EAST;
			i+=1;
		}
        if (yCurrent + 1 < SIDE){
		if((maze[yCurrent + 1][xCurrent] & TRAVELED) == 0){
			dir |= SOUTH;
			i+=1;
		}
	}
	if (xCurrent - 1 >= 0){
		if((maze[yCurrent][xCurrent - 1] & TRAVELED) == 0){
			dir |= WEST;
			i+=1;
		}
	}
	
	}

	if (i > 0){//there is an unvisited neighbor

		//move cell onto stack
		xStack[stackNum] = xCurrent;
		yStack[stackNum] = yCurrent;
		stackNum++;

		//select a direction
		int exit = 0;
		int random = rand()%4;

		do{
			if((1<<(random%4)) & dir){
				dir &= (1<<(random%4));
				exit =1; // a direction has been picked
			}
			else
				random += 1;// try another direction
		}while(exit == 0);

		//knock down walls in the direction chosen and set the current position to the new cell

		if ( dir == NORTH){
			maze[yCurrent][xCurrent] &= ~NORTH;//turn off wall
			maze[yCurrent - 1][xCurrent] &= ~SOUTH;//turn off wall
			yCurrent -= 1;//set new cell position
		}
		if ( dir == EAST){
			maze[yCurrent][xCurrent] &= ~EAST;
			maze[yCurrent][xCurrent + 1] &= ~WEST;
			xCurrent += 1;
		}
		if ( dir == SOUTH){
			maze[yCurrent][xCurrent] &= ~SOUTH;
			maze[yCurrent + 1][xCurrent] &= ~NORTH;
			yCurrent += 1;
		}
		if ( dir == WEST){
			maze[yCurrent][xCurrent] &= ~WEST;
			maze[yCurrent][xCurrent - 1] &= ~EAST;
			xCurrent -= 1;
		}

        //Recursively calls itself
		BuildMaze(maze, xCurrent, yCurrent, xStack, yStack, stackNum);
	}


	else{// no neighbor
		if (stackNum > 0){// if there are still cells to be explored
		
			//pick the first one off of the stack
			stackNum -=1;
			xCurrent = xStack[stackNum];
			yCurrent = yStack[stackNum];

			//make a recursive call with the new cell
			BuildMaze(maze, xCurrent, yCurrent, xStack, yStack, stackNum);
		}

	}

}

void InitializeMap(unsigned int map[][16]){

    int i, j;

    for(i = 0; i < SIDE; i++){// for every row
        for(j = 0; j < SIDE; j++){// for every collumn

			//add walls if they are on the perimiter
            if(i == 0){
                if (j == 0)
                    map[i][j] = WEST | NORTH;
                else if (j == SIDE-1)
                    map[i][j] = NORTH | EAST;
                else
                    map[i][j] = NORTH;
            }
            else if(i == SIDE-1){
                 if (j == 0)
                    map[i][j] = SOUTH | WEST;
                else if (j == SIDE-1)
                    map[i][j] = SOUTH | EAST;
                else
                    map[i][j] = SOUTH;
            }
            else{
                if (j == 0)
                    map[i][j] = WEST;
                else if (j == SIDE-1)
                    map[i][j] = EAST;
                else
                    map[i][j] = 0;
            }
        }
      }
}

