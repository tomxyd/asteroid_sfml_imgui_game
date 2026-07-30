#include <SFML/Graphics.hpp>
#include "Vec2.hpp"
//#include "Game.h"

#include <iostream>



int main()
{
	// test each Vec2 class functions before proceeding to the next
	Vec2 a(3.f, 4.f);
	Vec2 b(5.f, 1.f);

	Vec2 c = a.normalize();

	std::cout << c.x << ", " << c.y;


	// Game g("config.txt");
	// g.run();
}