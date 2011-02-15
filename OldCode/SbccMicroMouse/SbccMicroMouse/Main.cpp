
#include "Main.h"



int main (int argc, const char * argv[]) {

	
	srand((unsigned)time(0));// Seed the random number generator
	int choice = 0;// Used to store user's choice
	int numMazes, numLoops;// simulation parameters

	cout<<"Welcome To The MicroMouse Maze Simulator!"<<endl;
	cout<<"Programmed by Ryan Bahneman"<<endl;

	

	while (choice != 3){ // Main Menu Loop 
		
		cout<<endl;
		cout<<"Enter 1 to watch a maze be solved."<<endl;
		cout<<"Enter 2 to run the algorithm on many mazes."<<endl;
		cout<<"Enter 3 to exit."<<endl;
		cout<<"Choice: ";
		cin >> choice; // get choice

		switch(choice){
			case 1:

				cout<<"How many loops would you like to add to the maze?  ";
				cin >> numLoops;

				//Run the program
				simulateOne(numLoops);

				break;
			case 2:

				//Get some information from the user
				cout<<endl;
				cout<<"How many mazes would you like to Generate?  ";
				cin >> numMazes;
				cout<<"How many loops would you like to add to the maze?  ";
				cin >> numLoops;
				
				//Run the program
				simulateMany(numMazes, numLoops);
				
				break;

			case 3:
				cout<<"Goodbye.";
				// Wait a few seconds
				for (time_t t = time(NULL) + 2; time(NULL) < t; ) {}
				break;


		}
	}

	return 0;
}