#include<iostream>
#include<Windows.h>
#include<conio.h>
#include<vector>
#include<string>
#include<ctime>
#pragma comment(lib, "winmm.lib")



#define specificNumber 224
#define space 32
#define arrowNum 4
#define life 3
#define maxLevel 11

enum Keyboard {
    UP = 72,
    LEFT = 75,
    RIGHT = 77,
    DOWN = 80
};

enum Menu {
    Game_Start = 0,
    How_To_Do,
    Exit
};

void gotoxy(int x, int y) {
    COORD Pos;
    Pos.X = 2 * x;
    Pos.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}

void settingConsole() {
    system("mode con:cols=50 lines=20");
    system("title Typing_Arrow");
}

void DrawReadyGame()
{
	system("cls");
	gotoxy(5, 2);
	std::cout << "*****************************";
	gotoxy(5, 3);
	std::cout << "*     Typing Arrow Game     *";
	gotoxy(5, 4);
	std::cout << "*****************************";
	gotoxy(10, 8);
	std::cout << "GameStart";
	gotoxy(10, 9);
	std::cout << "GameInfo";
	gotoxy(10, 10);
	std::cout << "Quit" << std::endl;
}

void DrawHowToDoGame()
{
	system("cls");
	gotoxy(1, 3);
	std::cout << "*******************************************";
	gotoxy(1, 4);
	std::cout << "|How To Do \"Typing Arrow\" !";
	gotoxy(1, 5);
	std::cout << "|Just press the arrows on the screen as soon as possible!";
	gotoxy(1, 8);
	std::cout << "|Don\'t forget to press SPACEBAR after typing them!";
	gotoxy(1, 9);
	std::cout << "*******************************************";
}

void DrawStartGame(const int currentLife, const int score, const std::string questionStr, const std::string answerStr)
{
	system("cls");
	gotoxy(2, 1);
	std::cout << "*******************************************";
	gotoxy(4, 3);
	std::cout << "Life : " << currentLife << " / " << life;
	gotoxy(4, 4);
	std::cout << "Score : " << score;
	gotoxy(4, 8);
	std::cout << "Q : " << questionStr;
	gotoxy(4, 10);
	std::cout << "A : " << answerStr;
	gotoxy(4, 12);
	std::cout << "press SPACE to submit your answer!";
	gotoxy(2, 18);
	std::cout << "*******************************************" << std::endl;
}

//게임 오버 그리기
void DrawGameOver(const int playTime)
{
	gotoxy(8, 8);
	std::cout << "-------------------";
	gotoxy(8, 9);
	std::cout << "| G A M E O V E R |";
	gotoxy(8, 10);
	std::cout << " " << playTime << " sec";
	gotoxy(8, 11);
	std::cout << "-------------------";
	system("pause>null");
}

void DrawUserCursor(int& y) {
	if (y <= 0) {
		y = 0;
	} else if (y >= 2) {
		y = 2;
	}
	gotoxy(9, 8 + y);
	std::cout << ">";
}

// Setting a intro page
Menu readyGame() {
    int y = 0;
    int input = 0;
    while (true) {
        input = _getch();
        if (input == specificNumber) {
            switch (_getch()) {
                case DOWN:
                    --y;
                    break;
                
                case UP:
                    ++y;
                    break;
            }
        } else if (input == space) {
            switch (y) {
                case 0:
                    return Game_Start;
                case 1:
                    return How_To_Do;
                case 2:
                    return Exit;
            }
        }
    }
}

void howToDo() {
	DrawHowToDoGame();
	system("pause>null");
}

void setQuestion(std::vector<int> questionVec, int level) {
	if (level > maxLevel) {
		level = maxLevel;
	}

	int n = 0;
	srand(time(NULL)); // Set a seed of rand()
	
	for (int i = 0; i < level; i++) { //Number of Stages
		n = rand() % 4; // Kinds of Arrows
		switch (n) {
			case 0:
				questionVec.push_back(UP); //Insert specific arrows
				break;
			
			case 1:
				questionVec.push_back(RIGHT);
				break;
			
			case 2:
				questionVec.push_back(LEFT);
				break;
			
			case 3:
				questionVec.push_back(DOWN);
				break;
		}
	}
}

void vectorToString(const std::vector<int> v, std::string& str) {
	for (int i = 0; i < static_cast<int>(v.size()); i++) {
		switch (v[i]) {
			case UP:
				str += "w ";
				break;

			case LEFT:
				str += "a ";
				break;

			case RIGHT:
				str += "d ";
				break;

			case DOWN:
				str += "s ";
				break;
		}
	}
}

bool checkAnswer(const std::vector<int> questionVec, const std::vector<int> answerVec) {
	if (questionVec.size() != answerVec.size()) {
		return false;
	}

	for (int i = 0; i < static_cast<int>(questionVec.size()); i++) {
		if (questionVec[i] != answerVec[i]) {
			return false;
		}
	}

	return true;
}

void startGame() {

	// Define all variables
	int LIFE = life;
	int score = 0;
	clock_t startTime, endTime; // Play time
	startTime = clock();

	std::vector<int> questionVec; //Questions
	std::string questionStr = "";

	std::vector<int> answerVec; //Answers
	std::string answerStr = "";

	int firstInput = 0;
	int secondInput = 0;

	while (true) {
		int level = (score / 30) + 1;

		setQuestion(questionVec, level);
		vectorToString(questionVec, questionStr);

		while (true) {
			DrawStartGame(LIFE, score, questionStr, answerStr);

			if (LIFE == 0) {
			// Store current time when gameover
			endTime = clock();
			int playTime = static_cast<int>((endTime - startTime) / CLOCKS_PER_SEC);
			DrawGameOver(playTime);
			return;
			}

			firstInput = _getch();
			if (firstInput == specificNumber) {
				secondInput = _getch();
				answerVec.push_back(secondInput); //Put inputs in array
				switch (secondInput) { //Display my answers
					case UP:
						answerStr += "w ";
						break;

					case LEFT:
						answerStr += "a ";
						break;

					case RIGHT:
						answerStr += "s ";
						break;

					case DOWN:
						answerStr += "d ";
						break;
				}
			} else if (firstInput == space) {  // Check my answers
				if (checkAnswer(questionVec, answerVec)) {
					score += 10;
				} else {
					--LIFE;
					score -= 5;
					if (score < 0) {
						score = 0;
					}
				}

				questionVec.clear();
				questionStr = "";
				answerVec.clear();
				answerStr = "";
				break;
			}
		}
	}
}

int main(void) {
	settingConsole();
	while (true) {
		switch (readyGame()) {
		case Game_Start:
			startGame();
			break;
		case How_To_Do:
			howToDo();
			break;
		case Exit:
			return 0;
		}
	}
	return 0;
}
