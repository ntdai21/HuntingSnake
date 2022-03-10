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

	//Hide cursor
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
	ClearScreen();
	DrawTitle();
	//Selecting
	int def_color = 3; //Default color
	int curChoose = 0; //Current choose
	int colorChoose[4] = { def_color, 7, 7, 7 }; //Color of each choose
	char key;
	while (true) {
		// 0123 
		GotoXY(54, 19);
		SetTextColor(colorChoose[0]);
		cout << "  CONTINUE  ";

		GotoXY(54, 20);
		SetTextColor(colorChoose[1]);
		cout << "  NEW GAME  ";

		GotoXY(54, 21);
		SetTextColor(colorChoose[2]);
		cout << "  SETTINGS  ";

		GotoXY(54, 22);
		SetTextColor(colorChoose[3]);
		cout << "    QUIT    ";

		if (curChoose != 3) {
			GotoXY(54, 19 + curChoose);
			cout << '';
			GotoXY(65, 19 + curChoose);
			cout << '';
		}
		else {
			GotoXY(56, 19 + curChoose);
			cout << '';
			GotoXY(63, 19 + curChoose);
			cout << '';
		}

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
			ClearScreen();
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

void Play(GameMap gameMap, Snake snake) {
	DrawMap(gameMap);
	DrawInfoUI();
	_getch();
}

void DrawMap(GameMap gameMap) {
	
}

void DrawInfoUI() {
	//¿ À À Ú Ù ³ Ä
	GotoXY(0, 26);
	cout << "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿\n\n";
	cout << "³           SPEED: 00 px/s               FOOD: 00 / 00             LVL: 00               POINT: 000 000                ³\n\n";
	cout << "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ";
}

void ScaleMenu(int& scale) {
	ClearScreen();
	cout << "Choose your console windows size scale: \n\n";
	cout << "SCALE: ";
	GotoXY(9, 2);
	cout << "\n\nUse \'A\' and \'D\' to adjust. Hit \'Enter\' to continue with current scale.\n";
	cout << "\nIf the console window size is bigger than your computer screen size, it may causes some bugs.\n";
	char key;
	while (true) {
		GotoXY(7, 2);
		cout << DrawAdjustBar(20, scale / 10) << ' ' << setw(3) << scale << '%';
		SetFontScale(scale);
		key = _getch();
		// 72: Up     80: Down    '\r': Enter
		if ((key == 'a' || key == 'A') && (scale >= 40 && scale <= 200)) scale -= 20;
		else if ((key == 'd' || key == 'D') && (scale >= 20 && scale <= 180)) scale += 20;
		else if (key == '\r') {
			ClearScreen();
			return;
		}
	}
}

string DrawAdjustBar(const int& width, const int& fill) {
	string bar;
	for (int i = 1; i <= width; i++) {
		if (i <= fill) bar += 'Û';
		else bar += 'Ä';
	}
	return bar;
}