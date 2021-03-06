#include "pch.h"
#include <iostream>
#include<time.h>
#include<windows.h>
#include<conio.h>

using namespace std;

bool gameOver;
const int width = 40;
const int height = 20;
int x, y, fruitX, fruitY, score=0, dirSign=1;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN};
eDirection dir;
char headMark;
int tailX[100], tailY[100];
int tailN=0;

void Setup()
{
	srand(time(0));
	gameOver = false;
	dir = STOP;
	x = width / 2;
	y = height / 2;
	fruitX = 2+(rand() % width-3);
	fruitY = 2+(rand() % height-3);
	score = 0;
	headMark = '<';
}

void Draw()
{
	system("cls");
	/**for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;**/

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			int f = 0;
			if (j == 0 || j==width-2 || i==0 || i==height-1)
				cout << '#';
			for (int ti = 0; ti < tailN; ti++)
				if (j == tailX[ti] && i == tailY[ti])
				{
					f = 1;
					cout << 'X';
				}
			if (i == y && j == x)
				cout << headMark;
			else if (i == fruitY && j == fruitX)
				cout << 'O';
			else if (i != 0 && i != height - 1 && f==0)
				cout << ' ';
		}
		cout << endl;
	}

	/**for (int i = 0; i < width+1; i++)
		cout << "#";
	cout << endl;?**/
}

void Input()
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = LEFT;
			dirSign = -1;
			headMark = '<';
			break;
		case 's':
			dir = DOWN;
			dirSign = 1;
			headMark = 'v';
			break;
		case 'w':
			dir = UP;
			dirSign = -1;
			headMark = '^';
			break;
		case 'd':
			dir = RIGHT;
			dirSign = 1;
			headMark = '>';
			break;
		case '`':
			gameOver = true;
			break;
		}
	}
}

void Logic()
{
	if (x == fruitX && y == fruitY)
	{
		score++;
		tailN++;
		fruitX = (rand() % width - 3) + 2;
		fruitY = (rand() % height - 3) + 2;
	}
	int prevX = tailX[0], prev2X;
	int prevY = tailY[0], prev2Y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < tailN; i++)
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
	case LEFT:
		x--;
		break;
	case RIGHT:
		x++;
		break;
	case UP:
		Sleep(50);
		y--;
		break;
	case DOWN:
		Sleep(50);
		y++;
		break;
	default:
		break;
	}
	if (x > width-2 || x < 1 || y>height-2 || y < 1)
		gameOver = true;
}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep((50-score*10>0? 50 - score * 10:1));
	}
	cout << "SCORE:" << score;
}