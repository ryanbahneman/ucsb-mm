#include "StdAfx.h"
#include "GUI.h"
#include "MazeBuild.h"
#include "FloodFill.h"
#include "Maze_Definitions.h"

#include <queue>
#include <GL/glut.h>

// initialization of the global variables used for the gui
unsigned int completeMazeArray[16][16]; 
unsigned int emptyMazeArray[NUM_ROWS][NUM_COLS];
unsigned int floodValues[NUM_ROWS][NUM_COLS];

unsigned int anotherEmptyArray[NUM_ROWS][NUM_COLS];
unsigned int floodValuesForResult[NUM_ROWS][NUM_COLS];

// needs to be here so it can use while loop in gui
Loc currentLoc;

queue<node> Q;

void renderBitmapString( float x, float y, char *string) 
{  
  char *c;
  glRasterPos2f(x, y);
  for (c=string; *c != '\0'; c++) 
  {
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10 , *c);
  }
}
// METHODS USED FOR GUI
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
							
				if (i == currentLoc.x && j == currentLoc.y)
				
				//if ((arr[i][j] & CURRENT) == CURRENT)
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
					glColor3f(0,0,1);
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

				char *name = "";
				char buf[32] = { 0 };
				if (xpos > 50)
				{
						
					sprintf(buf, "%s%d", name, floodValues[i][j]);	
				}
				else
				{
					sprintf(buf, "%s%d", name, floodValuesForResult[i][j]);	
				}
						
				char* k = buf;
				glColor3f(1,1,0);
				renderBitmapString(xpos+size*j,ypos+size*i+size/2,k);
						
			}			
			ypos+=1;
			xpos = topX;			
		}		
		glColor3f(0,0,1);	
}

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

void checkSurroundingWalls(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int x, int y)
{
	if ((actualMaze[x][y] & NORTH) == NORTH)
	{

		unmappedMaze[x][y] |= NORTH;
		unmappedMaze[x-1][y] |= SOUTH;
	}
	if ((actualMaze[x][y] & SOUTH) == SOUTH)
	{
		unmappedMaze[x][y] |= SOUTH;
		unmappedMaze[x+1][y] |= NORTH;
	}		
	if ((actualMaze[x][y] & WEST) == WEST)
	{
		unmappedMaze[x][y] |= WEST;
		unmappedMaze[x][y-1] |= EAST;
	}		
	if ((actualMaze[x][y] & EAST) == EAST)
	{
		unmappedMaze[x][y] |= EAST;
		unmappedMaze[x][y+1] |= WEST;
	}
	
}

void renderScene(void) 
{	
	glClear(GL_COLOR_BUFFER_BIT| GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	glEnable2D();	

	Loc goal;
	goal.x = 8;
	goal.y = 8;

	Loc start;
	start.x = 0;
	start.y = 0;

	// map walls
	// floodfill
	// solvemaze

	checkSurroundingWalls(completeMazeArray,emptyMazeArray,currentLoc.x, currentLoc.y);
	floodFill(emptyMazeArray,floodValues, goal);
	solveMaze(completeMazeArray,floodValues,emptyMazeArray,start, &currentLoc);
	
	/* once its figured out to pass a queue<nodes> as an array, the next if statement can be moved to
	floodfill.cpp and modified from there or 
	*/

	/*
	if (Q.size() != 0)
	{
		node p = Q.front();		
		completeMazeArray[p.x][p.y] = completeMazeArray[p.x][p.y] | 16;					//x y are set to 0, since thats where the mouse starts from in this case
		checkSurroundingWalls(completeMazeArray,emptyMazeArray,p.x,p.y);
		
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
	}	*/
	
	drawGridUsingSquares(completeMazeArray,5,5,SIDE_SIZE, NUM_ROWS,NUM_COLS);
	drawGridUsingSquares(emptyMazeArray,NUM_COLS*SIDE_SIZE+NUM_COLS*2,5,SIDE_SIZE, NUM_ROWS,NUM_COLS);
	//drawGridUsingSquares(emptyMazeArray,5,NUM_COLS*SIDE_SIZE+NUM_COLS*2,SIDE_SIZE, NUM_ROWS,NUM_COLS);

	sleep(100);
	glFlush();	
}
void initializeWindow()
{
	Q.empty();
	node p = {0,0};	
	Q.push(p);	
	MakeMaze(completeMazeArray,10);

	currentLoc.x = 0;
	currentLoc.y = 0;
	
	Loc g;
	g.x = 8;
	g.y = 8;

	floodFill(completeMazeArray,floodValuesForResult, g);

	for(int r = 0; r <16; r++)
	{
		for(int c = 0; c < 16; c++)
		{
			emptyMazeArray[r][c] = 256;
		}
	}	

	// initialize window
	glutInitDisplayMode(GLUT_RGBA | GLUT_SINGLE);
	glutInitWindowPosition(100,100);
	glutInitWindowSize(SCREEN_WIDTH,SCREEN_HEIGHT);	
	glutCreateWindow("FLOOD_FILL");
	glutDisplayFunc(renderScene);
	glutIdleFunc(renderScene);	
	glutMainLoop();
}

