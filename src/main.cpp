#include <iostream>
#include "Game.h"



int main()
{
	Vec2f a(3.f, 4.f);
	Vec2f b = a.normalize();
	std::cout << b.x << ", " << b.y << '\n';
	Game g(RESOURCES_PATH "config.txt");
	g.run();
	return 0;
}