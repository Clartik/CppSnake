#include "board.h"

#include <iostream>

Board::Board(const unsigned int& width, const unsigned int& height, const char& playerChar, const char& playAreaChar)
	: HORIZONTAL_LENGTH(width), VERTICAL_LENGTH(height), CHAR_EMPTY(playAreaChar), CHAR_PLAYER(playerChar), 
	m_Board(VERTICAL_LENGTH, std::vector<char>(HORIZONTAL_LENGTH, CHAR_EMPTY)), m_Fruit(*GetPositionForFruit()), 
	m_Score(0)
{
	// Adds Empty Space Across the Whole Area
	for (unsigned short column = 0; column < VERTICAL_LENGTH; column++)
	{
		for (unsigned short row = 0; row < HORIZONTAL_LENGTH; row++)
		{
			m_Board[column][row] = CHAR_EMPTY;
		}
	}

	// Top and Bottom Border Added
	for (unsigned short width = 0; width < HORIZONTAL_LENGTH; width++)
	{
		m_Board[0][width] = CHAR_BORDER_VERTICAL;
		m_Board[VERTICAL_LENGTH - 1][width] = CHAR_BORDER_VERTICAL;
	}

	// Left and Right Border Added
	for (unsigned short length = 0; length < VERTICAL_LENGTH; length++)
	{
		m_Board[length][0] = CHAR_BORDER_HORIZONTAL;
		m_Board[length][HORIZONTAL_LENGTH - 1] = CHAR_BORDER_HORIZONTAL;
	}
}

const std::vector<std::vector<char>> Board::GetBoard() const
{
	return m_Board;
}

void Board::UpdatePlayerPosition(const std::vector<Point>& points)
{
	RefreshBoard();

	for (unsigned int i = 0; i < points.size(); i++)
	{
		Point currentPoint = points[i];
		m_Board[currentPoint.position.y][currentPoint.position.x] = currentPoint.charType;
	}
}

void Board::RefreshBoard()
{
	// Adds Empty Space Across the Whole Area
	for (unsigned short column = 1; column < VERTICAL_LENGTH - 1; column++)
	{
		for (unsigned short row = 1; row < HORIZONTAL_LENGTH - 1; row++)
		{
			m_Board[column][row] = CHAR_EMPTY;
		}
	}

	m_Board[m_Fruit.GetPosition().y][m_Fruit.GetPosition().x] = Fruit::CHAR;
}

const unsigned int& Board::GetScore() const
{
	return m_Score;
}

bool Board::IsTouchingBounds(const Vector2& position) const
{
	if (position.x < 2) return true;
	if (position.x > (int)HORIZONTAL_LENGTH - 3) return true;
	if (position.y < 2) return true;
	if (position.y > (int)VERTICAL_LENGTH - 3) return true;

	return false;
}

bool Board::IsTouchingSelf(const Point& point) const
{
	switch (point.dir)
	{
	case DIR_UP:
		if (m_Board[point.position.y + 1][point.position.x] == CHAR_PLAYER)
		{
			//Vector2 pos(point.position.x, point.position.y + 1);
			//std::cout << pos << " - " << m_Board[point.position.y + 1][point.position.x] << std::endl;
			return true;
		}
	case DIR_DOWN:
		if (m_Board[point.position.y - 1][point.position.x] == CHAR_PLAYER)
		{
			//Vector2 pos = Vector2(point.position.x, point.position.y - 1);
			//std::cout << pos << " - " << m_Board[point.position.y - 1][point.position.x] << std::endl;
			return true;
		}
	case DIR_LEFT:
		if (m_Board[point.position.y][point.position.x + 1] == CHAR_PLAYER)
		{
			//Vector2 pos = Vector2(point.position.x + 1, point.position.y);
			//std::cout << pos << " - " << m_Board[point.position.y][point.position.x + 1] << std::endl;
			return true;
		}
	case DIR_RIGHT:
		if (m_Board[point.position.y][point.position.x - 1] == CHAR_PLAYER)
		{
			//Vector2 pos = Vector2(point.position.x - 1, point.position.y);
			//std::cout << pos << " - " << m_Board[point.position.y][point.position.x - 1] << std::endl;
			return true;
		}
	default:
		break;
	}

	return false;
}

bool Board::IsTouchingFruit(const Vector2& position) const
{
	if (position.x == m_Fruit.GetPosition().x && position.y == m_Fruit.GetPosition().y)
		return true;

	return false;
}

const std::unique_ptr<Vector2> Board::GetCenter() const
{
	std::unique_ptr<Vector2> ptr = std::make_unique<Vector2>(HORIZONTAL_LENGTH / 2, VERTICAL_LENGTH / 2);
	return ptr;
}

const std::unique_ptr<Vector2> Board::GetPositionForFruit() const
{
	std::srand((unsigned int)time(0));

	// rand() % (max - min + 1) + min
	int x = rand() % ((HORIZONTAL_LENGTH - 1) - 1) + 1;
	int y = rand() % ((VERTICAL_LENGTH - 1) - 1) + 1;

	std::unique_ptr<Vector2> ptr = std::make_unique<Vector2>(x, y);

	return ptr;
}

void Board::EatFruit()
{
	m_Score++;
	m_Fruit.SetPosition(*GetPositionForFruit());
}