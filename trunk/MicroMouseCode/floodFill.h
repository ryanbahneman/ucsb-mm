#include "Maze_Definitions.h"

void floodFill(unsigned int maze[][], unsigned int floodValues[][], Loc goal);
void modifiedFloodfill(unsigned int maze[][NUM_COLS], unsigned int floodValues[][NUM_COLS], Loc goal);

void updateWalls(unsigned int newWalls, unsigned int maze[][NUM_COLS], Loc currentPosition);
void updateCurrentLocation(Loc* currentLocation, unsigned int newDirection);



unsigned int getNewDirection(Loc currentPosition, unsigned int maze[][NUM_COLS],unsigned floodValues[][NUM_COLS]);
unsigned int measureWalls (unsigned int currentDirection);
