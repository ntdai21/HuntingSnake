#pragma once

#include <vector>
#include <Windows.h>

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Window & buffer properties
	//Size
#define WINDOW_WIDTH 120
#define WINDOW_HEIGHT 30
	//Window size scale (%)
#define WINDOW_SCALE 100

//Font properties
	//Width(X) & Height(Y) of single character 
#define FONT_SIZE_X 1
#define FONT_SIZE_Y 2
	//Width & Height scale (%)
#define FONT_SCALE 100
	//Colors
#define BACKGROUND_COLOR 14
#define NORMAL_TEXT_COLOR 10
#define INFO_TITLE_COLOR 3
#define BUTTON_TEXT_COLOR 3
#define FOOD_COLOR 12

//Play area
#define PA_X 1
#define PA_Y 1
#define PA_DX 93
#define PA_DY 25

//Game UI position
	//OBJECTIVE
#define UI_OJECTIVE_X 96
#define UI_OJECTIVE_Y 3
	//CURRENT LVL
#define UI_LVL_X 113
#define UI_LVL_Y 10
	//SPEED
#define UI_SPEED_X 106
#define UI_SPEED_Y 13
	//FOOD
#define UI_FOOD_X 105
#define UI_FOOD_Y 15
	//LIFE
#define UI_LIFE_X 105
#define UI_LIFE_Y 17
	//POINT
#define UI_POINT_X 102
#define UI_POINT_Y 23
	//TIMER
#define UI_TIMER_X 11
#define UI_TIMER_Y 28
	//TITLE AND TEXT
#define TEXT_SUB_PA 17

//Game mechanics

//--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

struct GameLVL {
	int maxFood = 6; //Maximum amount of food can be collected in this level.
	std::vector<COORD> wall; //Wall positions.
	COORD food = { -1, -1 }; //Food position.
	int foodToSpeedUp = 5; //Amount of food to increase speed.
	float extraTimePerFood;
	size_t timer = 20;
	size_t baseTimer = 20;
	//Modes
	bool timeLimit = 0;
	bool canSelfTouching = 0;
	bool gateOpen = false;
	std::vector<COORD> gate;
	bool isWin = false;
	int maxSizeSnake = 0;
	bool quit = 0;
};

struct Snake {
	int food = 0;
	std::vector<COORD> body; //Snake's body positions.
	std::vector<char> bodyPattern;
	int speed = 8;
	char direction = 'd';
	char curDirection = 'd';
	bool state; //0 = dead, 1 = alive.
	unsigned int point = 0;
	int life = 1;
	int nextPattern = 0; // 0-31
	std::string pattern = "21127587";
};

struct Square {
	short x;
	short y;
	short dx;
	short dy;
};

struct Title {
	std::string text[5];
	char pattern = '²';
	int color = 7;
};

