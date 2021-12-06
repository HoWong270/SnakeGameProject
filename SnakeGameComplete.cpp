#include <iostream>
#include <conio.h>
#include <Windows.h>
#include <ctime>
using namespace std;
bool gameOver;
const int width = 25; //map
const int height = 25; //map
int x, y, fruitx, fruity, score, speed = 1;
int tailX[100], tailY[100]; //tail
int nTail;
enum eDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
eDirection dir;
void Setup()
{
	gameOver = false;
	dir = STOP;
	x = width / 2; //middle snake spawn
	y = height / 2;
	srand(time(0));
	fruitx = rand() % width; //random fruit spawn
	fruity = rand() % height;
	score = 0;
}
void Draw() //arena
{
	system("cls");
	for (int i = 0; i < width + 2; i++) //top border
		cout << "=";
	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
				cout << "||";
			if (i == y && j == x) //head 
				cout << "O";
			else if (i == fruity && j == fruitx)
				cout << "F";
			else
			{
				bool print = false;
				for (int k = 0; k < nTail; k++)
				{
					if (tailX[k] == j && tailY[k] == i)
					{
						cout << "o";
						speed + 0.01; //speed increase
						print = true;
					}
				}
				if (!print)
					cout << " ";
			}
			if (j == width - 1)
				cout << "||";
		}
		cout << endl;
	}
	for (int i = 0; i < width + 2; i++) //bottom row
		cout << "=";
	cout << endl;
	cout << "Score:" << score << endl;
	cout << "Your keys will be inverted||";
	cout << "Everytime you eat a fruit you speed is increased by a bit";
	system("Color 74");

}
void Input() //controls
{
	if (_kbhit())
	{
		switch (_getch())
		{
		case 'a':
			dir = RIGHT;
			break;
		case 'd':
			dir = LEFT;
			break;
		case 'w':
			dir = DOWN;
			break;
		case 's':
			dir = UP;
			break;
		case 'x':
			gameOver = true;
			break;
		}
	}
}
void Logic()
{
	int preX = tailX[0];
	int preY = tailY[0];
	int pre2x, pre2y;
	tailX[0] = x;
	tailY[0] = y;
	for (int i = 1; i < nTail; i++)
	{
		pre2x = tailX[i];
		pre2y = tailY[i];
		tailX[i] = preX;
		tailY[i] = preY;
		preX = pre2x;
		preY = pre2y;
	}
	switch (dir)
	{
	case RIGHT:
		x+= speed;
		break;
	case LEFT:
		x-= speed;
		break;
	case DOWN:
		y+= speed;
		break;
	case UP:
		y-= speed;
		break;
	default:
		break;
	}
	if (x > width || x < 0 || y > height || y < 0)
		gameOver = true;

	for (int i = 0; i < nTail;i++)
		if (tailX[i] == x && tailY[i] == y)
			gameOver = true;

	if (x == fruitx && y == fruity)
	{
		score += 20;
		fruitx = rand() % width; //random fruit spawn
		fruity = rand() % height;
		nTail++;
	}

}

int main()
{
	Setup();
	while (!gameOver)
	{
		Draw();
		Input();
		Logic();
		Sleep(50);
	}

	return 0;
}

