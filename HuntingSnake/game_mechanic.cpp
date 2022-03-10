#include "graphic.h"
#include "game_mechanic.h"

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
		DrawSnake(snake->body, snake->bodyPattern);
		CheckHitting(gameLVL, snake);
		Sleep(1000 / snake->speed);
	}
}

void DrawSnake(const vector<COORD>& body, const vector<char>& parttern) {
	for (int i = 0; i < body.size(); i++) {
		GotoXY(body[i].X, body[i].Y);
		cout << parttern[i];
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
	if (food->X == snake->body[0].X && food->Y == snake->body[0].Y) EatFood(gameLVL, snake);
	//Check if snake hits wall or its body
	else if ((FindInCOORD(snake->body[0], gameLVL->wall) != -1) || (!gameLVL->canSelfTouching && (FindInCOORD(snake->body[0], snake->body) > 0))) {
		snake->life--;
		snake->state = 0;
	};
}

void EatFood(GameLVL* gameLVL, Snake* snake) {
	gameLVL->food = SpawnFood(&snake->body, &gameLVL->wall);
	snake->food++;
	if (snake->food == gameLVL->maxFood) snake->state = 0;
	UpdateUIInfo(&snake->food, 3, UI_FOOD_X, UI_FOOD_Y);
	if (snake->food % gameLVL->foodToSpeedUp == 0) {
		snake->speed++;
		UpdateUIInfo(&snake->speed, 2, UI_SPEED_X, UI_SPEED_Y);
	}
	GrowUp(snake);
}

void HitWall(bool& snakeState) {
	snakeState = 0;
}

void Win(int* curLVL) {
	DrawTitlePlayArea("YOU WIN");
	GotoXY(0, TEXT_SUB_PA);
	srand(time(0));
	switch (rand() % 10)
	{
	case 0:
		cout << CenterAlign("GGWP! =)", PA_DX);
		break;
	case 1:
		cout << CenterAlign("Sometimes by losing a battle you find a new way to win the war", PA_DX);
		break;
	case 2:
		cout << CenterAlign("Take a break to get more energy", PA_DX);
		break;
	case 3:
		cout << CenterAlign("Ah! That was so close", PA_DX);
		break;
	case 4:
		cout << CenterAlign("Believe in yourself", PA_DX);
		break;
	case 5:
		cout << CenterAlign("Don\'t worry! Just try again.", PA_DX);
		break;
	case 6:
		cout << CenterAlign("Do not fear failure but rather fear not trying", PA_DX);
		break;
	case 7:
		cout << CenterAlign("Just because you fail once doesn\'t mean you\'re gonna fail at everything", PA_DX);
		break;
	case 8:
		cout << CenterAlign("Failure is mother\'s success", PA_DX);
		break;
	case 9:
		cout << CenterAlign("Winning provides happiness, losing provides wisdom", PA_DX);
		break;
	default:
		break;
	}
	//Reset data
	++*curLVL;
	_getch();
}

void Lose(const GameLVL* gameLVL, Snake* snake, int* curLVL) {
	DrawTitlePlayArea("YOU LOSE");
	GotoXY(0, TEXT_SUB_PA);
	srand(time(0));
	switch (rand() % 10)
	{
	case 0:
		cout << CenterAlign("Don\'t worry! Just try again", PA_DX);
		break;
	case 1:
		cout << CenterAlign("Sometimes by losing a battle you find a new way to win the war", PA_DX);
		break;
	case 2:
		cout << CenterAlign("Take a break to get more energy", PA_DX);
		break;
	case 3:
		cout << CenterAlign("Ah! That was so close", PA_DX);
		break;
	case 4:
		cout << CenterAlign("Believe in yourself", PA_DX);
		break;
	case 5:
		cout << CenterAlign("Don\'t worry! Just try again.", PA_DX);
		break;
	case 6:
		cout << CenterAlign("Do not fear failure but rather fear not trying", PA_DX);
		break;
	case 7:
		cout << CenterAlign("Just because you fail once doesn\'t mean you\'re gonna fail at everything", PA_DX);
		break;
	case 8:
		cout << CenterAlign("Failure is mother\'s success", PA_DX);
		break;
	case 9:
		cout << CenterAlign("Winning provides happiness, losing provides wisdom", PA_DX);
		break;
	default:
		break;
	}
	//Reset data
	*curLVL = 1;
	snake->point = 0;
	_getch();
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
	GotoXY(pos.X, pos.Y);
	cout << '';
	return pos;
}

void Play(GameLVL* gameLVL, Snake* snake, const int* curLVL) {
	DrawInfoUI(*gameLVL, *snake, curLVL);
	DrawWall(*gameLVL);
	gameLVL->food = SpawnFood(&snake->body, &gameLVL->wall);
	thread thread_1(MoveSnake, gameLVL, snake);
	thread thread_2(KeyInputThread, &snake->curDirection, &snake->state);
	thread_2.detach();
	//thread thread_3(CheckHitting, &gameLVL, &snake);
	//thread_3.detach();
	thread_1.join();
}

bool LoadLVL(const int* lvl, GameLVL* gameLVL, Snake* snake) {
	ResetGameLVLAndSnakeData(gameLVL, snake);
	ifstream fIn;
	fIn.open("data\\levels\\level" + to_string(*lvl) + ".txt", ios::in);
	if (!fIn) {
		DrawTitlePlayArea("MAX LEVEL");
		PrintSubTextPA("Congratulation! You have passed all levels");
		_getch();
		return 0;
	}
	string str;
	//Get wall and snake body positions
	for (int i = 0; i < 27; i++) {
		getline(fIn, str);
		for (int j = 0; j < 95; j++) {
			char ch = str.at(j);
			if (ch == '0') gameLVL->wall.push_back({ (short)j, (short)i });
			else if (ch >= 65 && ch <= 90) {
				if (snake->body.size() < (ch -= 64)) {
					snake->body.resize(ch);
					snake->bodyPattern.resize(ch);
				}
				ch--;
				snake->body[ch] = { (short)j, (short)i };
			}
		}
	}
	getline(fIn, str);
	getline(fIn, str);
	getline(fIn, str);
	//Get snake properties
	fIn >> str >> snake->speed;
	fIn >> str >> snake->direction;
	snake->curDirection = snake->direction;
	//Get game level properties
	char temp_char;
	fIn >> temp_char;
	getline(fIn, str);
	fIn >> str >> gameLVL->maxFood;
	fIn >> str >> gameLVL->foodToSpeedUp;
	fIn >> str >> gameLVL->extraTimePerFood;
	fIn >> temp_char;
	getline(fIn, str);
	fIn >> str >> gameLVL->timeLimit;
	fIn >> str >> gameLVL->canSelfTouching;
	fIn.close();

	//Get snake body parttern
	snake->bodyPattern[0] = char(2);
	for (int i = 1; i < snake->bodyPattern.size(); i++) {
		snake->bodyPattern[i] = snake->pattern[snake->nextPattern];
		snake->nextPattern++;
		if (snake->nextPattern == snake->pattern.size()) snake->nextPattern = 0;
	}
	snake->food = 0;
	snake->state = 1;
	snake->life = 1;
	return 1;
}

void ResetGameLVLAndSnakeData(GameLVL* gameLVL, Snake* snake) {
	//Snake
	snake->food = 0;
	snake->body.resize(0);
	snake->bodyPattern.resize(0);
	snake->nextPattern = 0;
}