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
	Title title = CreateTitle("HUNTINGSNAKE");
	Square titleSquare = { 0, 0, title.text[0].size(), 5 };
	CenterSquareInSquare({ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT - 10 }, &titleSquare);
	DrawTitle({ titleSquare.x, titleSquare.y }, title);
	GotoXY(52, 13);
	cout << "MADE BY GROUP 12";
	ifstream fIn;
	string name;
	int point = 0;
	fIn.open("data\\HighestPoint.txt", ios::in);
	if (fIn.is_open()) {
		fIn >> point >> name;
		fIn.close();
	}
	GotoXY(0, 15);
	SetTextColor(BACKGROUND_COLOR, FOOD_COLOR);
	string str1 = "Highest Score: " + to_string(point) + "\t Player: " + name;
	cout << CenterAlign(str1, WINDOW_WIDTH);
}

void MainMenu(int* choose) {
	ClearScreen();
	DrawTitle1();
	//Selecting
	int curChoose = 0; //Current choose
	int colorChoose[3] = { BUTTON_TEXT_COLOR, NORMAL_TEXT_COLOR, NORMAL_TEXT_COLOR}; //Color of each choose
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
		cout << "    QUIT    ";

		SetTextColor(BACKGROUND_COLOR, BUTTON_TEXT_COLOR);
		if (curChoose != 2) {
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
		if ((key == 'w' || key == 'W') && (curChoose >= 1 && curChoose <= 2)) {
			colorChoose[curChoose] = NORMAL_TEXT_COLOR;
			curChoose--;
			colorChoose[curChoose] = BUTTON_TEXT_COLOR;
		}
		else if ((key == 's' || key == 'S') && (curChoose >= 0 && curChoose <= 1)) {
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
	cf.dwFontSize.X = 10 * (float)scale / 100;
	cf.dwFontSize.Y = 20 * (float)scale / 100;
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
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	for (COORD i : gameLVL.wall) {
		GotoXY(i.X, i.Y);
		cout << '²';
	}
}

void DrawFood(const COORD* food, const bool* isLifeFood) {
	GotoXY(food->X, food->Y);
	if (*isLifeFood) {
		SetTextColor(BACKGROUND_COLOR, LIFE_FOOD_COLOR);
		cout << char(3);
	}
	else {
		SetTextColor(BACKGROUND_COLOR, FOOD_COLOR);
		cout << '';
	}
	
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

Title CreateTitle(const string& str) {
	Title title;
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
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û   Û";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "Û   Û";
			title.text[4] += "Û   Û";
			break;
		case 'b':
		case 'B':
			title.text[0] += "ÛÛÛÛ ";
			title.text[1] += "Û  ßÛ";
			title.text[2] += "ÛÛÛÛ ";
			title.text[3] += "Û  ßÛ";
			title.text[4] += "ÛÛÛÛ ";
			break;
		case 'c':
		case 'C':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û    ";
			title.text[2] += "Û    ";
			title.text[3] += "Û    ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'd':
		case 'D':
			title.text[0] += "ÛÛÛÛ ";
			title.text[1] += "Û  ßÛ";
			title.text[2] += "Û   Û";
			title.text[3] += "Û  ÜÛ";
			title.text[4] += "ÛÛÛÛ ";
			break;
		case 'e':
		case 'E':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û    ";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "Û    ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'f':
		case 'F':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û    ";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "Û    ";
			title.text[4] += "Û    ";
			break;
		case 'g':
		case 'G':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û    ";
			title.text[2] += "Û ÛÛÛ";
			title.text[3] += "Û   Û";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'h':
		case 'H':
			title.text[0] += "Û   Û";
			title.text[1] += "Û   Û";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "Û   Û";
			title.text[4] += "Û   Û";
			break;
		case 'i':
		case 'I':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "  Û  ";
			title.text[2] += "  Û  ";
			title.text[3] += "  Û  ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'j':
		case 'J':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "   Û ";
			title.text[2] += "   Û ";
			title.text[3] += "  ÜÛ ";
			title.text[4] += "ÛÛÛ  ";
			break;
		case 'k':
		case 'K':
			title.text[0] += "Û  ÜÛ";
			title.text[1] += "Û ÜÛ ";
			title.text[2] += "ÛÛÛ  ";
			title.text[3] += "Û ßÛ ";
			title.text[4] += "Û  ßÛ";
			break;
		case 'l':
		case 'L':
			title.text[0] += "Û    ";
			title.text[1] += "Û    ";
			title.text[2] += "Û    ";
			title.text[3] += "Û    ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'm':
		case 'M':
			title.text[0] += "ÛÜ ÜÛ";
			title.text[1] += "ÛßÛßÛ";
			title.text[2] += "Û Û Û";
			title.text[3] += "Û   Û";
			title.text[4] += "Û   Û";
			break;
		case 'n':
		case 'N':
			title.text[0] += "ÛÜ  Û";
			title.text[1] += "ÛÛÜ Û";
			title.text[2] += "Û ÛÜÛ";
			title.text[3] += "Û  ÛÛ";
			title.text[4] += "Û   Û";
			break;
		case 'o':
		case 'O':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û   Û";
			title.text[2] += "Û   Û";
			title.text[3] += "Û   Û";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'p':
		case 'P':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û   Û";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "Û    ";
			title.text[4] += "Û    ";
			break;
		case 'q':
		case 'Q':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û   Û";
			title.text[2] += "Û   Û";
			title.text[3] += "Û  ÛÛ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'r':
		case 'R':
			title.text[0] += "ÛÛÛÛ ";
			title.text[1] += "Û  ßÛ";
			title.text[2] += "ÛÛÛÛ ";
			title.text[3] += "Û  ßÛ";
			title.text[4] += "Û   Û";
			break;
		case 's':
		case 'S':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û    ";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "    Û";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 't':
		case 'T':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "  Û  ";
			title.text[2] += "  Û  ";
			title.text[3] += "  Û  ";
			title.text[4] += "  Û  ";
			break;
		case 'u':
		case 'U':
			title.text[0] += "Û   Û";
			title.text[1] += "Û   Û";
			title.text[2] += "Û   Û";
			title.text[3] += "Û   Û";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case 'v':
		case 'V':
			title.text[0] += "Û   Û";
			title.text[1] += "Û   Û";
			title.text[2] += "ßÛ Ûß";
			title.text[3] += " Û Û ";
			title.text[4] += " ßÛß ";
			break;
		case 'w':
		case 'W':
			title.text[0] += "Û   Û";
			title.text[1] += "Û   Û";
			title.text[2] += "Û Û Û";
			title.text[3] += "ÛÜÛÜÛ";
			title.text[4] += "Ûß ßÛ";
			break;
		case 'x':
		case 'X':
			title.text[0] += "Û   Û";
			title.text[1] += " Û Û ";
			title.text[2] += "  Û  ";
			title.text[3] += " Û Û ";
			title.text[4] += "Û   Û";
			break;
		case 'y':
		case 'Y':
			title.text[0] += "Û   Û";
			title.text[1] += "ßÛ Ûß";
			title.text[2] += " ßÛß ";
			title.text[3] += "  Û  ";
			title.text[4] += "  Û  ";
			break;
		case 'z':
		case 'Z':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "   Û ";
			title.text[2] += "  Û  ";
			title.text[3] += " Û   ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case ' ':
			title.text[0] += "     ";
			title.text[1] += "     ";
			title.text[2] += "     ";
			title.text[3] += "     ";
			title.text[4] += "     ";
			break;
		case '0':
			title.text[0] += " ÛÛÛ ";
			title.text[1] += "Û   Û";
			title.text[2] += "Û   Û";
			title.text[3] += "Û   Û";
			title.text[4] += " ÛÛÛ ";
			break;
		case '1':
			title.text[0] += "  ÛÛ ";
			title.text[1] += " Û Û ";
			title.text[2] += "Û  Û ";
			title.text[3] += "   Û ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case '2':
			title.text[0] += " ÛÛÛ ";
			title.text[1] += "Û   Û";
			title.text[2] += "   Û ";
			title.text[3] += "  Û  ";
			title.text[4] += "ÛÛÛÛÛ";
			break;
		case '3':
			title.text[0] += " ÛÛÛ ";
			title.text[1] += "Û   Û";
			title.text[2] += "  ÛÛ ";
			title.text[3] += "Û   Û";
			title.text[4] += " ÛÛÛ ";
			break;
		case '4':
			title.text[0] += "   Û ";
			title.text[1] += "  Û  ";
			title.text[2] += " Û Û ";
			title.text[3] += "ÛÛÛÛÛ";
			title.text[4] += "   Û ";
			break;
		case '5':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "Û    ";
			title.text[2] += " ÛÛÛ ";
			title.text[3] += "    Û";
			title.text[4] += "ÛÛÛÛ ";
			break;
		case '6':
			title.text[0] += " ÛÛÛ ";
			title.text[1] += "Û    ";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "Û   Û";
			title.text[4] += " ÛÛÛ ";
			break;
		case '7':
			title.text[0] += "ÛÛÛÛÛ";
			title.text[1] += "   Û ";
			title.text[2] += "  Û  ";
			title.text[3] += " Û   ";
			title.text[4] += " Û   ";
			break;
		case '8':
			title.text[0] += " ÛÛÛ ";
			title.text[1] += "Û   Û";
			title.text[2] += " ÛÛÛ ";
			title.text[3] += "Û   Û";
			title.text[4] += " ÛÛÛ ";
			break;
		case '9':
			title.text[0] += " ÛÛÛ ";
			title.text[1] += "Û   Û";
			title.text[2] += "ÛÛÛÛÛ";
			title.text[3] += "    Û";
			title.text[4] += " ÛÛÛ ";
			break;
		default:
			break;
		}
	}
	return title;
}

void DrawTitle(const COORD& pos, const Title& title) {
	SetTextColor(BACKGROUND_COLOR, INFO_TITLE_COLOR);
	for (int i = 0; i < 5; i++) {
		GotoXY(pos.X, pos.Y + i);
		cout << title.text[i];
	}
}

void DrawTitlePlayArea(const string& str) {
	Title title = CreateTitle(str);
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
	cout << "³                                                                                             ³³   SPEED: 00 cells/sec ³";
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
	setprecision(2);
	UpdateUIInfo(&snake->speed, 2, UI_SPEED_X, UI_SPEED_Y);
	UpdateUIInfo(&snake->food, 3, UI_FOOD_X, UI_FOOD_Y);
	UpdateUIInfo(&gameLVL->maxFood, 3, UI_FOOD_X + 6, UI_FOOD_Y);
	UpdateUIInfo(&snake->life, 2, UI_LIFE_X, UI_LIFE_Y);
	UpdatePoint(snake->point);
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
	else {
		SetTextColor(BACKGROUND_COLOR, 2);
		cout << DrawAdjustBar(LifeTimeBar, LifeTimeBar);
	}
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
	PlayMP3("count_down_3");
	//cout << "     3...2...1...0     ";
	cout << "     3";
	for (int i = 1, j = 2; i < 14; i++) {
		Sleep(250);
		if (i % 4 == 0) cout << j--;
		else cout << '.';
	}
	DrawObjective(gameLVL);
}

void UpdatePoint(int point) {

	string str = "000.000.000";
	int digit = 10;
	while (point) {
		str.at(digit--) = char(point % 10 + 48);
		point /= 10;
		if (digit == 7 || digit == 3) digit--;
	}
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	GotoXY(UI_POINT_X, UI_POINT_Y);
	cout << str;
}

string GetName() {
	ClearSquare({ PA_X, PA_Y, PA_DX, PA_DY });
	DrawTitlePlayArea("HIGHEST POINT");
	PrintSubTextPA("You are the best player from now, tell us your name");
	GotoXY(0, TEXT_SUB_PA + 1);
	cout << CenterAlign("Name (max 16 character, no space):                 ", PA_DX);
	GotoXY(56, TEXT_SUB_PA + 1);
	string str;
	cin >> str;
	if (str.size() > 16) str.resize(16);
	return str;
}

void UpdateHighestPoint(const int& point) {
	size_t highestPoint = 0;
	ifstream fIn;
	fIn.open("data\\HighestPoint.txt", ios::in);
	if (fIn.is_open()) {
		fIn >> highestPoint;
		fIn.close();
	}
	if (point > highestPoint) {
		ofstream fOut;
		fOut.open("data\\HighestPoint.txt", ios::out);
		fOut << point << ' ' << GetName();
		fOut.close();
	}
}