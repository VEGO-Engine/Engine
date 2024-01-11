#include "Vector2D.h"

Vector2D::Vector2D()
{
	this->x = 0.0f;
	this->y = 0.0f;
}

Vector2D::Vector2D(float x, float y)
{
	this->x = x;
	this->y = y;
}

Vector2D& operator+(Vector2D& vector1, const Vector2D& vector2)
{
	vector1.x += vector2.x;
	vector1.y += vector2.y;
	return vector1;
}
Vector2D& operator-(Vector2D& vector1, const Vector2D& vector2)
{
	vector1.x -= vector2.x;
	vector1.y -= vector2.y;
	return vector1;
}
Vector2D& operator*(Vector2D& vector1, const Vector2D& vector2)
{
	vector1.x *= vector2.x;
	vector1.y *= vector2.y;
	return vector1;
}
Vector2D& operator/(Vector2D& vector1, const Vector2D& vector2)
{
	vector1.x /= vector2.x;
	vector1.y /= vector2.y;
	return vector1;
}
Vector2D& Vector2D::operator*(const int& i)
{
	this->x *= i;
	this->y *= i;

	return *this;
}
Vector2D& Vector2D::zero()
{
	this->x = 0.0f;
	this->y = 0.0f;

	return *this;
}
