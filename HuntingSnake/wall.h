#pragma once
#include <Windows.h>
#include "struct.h"
#include <vector>
#include <fstream>
#include <string>
using namespace std;
bool checkWall(const COORD a, const vector<COORD> b);
void inputWall(const int lv, const GameMap gameMap);