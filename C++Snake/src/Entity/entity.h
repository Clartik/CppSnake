#pragma once

#include "math/vector2.h"

class Entity
{
public:
	static const char CHAR;
	Vector2 m_Position;
	const Vector2& GetPosition() const;
protected:
	Entity(const Vector2& position);
};