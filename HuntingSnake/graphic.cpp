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
	ShowScrollBar(hWnd, SB_BOTH, 0); //If third parameter is 0, scrollbars are hidden.

	//Set font
	SetFontScale(100);

	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = false; //Set the cursor visibility
	SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
}

void LoadMap(int lvl) {
	ifstream fIn;
	fIn.open("data\\levels\\template1.txt", ios::in);
	char str[20];
	fIn >> str;
	cout << str;
	fIn.close();
}

void DrawTitle() {
	//Ü ß Û
	GotoXY(0, 5);
	cout << "                ÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜÜ                ";
	cout << "                Û                                                                                      Û                ";
	cout << "                Û  ²   ²  ²   ²  ²   ²  ²²²²²  ²²²²²  ²   ²  ²²²²²  ²²²²²  ²   ²  ²²²²²  ²   ²  ²²²²²  Û                ";
	cout << "                Û  ²   ²  ²   ²  ²²  ²    ²      ²    ²²  ²  ²      ²      ²²  ²  ²   ²  ²  ²   ²      Û                ";
	cout << "                Û  ²²²²²  ²   ²  ² ² ²    ²      ²    ² ² ²  ²  ²²  ²²²²²  ² ² ²  ²²²²²  ²²²    ²²²²²  Û                ";
	cout << "                Û  ²   ²  ²   ²  ²  ²²    ²      ²    ²  ²²  ²   ²      ²  ²  ²²  ²   ²  ²  ²   ²      Û                ";
	cout << "                Û  ²   ²  ²²²²²  ²   ²    ²    ²²²²²  ²   ²  ²²²²²  ²²²²²  ²   ²  ²   ²  ²   ²  ²²²²²  Û                ";
	cout << "                Û                                                                                      Û                ";
	cout << "                ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß                    ßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßßß                ";
	GotoXY(52, 13);
	cout << "MADE BY GROUP 12";
}

void MainMenu(int& choose) {
	DrawTitle();
	//Selecting
	int def_color = 3; //Default color
	int curChoose = 0; //Current choose
	int colorChoose[4] = { def_color, 7, 7, 7 }; //Color of each choose
	char key;
	while (true) {
		GotoXY(56, 19);
		SetTextColor(colorChoose[0]);
		cout << "CONTINUE";

		GotoXY(56, 20);
		SetTextColor(colorChoose[1]);
		cout << "NEW GAME";

		GotoXY(56, 21);
		SetTextColor(colorChoose[2]);
		cout << "SETTINGS";

		GotoXY(58, 22);
		SetTextColor(colorChoose[3]);
		cout << "QUIT";

		key = _getch();
		// 72: Up     80: Down    '\r': Enter
		if ((key == 'w' || key == 'W') && (curChoose >= 1 && curChoose <= 3)) {
			colorChoose[curChoose] = 7;
			curChoose--;
			colorChoose[curChoose] = def_color;
		}
		else if ((key == 's' || key == 'S') && (curChoose >= 0 && curChoose <= 2)) {
			colorChoose[curChoose] = 7;
			curChoose++;
			colorChoose[curChoose] = def_color;
		}
		else if (key == '\r') {
			choose = curChoose;
			return;
		}
	}
}

void GotoXY(const int& x, const int& y) {
	COORD pos;
	pos.X = x;
	pos.Y = y;
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

void SetFontScale(const int& scale) {
	CONSOLE_FONT_INFOEX cf = { 0 };
	cf.cbSize = sizeof cf;
	cf.dwFontSize.X = 10 * scale / 100;
	cf.dwFontSize.Y = 20 * scale / 100;
	wcscpy_s(cf.FaceName, L"Terminal");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), 0, &cf);
}

void SetTextColor(int color) {
	// 0. Black
	// 1. Blue
	// 2. Green
	// 3. Aqua
	// 4. Red
	// 5. Purple
	// 6. Yellow
	// 7. White
	// 8. Gray
	// 9. Light Blue
	// 10. Light Green
	// 11. Light Aqua
	// 12. Light Red
	// 13. Light Purple
	// 14. Light Yellow
	// 15. Light White
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void ClearScreen() {
	cout << "\x1B[2J\x1B[H";
}