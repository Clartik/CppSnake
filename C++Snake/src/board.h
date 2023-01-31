#pragma once

#include <vector>
#include <memory>

#include "math/vector2.h"
#include "Entity/fruit.h"
#include "constants.h"

class Board
{
private:
	const unsigned int HORIZONTAL_LENGTH, VERTICAL_LENGTH;
	static const char CHAR_BORDER_VERTICAL = '-';
	static const char CHAR_BORDER_HORIZONTAL = '|';
	const char CHAR_EMPTY;
	const char CHAR_PLAYER;
private:
	std::vector<std::vector<char>> m_Board;
	Fruit m_Fruit;
	unsigned int m_Score;
public:
	Board(const unsigned int& width, const unsigned int& height, const char& playerChar, const char& playAreaChar=' ');
	const std::vector<std::vector<char>> GetBoard() const;
	void UpdatePlayerPosition(const std::vector<Point>& points);
	void EatFruit();
	bool IsTouchingBounds(const Vector2& position) const;
	bool IsTouchingFruit(const Vector2& position) const;
	bool IsTouchingSelf(const Point& point) const;
	const unsigned int& GetScore() const;
	const std::unique_ptr<Vector2> GetCenter() const;
	const std::unique_ptr<Vector2> GetPositionForFruit() const;
private:
	void RefreshBoard();
};