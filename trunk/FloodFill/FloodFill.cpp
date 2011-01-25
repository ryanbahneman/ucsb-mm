#include "stdafx.h"
#include "Maze_Definitions.h"
#include "MazeBuild.h"
#include <iostream>
#include <time.h>
#include <GL/glut.h>
#include <queue>
using namespace std;

struct node
{
	int x;
	int y;
	int direction;
};

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define NUM_ROWS 16
#define NUM_COLS 16

queue<node> Q;
queue<node> emptyMazeQueue;
int x = 0;
int y = 0;

void determineFork(int actualMaze[][NUM_COLS], int x, int y);
void determineInitialDirection(int actualMaze[][NUM_COLS], int x, int y);

unsigned int completeMazeArray[16][16]; 
unsigned int emptyMazeArray[NUM_ROWS][NUM_COLS];

void sleep(unsigned int mseconds)
{
    clock_t goal = mseconds + clock();
    while (goal > clock());
}
void glEnable2D()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();

	glOrtho(0,SCREEN_WIDTH, SCREEN_HEIGHT,0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();
}
void drawGridUsingSquares(unsigned int arr[][NUM_COLS], int xpos, int ypos, int size, int rows, int columns)
{
		int x = xpos;
		int y = ypos;		
		glColor3f(1,1,0);
		int topX = xpos;
		int topY = ypos;
		int count = 0;

		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < columns; j++)
			{				
							
				if ((arr[i][j] & FORK) == FORK)
				{
					glColor3f(0,1,0);
					glBegin(GL_QUADS);
						glVertex2f(xpos+size*j,			    ypos+size*i);     // TOP LEFT	
						glVertex2f(xpos+size*j+size,		ypos+size*i);     // TOP RIGHT
						glVertex2f(xpos+size*j+size,		ypos+size*i+size); // BOTTOM RIGHT
						glVertex2f(xpos+size*j,				ypos+size*i+size); // BOTTOM LEFT
	     			glEnd();
				}	
				else if ((arr[i][j] & TRAVELED) == TRAVELED)
				{
					glColor3f(1,0,1);
					glBegin(GL_QUADS);
						glVertex2f(xpos+size*j,			    ypos+size*i);     // TOP LEFT	
						glVertex2f(xpos+size*j+size,		ypos+size*i);     // TOP RIGHT
						glVertex2f(xpos+size*j+size,		ypos+size*i+size); // BOTTOM RIGHT
						glVertex2f(xpos+size*j,				ypos+size*i+size); // BOTTOM LEFT
	     			glEnd();
				}					
				
				//if (count % 2 == 0)
				//	glColor3f(1,0,1);
				//else
				glColor3f(1,0,0);
				if ((arr[i][j] & NORTH) == NORTH)
				{		
					glBegin(GL_LINES);
						glVertex2f(xpos+size*j,			    ypos+size*i); // TOP LEFT
						glVertex2f(xpos+size*j+size,		ypos+size*i); // TOP RIGHT
					glEnd();
				}
				if ((arr[i][j] & EAST) == EAST)
				{
					glBegin(GL_LINES);
						glVertex2f(xpos+size*j+size,		ypos+size*i);     // TOP RIGHT
						glVertex2f(xpos+size*j+size,		ypos+size*i+size); // BOTTOM RIGHT
					glEnd();
				}
				if ((arr[i][j] & SOUTH) == SOUTH)
				{
					glBegin(GL_LINES);
						glVertex2f(xpos+size*j,				ypos+size*i+size); // BOTTOM LEFT
						glVertex2f(xpos+size*j+size,		ypos+size*i+size); // BOTTOM RIGHT
					glEnd();
				}
				if ((arr[i][j] & WEST) == WEST)
				{
					glBegin(GL_LINES);
						glVertex2f(xpos+size*j,			    ypos+size*i); // TOP LEFT	
						glVertex2f(xpos+size*j,				ypos+size*i+size); // BOTTOM LEFT
	     			glEnd();
				}
				xpos+=1;
				count++;
				
			}
			cout << endl;
			ypos+=1;
			xpos = topX;			
			
		}
		cout << endl;
		glColor3f(0,0,1);
	
}
void determineFork(unsigned int actualMaze[][NUM_COLS], int x, int y)
{
	// if there are more than one direction to choosefrom, set a fork at the specific location
	if ((actualMaze[x][y] & 15) != NORTH && (actualMaze[x][y] & 15) != SOUTH && (actualMaze[x][y] & 15) != EAST && (actualMaze[x][y] & 15) != WEST)
	{
		actualMaze[x][y] |= 32; 
	}

}

void determineInitialDirection(unsigned int actualMaze[][NUM_COLS], int x, int y, queue<node> q)
{
	if ((actualMaze[x][y] & NORTH) == 0)
	{
		node n = {x-1,y,NORTH};
		q.push(n);
	}
	if ((actualMaze[x][y] & SOUTH) == 0)
	{
		node n = {x+1,y,SOUTH};
		q.push(n);
	}
	if ((actualMaze[x][y] & WEST) == 0)
	{
		node n = {x,y-1,WEST};
		q.push(n);
	}
	if ((actualMaze[x][y] & EAST) == 0)
	{
		node n = {x,y+1,EAST};
		q.push(n);
	}
}

void checkSurroundingWalls(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int x, int y)
{
	if ((actualMaze[x][y] & NORTH) == NORTH)
		unmappedMaze[x][y] |= NORTH;
	if ((actualMaze[x][y] & SOUTH) == SOUTH)
		unmappedMaze[x][y] |= SOUTH;
	if ((actualMaze[x][y] & WEST) == WEST)
		unmappedMaze[x][y] |= WEST;
	if ((actualMaze[x][y] & EAST) == EAST)
		unmappedMaze[x][y] |= EAST;
	
}
void renderScene(void) 
{	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable2D();	
	
	if (Q.size() != 0)
	{
		node p = Q.front();		
		completeMazeArray[p.x][p.y] = completeMazeArray[p.x][p.y] | 16;					//x y are set to 0, since thats where the mouse starts from in this case
		checkSurroundingWalls(completeMazeArray,emptyMazeArray,p.x,p.y);
		determineFork(completeMazeArray,p.x,p.y);
		Q.pop();

		if (p.x < NUM_ROWS && p.y < NUM_COLS && (completeMazeArray[p.x][p.y] & SOUTH) == 0 && (completeMazeArray[p.x+1][p.y] & TRAVELED) != TRAVELED ) // CHECK SOUTH
		{
			completeMazeArray[p.x+1][p.y] |= 16;
			node a = {p.x+1,p.y,SOUTH};			
			Q.push(a);
		}			
		if (p.x < NUM_ROWS && p.y < NUM_COLS && (completeMazeArray[p.x][p.y] & EAST) == 0 && (completeMazeArray[p.x][p.y+1] & TRAVELED) != TRAVELED ) // CHECK EAST
		{
			completeMazeArray[p.x][p.y+1] |= 16;
			node a = {p.x,p.y+1,EAST};			
			Q.push(a);
		}	
		if (p.x > 0 && p.x < NUM_ROWS && p.y < NUM_COLS && (completeMazeArray[p.x][p.y] & NORTH) == 0 && (completeMazeArray[p.x-1][p.y] & TRAVELED) != TRAVELED ) // CHECK NORTH
		{
			completeMazeArray[p.x-1][p.y] |= 16;
			node a = {p.x-1,p.y,NORTH};
			Q.push(a);			
		
		}		
		if (p.y > 0 && p.x < NUM_ROWS && p.y < NUM_COLS && (completeMazeArray[p.x][p.y] & WEST) == 0 && (completeMazeArray[p.x][p.y-1] & TRAVELED) != TRAVELED ) // CHECK WEST
		{
			completeMazeArray[p.x][p.y-1] |= 16;
			node a = {p.x,p.y-1,WEST};
			Q.push(a);			
		}
	}
	drawGridUsingSquares(completeMazeArray,5,5,SIDE_SIZE, NUM_ROWS,NUM_COLS);
	drawGridUsingSquares(emptyMazeArray,NUM_COLS*SIDE_SIZE+NUM_COLS*2,5,SIDE_SIZE, NUM_ROWS,NUM_COLS);

	sleep(100);
	glFlush();	
}

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	Q.empty();
	node p = {x,y};
	
	Q.push(p);	
	MakeMaze(completeMazeArray,2);


	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);	
	glutCreateWindow("FLOOD_FILL");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);	
	glutMainLoop();
	
	return 0;
	
}

