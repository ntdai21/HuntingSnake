#pragma once

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>

//Fix console window to specify height and width
//Prevent user from maximizing or scrolling console window
//Idea: https://codelearn.io/sharing/windowsh-va-ham-dinh-dang-console-p1
void FixConsole();

void LoadMap(int lvl);

//Create area displaying all game properties like point, speed, lvl,...
void CreatePlayMenu();

//Move the cursor to the position on the screen
void GoToXY(COORD pos);

//Return centered string
std::string CenterAlign(const std::string& str, const int& width);