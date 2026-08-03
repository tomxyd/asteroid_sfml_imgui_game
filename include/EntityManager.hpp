#pragma once

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "Entity.hpp"

using EntityVec = std::vector<std::shared_ptr<Entity>>;
using EntityMap = std::map <std::string, EntityVec>;

class EntityManager
{
private:
	EntityVec m_entities;
	EntityVec m_entities_to_add;
	EntityMap m_entity_map;
	std::size_t m_total_entities = 0;


	void remove_dead_entities(EntityVec& entity)
	{
		//TO DO
		// remove all entites from vec that are not alive
		for (std::size_t i = 0; i < entity.size(); ++i)
		{
			if (!entity[i]->is_alive())
			{
				//remove entity from vector
				entity.erase(entity.begin() + i);
			}
		}
	}

public:

	EntityManager() = default;
	void update()
	{
		for (auto e : m_entities_to_add)
		{
			m_entities.push_back(e);
			m_entity_map[e->tag()].push_back(e);
		}

		m_entities_to_add.clear();

		remove_dead_entities(m_entities);

		for (auto& [tag, entity_vec] : m_entity_map)
		{
			remove_dead_entities(entity_vec);
		}
	}
	std::shared_ptr<Entity> add_entity(const std::string& tag)
	{
		//create a new Entity object
		auto e = std::make_shared<Entity>(tag, m_total_entities++);
		//store it in the vector of all entities
		m_entities.push_back(e);
		//store it in the map of tag->entityvector
		m_entity_map[tag].push_back(e);
		//return the shared ptr pointing to that entity
		return e;
	}
	EntityVec& get_entities()
	{
		return m_entities;
	}
	EntityVec& get_entities(const std::string& tag)
	{
		return m_entity_map[tag];
	}
};
