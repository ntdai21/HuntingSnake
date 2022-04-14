#pragma once

#include "struct.h"

//Move snake in real time
void MoveSnake(GameLVL* gameLVL, Snake* snake);

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

bool Lose(GameLVL* gameLVL, Snake* snake, int* curLVL);

COORD SpawnFood(const std::vector<COORD>* body, const std::vector<COORD>* wall, bool* isLifeFood);

//Play
void Play(GameLVL* gameLVL, Snake* snake, const int* curLVL);

bool LoadLVL(int* lvl, GameLVL* gameLVL, Snake* snake, bool* loadData);

void ResetGameLVLAndSnakeData(GameLVL* gameLVL, Snake* snake);

void TimeCountDown(size_t* timer, const bool* state);

void CheckTimer(GameLVL* gameLVL, Snake* snake);

void UpdateLifeTime(const GameLVL* gameLVL);

void PauseGame(HANDLE thrd1, HANDLE thrd2, const int* curLVL, GameLVL* gameLVL, Snake* snake);

void SaveData(const int* curLVL, const GameLVL* gameLVL, const Snake* snake);

bool LoadData(int* curLVL, GameLVL* gameLVL, Snake* snake);

void PointRewardByTime(const GameLVL* gameLVL, Snake* snake);

void ResetAllData(GameLVL* gameLVL, Snake* snake, int* curLVL);