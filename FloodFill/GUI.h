#pragma once

#include "Maze_Definitions.h"
#include <queue>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600


struct node
{
	int x;
	int y;
	int direction;
};

void drawGridUsingSquares(unsigned int arr[][NUM_COLS], int xpos, int ypos, int size, int rows, int columns);
void sleep(unsigned int mseconds);
void glEnable2D();
void checkSurroundingWalls(unsigned int actualMaze[][NUM_COLS], unsigned int unmappedMaze[][NUM_COLS], int x, int y);
void initializeWindow();