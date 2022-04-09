#include "graphic.h"
#include "game_mechanic.h"
#include "struct.h"
#include <conio.h>

using namespace std;

int main() {
	SetTextColor(BACKGROUND_COLOR, NORMAL_TEXT_COLOR);
	//VARIABLES--------------------------------------------------------------------------------------------------------------------------------
	int choose = 0; //Main menu choose. 0 = CONTINUE, 1 = NEW GAME, 2 = SETTINGS, 3 = QUIT.
	GameLVL gameLVL;
	Snake snake; 
	int curLVL = 1; //Current level
	bool loadData = 0;
	int consoleSizeScale = 100;

	//Functions
	FixConsole();
	ScaleMenu(consoleSizeScale);
	
	while (choose != 2) {
		MainMenu(&choose);
		if (choose == 0) loadData = 1;
		else if (choose == 1) {
			remove("data\\save.txt");
			curLVL = 1;
			loadData = 0;
		}
		bool isLose = 0;
		switch (choose)
		{
		case 0:
		case 1:
			while (!isLose) {
				if (!LoadLVL(&curLVL, &gameLVL, &snake, &loadData)) {
					break;
				};
				Play(&gameLVL, &snake, &curLVL);
				ClearSquare({ PA_X, PA_Y, PA_DX, PA_DY });
				
				if (gameLVL.quit) {
					gameLVL.quit = 0;
					break;
				}

				if (gameLVL.isWin) {
					PointRewardByTime(&gameLVL, &snake);
					UpdatePoint(snake.point);
					Win(&curLVL);
					continue;
				}
				else {
					isLose = Lose(&gameLVL, &snake, &curLVL);
					if (isLose) break;
				}
			}
			break;
		default:
			break;
		}
		
	}
	mciSendString(TEXT("close mp3"), NULL, 0, NULL);
	cout << char(176);
	system("pause");
	return 0;
	
}