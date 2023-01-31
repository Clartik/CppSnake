#include "player.h"

Player::TurnPoints::TurnPoints(const Vector2& position, const DIRECTION& dir)
	: position(position), dir(dir), amountOfPointsGoneThrough(0)
{
}

Player::Player(const Vector2& startPosition)
	: m_LastHeadDir(DIR_UP)
{
	Point headPoint(startPosition, CHAR_HEAD, m_LastHeadDir);
	m_Points.emplace_back(headPoint);

	for (unsigned short i = 0; i < START_SIZE - 1; i++)
	{
		AddToPlayer();
	}
}

void Player::SendInput(const DIRECTION& dir)
{
	m_LastHeadDir = dir;
}

void Player::EvalutePosition(Point& point)
{
	for (unsigned short i = 0; i < m_TurnPoints.size(); i++)
	{
		if (point.position == m_TurnPoints[i].position)
		{
			point.dir = m_TurnPoints[i].dir;
			m_TurnPoints[i].amountOfPointsGoneThrough++;
		}

		if (m_TurnPoints[i].amountOfPointsGoneThrough == m_Points.size())
			m_TurnPoints.erase(m_TurnPoints.begin() + i);
	}

	switch (point.dir)
	{
	case DIR_UP:
		point.position += Vector2::UP;
		break;
	case DIR_DOWN:
		point.position += Vector2::DOWN;
		break;
	case DIR_LEFT:
		point.position += Vector2::LEFT;
		break;
	case DIR_RIGHT:
		point.position += Vector2::RIGHT;
		break;
	default:
		break;
	}
}

void Player::MoveSnake()
{
	if (m_Points[0].dir != m_LastHeadDir)
	{
		m_Points[0].dir = m_LastHeadDir;
		m_TurnPoints.push_back({ m_Points[0].position, m_Points[0].dir });
	}

	for (unsigned int i = 0; i < m_Points.size(); i++)
	{
		EvalutePosition(m_Points[i]);
	}
}

void Player::EatenFruit()
{
	AddToPlayer();
}

const std::vector<Point>& Player::GetPoints() const
{
	return m_Points;
}

const Point& Player::GetHeadPoint() const
{
	return m_Points[0];
}

const DIRECTION& Player::GetLastDirection() const
{
	return m_LastHeadDir;
}

void Player::AddToPlayer()
{
	DIRECTION& lastDir = m_Points.back().dir;
	Vector2 position = m_Points.back().position;

	switch (lastDir)
	{
	case DIR_UP:
		position += Vector2::DOWN;
		break;
	case DIR_DOWN:
		position += Vector2::UP;
		break;
	case DIR_LEFT:
		position += Vector2::RIGHT;
		break;
	case DIR_RIGHT:
		position += Vector2::LEFT;
		break;
	default:
		break;
	}

	Point point(position, CHAR_BODY, lastDir);
	m_Points.emplace_back(point);
}