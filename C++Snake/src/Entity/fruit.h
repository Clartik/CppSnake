#pragma once

#include "entity.h"

class Fruit : Entity
{
public:
	static const char CHAR = 'F';
public:
	Fruit(const Vector2& startPosition);
	using Entity::GetPosition;
	void SetPosition(const Vector2& position);
};