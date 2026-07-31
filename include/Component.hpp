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
	Vec2f pos = { 0,0 };
	Vec2f vel = { 0, 0 };
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
};

class CCollision : public Component
{
public:
	float radius;
	CCollision() {};
};


class CScore : public Component
{
public:
	int score;
	CScore() {};
};

class CLifespan : public Component
{
public:
	int lifespan;
	int remaining;
	CLifespan() {};
};


class CInput : public Component
{
public:
	int up;
	int down;
	int left;
	int right;
	int shoot;
	CInput() {};
};

