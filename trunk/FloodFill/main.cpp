#include "StdAfx.h"
#include "GUI.h"
#include "MazeBuild.h"

#include <queue>
#include <GL/glut.h>

int main(int argc, char** argv)
{
	/* initialize random seed: */
	srand( time(NULL) );
	glutInit(&argc, argv);
	initializeWindow();
	
	/* once we figure out that our code works and we dont need the gui,
	we will be able to initalize everything here. For now, because of the way
	glut works, they are globals in GUI.cpp	
	*/


	return 0;
	
}