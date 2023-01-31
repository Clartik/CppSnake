#include "entity.h"

Entity::Entity(const Vector2& position)
	: m_Position(Vector2(position))
{
}

const Vector2& Entity::GetPosition() const
{
	return m_Position;
}