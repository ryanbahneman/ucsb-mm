#ifndef _MAZESIM_H
#define	_MAZESIM_H

#include "MazeDefinitions.h"
#include "MazeFlood.h"
#include "MazeBuild.h"
#include "Solve.h"

#include <stdlib.h>
#include <iostream>

using namespace std;

/*
Runs the maze solving algorithms on randomly generated mazes 'numMazes' times.
When the mazes are originally built, there are no loops, however the competition maze will have loops.
'numLoops' is the number of walls randomly knocked down to form loops.

Outputs the average number of steps taken to solve the maze. The maze is considered solved when the 
"mouse" is sitting at the start square and knows with 100% confidence that it knows the shortest 
route to the center. 
*/

void simulateMany(int numMazes, int numLoops);

/*
Runs the maze solving algorithms on a randomly generated maze.
When the mazes are originally built, there are no loops, however the competition maze will have loops.
'numLoops' is the number of walls randomly knocked down to form loops.

Displays the maze as it is being solved
*/

void simulateOne(int numLoops);


#endif	/* _MAZEBUILD_H */

