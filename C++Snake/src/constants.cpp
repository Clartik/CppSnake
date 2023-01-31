#include "constants.h"

Point::Point(const unsigned int& x, const unsigned int& y, const char& charType, const DIRECTION& dir)
	: position(x, y), charType(charType), dir(dir)
{
}

Point::Point(const Vector2& position, const char& charType, const DIRECTION& dir)
	: position(position), charType(charType), dir(dir)
{
}
bool Point::operator==(const Point& other)
{
	if (this->position != other.position)
		return false;

	if (this->charType != other.charType)
		return false;

	if (this->dir != other.dir)
		return false;

	return true;
}

bool Point::operator!=(const Point& other)
{
	if (this->position == other.position)
		return false;

	if (this->charType == other.charType)
		return false;

	if (this->dir == other.dir)
		return false;

	return true;
}