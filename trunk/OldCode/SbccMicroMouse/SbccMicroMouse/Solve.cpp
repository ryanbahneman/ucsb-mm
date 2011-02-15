
#include "Solve.h"


int SolveWithFF0(unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal){

	// Initialize variables
	int steps, totalSteps = 0;
	unsigned int map[16][16]; //used to store discovered walls

	// adds perimiter walls to the map
	InitializeMap(map);

	do{

		steps = GoFFtoCell(map, maze, xStart, yStart, xGoal, yGoal);
		/*GoFFtoCell is a function that moves the mouse from start to the goal, "reflooding"
		 *the maze every time it moves to a new cell, and choosing the lowest value neighbor.
		 */

		totalSteps += 2*steps;//accounting for the backtracking to the center

	}while( steps != ((map[yStart][xStart] & 65280) >> 8));
	//checks to see if the path traveled is the same as the value of the start cell.
	//if they match, the shortest route is guarnteed.

	return totalSteps;
}

int SolveWithFF1( unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal, bool print){

	int steps, totalSteps = 0;

	unsigned int map[16][16]; //used to store discovered walls

	InitializeMap(map); // adds perimiter walls to the map


	FloodFill(map, xGoal, yGoal);//Floods the maze

	do{
		//Same as FF0, but tries to find a quicker way back
		if(print)
			steps = GoFFtoCellConfigurable(map, maze, xStart, yStart, xGoal, yGoal, true);
		else
			steps = GoFFtoCell(map, maze, xStart, yStart, xGoal, yGoal);
		
		totalSteps += steps;
		
		if(print)
			steps = GoFFtoCellConfigurable(map, maze, xGoal, yGoal, xStart, yStart, true);
		else
			steps = GoFFtoCell(map, maze, xGoal, yGoal, xStart, yStart);

		totalSteps += steps;

		//This extra floodfill is necessary because the maze is currently floodfilled assuming
		//that the starting cell in the goal
		FloodFill(map, xGoal, yGoal);
	}while( steps != ((map[yStart][xStart] & 65280) >> 8));
	//checks to see if the path traveled is the same as the value of the start cell.
	//if they match, the shortest route is guarnteed.

	return totalSteps;

}



int GoFFtoCellConfigurable(unsigned int map[][16], unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal, bool print){

    int steps = 0, dir;
    unsigned int neighbor[4];
    int yCurrent = yStart, xCurrent = xStart;


	// initially Flood the maze with new distance values
	FloodFill(map, xGoal, yGoal);
    
    do{

        if ((map[yCurrent][xCurrent] & TRAVELED) == 0){
           
			//(1) Update the wall map

			/*This checks for walls and updates map acordingly */
			if (yCurrent > 0){
				if ((maze[yCurrent][xCurrent] & NORTH) != 0){
					map[yCurrent][xCurrent] |= NORTH;
					map[yCurrent - 1][xCurrent] |= SOUTH;
				}
			}
			else
				map[yCurrent][xCurrent] |= NORTH;



			if (xCurrent < (SIDE - 1)){
				if ((maze[yCurrent][xCurrent] & EAST) != 0){
					map[yCurrent][xCurrent] |= EAST;
					map[yCurrent][xCurrent + 1] |= WEST;
				}
			}
			else
				map[yCurrent][xCurrent] |= EAST;



			if (yCurrent < (SIDE - 1)){
				if ((maze[yCurrent][xCurrent] & SOUTH) != 0){
					map[yCurrent][xCurrent] |= SOUTH;
					map[yCurrent + 1][xCurrent] |= NORTH;
				}
			}
			else
				map[yCurrent][xCurrent] |= SOUTH;



			if (xCurrent > 0){
				if ((maze[yCurrent][xCurrent] & WEST) != 0){
					map[yCurrent][xCurrent] |= WEST;
					map[yCurrent][xCurrent - 1] |= EAST;
				}
			}
			else
				map[yCurrent][xCurrent] |= WEST;

    

			//(2) Flood the maze with new distance values
			FloodFill(map, xGoal, yGoal);

		


			map[yCurrent][xCurrent] |= TRAVELED;
		}

		if(print){//draw the maze
			DrawMaze(map, maze, xCurrent, yCurrent, xGoal, yGoal);
		}

		//(3) Decide which neighboring cell has the lowest distance value
		const int MAX = 255;

			if (yCurrent > 0){
				if ((map[yCurrent][xCurrent] & NORTH) == 0)
					neighbor[0] = ((map[yCurrent - 1][xCurrent]& 65280) >> 8);
				else
					neighbor[0] = MAX;
			}
			else
					neighbor[0] = MAX;

			if (xCurrent < (SIDE - 1)){
				if ((map[yCurrent][xCurrent] & EAST) == 0)
					neighbor[1] = ((map[yCurrent][xCurrent + 1] & 65280) >> 8);
				else
					neighbor[1] = MAX;
			}
			else
					neighbor[1] = MAX;

			if (yCurrent < (SIDE - 1)){
				if ((map[yCurrent][xCurrent] & SOUTH) == 0)
					neighbor[2] = ((map[yCurrent + 1][xCurrent] & 65280) >> 8);
				else
					neighbor[2] = MAX;
			}
			else
					neighbor[2] = MAX;

			if (xCurrent > 0){
				if ((map[yCurrent][xCurrent] & WEST) == 0)
					neighbor[3] = ((map[yCurrent][xCurrent - 1] & 65280) >> 8);
				else
					neighbor[3] = MAX;
			}
			else
					neighbor[3] = MAX;


		int i, lowest = MAX;
			for( i = 0; i < 4; i++){
				if (neighbor[i] < lowest){
					dir = i;
					lowest = neighbor[i];
				}
			}

		//(4) Move to the neighboring cell with the lowest distance value

		if(dir == 0)
			yCurrent--;
		else if(dir == 1)
			xCurrent++;
		else if(dir == 2)
			yCurrent++;
		else if(dir == 3)
			xCurrent--;


		steps +=1;


	}while(yCurrent != yGoal || xCurrent != xGoal);
	//checks to see if it is made it to the goal
    
	return steps;
}

int GoFFtoCell(unsigned int map[][16], unsigned int maze[][16], int xStart, int yStart, int xGoal, int yGoal){
	return GoFFtoCellConfigurable(map, maze, xStart, yStart, xGoal, yGoal, false);
}