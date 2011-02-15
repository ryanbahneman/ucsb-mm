#include "MazeSim.h"


void simulateMany(int numMazes, int numLoops){

    unsigned int maze[16][16];// used to store the maze
    float averageSteps = 0, averageShortestRoute = 0;// Tracks averages
	int mazesGenerated = 0, successfulMazes = 0, solvable;// maze generation variables
	float successRate;//percent of generated mazes that were solveable

	cout<<endl<<"Working..."<<endl;

    do{// until enough mazes have been solved
        
		do{// get a new maze

            solvable = MakeMaze(maze, numLoops);//generate maze
            mazesGenerated ++;

        }while(solvable != 0 );//if the maze is unsolvable generate a new maze
        successfulMazes++;


		//Solve the maze. return number of steps needed to to guarantee the shortest path
		averageSteps += SolveWithFF1( maze, STARTX, STARTY, GOALX, GOALY, false); 
		//The shortest path to the center of the maze is stored in final flood fill values at the start of the maze.
		averageShortestRoute += ((maze[STARTX][STARTY] & 65280) >> 8);

		// DrawMaze(maze);

    }while(successfulMazes < numMazes);


	//do the averaging
    successRate = ((float)successfulMazes / (float)mazesGenerated) * 100;
	averageSteps /= numMazes;
	averageShortestRoute /= numMazes;


	cout<<"Finished!"<<endl<<endl;
	cout<<"Average number of steps to solve the maze: "<<averageSteps<<endl;
	cout<<"Average length of the shortest possible route: "<<averageShortestRoute<<endl;
	cout<<"Maze generation sucess rate: "<<successRate<<endl;


}

void simulateOne(int numLoops){
	
    unsigned int maze[16][16];// used to store the maze
	int solvable;// maze generation variables
	int numSteps = 0;// keep track of the steps taken
	cout<<endl<<"Generating Maze..."<<endl;

	do{// get a new maze

        solvable = MakeMaze(maze, numLoops);//generate maze

    }while(solvable != 0 );//if the maze is unsolvable generate a new maze


	SolveWithFF1( maze, STARTX, STARTY, GOALX, GOALY, true);

}