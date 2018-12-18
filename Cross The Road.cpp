#include "stdafx.h"
#include <iostream>
#include <deque>
#include <vector>
#include <conio.h>

using namespace std;

class cPlayer
{
public:
	int x, y;
	cPlayer (int width) { x = width / 2; y = 0; }
};

class cLane
{
private:
	deque<bool> cars;

public:
	cLane(int width)
	{
		for (int i = 0; i < width; i++)
			cars.push_front(true);
	}

	void Move()
	{
		if (rand() % 10 == 1)
			cars.push_front(true);
		else
			cars.push_front(false);
		cars.pop_back();
	}
	bool CheckPos(int pos) { return cars[pos]; }
};

class cGame
{
private:
	bool quit;
	int NumberOfLanes;
	int width;
	int score;
	cPlayer * player;
	vector<cLane*> map;

public:
	cGame(int w = 20, int h = 20)
	{
		NumberOfLanes = h;
		width = w;
		quit = false;

		for (int i = 0; i < NumberOfLanes; i++)
			map.push_back(new cLane(width));

		player = new cPlayer(width);
	}

	void Draw()
	{
		system ("cls");
		for (int i = 0; i < NumberOfLanes; i++)
		{
			for (int j = 0; j < width; j++)
			{
				if (map[i]->CheckPos(j) && i != 0 && i != NumberOfLanes - 1)
					cout << "#";

				else if (player->x == j && player->y == i)
					cout << "V";

				else
					cout << " ";
			}
			cout << endl;
		}
	}

	void Input()
	{
		if (_kbhit())
		{
			char current = _getch();

			if (current == 'a')
				player->x--;
			if (current == 'd')
				player->x++;
			if (current == 'w')
				player->y--;
			if (current == 's')
				player->y++;
			if (current == 'q')
				quit = true;
		}

	}

	void Logic()
	{
		for (int i = 1 ; i < NumberOfLanes - 1; i++)
		{
			if (rand() % 10 == 1)
				map[i]->Move();
			if (map[i]->CheckPos(player->x) && player->y == i)
				quit = true;
		}
	}

	void Run()
	{
		while (!quit)
		{
			Input();
			Draw();
			Logic();
		}
	}
};

int main()
{
	cGame game(30, 5);
	game.Run();

	getchar();
	return 0;
}