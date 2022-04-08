#pragma once

#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <conio.h>
#include "struct.h"
#include <ctime>
#include <thread>
#include <mmsystem.h>
#include <stdio.h>

//Usable characters: • Ö ö × ¤ « » 

//Fix console window to specify height and width
//Prevent user from maximizing or scrolling console window
//Idea: https://codelearn.io/sharing/windowsh-va-ham-dinh-dang-console-p1
void FixConsole();

//Draw title HUNTINGSNAKE
void DrawTitle1();

//Interact with main menu
void MainMenu(int* choose);

//Move the cursor to the position on the screen
void GotoXY(const int& x, const int& y);

//Return centered string
std::string CenterAlign(const std::string& str, const int& width);

//Resize font size with scale
void SetFontScale(const int& scale);

//Set text color
void SetTextColor(const int& background, const int& text);

//Draw map from file 
void DrawWall(GameLVL& gameLVL);

void DrawFood(const COORD* food);

//Draw menu for scale size of console window
void ScaleMenu(int& scale);

//Draw adjust bar showing percentage
std::string DrawAdjustBar(const int& width, const float& fill);

void KeyInputThread(const int* curLVL, GameLVL* gameLVL, Snake* snake, HANDLE thrd1, HANDLE thrd2);

void SwapCOORD(COORD& A, COORD& B);

int FindInCOORD(const COORD& var, const std::vector<COORD>& arr);

//TITLE------------------------------------------------------------------------------------------------------------------------------------
	//Create a title from a string
Title CreateTitle(const std::string& str, const int& color, const char& pattern);
	//Replace old character to new one in a string;
void ReplaceCharacterString(std::string& str, const char& oldChar, const char& newChar);
	//Replace old pattern to new one in a title
void ReplacePatternTitle(Title& title, const char& pattern);
	//Draw title
void DrawTitle(const COORD& pos, const Title& title);
	//Draw title in center play area
void DrawTitlePlayArea(const std::string& str);
void PrintSubTextPA(const std::string& str);

//CLEAR SCREEN-----------------------------------------------------------------------------------------------------------------------------
	//Clear a square area on screen
void ClearSquare(const Square& square);
	//Clear entire screen
void ClearScreen();

//SCREEN CALCULATOR------------------------------------------------------------------------------------------------------------------------
	//Get position that
void CenterSquareInSquare(const Square& bigSquare, Square* smallSquare);

//PLAY AREA--------------------------------------------------------------------------------------------------------------------------------



//UI---------------------------------------------------------------------------------------------------------------------------------------
	//Draw area display UI
void DrawInfoUI(const GameLVL* gameLVL, const Snake* snake, const int* curLVL);
	//Update UI
void UpdateUIInfo(const int* info, const int& maxLengthInfo, const short& x, const short& y);

int PauseMenu();

void DrawGate(GameLVL* gameLVL, Snake* snake);