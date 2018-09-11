#include<iostream>
#include"ProjectFile.h"

int main()
{
	//creats a new project
	ProjectFile* app = new ProjectFile();
	//initialises the project
	app->Initialise();
	//runs the project
	app->run();
	//cleaning
	delete app;
	return 0;
}