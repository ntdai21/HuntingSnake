#pragma once

#include <vector>
#include <Windows.h>

struct GameMap {
	int lvl; //Level
	int maxFood; //Maximum amount of food can be collected in this level
	std::vector<COORD> wall; //Wall positions.
	std::vector<COORD> gate; //Gate positions.
};

struct Snake {
	int food;
	std::vector<COORD> snakeBody; //Snake's body positions.
	int speed;
	int state; //0 = dead, 1 = alive.
};