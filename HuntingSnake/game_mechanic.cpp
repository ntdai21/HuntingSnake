#include "graphic.h"
#include "game_mechanic.h"
#include "sound.h"

using namespace std;

void MoveSnake(GameLVL* gameLVL, Snake* snake) {
	COORD head;
	int size;
	while (snake->state) {
		head = snake->body[0];
		if (snake->direction == 'a' && snake->curDirection != 'd') snake->direction = snake->curDirection;
		else if (snake->direction == 'd' && snake->curDirection != 'a') snake->direction = snake->curDirection;
		else if (snake->direction == 'w' && snake->curDirection != 's') snake->direction = snake->curDirection;
		else if (snake->direction == 's' && snake->curDirection != 'w') snake->direction = snake->curDirection;
		switch (snake->direction)
		{
		case 'a':
			if (snake)
				head.X--;
			if (head.X == (int)PA_X - 1) head.X = PA_DX;
			break;
		case 'd':
			head.X++;
			if (head.X == (int)PA_DX + 1) head.X = PA_X;
			break;
		case 'w':
			head.Y--;
			if (head.Y == (int)PA_Y - 1) head.Y = PA_DY;
			break;
		case 's':
			head.Y++;
			if (head.Y == (int)PA_DY + 1) head.Y = PA_Y;
			break;
		default:
			break;
		}
		size = snake->body.size();
		GotoXY(snake->body[size - 1].X, snake->body[size - 1].Y);
		cout << ' ';
		for (int i = size - 1; i > 0; i--) {
			SwapCOORD(snake->body[i - 1], snake->body[i]);
		}
		snake->body[0] = head;
		DrawSnake(snake);
		CheckHitting(gameLVL, snake);
		if (gameLVL->timeLimit) CheckTimer(gameLVL, snake);
		Sleep(1000 / snake->speed);
	}
}



void GrowUp(Snake* snake) {
	int size = snake->body.size();
	snake->body.push_back(snake->body[size - 1]);
	snake->bodyPattern.push_back(snake->pattern[snake->nextPattern]);
	snake->nextPattern++;
	if (snake->nextPattern == snake->pattern.size()) snake->nextPattern = 0;
}

void CheckHitting(GameLVL* gameLVL, Snake* snake) {
	COORD* food = &gameLVL->food;
	//Check if snake hits food
	if (!gameLVL->gateOpen && food->X == snake->body[0].X && food->Y == snake->body[0].Y) EatFood(gameLVL, snake);
	//If gate is open
	else if (gameLVL->gateOpen) {
		if (FindInCOORD(snake->body[0], gameLVL->gate) != -1) {
			snake->state = 0;
			gameLVL->isWin = true;
			return;
		}
	}
	//Check if snake hits wall or its body
	if ((FindInCOORD(snake->body[0], gameLVL->wall) != -1) || (!gameLVL->canSelfTouching && (FindInCOORD(snake->body[0], snake->body) > 0))) {
		snake->life--;
		snake->state = 0;
	}
}

void CheckTimer(GameLVL* gameLVL, Snake* snake) {
	UpdateLifeTime(gameLVL);
	if (gameLVL->timer > 0) return;
	snake->life--;
	snake->state = 0;
}

void EatFood(GameLVL* gameLVL, Snake* snake) {
	PlayMP3("eat_food");
	snake->food++;
	if (gameLVL->timeLimit) {
		gameLVL->timer += gameLVL->extraTimePerFood;
		if (gameLVL->timer > gameLVL->baseTimer) gameLVL->timer = gameLVL->baseTimer;
	}
	if (snake->food == gameLVL->maxFood) {
		PlayMP3("gate_open");
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
		DrawObjective(gameLVL);
	}
	UpdateUIInfo(&snake->food, 3, UI_FOOD_X, UI_FOOD_Y);
	if (snake->food % gameLVL->foodToSpeedUp == 0) {
		snake->speed++;
		UpdateUIInfo(&snake->speed, 2, UI_SPEED_X, UI_SPEED_Y);
	}
	if (snake->body.size() < gameLVL->maxSizeSnake) GrowUp(snake);
	if (!gameLVL->gateOpen)	gameLVL->food = SpawnFood(&snake->body, &gameLVL->wall);

}

void HitWall(bool& snakeState) {
	snakeState = 0;
}

void Win(int* curLVL) {
	PlayMP3("win");
	DrawTitlePlayArea("YOU WIN");
	GotoXY(PA_X, TEXT_SUB_PA);
	srand(time(0));
	switch (rand() % 10)
	{
	case 0:
		PrintSubTextPA("GGWP! =)");
		break;
	case 1:
		PrintSubTextPA("You are so good at this");
		break;
	case 2:
		PrintSubTextPA("GO, GO, GO...");
		break;
	case 3:
		PrintSubTextPA("A quitter never wins and a winner never quits");
		break;
	case 4:
		PrintSubTextPA("OMG you did it!");
		break;
	case 5:
		PrintSubTextPA("Good job!");
		break;
	case 6:
		PrintSubTextPA("Well done");
		break;
	case 7:
		PrintSubTextPA("Perfect!");
		break;
	case 8:
		PrintSubTextPA("That was so fast!");
		break;
	case 9:
		PrintSubTextPA("Keep going CHAMPION!");
		break;
	default:
		break;
	}
	//Reset data
	++*curLVL;
	_getch();
}

bool Lose(const GameLVL* gameLVL, Snake* snake, int* curLVL) {
	PlayMP3("die");
	if (snake->life > 0) {
		DrawTitlePlayArea("YOU DIE");
	}
	else {
		DrawTitlePlayArea("YOU LOSE");
		*curLVL = 1;
		snake->point = 0;
	}
	GotoXY(0, TEXT_SUB_PA);
	srand(time(0));
	switch (rand() % 10)
	{
	case 0:
		PrintSubTextPA("Don\'t worry! Just try again");
		break;
	case 1:
		PrintSubTextPA("It does not matter how slowly you go as long as you do not stop");
		break;
	case 2:
		PrintSubTextPA("Take a break to get more energy");
		break;
	case 3:
		PrintSubTextPA("Ah! That was so close");
		break;
	case 4:
		PrintSubTextPA("Believe in yourself, you can do that");
		break;
	case 5:
		PrintSubTextPA("Don\'t worry! Just try again.");
		break;
	case 6:
		PrintSubTextPA("Do not fear failure but rather fear not trying");
		break;
	case 7:
		PrintSubTextPA("Just because you fail once doesn\'t mean you\'re gonna fail at everything");
		break;
	case 8:
		PrintSubTextPA("Failure is mother\'s success");
		break;
	case 9:
		PrintSubTextPA("You can\'t win unless you learn how to lose");
		break;
	default:
		break;
	}
	_getch();
	if (snake->life == 0) {
		snake->life = 1;
		remove("data\\save.txt");
		return 1;
	}
	return 0;
}

COORD SpawnFood(const vector<COORD>* body, const vector<COORD>* wall) {
	srand(time(0));
	COORD pos;
	int minX = PA_X;
	int minY = PA_Y;
	int maxX = PA_DX;
	int maxY = PA_DY;
	do {
		//min + rand() % ((max + 1) - min);
		pos.X = minX + rand() % ((maxX + 1) - minX);
		pos.Y = minY + rand() % ((maxY + 1) - minY);
		if (pos.X < minX || pos.X > maxX) continue;
		if (pos.Y < minY || pos.Y > maxY) continue;
		if (FindInCOORD(pos, *body) != -1) continue;
		if (FindInCOORD(pos, *wall) != -1) continue;
		break;
	} while (true);
	DrawFood(&pos);
	return pos;
}

void Play(GameLVL* gameLVL, Snake* snake, const int* curLVL) {
	DrawInfoUI(gameLVL, snake, curLVL);
	DrawWall(*gameLVL);
	if (gameLVL->gateOpen) DrawGate(gameLVL, snake);
	else if (gameLVL->food.X == -1) gameLVL->food = SpawnFood(&snake->body, &gameLVL->wall);
	else DrawFood(&gameLVL->food);
	DrawSnake(snake);
	WaitForReady(gameLVL);
	thread thread_1(MoveSnake, gameLVL, snake);
	thread thread_2(TimeCountDown, &gameLVL->timer, &snake->state);
	thread thread_3(KeyInputThread, curLVL, gameLVL, snake, thread_1.native_handle(), thread_2.native_handle());
	//thread_2.detach();
	thread_3.detach();
	thread_1.join();
	if (thread_2.joinable()) thread_2.detach();
}

bool LoadLVL(int* lvl, GameLVL* gameLVL, Snake* snake, bool* loadData) {
	ResetGameLVLAndSnakeData(gameLVL, snake);
	if (*loadData) *loadData = LoadData(lvl, gameLVL, snake);
	ifstream fIn;
	fIn.open("data\\levels\\level" + to_string(*lvl) + ".txt", ios::in);
	if (!fIn) {
		PlayMP3("max_level");
		*lvl = 1;
		remove("data\\save.txt");
		DrawTitlePlayArea("MAX LEVEL");
		PrintSubTextPA("Congratulation! You have passed all levels");
		_getch();
		return 0;
	}
	string str;
	//Get wall and snake body positions
	getline(fIn, str);
	for (int i = 1; i < 26; i++) {
		getline(fIn, str);
		for (int j = 0; j < 95; j++) {
			char ch = str.at(j);
			if (ch == '0' || ch == '1') gameLVL->wall.push_back({(short)j, (short)i});
			if (ch == '1') gameLVL->gate.push_back({ (short)j, (short)i });
			else if (ch >= 65 && ch <= 90 && !*loadData) {
				if (snake->body.size() < (ch -= 64)) {
					snake->body.resize(ch);
				}
				ch--;
				snake->body[ch] = { (short)j, (short)i };
			}
		}
	}
	getline(fIn, str);
	getline(fIn, str);
	getline(fIn, str);
	getline(fIn, str);
	//Get snake properties
	if (!*loadData) {
		fIn >> str >> snake->speed;
		fIn >> str >> snake->direction;
		snake->curDirection = snake->direction;
	}
	else {
		fIn >> str >> str;
		fIn >> str >> str;
	}
	//Get game level properties
	char temp_char;
	fIn >> temp_char;
	getline(fIn, str);
	fIn >> str >> gameLVL->maxFood;
	fIn >> str >> gameLVL->maxSizeSnake;
	fIn >> str >> gameLVL->foodToSpeedUp;
	fIn >> str >> gameLVL->extraTimePerFood;
	if (!*loadData) {
		fIn >> str >> gameLVL->timer;
		gameLVL->baseTimer = gameLVL->timer;
	}
	else fIn >> str >> gameLVL->baseTimer;
	fIn >> temp_char;
	getline(fIn, str);
	fIn >> str >> gameLVL->timeLimit;
	fIn >> str >> gameLVL->canSelfTouching;
	fIn.close();

	//Get snake body parttern
	snake->bodyPattern.resize(snake->body.size());
	snake->bodyPattern[0] = char(2);
	for (int i = 1; i < snake->bodyPattern.size(); i++) {
		snake->bodyPattern[i] = snake->pattern[snake->nextPattern];
		snake->nextPattern++;
		if (snake->nextPattern == snake->pattern.size()) snake->nextPattern = 0;
	}
	*loadData = 0;
	return 1;
}

void ResetGameLVLAndSnakeData(GameLVL* gameLVL, Snake* snake) {
	//Snake
	snake->food = 0;
	snake->body.resize(0);
	snake->bodyPattern.resize(0);
	snake->nextPattern = 0;
	snake->state = 1;
	//Game LVL
	gameLVL->food = { -1, -1 };
	gameLVL->wall.resize(0);
	gameLVL->gate.resize(0);
	gameLVL->gateOpen = false;
	gameLVL->isWin = false;
}

void TimeCountDown(size_t* timer, const bool* state) {
	while (*timer > 0 && *state) {
		(*timer) -= 1;
		Sleep(1000);
	}
}

void PauseGame(HANDLE thrd1, HANDLE thrd2, const int* curLVL, GameLVL* gameLVL, Snake* snake) {
	SuspendThread(thrd1);
	SuspendThread(thrd2);
	Sleep(100);
	int choose = PauseMenu();
	if (choose == 1) {
		SaveData(curLVL, gameLVL, snake);
		gameLVL->quit = 1;
		snake->state = 0;
	}
	WaitForReady(gameLVL);
	ResumeThread(thrd1);
	ResumeThread(thrd2);
}

void SaveData(const int* curLVL, const GameLVL* gameLVL, const Snake* snake) {
	ofstream fOut;
	fOut.open("data\\save.txt", ios::out);

	fOut << "CURRENT_LVL " << *curLVL << endl;
	//Game LVL
	fOut << "FOOD_COORD " << gameLVL->food.X << ' ' << gameLVL->food.Y << endl;
	fOut << "GATE_OPEN " << gameLVL->gateOpen << endl;
	fOut << "TIMER " << gameLVL->timer << endl;
	//Snake
	fOut << "CURRENT_FOOD " << snake->food << endl;
	fOut << "BODY ";
	for (int i = 0, size = snake->body.size(); i < size; i++) {
		fOut << snake->body[i].X << ' ' << snake->body[i].Y << ' ';
	}
	fOut << -1 << endl;
	fOut << "\nSPEED " << snake->speed << endl;
	fOut << "DIRECTION " << snake->direction << endl;
	fOut << "POINT " << snake->point << endl;
	fOut << "LIFE " << snake->life << endl;

	fOut.close();
}

bool LoadData(int* curLVL, GameLVL* gameLVL, Snake* snake) {
	ResetGameLVLAndSnakeData(gameLVL, snake);
	ifstream fIn;
	fIn.open("data\\save.txt", ios::in);
	if (!fIn.is_open()) return 0;
	
	string str;
	int value1, value2;

	fIn >> str >> *curLVL;
	
	//GameLVL
	fIn >> str >> gameLVL->food.X >> gameLVL->food.Y;
	fIn >> str >> gameLVL->gateOpen;
	fIn >> str >> gameLVL->timer;
	//Snake
	fIn >> str >> snake->food;
	fIn >> str;
	for (int i = 1;; i++) {
		fIn >> value1;
		if (value1 == -1) break;
		fIn >> value2;
		snake->body.resize(i);
		snake->body[i - 1] = { (short)value1, (short)value2 };
	}
	fIn >> str >> snake->speed;
	fIn >> str >> snake->direction;
	snake->curDirection = snake->direction;
	fIn >> str >> snake->point;
	fIn >> str >> snake->life;

	fIn.close();
	return 1;
}