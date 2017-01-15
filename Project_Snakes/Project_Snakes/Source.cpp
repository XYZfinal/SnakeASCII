#include <iostream>
#include <conio.h>
#include <string>
#include <Windows.h>
using namespace std;

char head;
char tail = 'o';
bool GameOver, pause;
bool paint = false;
const int width = 20;
const int height = 20;
int x, y, fruitX, fruitY, score;
int tailX[100], tailY[100];
int ntail;
enum Direction { Stop = 0, Left, Right, Up, Down };
Direction dir;


void SetUp() {
	GameOver = false;
	dir = Stop;
	x = width / 2;
	y = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	score = 0;
	ntail = 0;
	head = '@';
	pause = false;
}

void Draw() {
	system("cls");
	for (int i = 0; i < width; i++)
	{
		cout << '#';
	}

	cout << "W(5), A(1), S(2), and D(3) to move, X to end and P to pause";
	cout << endl;
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if ((j == 0) || j == (width - 1))
			{
				cout << '#';
			}
			else if ((j == x) && (i == y))
			{
				cout << head;
			}
			else if ((j == fruitX) && (i == fruitY))
			{
				cout << 'F';
			}
			else
			{
				for (int k = 0; k < ntail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << tail;
						paint = true;
					}
				}
				if (!paint) {
					cout << ' ';
				}
				paint = false;
			}
		}
		cout << endl;
	}
	for (int i = 0; i < width; i++)
	{
		cout << '#';
	}
	cout << endl << "Score: " << score;
	if (pause)
	{
		cout << "        PAUSED";
	}
}

void Input() {
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'w':
			dir = Up;
			break;
		case 'a':
			dir = Left;
			break;
		case 's':
			dir = Down;
			break;
		case 'd':
			dir = Right;
			break;
		case '5':
			dir = Up;
			break;
		case '1':
			dir = Left;
			break;
		case '2':
			dir = Down;
			break;
		case '3':
			dir = Right;
			break;
		case 'p':
			if (!pause)
			{
				pause = true;
			}
			else
			{
				pause = false;
			}
			break;
		case 'x':
			GameOver = true;
			break;
		}
	}
}

void Logic() {

	int prevX = tailX[0];
	int prevY = tailY[0];
	int prev2X, prev2Y;
	tailX[0] = x;
	tailY[0] = y;

	for (int i = 1; i < ntail; i++)
	{
		prev2X = tailX[i];
		prev2Y = tailY[i];
		tailX[i] = prevX;
		tailY[i] = prevY;
		prevX = prev2X;
		prevY = prev2Y;
	}

	switch (dir)
	{
	case Left:
		x--;
		head = '<';
		break;
	case Right:
		x++;
		head = '>';
		break;
	case Up:
		y--;
		head = '^';
		break;
	case Down:
		y++;
		head = 'v';
		break;
	default:
		break;
	}
	if (x == width - 1 || x == -1 || y == height + 1 || y == -2)
	{
		GameOver = true;
	}
	if (x == fruitX && y == fruitY) {
		fruitX = rand() % width;
		fruitY = rand() % height;
		score += 10;
		ntail++;
	}
	for (int k = 0; k < ntail; k++)
	{
		if (tailX[k] == x && tailY[k] == y)
		{
			GameOver = true;
		}
	}
}

int main() {
	char YESorNo;

	do
	{
		SetUp();
		while (!GameOver)
		{
			Sleep(300);
			Draw();
			Input();
			if (!pause) {
				Logic();
			}
		}

		system("cls");
		cout << "GAME OVER" << endl;
		cout << "Score: " << score << endl;
		cout << "Do you want to replay? (Respond with y or n)" << endl;
		cin.get(YESorNo);
		cin.get();
		if (YESorNo == 'y' || YESorNo == 'Y')
		{
			GameOver = false;
		}
		if (YESorNo == 'n' || YESorNo == 'N')
		{
			GameOver = true;
		}
	} while (!GameOver);

	return 0;
}

/* A few problems to the game to be fixed:
1. wall limitations unclear

2. the snake occasionnaly goes into wall even though it is supposed to be on the edge
3. after precisely 33 fruits, there is no more generation of fruit in the board*/