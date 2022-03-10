#include "graphic.h"
#include "game_mechanic.h"
#include "struct.h"
#include <conio.h>

using namespace std;

int main() {

	//VARIABLES--------------------------------------------------------------------------------------------------------------------------------
	int choose = 0; //Main menu choose. 0 = CONTINUE, 1 = NEW GAME, 2 = SETTINGS, 3 = QUIT.
	GameLVL gameLVL;
	Snake snake; 
	int curLVL = 1; //Current level
	int consoleSizeScale = 100;

	//Functions
	FixConsole();
	ScaleMenu(consoleSizeScale);
	
	while (choose != 3) {
		MainMenu(&choose);
		if (choose == 1) {
			curLVL = 1;
		}
		bool isLose = 0;
		switch (choose)
		{
		case 0:
		case 1:
			while (!isLose) {
				if (!LoadLVL(&curLVL, &gameLVL, &snake)) {
					break;
				};
				Play(&gameLVL, &snake, &curLVL);
				ClearSquare({ PA_X, PA_Y, PA_DX, PA_DY });
				
				if (snake.food == gameLVL.maxFood) {
					Win(&curLVL);
					continue;
				}
				else {
					Lose(&gameLVL, &snake, &curLVL);
					isLose = 1;
					break;
				}
			}
			break;
		case 2:
			break;
		default:
			break;
		}
		
	}
	cout << char(176);
	system("pause");
	return 0;
	
}