#pragma once
#include "Vec2.hpp"

class Component
{
public:
	bool exists = false;
};


class CTransform : public Component
{

public:
	Vec2f pos = { 0.f,0.f };
	Vec2f vel = { 0.f,0.f };
	float angle = 0;
	CTransform() = default;
	CTransform(Vec2f position)
		:pos(position) { }
	CTransform(const Vec2f& p, const Vec2f &v)
		: pos(p), vel(v) { }
};

class CShape : public Component
{
public:
	sf::CircleShape shape;
	CShape() {};
	CShape(float radius, std::size_t vertices, const sf::Color& fill, const sf::Color& outline, const int& thickness)
		: shape(radius, vertices)
	{
		shape.setFillColor(fill);
		shape.setOutlineColor(outline);
		shape.setOutlineThickness(thickness);
		shape.setOrigin({ radius, radius });
	}
	sf::CircleShape& get_shape()
	{
		return shape;
	}
};

class CCollision : public Component
{
public:
	float radius;
	CCollision() {};
	CCollision(int in_radius)
		: radius(in_radius) { }
};


class CScore : public Component
{
public:
	int score = 0;
	CScore() {};
};

class CLifespan : public Component
{
public:
	int lifespan = 0;
	int remaining = 0;
	CLifespan() {};
	CLifespan(int total_lifespan)
		: lifespan(total_lifespan), remaining(total_lifespan)
	{ }
};


class CInput : public Component
{
public:
	bool up = false;
	bool down = false;
	bool left = false;
	bool right = false;
	bool shoot = false;
	CInput() {};
};

