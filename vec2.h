#ifndef _VEC2_H_
#define _VEC2_H_

#include <cmath>

class Vec2
{
public:
	float x;
	float y;

public:
	Vec2();
	Vec2(float x, float y);
	~Vec2();

	Vec2 operator+(const Vec2& vec) const;
	Vec2 operator-(const Vec2& vec) const;
	Vec2 operator*(float scalar) const;
	float operator*(const Vec2& vec) const;
	Vec2 operator/(float scalar) const;
	void operator+=(const Vec2& vec);
	void operator-=(const Vec2& vec);
	void operator*=(float scalar);

	float length() const;
	Vec2 normalize() const;
};

#endif // !_VEC2_H_
