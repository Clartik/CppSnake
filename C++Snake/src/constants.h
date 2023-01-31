#pragma once

#include "math/vector2.h"

const enum DIRECTION
{
	DIR_UP,
	DIR_DOWN,
	DIR_LEFT,
	DIR_RIGHT
};

class Point
{
public:
	Vector2 position;
	char charType;
	DIRECTION dir;
public:
	Point(const unsigned int& x, const unsigned int& y, const char& charType, const DIRECTION& dir);
	Point(const Vector2& position, const char& charType, const DIRECTION& dir);
	bool operator==(const Point& other);
	bool operator!=(const Point& other);
};