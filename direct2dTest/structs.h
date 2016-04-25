#pragma once

struct VectorInt2
{
	int x;
	int y;

	VectorInt2(int x = 0, int y = 0)
	{
		this->x = x;
		this->y = y;
	}
};

struct VectorFloat2
{
	float x;
	float y;
	VectorFloat2(float x = 0, float y = 0)
	{
		this->x = x;
		this->y = y;
	}
	VectorFloat2 operator+(VectorFloat2& other)
	{
		return VectorFloat2(this->x + other.x, this->y + other.y);
	}
};

