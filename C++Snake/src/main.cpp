#include "main.h"

#include <iostream>

int main()
{
	Engine engine(SCREEN_WIDTH, SCREEN_HEIGHT);

	Board board(GRID_WIDTH, GRID_HEIGHT, Player::CHAR_BODY);
	Player player(*board.GetCenter());

	board.UpdatePlayerPosition(player.GetPoints());

	while (engine.IsRunning())
	{
		// Input
		auto t1 = std::chrono::system_clock::now();
		while ((std::chrono::system_clock::now() - t1) < std::chrono::milliseconds(FRAMES_PER_MILLISECOND))
		{
			if (engine.IsKeyPressed(VK_ESCAPE))
				engine.Stop();

			ReadInput(engine, player);
		}

		// Logic
		player.MoveSnake();

		const Point& headPoint = player.GetHeadPoint();

		if (board.IsTouchingSelf(headPoint))
		{
			engine.Draw(POS_INFO, "Died From Running Into Your Self!", Engine::RED);
			engine.Stop();
		}

		if (board.IsTouchingBounds(headPoint.position))
		{
			engine.Draw(POS_INFO, "Died From Touching Walls!", Engine::RED);
			engine.Stop();
		}

		if (board.IsTouchingFruit(headPoint.position))
		{
			board.EatFruit();
			player.EatenFruit();
		}

		board.UpdatePlayerPosition(player.GetPoints());

		// Draw
		engine.Draw(POS_SCORE, "Score: " + std::to_string(board.GetScore()));
		DrawBoard(engine, POS_GRID, board.GetBoard());
#if DEBUG
		engine.Draw({ SCREEN_WIDTH / 2, 0 }, "DEBUG BUILD");
#endif

		// Render
		engine.Render();
	}

	WaitForEnter(engine);
}

void WaitForEnter(const Engine& engine)
{
	engine.ShowConsoleCursor(true);

	std::cout << "Press Enter to Exit: ";

	while (true)
	{
		if (engine.IsKeyPressed(VK_RETURN))
			return;
	}
}

void DrawBoard(Engine& engine, const Vector2& position, const std::vector<std::vector<char>>& printBoard)
{
	Vector2 tempPosition = position;

	for (unsigned short height = 0; height < printBoard.size(); height++)
	{
		for (unsigned short width = 0; width < printBoard[0].size(); width++)
		{
			engine.Draw({ tempPosition.x + width, tempPosition.y + height }, printBoard[height][width]);
		}
	}
}

void ReadInput(Engine& engine, Player& player)
{
	if (engine.IsKeyPressed(VK_UP) && player.GetLastDirection() != DIR_UP && player.GetLastDirection() != DIR_DOWN)
	{
		//engine.Draw({ 0, SCREEN_HEIGHT - 1 }, "Player: UP");
		player.SendInput(DIR_UP);
	}
	else if (engine.IsKeyPressed(VK_DOWN) && player.GetLastDirection() != DIR_DOWN && player.GetLastDirection() != DIR_UP)
	{
		//engine.Draw({ 0, SCREEN_HEIGHT - 1 }, "Player: DOWN");
		player.SendInput(DIR_DOWN);
	}
	else if (engine.IsKeyPressed(VK_LEFT) && player.GetLastDirection() != DIR_LEFT && player.GetLastDirection() != DIR_RIGHT)
	{
		//engine.Draw({ 0, SCREEN_HEIGHT - 1 }, "Player: LEFT");
		player.SendInput(DIR_LEFT);
	}
	else if (engine.IsKeyPressed(VK_RIGHT) && player.GetLastDirection() != DIR_RIGHT && player.GetLastDirection() != DIR_LEFT)
	{
		//engine.Draw({ 0, SCREEN_HEIGHT - 1 }, "Player: RIGHT");
		player.SendInput(DIR_RIGHT);
	}
}