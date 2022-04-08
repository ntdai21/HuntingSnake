#include "graphic.h"
#include "game_mechanic.h"
#include <cmath>
#include "sound.h"

using namespace std;

void FixConsole() {
	

	//Set console window size
	HANDLE hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT lpConsoleWindow;
	lpConsoleWindow.Top = 0;
	lpConsoleWindow.Left = 0;
	lpConsoleWindow.Right = WINDOW_WIDTH;
	lpConsoleWindow.Bottom = WINDOW_HEIGHT;
	SetConsoleWindowInfo(hConsoleOutput, 1, &lpConsoleWindow); //Parameter '1' specifies the upper left corner as the coordinate angle

	//Set console screen buffer size
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	COORD dwSize;
	dwSize.X = WINDOW_WIDTH;
	dwSize.Y = WINDOW_HEIGHT;
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
	SetFontScale(FONT_SCALE);

	//Hide cursor
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = false; //Set the cursor visibility
	SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
}



void DrawTitle1() {
	//Ü ß Û
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
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
	Title title = CreateTitle("HUNTINGSNAKE", INFO_TITLE_COLOR, char(219));
	Square titleSquare = { 0, 0, title.text[0].size(), 5 };
	CenterSquareInSquare({ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - 10 }, &titleSquare);
	DrawTitle({ titleSquare.x, titleSquare.y }, title);
	GotoXY(52, 13);
	cout << "MADE BY GROUP 12";
}

void MainMenu(int* choose) {
	ClearScreen();
	DrawTitle1();
	//Selecting
	int curChoose = 0; //Current choose
	int colorChoose[4] = { BUTTON_TEXT_COLOR, NORMAL_TEXT_COLOR, NORMAL_TEXT_COLOR, NORMAL_TEXT_COLOR }; //Color of each choose
	char key;
	while (true) {
		// 0123 
		GotoXY(54, 19);
		SetTextColor(BACKGROUND_COLOR, colorChoose[0]);
		cout << "  CONTINUE  ";

		GotoXY(54, 20);
		SetTextColor(BACKGROUND_COLOR, colorChoose[1]);
		cout << "  NEW GAME  ";

		GotoXY(54, 21);
		SetTextColor(BACKGROUND_COLOR, colorChoose[2]);
		cout << "  SETTINGS  ";

		GotoXY(54, 22);
		SetTextColor(BACKGROUND_COLOR, colorChoose[3]);
		cout << "    QUIT    ";

		SetTextColor(BACKGROUND_COLOR, BUTTON_TEXT_COLOR);
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
		PlayMP3("menu_choosing");
		// 72: Up     80: Down    '\r': Enter
		if ((key == 'w' || key == 'W') && (curChoose >= 1 && curChoose <= 3)) {
			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
			curChoose--;
			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
		}
		else if ((key == 's' || key == 'S') && (curChoose >= 0 && curChoose <= 2)) {
			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
			curChoose++;
			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
		}
		else if (key == '\r') {
			PlayMP3("enter");
			*choose = curChoose;
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
	for (int i = newstr.size(); i < width; i++) {
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

void SetTextColor(const int& background, const int& text) {
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
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16 * background + text);
}

void DrawWall(GameLVL& gameLVL) {
	for (COORD i : gameLVL.wall) {
		GotoXY(i.X, i.Y);
		cout << '²';
	}
}

void DrawFood(const COORD* food) {
	GotoXY(food->X, food->Y);
	SetTextColor(BACKGROUND_COLOR, FOOD_COLOR);
	cout << '';
}

void DrawSnake(const Snake* snake) {
	GotoXY(snake->body[0].X, snake->body[0].Y);
	SetTextColor(BACKGROUND_COLOR, BUTTON_TEXT_COLOR);
	cout << snake->bodyPattern[0];
	for (int i = 1; i < snake->body.size(); i++) {
		SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
		GotoXY(snake->body[i].X, snake->body[i].Y);
		cout << snake->bodyPattern[i];
	}
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
		cout << DrawAdjustBar(20, (float)scale / (10 * 20)) << ' ' << setw(3) << scale << '%';
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

string DrawAdjustBar(const int& width, const float& fill) {
	string bar;
	for (int i = 1; i <= width; i++) {
		if (i <= fill * width) bar += 'Û';
		else bar += '°';
	}
	return bar;
}

void KeyInputThread(const int* curLVL, GameLVL* gameLVL, Snake* snake, HANDLE thrd1, HANDLE thrd2) {
	char key = 'A';
	while (snake->state) {
		key = _getch();
		switch (key)
		{
		case 'a':
		case 'A':
			snake->curDirection = 'a';
			break;
		case 'd':
		case 'D':
			snake->curDirection = 'd';
			break;
		case 'w':
		case 'W':
			snake->curDirection = 'w';
			break;
		case 's':
		case 'S':
			snake->curDirection = 's';
			break;
		case 27:
		case 'p':
		case 'P':
			PauseGame(thrd1, thrd2, curLVL, gameLVL, snake);
		default:
			break;
		}
	}
}

void SwapCOORD(COORD& A, COORD& B) {
	COORD temp = A;
	A = B;
	B = temp;
}

int FindInCOORD(const COORD& var, const vector<COORD>& arr) {
	for (int i = arr.size() - 1; i > -1; i--) {
		if (var.X == arr[i].X && var.Y == arr[i].Y) return i;
	}
	return -1;
}

//TITLE------------------------------------------------------------------------------------------------------------------------------------

Title CreateTitle(const string& str, const int& color, const char& pattern) {
	Title title;
	title.color = color;
	title.pattern = pattern;
	for (int i = 0; i < str.size(); i++) {
		//Create space between 2 big characters
		if (i != 0) {
			for (int i = 0; i < 5; i++) {
				title.text[i] += "  ";
			}
		}

		switch (str.at(i))
		{
		case 'a':
		case 'A':
			title.text[0] += "00000";
			title.text[1] += "0   0";
			title.text[2] += "00000";
			title.text[3] += "0   0";
			title.text[4] += "0   0";
			break;
		case 'b':
		case 'B':
			title.text[0] += "0000 ";
			title.text[1] += "0   0";
			title.text[2] += "0000 ";
			title.text[3] += "0   0";
			title.text[4] += "0000 ";
			break;
		case 'c':
		case 'C':
			title.text[0] += "00000";
			title.text[1] += "0    ";
			title.text[2] += "0    ";
			title.text[3] += "0    ";
			title.text[4] += "00000";
			break;
		case 'd':
		case 'D':
			title.text[0] += "0000 ";
			title.text[1] += "0   0";
			title.text[2] += "0   0";
			title.text[3] += "0   0";
			title.text[4] += "0000 ";
			break;
		case 'e':
		case 'E':
			title.text[0] += "00000";
			title.text[1] += "0    ";
			title.text[2] += "00000";
			title.text[3] += "0    ";
			title.text[4] += "00000";
			break;
		case 'f':
		case 'F':
			title.text[0] += "00000";
			title.text[1] += "0    ";
			title.text[2] += "00000";
			title.text[3] += "0    ";
			title.text[4] += "0    ";
			break;
		case 'g':
		case 'G':
			title.text[0] += "00000";
			title.text[1] += "0    ";
			title.text[2] += "0 000";
			title.text[3] += "0   0";
			title.text[4] += "00000";
			break;
		case 'h':
		case 'H':
			title.text[0] += "0   0";
			title.text[1] += "0   0";
			title.text[2] += "00000";
			title.text[3] += "0   0";
			title.text[4] += "0   0";
			break;
		case 'i':
		case 'I':
			title.text[0] += "00000";
			title.text[1] += "  0  ";
			title.text[2] += "  0  ";
			title.text[3] += "  0  ";
			title.text[4] += "00000";
			break;
		case 'j':
		case 'J':
			title.text[0] += "00000";
			title.text[1] += "   0 ";
			title.text[2] += "   0 ";
			title.text[3] += "   0 ";
			title.text[4] += "000  ";
			break;
		case 'k':
		case 'K':
			title.text[0] += "0   0";
			title.text[1] += "0  0 ";
			title.text[2] += "000  ";
			title.text[3] += "0  0 ";
			title.text[4] += "0   0";
			break;
		case 'l':
		case 'L':
			title.text[0] += "0    ";
			title.text[1] += "0    ";
			title.text[2] += "0    ";
			title.text[3] += "0    ";
			title.text[4] += "00000";
			break;
		case 'm':
		case 'M':
			title.text[0] += "00 00";
			title.text[1] += "0 0 0";
			title.text[2] += "0 0 0";
			title.text[3] += "0   0";
			title.text[4] += "0   0";
			break;
		case 'n':
		case 'N':
			title.text[0] += "0   0";
			title.text[1] += "00  0";
			title.text[2] += "0 0 0";
			title.text[3] += "0  00";
			title.text[4] += "0   0";
			break;
		case 'o':
		case 'O':
			title.text[0] += "00000";
			title.text[1] += "0   0";
			title.text[2] += "0   0";
			title.text[3] += "0   0";
			title.text[4] += "00000";
			break;
		case 'p':
		case 'P':
			title.text[0] += "00000";
			title.text[1] += "0   0";
			title.text[2] += "00000";
			title.text[3] += "0    ";
			title.text[4] += "0    ";
			break;
		case 'q':
		case 'Q':
			title.text[0] += "00000";
			title.text[1] += "0   0";
			title.text[2] += "0   0";
			title.text[3] += "0  00";
			title.text[4] += "00000";
			break;
		case 'r':
		case 'R':
			title.text[0] += "0000 ";
			title.text[1] += "0   0";
			title.text[2] += "0000 ";
			title.text[3] += "0   0";
			title.text[4] += "0   0";
			break;
		case 's':
		case 'S':
			title.text[0] += "00000";
			title.text[1] += "0    ";
			title.text[2] += "00000";
			title.text[3] += "    0";
			title.text[4] += "00000";
			break;
		case 't':
		case 'T':
			title.text[0] += "00000";
			title.text[1] += "  0  ";
			title.text[2] += "  0  ";
			title.text[3] += "  0  ";
			title.text[4] += "  0  ";
			break;
		case 'u':
		case 'U':
			title.text[0] += "0   0";
			title.text[1] += "0   0";
			title.text[2] += "0   0";
			title.text[3] += "0   0";
			title.text[4] += "00000";
			break;
		case 'v':
		case 'V':
			title.text[0] += "0   0";
			title.text[1] += "0   0";
			title.text[2] += " 0 0 ";
			title.text[3] += " 0 0 ";
			title.text[4] += "  0  ";
			break;
		case 'w':
		case 'W':
			title.text[0] += "0   0";
			title.text[1] += "0   0";
			title.text[2] += "0 0 0";
			title.text[3] += "0 0 0";
			title.text[4] += "00 00";
			break;
		case 'x':
		case 'X':
			title.text[0] += "0   0";
			title.text[1] += " 0 0 ";
			title.text[2] += "  0  ";
			title.text[3] += " 0 0 ";
			title.text[4] += "0   0";
			break;
		case 'y':
		case 'Y':
			title.text[0] += "0   0";
			title.text[1] += " 0 0 ";
			title.text[2] += "  0  ";
			title.text[3] += "  0  ";
			title.text[4] += "  0  ";
			break;
		case 'z':
		case 'Z':
			title.text[0] += "00000";
			title.text[1] += "   0 ";
			title.text[2] += "  0  ";
			title.text[3] += " 0   ";
			title.text[4] += "00000";
			break;
		case ' ':
			title.text[0] += "     ";
			title.text[1] += "     ";
			title.text[2] += "     ";
			title.text[3] += "     ";
			title.text[4] += "     ";
			break;
		case '0':
			title.text[0] += " 000 ";
			title.text[1] += "0   0";
			title.text[2] += "0   0";
			title.text[3] += "0   0";
			title.text[4] += " 000 ";
			break;
		case '1':
			title.text[0] += "  00 ";
			title.text[1] += " 0 0 ";
			title.text[2] += "0  0 ";
			title.text[3] += "   0 ";
			title.text[4] += "00000";
			break;
		case '2':
			title.text[0] += " 000 ";
			title.text[1] += "0   0";
			title.text[2] += "   0 ";
			title.text[3] += "  0  ";
			title.text[4] += "00000";
			break;
		case '3':
			title.text[0] += " 000 ";
			title.text[1] += "0   0";
			title.text[2] += "  00 ";
			title.text[3] += "0   0";
			title.text[4] += " 000 ";
			break;
		case '4':
			title.text[0] += "   0 ";
			title.text[1] += "  0  ";
			title.text[2] += " 0 0 ";
			title.text[3] += "00000";
			title.text[4] += "   0 ";
			break;
		case '5':
			title.text[0] += "00000";
			title.text[1] += "0    ";
			title.text[2] += " 000 ";
			title.text[3] += "    0";
			title.text[4] += "0000 ";
			break;
		case '6':
			title.text[0] += " 000 ";
			title.text[1] += "0    ";
			title.text[2] += "00000";
			title.text[3] += "0   0";
			title.text[4] += " 000 ";
			break;
		case '7':
			title.text[0] += "00000";
			title.text[1] += "   0 ";
			title.text[2] += "  0  ";
			title.text[3] += " 0   ";
			title.text[4] += " 0   ";
			break;
		case '8':
			title.text[0] += " 000 ";
			title.text[1] += "0   0";
			title.text[2] += " 000 ";
			title.text[3] += "0   0";
			title.text[4] += " 000 ";
			break;
		case '9':
			title.text[0] += " 000 ";
			title.text[1] += "0   0";
			title.text[2] += "00000";
			title.text[3] += "    0";
			title.text[4] += " 000 ";
			break;
		default:
			break;
		}
	}
	ReplacePatternTitle(title, pattern);
	return title;
}

void ReplaceCharacterString(string& str, const char& oldChar, const char& newChar) {
	for (int i = 0; i < str.size(); i++) {
		if (str.at(i) == oldChar) str.at(i) = newChar;
	}
}

void ReplacePatternTitle(Title& title, const char& pattern) {
	for (int i = 0; i < 5; i++) {
		ReplaceCharacterString(title.text[i], '0', pattern);
	}
}

void DrawTitle(const COORD& pos, const Title& title) {
	SetTextColor(BACKGROUND_COLOR, INFO_TITLE_COLOR);
	for (int i = 0; i < 5; i++) {
		GotoXY(pos.X, pos.Y + i);
		cout << title.text[i];
	}
}

void DrawTitlePlayArea(const string& str) {
	Title title = CreateTitle(str, 7, char(219));
	Square titleSquare = { 0, 0, title.text[0].size(), 5 };
	CenterSquareInSquare({ PA_X, PA_Y, PA_DX, PA_DY }, &titleSquare);
	DrawTitle({ titleSquare.x, titleSquare.y }, title);
}

void PrintSubTextPA(const string& str) {
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	GotoXY(PA_X , TEXT_SUB_PA);
	cout << CenterAlign(str, PA_DX );
}


//CLEAR SCREEN-----------------------------------------------------------------------------------------------------------------------------

void ClearSquare(const Square& square) {
	for (int i = square.y; i < square.dy + square.y; i++) {
		GotoXY(square.x, i);
		for (int j = 1; j <= square.dx; j++) {
			cout << ' ';
		}
	}
}

void ClearScreen() {
	cout << "\x1B[2J\x1B[H";
}

//SCREEN CALCULATOR------------------------------------------------------------------------------------------------------------------------

void CenterSquareInSquare(const Square& bigSquare, Square* smallSquare) {
	COORD pos;
	if (bigSquare.dx * bigSquare.dy <= smallSquare->dx * smallSquare->dy) return;
	smallSquare->x = bigSquare.x + (bigSquare.dx - smallSquare->dx) / 2;
	smallSquare->y = bigSquare.y + (bigSquare.dy - smallSquare->dy) / 2;
}

//PLAY AREA--------------------------------------------------------------------------------------------------------------------------------

//UI---------------------------------------------------------------------------------------------------------------------------------------

void DrawInfoUI(const GameLVL* gameLVL, const Snake* snake, const int* curLVL) {
	//¿ À À Ú Ù ³ Ä
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	GotoXY(0, 0);
	cout << "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿";
	cout << "³                                                                                             ³³       OBJECTIVE       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´";
	cout << "³                                                                                             ³³    CURRENT LVL: 00    ³";
	cout << "³                                                                                             ³ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³   SPEED: 00 cell/s    ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³   FOOD: 000 / 000     ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³   LIFE: 00            ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³         POINT         ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³³      000.000.000      ³";
	cout << "³                                                                                             ³³                       ³";
	cout << "³                                                                                             ³ÃÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ´";
	cout << "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ³  A,S,W,D: MOVE SNAKE  ³";
	cout << "ÚÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄ¿³                       ³";
	cout << "³LIFE TIME:                                                                                   ³³   ESC, P: PAUSE GAME  ³";
	cout << "ÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙÀÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÄÙ";
	
	//Set colors
	SetTextColor(BACKGROUND_COLOR, INFO_TITLE_COLOR);
	GotoXY(103, 1);
	cout << "OBJECTIVE";
	GotoXY(100, 10);
	cout << "CURRENT LVL:";
	GotoXY(99, 13);
	cout << "SPEED:";
	GotoXY(99, 15);
	cout << "FOOD:";
	GotoXY(99, 17);
	cout << "LIFE:";
	GotoXY(105, 21);
	cout << "POINT";
	GotoXY(1, 28);
	cout << "LIFE TIME:";

	//Update UI infomation
	UpdateUIInfo(curLVL, 2, UI_LVL_X, UI_LVL_Y);
	UpdateUIInfo(&snake->speed, 2, UI_SPEED_X, UI_SPEED_Y);
	UpdateUIInfo(&snake->food, 3, UI_FOOD_X, UI_FOOD_Y);
	UpdateUIInfo(&gameLVL->maxFood, 3, UI_FOOD_X + 6, UI_FOOD_Y);
	UpdateUIInfo(&snake->life, 2, UI_LIFE_X, UI_LIFE_Y);
	UpdateLifeTime(gameLVL);
}

void UpdateUIInfo(const int* info, const int& maxLengthInfo, const short& x, const short& y) {
	int maxLength = *info;
	int pos = 0;
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	while (maxLength >= 10) {
		maxLength /= 10;
		pos++;
	}
	GotoXY(x + maxLengthInfo - pos - 1, y);
	cout << *info;
}

void UpdateLifeTime(const GameLVL* gameLVL) {
	GotoXY(UI_TIMER_X, UI_TIMER_Y);
	size_t LifeTimeBar = PA_DX - UI_TIMER_X + 1;
	float percent = (float)gameLVL->timer / gameLVL->baseTimer;
	if (percent > 0.5) SetTextColor(BACKGROUND_COLOR, 2);
	else if (percent > 0.25) SetTextColor(BACKGROUND_COLOR, 6);
	else SetTextColor(BACKGROUND_COLOR, 4);
	if (gameLVL->timeLimit) cout << DrawAdjustBar(LifeTimeBar, percent);
	else cout << DrawAdjustBar(LifeTimeBar, LifeTimeBar);
}

int PauseMenu() {
	ClearObjective();
	//Selecting
	int curChoose = 0; //Current choose
	int colorChoose[2] = { BUTTON_TEXT_COLOR, NORMAL_TEXT_COLOR }; //Color of each choose
	char key;
	while (true) {
		// 0123 
		GotoXY(UI_OJECTIVE_X + 5, UI_OJECTIVE_Y + 1);
		SetTextColor(BACKGROUND_COLOR, colorChoose[0]);
		//.......01234567890123456789012
		cout << "  CONTINUE  ";

		GotoXY(UI_OJECTIVE_X + 5, UI_OJECTIVE_Y + 2);
		SetTextColor(BACKGROUND_COLOR, colorChoose[1]);
		cout << "  MAIN MENU  ";
		
		SetTextColor(BACKGROUND_COLOR, BUTTON_TEXT_COLOR);
		GotoXY(UI_OJECTIVE_X + 5, UI_OJECTIVE_Y + 1 + curChoose);
		cout << '';
		if (curChoose == 0) GotoXY(UI_OJECTIVE_X + 16, UI_OJECTIVE_Y + 1 + curChoose);
		else GotoXY(UI_OJECTIVE_X + 17, UI_OJECTIVE_Y + 1 + curChoose);
		cout << '';

		key = _getch();
		PlayMP3("menu_choosing");
		// 72: Up     80: Down    '\r': Enter
		if ((key == 'w' || key == 'W') && (curChoose == 1 )) {
			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
			curChoose--;
			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
		}
		else if ((key == 's' || key == 'S') && (curChoose == 0)) {
			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
			curChoose++;
			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
		}
		else if (key == '\r') {
			PlayMP3("enter");
			break;
		}
	}
	return curChoose;
}

void DrawGate(GameLVL* gameLVL, Snake* snake) {
	gameLVL->gateOpen = true;
	if (gameLVL->gate.size() == 0) {
		snake->state = 0;
		gameLVL->isWin = 1;
		return;
	}
	for (COORD& i : gameLVL->gate) {
		GotoXY(i.X, i.Y);
		SetTextColor(BACKGROUND_COLOR, FOOD_COLOR);
		cout << char(219);
	}
}

void DrawObjective(const GameLVL* gameLVL) {
	ClearObjective();
	int pos = 0;
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	//"                       "
	if (gameLVL->gateOpen) {
		if (gameLVL->timeLimit) {
			GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
			cout << CenterAlign("Enter a gate before", 23);
			GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
			cout << CenterAlign("time out.", 23);
		}
		else {
			GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
			cout << CenterAlign("Enter a gate.", 23);
		}
	}
	else {
		if (gameLVL->timeLimit) {
			GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
			cout << CenterAlign("Eat enough food", 23);
			GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
			cout << CenterAlign("before time out.", 23);
		}
		else {
			GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
			cout << CenterAlign("Eat enough food.", 23);
		}
	}
	pos++;
	if (gameLVL->canSelfTouching) {
		GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
		cout << CenterAlign("You can go through", 23);
		GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + pos++);
		cout << CenterAlign("your body.", 23);
	}
}

void ClearObjective() {
	ClearSquare({UI_OJECTIVE_X, UI_OJECTIVE_Y, 23, 5});
}

void WaitForReady(const GameLVL* gameLVL) {
	ClearObjective();
	SetTextColor(BACKGROUND_COLOR, FOOD_COLOR);
	GotoXY(UI_OJECTIVE_X, UI_OJECTIVE_Y + 2);
	//cout << "     3...2...1...0     ";
	cout << "     3";
	for (int i = 1, j = 2; i < 14; i++) {
		Sleep(250);
		if (i % 4 == 0) cout << j--;
		else cout << '.';
	}
	DrawObjective(gameLVL);
}

//void SettingMenu() {
//	int curChoose = 0; //Current choose
//	int colorChoose[4] = { BUTTON_TEXT_COLOR, NORMAL_TEXT_COLOR, NORMAL_TEXT_COLOR, NORMAL_TEXT_COLOR }; //Color of each choose
//	char key;
//	int pos_X = 38;
//	int pos_Y = 19;
//	while (true) {
//		// 0123 
//		GotoXY(pos_X, pos_Y);
//		SetTextColor(BACKGROUND_COLOR, colorChoose[0]);
//		cout << "       SOUND VOLUME:";
//
//		GotoXY(pos_X, pos_Y + 1);
//		SetTextColor(BACKGROUND_COLOR, colorChoose[1]);
//		cout << "SOUND VOLUME:       ";
//
//		GotoXY(pos_X, pos_Y + 2);
//		SetTextColor(BACKGROUND_COLOR, colorChoose[2]);
//		cout << "SOUND VOLUME:       ";
//
//		GotoXY(pos_X, pos_Y + 3);
//		SetTextColor(BACKGROUND_COLOR, colorChoose[3]);
//		cout << "SOUND VOLUME:       ";
//
//		SetTextColor(BACKGROUND_COLOR, BUTTON_TEXT_COLOR);
//		switch (curChoose)
//		{
//		case 0:
//			GotoXY(pos_X - 2, pos_Y + curChoose);
//			cout << '';
//			break;
//		default:
//			break;
//		}
//
//		key = _getch();
//		PlayMP3("menu_choosing");
//		// 72: Up     80: Down    '\r': Enter
//		if ((key == 'w' || key == 'W') && (curChoose >= 1 && curChoose <= 3)) {
//			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
//			curChoose--;
//			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
//		}
//		else if ((key == 's' || key == 'S') && (curChoose >= 0 && curChoose <= 2)) {
//			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
//			curChoose++;
//			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
//		}
//		else if (key == '\r') {
//			PlayMP3("enter");
//			ClearScreen();
//			return;
//		}
//	}
//}