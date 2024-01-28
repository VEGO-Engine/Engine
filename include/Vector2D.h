#pragma once

class Vector2D
{
public:
	float x;
	float y;

	Vector2D();
	Vector2D(float x, float y);

	friend Vector2D& operator+(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D& operator-(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D& operator*(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D& operator/(Vector2D& vector1, const Vector2D& vector2);
	friend Vector2D& operator+=(Vector2D& vector1, const Vector2D& vector2);

	Vector2D& operator*(const int& i);
	Vector2D& zero();
};