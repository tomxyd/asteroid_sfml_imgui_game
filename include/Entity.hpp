#pragma once
#include <string>
#include <tuple>
#include "Component.hpp"


using ComponentTuple = std::tuple<int>;

class Entity
{
private:
	ComponentTuple m_component;
	bool m_alive = true;
	std::string m_tag = "default";
	std::size_t m_id = 0;
public:
	Entity() = default;
	Entity(std::string tag, std::size_t id)
		: m_tag(tag), m_id(id) { }

	//void	add<T>(args);
	//T&		get<T>();
	//bool	has<T>;
	//void	remove<T>;


	std::size_t id() const
	{
		return m_id;
	}
	bool is_alive() const
	{
		return m_alive;
	}
	void destroy()
	{
		m_alive = false;
	}
	const std::string& tag() const
	{
		return m_tag;
	}
};