#include "MainActivity.h"
#include <ANUT/ANUT.h>
#include <fstream>

void android_main(android_app* state)
{
	anut::Window::redSize = 8;
	anut::Window::greenSize = 8;
	anut::Window::blueSize = 8;
	anut::Window::minDepthSize = 8;
	
	anut::Engine* andronaut = new anut::Engine(state);
	MainActivity* app = new MainActivity;
	int exitCode = andronaut->run(app);
	
	if (exitCode != 0)
	{
		// TODO: write a log to a file
	}
	
	delete andronaut;
	delete app;
}

