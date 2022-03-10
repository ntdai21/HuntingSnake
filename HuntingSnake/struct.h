#pragma once

#include <vector>
#include <Windows.h>

struct GameMap {
	int lvl; //Level
	int maxFood; //Maximum amount of food can be collected in this level
	std::vector<COORD> wall; //Wall positions.
	std::vector<COORD> gate; //Gate positions.
	COORD food; //Food position.
};

struct Snake {
	int food = 0;
	std::vector<COORD> body; //Snake's body positions.
	std::vector<char> bodyPattern;
	int speed = 10;
	char direction = 'd';
	char curDirection = 'd';
	bool state; //0 = dead, 1 = alive.
};

