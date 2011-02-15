#include "MazeDraw.h"

void DrawMaze(unsigned int map[][16], unsigned int maze[][16], int mouseX, int mouseY, int goalX, int goalY){

	//define the ascii characters for the walls and floor
	char wall = 178, partialWall = 248, floors = ' ';
	char mouse = 'M', goal = 'G';

	printf("\n");//make some space
	printf("\n");
	printf("\n");

	int i1, i2, row;
	for(i1 = 0; i1 < SIDE; i1++){//for each row
		for(row = 0; row < 3; row++){//each cell is a 3x3 block
			for(i2 = 0; i2 < SIDE; i2++){//for each collumn

				// # N #
				// W _ E
				// # S #

				if(row == 0 ){

				  printf("%c", wall);

				  if ((map[i1][i2] &  NORTH) == NORTH)
					printf("%c", wall);
				  else if ((maze[i1][i2] &  NORTH) == NORTH)
					printf("%c", partialWall);
				  else
					printf("%c", floors);

				  printf("%c", wall);
				}

				else if (row == 1){ 

				  if ((map[i1][i2] &  WEST) == WEST)
					printf("%c", wall);
				  else if ((maze[i1][i2] &   WEST) == WEST)
					printf("%c", partialWall);
				  else
					printf("%c", floors);

				  if(i1 == mouseY && i2 == mouseX) //special case. print the mouse if it is in the cell
					printf("%c", mouse);
				  else if (i1 == goalY && i2 == goalX) //special case. print the goal
					printf("%c", goal);
				  else
					printf("%c", floors);

				  if ((map[i1][i2] &  EAST) == EAST)
					printf("%c", wall);
				   else if ((maze[i1][i2] &   EAST) == EAST)
					printf("%c", partialWall);
				  else
					printf("%c", floors);
					}

			else{

			  printf("%c", wall);

			  if ((map[i1][i2] &  SOUTH) == SOUTH)
				printf("%c", wall);
			   else if ((maze[i1][i2] &   SOUTH) == SOUTH)
					printf("%c", partialWall);
			  else
				printf("%c", floors);

			  printf("%c", wall);
				}

			}
			printf("\n");
		}
	}

	// Wait a second
	for (time_t t = time(NULL) + 2; time(NULL) < t; ) {}
}
