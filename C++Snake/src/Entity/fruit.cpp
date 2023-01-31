#include "fruit.h"

Fruit::Fruit(const Vector2& startPosition)
	: Entity(startPosition)
{
}

void Fruit::SetPosition(const Vector2& position)
{
	m_Position = position;
}