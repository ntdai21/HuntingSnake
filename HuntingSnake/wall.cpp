#include "wall.h"
bool checkWall(const COORD a, const vector<COORD> arr)
{
	for (int i = 0; i < arr.size(); i++) {
		if (a.X == arr[i].X && a.X == arr[i].Y) return false;
	}
	return true;
}
void inputWall(const int lv, GameMap &gameMap)
{
	ifstream f;
	f.open("data\\levels\\map1.txt", ios::in);
	string s;
	for (int i = 0; i < 27; i++) {
		getline(f, s);
		for (int j = 0; j < 96; j++) {
			if (s[j] == '0') gameMap.wall.push_back({ (short)j, (short)i });
		}
	}
	f.close();
}