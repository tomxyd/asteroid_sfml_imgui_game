#include <iostream>
#include "Game.h"



int main()
{
	Game g(RESOURCES_PATH "config.txt");
	g.run();
	return 0;
}