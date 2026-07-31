#include <iostream>
#include "EntityManager.hpp"



int main()
{
	EntityManager m_entities;

	//spawn enemy
	auto e = m_entities.add_entity("enemy");
	//e->add<CTransform>({10.f, 10.f});
	// Game g("config.txt");
	// g.run();
	return 0;
}