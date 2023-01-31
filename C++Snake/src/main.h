#pragma once

#include "engine.h"
#include "board.h"
#include "Entity/player.h"

#define SCREEN_WIDTH 50
#define SCREEN_HEIGHT 23
#define GRID_WIDTH SCREEN_WIDTH
#define GRID_HEIGHT 20
#define DEBUG false

static const Vector2 POS_SCORE(0, 0);
static const Vector2 POS_GRID(0, 1);
static const Vector2 POS_INFO(0, SCREEN_HEIGHT - 2);
static const Vector2 POS_DEBUG(0, SCREEN_HEIGHT - 1);

void WaitForEnter(const Engine& engine);
void DrawBoard(Engine& engine, const Vector2& position, const std::vector<std::vector<char>>& printBoard);
void ReadInput(Engine& engine, Player& player);