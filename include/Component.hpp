#pragma once
#include "Vec2.hpp"

class Component
{
public:
	bool exists = false;
};


class CTransform : public Component
{
private:
	Vec2f m_position;
public:
	CTransform(Vec2f position)
		:m_position(position) { }
};