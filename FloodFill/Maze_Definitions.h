
#pragma once

#define NORTH 1     //00000001
#define EAST 2      //00000010
#define SOUTH 4     //00000100
#define WEST 8      //00001000
#define ALLWALLS 15 //00001111
#define TRAVELED 16 //00010000
#define FORK 32     //00010000
#define CURRENT 64  //00010000

#define SIDE 16 //number of cells per side
#define SIDE_SIZE 20

#define NUM_ROWS 16
#define NUM_COLS 16

#define GOALX 7
#define GOALY 7
#define STARTX 0
#define STARTY 0

struct Loc
{
	unsigned int x, y;
};