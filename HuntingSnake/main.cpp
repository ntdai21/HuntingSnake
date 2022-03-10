#include "graphic.h"
#include "struct.h"
#include <conio.h>

using namespace std;

int main() {

	//Variables
	int choose = 0; //Main menu choose. 0 = CONTINUE, 1 = NEW GAME, 2 = SETTINGS, 3 = QUIT.
	GameMap gameMap;
	Snake snake; 
	int curLVL; //Current level
	int consoleSizeScale = 100;

	//Functions
	FixConsole();
	ScaleMenu(consoleSizeScale);
	while (choose != 3) {
		MainMenu(choose);
		if (choose == 0) {
			
		}
		switch (choose)
		{
		case 0:
		case 1:
			Play(gameMap, snake);
			break;
		case 2:
			break;
		default:
			break;
		}
	}
	system("pause");
	return 0;
	
}