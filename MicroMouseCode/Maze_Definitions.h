#pragma once

#define NORTH 1     //00000001
#define EAST 2      //00000010
#define SOUTH 4     //00000100
#define WEST 8      //00001000
#define ALLWALLS 15 //00001111
#define TRAVELED 16 //00010000

#define SIDE 16 //number of cells per side

#define NUM_ROWS 16
#define NUM_COLS 16

#define GOALR 8
#define GOALC 8
#define STARTR 0
#define STARTC 0

#define bool short int
#define true 1
#define false 0

typedef struct Loc
{
	unsigned int row, col;
}Loc;
