#pragma once
#include <SFML/Graphics.hpp>
#include <cassert>
#include <cmath>

template<typename T>
class Vec2
{
public:

	T x = 0;
	T y = 0;
	Vec2() = default;

	Vec2(T xin, T yin)
		: x(xin), y(yin)
	{ }


	// constructor to convert from sf::Vector2
	Vec2(const sf::Vector2<T>& vec)
		: x(vec.x), y(vec.y)
	{ }

	//Vec2(const sf::Vector2i& vec)
	//	: x(T(vec.x)), y(T(vec.y))
	//{ }


	//allow automatic conversion to sf::Vector2
	//this lets us pass Vec2 into sfml functions
	operator sf::Vector2<T>()
	{
		return sf::Vector2<T>(x, y);
	}

	Vec2 operator + (const Vec2& rhs) const
	{
		return Vec2(x + rhs.x, y + rhs.y);
	}


	Vec2 operator - (const Vec2& rhs) const
	{
		return Vec2(x - rhs.x, y - rhs.y);
	}

	Vec2 operator / (const Vec2& rhs) const
	{
		assert(rhs.x != 0 && "x divisor, cannot be 0");
		assert(rhs.y != 0 && "y divisor, cannot be 0");

		return Vec2(x / rhs.x, y / rhs.y);
	}

	Vec2 operator * (const Vec2& rhs) const
	{
		return Vec2(x * rhs.x, y * rhs.y);
	}

	bool operator == (const Vec2& rhs) const
	{
		return x == rhs.x && y == rhs.y;
	}

	bool operator != (const Vec2& rhs) const
	{
		return x != rhs.x || y != rhs.y;

	}

	Vec2& operator += (const Vec2& rhs)
	{
		this->x += rhs.x;
		this->y += rhs.y;
		return *this;
	}

	Vec2& operator -= (const Vec2& rhs)
	{
		this->x -= rhs.x;
		this->y -= rhs.y;
		return *this;
	}

	Vec2& operator *= (const T val)
	{
		this->x *= val;
		this->y *= val;
		return *this;
	}

	Vec2& operator /= (const T val)
	{
		assert(val != 0 && "val cannot be zero");
		this->x /= val;
		this->y /= val;
		return *this;
	}

	float dist(const Vec2& rhs) const
	{
		float result = 0;
		result = std::pow((this->x - rhs.x), 2) + std::pow((this->y - rhs.y), 2);
		return std::sqrt(result);
	}

	float length() const
	{
		float result = (std::pow(this->x, 2) + std::pow(this->y, 2));
		return std::sqrt(result);
	}

	Vec2 normalize() const
	{
		float magnitude = this->length();
		return Vec2(x / magnitude, y / magnitude);
	}
};

using Vec2i = Vec2<int>;
using Vec2f = Vec2<float>;


