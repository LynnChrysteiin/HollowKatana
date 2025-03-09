#include "vec2.h"

Vec2::Vec2()
{
	x = 0;
	y = 0;
}

Vec2::Vec2(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vec2::~Vec2() = default;

Vec2 Vec2::operator+(const Vec2& vec) const
{
	return Vec2(x + vec.x, y + vec.y);
}

Vec2 Vec2::operator-(const Vec2& vec) const
{
	return Vec2(x - vec.x, y - vec.y);
}

Vec2 Vec2::operator*(float scalar) const
{
	return Vec2(x * scalar, y * scalar);
}

float Vec2::operator*(const Vec2& vec) const
{
	return x * vec.x + y * vec.y;
}

Vec2 Vec2::operator/(float scalar) const
{
	return Vec2(x / scalar, y / scalar);
}

void Vec2::operator+=(const Vec2& vec)
{
	x += vec.x;
	y += vec.y;
}

void Vec2::operator-=(const Vec2& vec)
{
	x -= vec.x;
	y -= vec.y;
}

void Vec2::operator*=(float scalar)
{
	x *= scalar;
	y *= scalar;
}

float Vec2::length() const
{
	return sqrt(x * x + y * y);
}

Vec2 Vec2::normalize() const
{
	float len = length();

	if (len == 0)
		return Vec2(0, 0);

	return Vec2(x / len, y / len);
}
