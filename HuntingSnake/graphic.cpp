#include "graphic.h"

#define heightCon 30;
#define widthCon 120;


using namespace std;

void FixConsole() {

	//Set console window size
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT lpConsoleWindow;
	lpConsoleWindow.Top = 0;
	lpConsoleWindow.Left = 0;
	lpConsoleWindow.Right = widthCon;
	lpConsoleWindow.Bottom = heightCon;
	SetConsoleWindowInfo(hConsoleOutput, 1, &lpConsoleWindow); //Parameter '1' specifies the upper left corner as the coordinate angle
	
	//Set console screen buffer size
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD dwSize;
	dwSize.X = widthCon;
	dwSize.Y = heightCon;
	SetConsoleScreenBufferSize(hConsoleOutput, dwSize);	

	//Disable maximize console window
		//Disable dragging
	HWND hWnd = GetConsoleWindow();
	SetWindowLong(hWnd, GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_SIZEBOX);
		//Disable menu button
	HMENU hMenu = GetSystemMenu(hWnd, false);
	DeleteMenu(hMenu, SC_MAXIMIZE, MF_BYCOMMAND);

	//Hide scrollbars
	//ShowScrollBar(hWnd, SB_BOTH, 0); //If third parameter is 0, scrollbars are hidden.
}

void LoadMap(int lvl) {
	ifstream fIn;
	fIn.open("data\\levels\\template1.txt", ios::in);
	char str[20];
	fIn >> str;
	cout << str;
	fIn.close();
}

void CreatePlayMenu() {
	
}

void GoToXY(COORD pos) {
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

string CenterAlign(const string& str, const int& width) {
	if (width <= str.size()) return str;
	string newstr;
	int index = width / 2 - str.size() / 2;
	for (int i = 0; i < index; i++) {
		newstr += ' ';
	}
	newstr += str;
	for (int i = 0; i < width; i++) {
		newstr += ' ';
	}
	return newstr;
}