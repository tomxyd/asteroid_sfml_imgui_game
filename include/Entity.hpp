#pragma once
#include <string>
#include <tuple>
#include "Component.hpp"


using ComponentTuple = std::tuple<
	CTransform,
	CShape,
	CCollision,
	CScore,
	CLifespan,
	CInput>;

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

	template <typename T, typename... TArgs>
	T& add(TArgs&&... mArgs)
	{
		auto& component = get<T>();
		component = T(std::forward<TArgs>(mArgs)...);
		component.exists = true;
		return component;
	}

	template <typename T>
	T& get() 
	{
		return std::get<T>(m_component);
	}

	template <typename T>
	bool has() const
	{
		return get<T>().exists;
	}

	template <typename T>
	void	remove()
	{
		get<T>() = T();
	}


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