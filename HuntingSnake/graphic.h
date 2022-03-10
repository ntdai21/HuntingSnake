#pragma once

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include <vector>
#include "struct.h"

//Usable characters: • Ö ö × ¤ « » 

//Fix console window to specify height and width
//Prevent user from maximizing or scrolling console window
//Idea: https://codelearn.io/sharing/windowsh-va-ham-dinh-dang-console-p1
void FixConsole();

void LoadMap(int lvl);

//Draw title HUNTINGSNAKE
void DrawTitle();

//Interact with main menu
void MainMenu(int& choose);

//Move the cursor to the position on the screen
void GotoXY(const int& x, const int& y);

//Return centered string
std::string CenterAlign(const std::string& str, const int& width);

//Resize font size with scale
void SetFontScale(const int& scale);

//Set text color
void SetTextColor(int color);

//Clear screen
void ClearScreen();

//Play
void Play(GameMap gameMap, Snake snake);

//Draw map from file 
void DrawMap(GameMap gameMap);

//Draw area display gameplay infomation
void DrawInfoUI();

//Draw menu for scale size of console window
void ScaleMenu(int& scale);

//Draw adjust bar showing percentage
std::string DrawAdjustBar(const int& width, const int& fill);

void Makefood(GameMap& gameMap, int n);