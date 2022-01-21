#include "graphic.h"
#include <conio.h>

using namespace std;

int main() {
	FixConsole();

	//Variables
	int choose; //Main menu choose

	MainMenu(choose);
	ClearScreen();

	system("pause");
	return 0;
	
}