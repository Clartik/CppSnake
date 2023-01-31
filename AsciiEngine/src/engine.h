#pragma once

#include <Windows.h>
#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <string>

#include "math/vector2.h"

#define FRAMES_PER_MILLISECOND 200

class Engine
{
public:
	enum Color
	{
		BLACK = 0,
		DARKBLUE = FOREGROUND_BLUE,
		DARKGREEN = FOREGROUND_GREEN,
		DARKCYAN = FOREGROUND_GREEN | FOREGROUND_BLUE,
		DARKRED = FOREGROUND_RED,
		DARKMAGENTA = FOREGROUND_RED | FOREGROUND_BLUE,
		DARKYELLOW = FOREGROUND_RED | FOREGROUND_GREEN,
		DARKGRAY = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
		GRAY = FOREGROUND_INTENSITY,
		BLUE = FOREGROUND_INTENSITY | FOREGROUND_BLUE,
		GREEN = FOREGROUND_INTENSITY | FOREGROUND_GREEN,
		CYAN = FOREGROUND_INTENSITY | FOREGROUND_GREEN | FOREGROUND_BLUE,
		RED = FOREGROUND_INTENSITY | FOREGROUND_RED,
		MAGENTA = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_BLUE,
		YELLOW = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN,
		WHITE = FOREGROUND_INTENSITY | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE,
	};
public:
	const unsigned short SCREEN_WIDTH, SCREEN_HEIGHT;
private:
	const char CHAR_EMPTY;
private:
	/// <summary>
	/// Whether the Engine is Running or Not
	/// </summary>
	bool m_Running;
	/// <summary>
	/// Screen Buffer
	/// </summary>
	std::vector<std::vector<char>> m_Screen;
	/// <summary>
	/// Text Color Buffer
	/// </summary>
	std::vector<std::vector<Color>> m_Color;
public:
	/// <summary>
	/// Default Constructor
	/// </summary>
	/// <param name="width">The Width of the Screen</param>
	/// <param name="height">The Height of the Screen</param>
	/// <param name="emptyChar">The Character of the Empty Area</param>
	/// <param name="showCursor">Whether to Show the Console Cursor or Not</param>
	Engine(const unsigned short& width, const unsigned short& height, const char& emptyChar=' ', bool showCursor = false);
	/// <summary>
	/// Checks if the Key Entered Has Been Pressed
	/// </summary>
	/// <param name="key">Keyboard Keys</param>
	/// <returns></returns>
	bool IsKeyPressed(const unsigned short& key) const;
	/// <summary>
	/// Adds Char to Draw Call
	/// </summary>
	/// <param name="position">The Position Where It Should Draw</param>
	/// <param name="printChar">The Character That Will Be Drawn</param>
	/// <param name="color">The Color of the Text</param>
	void Draw(const Vector2& position, const char& printChar, const Color& color=WHITE);
	/// <summary>
	/// Adds the String to the Draw Call
	/// </summary>
	/// <param name="position">The Position Where It Should Draw</param>
	/// <param name="printString">The C++ String That Should Be Drawn</param>
	/// <param name="color">The Color of the Text</param>
	void Draw(const Vector2& position, const std::string& printString, const Color& color=WHITE);
	/// <summary>
	/// Renders Everything that is in the Draw Buffer
	/// </summary>
	void Render();
	/// <summary>
	/// Show or Hide the Console Cursor
	/// </summary>
	/// <param name="showFlag">Boolean that Controls The Console Cursor's Visibility</param>
	void ShowConsoleCursor(const bool showFlag) const;
	/// <summary>
	/// Says if the Engine is Running. Should Be Used in the While Loop
	/// </summary>
	/// <returns>Whether the Engine is Running or Not</returns>
	bool IsRunning() const;
	/// <summary>
	/// Stops the Engine From Running
	/// </summary>
	void Stop();
private:
	/// <summary>
	/// Sets the Position Where the Engine Will Draw
	/// </summary>
	/// <param name="cursorPos">The Position Where the Engine Will Draw</param>
	/// <returns></returns>
	BOOL SetCursorPosition(const Vector2& cursorPos);
	/// <summary>
	/// Checks If You Are Drawing Out of Bounds
	/// </summary>
	/// <param name="position">The Position</param>
	/// <returns>Whether You Are Drawing Out of Frame Or Not</returns>
	bool IsDrawingOutOfBounds(const Vector2& position);
	/// <summary>
	/// Cleans the Screen Buffer
	/// </summary>
	void CleanScreenBuffer();
	/// <summary>
	/// Cleans the Color Buffer
	/// </summary>
	void CleanColorBuffer();
	/// <summary>
	/// Sets the Text Color
	/// </summary>
	/// <param name="color">The Color Specified</param>
	void SetColor(int8_t color) const;
};