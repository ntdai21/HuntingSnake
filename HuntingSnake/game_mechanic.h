#pragma once

#include "struct.h"

//Move snake in real time
void MoveSnake(GameLVL* gameLVL, Snake* snake);

//Draw snake
void DrawSnake(const std::vector<COORD>& body, const std::vector<char>& parttern);

//Call when eat food
void GrowUp(Snake* snake);

//Check if snake hits something
void CheckHitting(GameLVL* gameLVL, Snake* snake);

//Call when snake hits food
void EatFood(GameLVL* gameLVL, Snake* snake);

//Call when snake hits wall
void HitWall(bool& snakeState);

//Call when eat enough food
void Win(int* curLVL);

bool Lose(const GameLVL* gameLVL, Snake* snake, int* curLVL);

COORD SpawnFood(const std::vector<COORD>* body, const std::vector<COORD>* wall);

//Play
void Play(GameLVL* gameLVL, Snake* snake, const int* curLVL);

bool LoadLVL(const int* lvl, GameLVL* gameLVL, Snake* snake);

void ResetGameLVLAndSnakeData(GameLVL* gameLVL, Snake* snake);

void TimeCountDown(size_t* timer);

void CheckTimer(GameLVL* gameLVL, Snake* snake);

void UpdateLifeTime(const GameLVL* gameLVL);