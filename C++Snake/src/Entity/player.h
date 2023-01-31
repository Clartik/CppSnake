#pragma once

#include <vector>

#include "math/vector2.h"
#include "entity.h"
#include "../constants.h"

class Player
{
private:
	struct TurnPoints
	{
		Vector2 position;
		DIRECTION dir;
		unsigned int amountOfPointsGoneThrough;

		TurnPoints(const Vector2& position, const DIRECTION& dir);
	};
public:
	static const char CHAR_BODY = 'O';
	static const char CHAR_HEAD = '@';
private:
	static const unsigned short START_SIZE = 3;
	std::vector<Point> m_Points;
	std::vector<TurnPoints> m_TurnPoints;
	DIRECTION m_LastHeadDir;
public:
	Player(const Vector2& startPosition);
	void SendInput(const DIRECTION& dir);
	void EvalutePosition(Point& point);
	void MoveSnake();
	const std::vector<Point>& GetPoints() const;
	const Point& GetHeadPoint() const;
	void EatenFruit();
	const DIRECTION& GetLastDirection() const;
private:
	void AddToPlayer();
};