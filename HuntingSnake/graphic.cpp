#include "graphic.h"
#include "game_mechanic.h"
#include <cmath>

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
	//� � �
	GotoXY(0, 5);
	cout << "                ����������������������������������������������������������������������������������������                ";
	cout << "                �                                                                                      �                ";
	cout << "                �  �   �  �   �  �   �  �����  �����  �   �  �����  �����  �   �  �����  �   �  �����  �                ";
	cout << "                �  �   �  �   �  ��  �    �      �    ��  �  �      �      ��  �  �   �  �  �   �      �                ";
	cout << "                �  �����  �   �  � � �    �      �    � � �  �  ��  �����  � � �  �����  ���    �����  �                ";
	cout << "                �  �   �  �   �  �  ��    �      �    �  ��  �   �      �  �  ��  �   �  �  �   �      �                ";
	cout << "                �  �   �  �����  �   �    �    �����  �   �  �����  �����  �   �  �   �  �   �  �����  �                ";
	cout << "                �                                                                                      �                ";
	cout << "                ����������������������������������                    ����������������������������������                ";
	GotoXY(52, 13);
	cout << "MADE BY GROUP 12";
}

void MainMenu(int* choose) {
	ClearScreen();
	DrawTitle1();
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



void DrawWall(GameLVL& gameLVL) {
	for (COORD i : gameLVL.wall) {
		GotoXY(i.X, i.Y);
		cout << '�';
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
		if (i <= fill) bar += '�';
		else bar += '�';
	}
	return bar;
}

void KeyInputThread(char *direct, bool *snakeState) {
	char key = 'A';
	while (*snakeState) {
		key = _getch();
		switch (key)
		{
		case 'a':
		case 'A':
			*direct = 'a';
			break;
		case 'd':
		case 'D':
			*direct = 'd';
			break;
		case 'w':
		case 'W':
			*direct = 'w';
			break;
		case 's':
		case 'S':
			*direct = 's';
			break;
		case 'p':
		case 'P':
			*snakeState = 0;
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
	for (int i = 0; i < 5; i++) {
		GotoXY(pos.X, pos.Y + i);
		cout << title.text[i];
	}
}

void DrawTitlePlayArea(const string& str) {
	Title title = CreateTitle(str, 7, '�');
	Square titleSquare = { 0, 0, title.text[0].size(), 5 };
	CenterSquareInSquare({ PA_X, PA_Y, PA_DX, PA_DY }, &titleSquare);
	DrawTitle({ titleSquare.x, titleSquare.y }, title);
}

void PrintSubTextPA(const string& str) {
	GotoXY(0, TEXT_SUB_PA);
	cout << CenterAlign(str, PA_DX);
}


//CLEAR SCREEN-----------------------------------------------------------------------------------------------------------------------------

void ClearSquare(const Square& square) {
	for (int i = square.y; i <= square.dy + square.y; i++) {
		GotoXY(square.x, i);
		for (int j = 1; j <= square.dx + 1; j++) {
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

void DrawInfoUI(GameLVL& gameLVL, Snake& snake, const int* curLVL) {
	//� � � � � � �
	GotoXY(0, 0);
	cout << "                                                                                               �����������������������Ŀ";
	cout << "                                                                                               �       OBJECTIVE       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �����������������������Ĵ";
	cout << "                                                                                               �    CURRENT LVL: 00    �";
	cout << "                                                                                               �����������������������Ĵ";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �   SPEED: 00 cell/s    �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �   FOOD: 000 / 000     �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �   LIFE: 00            �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �����������������������Ĵ";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �         POINT         �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �      000.000.000      �";
	cout << "                                                                                               �                       �";
	cout << "                                                                                               �����������������������Ĵ";
	cout << "                                                                                               �  A,S,W,D: MOVE SNAKE  �";
	cout << "���������������������������������������������������������������������������������������������Ŀ�                       �";
	cout << "� LIFE TIME:                                                                                  ��    ESC: PAUSE GAME    �";
	cout << "������������������������������������������������������������������������������������������������������������������������";
	//Update UI infomation
	UpdateUIInfo(curLVL, 2, UI_LVL_X, UI_LVL_Y);
	UpdateUIInfo(&snake.speed, 2, UI_SPEED_X, UI_SPEED_Y);
}

void UpdateFoodUI(const int& food) {
	if (food < 10) GotoXY(2 + UI_FOOD_X, UI_FOOD_Y);
	else if (food < 100) GotoXY(1 + UI_FOOD_X, UI_FOOD_Y);
	else GotoXY(UI_FOOD_X, UI_FOOD_Y);
	cout << food;
}

void UpdateUIInfo(const int* info, const int& maxLengthInfo, const short& x, const short& y) {
	int maxLength = *info;
	int pos = 0;
	while (maxLength >= 10) {
		maxLength /= 10;
		pos++;
	}
	GotoXY(x + maxLengthInfo - pos - 1, y);
	cout << *info;
}