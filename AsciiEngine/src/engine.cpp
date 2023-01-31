#include "engine.h"

Engine::Engine(const unsigned short& width, const unsigned short& height, const char& emptyChar, bool showCursor)
	: SCREEN_WIDTH(width), SCREEN_HEIGHT(height), CHAR_EMPTY(emptyChar), m_Running(true), 
	m_Screen(SCREEN_HEIGHT, std::vector<char>(SCREEN_WIDTH, CHAR_EMPTY)), 
	m_Color(SCREEN_HEIGHT, std::vector<Color>(SCREEN_WIDTH, WHITE))
{
	ShowConsoleCursor(showCursor);
}

BOOL Engine::SetCursorPosition(const Vector2& cursorPos)
{
	COORD cPos;
	cPos.X = cursorPos.x;
	cPos.Y = cursorPos.y;

	return SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cPos);
}

bool Engine::IsKeyPressed(const unsigned short& key) const
{
	// toUpper Used Because KeyState Had a Hard Time Converting Chars to the Virtual Key Values
	return GetAsyncKeyState(toupper(key)) & 0x8000;
}

void Engine::Draw(const Vector2& position, const char& printChar, const Color& color)
{
	if (IsDrawingOutOfBounds(position)) return;

	if (color != WHITE)
		m_Color[position.y][position.x] = color;

	m_Screen[position.y][position.x] = printChar;
}

void Engine::Draw(const Vector2& position, const std::string& printString, const Color& color)
{
	if (IsDrawingOutOfBounds(position)) return;

	int tempX = position.x;

	for (unsigned short i = 0; i < printString.size(); i++)
	{
		if (color != WHITE)
			m_Color[position.y][tempX] = color;

		m_Screen[position.y][tempX] = printString[i];

		tempX++;
	}
}

void Engine::Render()
{
	// Drawing From the Start
	SetCursorPosition(Vector2(0, 0));

	for (unsigned short row = 0; row < SCREEN_HEIGHT; row++)
	{
		for (unsigned short column = 0; column < SCREEN_WIDTH; column++)
		{
			SetColor(m_Color[row][column]);
			std::cout << m_Screen[row][column];
		}
		std::cout << std::endl;
	}

	CleanScreenBuffer();
	CleanColorBuffer();
}

void Engine::ShowConsoleCursor(const bool showFlag) const
{
	HANDLE out = GetStdHandle(STD_OUTPUT_HANDLE);

	CONSOLE_CURSOR_INFO cursorInfo;
	
	GetConsoleCursorInfo(out, &cursorInfo);
	cursorInfo.bVisible = showFlag;
	SetConsoleCursorInfo(out, &cursorInfo);
}

bool Engine::IsRunning() const
{
	return m_Running;
}

void Engine::Stop()
{
	m_Running = false;
}

bool Engine::IsDrawingOutOfBounds(const Vector2& position)
{
	if (position.x < 0 || position.y < 0 || position.x > SCREEN_WIDTH - 1 || position.y > SCREEN_HEIGHT - 1)
	{
		std::cout << "[ERROR]: You Are Accessing Out of Bounds!" << std::endl;
		return true;
	}

	return false;
}

void Engine::CleanScreenBuffer()
{
	// Refreshing Screen Buffer
	for (unsigned short row = 0; row < SCREEN_HEIGHT; row++)
	{
		for (unsigned short column = 0; column < SCREEN_WIDTH; column++)
		{
			m_Screen[row][column] = CHAR_EMPTY;
		}
	}
}

void Engine::CleanColorBuffer()
{
	// Refreshing Color Buffer
	for (unsigned short row = 0; row < SCREEN_HEIGHT; row++)
	{
		for (unsigned short column = 0; column < SCREEN_WIDTH; column++)
		{
			m_Screen[row][column] = WHITE;
		}
	}
}

void Engine::SetColor(int8_t color) const
{
	WORD wColor;
	HANDLE hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	if (!GetConsoleScreenBufferInfo(hConsoleOut, &csbi))
	{
		std::cout << "Failed to Change Color" << std::endl;
		return;
	}

	wColor = (csbi.wAttributes & 0xF0) + (color & 0x0F);
	SetConsoleTextAttribute(hConsoleOut, wColor);
}