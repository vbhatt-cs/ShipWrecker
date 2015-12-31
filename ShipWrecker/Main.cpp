#include <iostream>
#include <assert.h>
#include <cstdlib>
#include <time.h>
#include <conio.h>
#include "Ship.h"
using namespace std;

void startingScreen();
void characterSelection();
void howToPlay();
void game();
void win(int a, int b);

Ship players[4];
const int MAX_TURNS = 10;

int main()
{
	srand(time(0));
	startingScreen();
}

void startingScreen()
{
	system("cls");
	cout << "\t\t\tShip Wrecker.\n\n";

	cout << "\n1. Start"
		<< "\n2. How to play"
		<< "\n3. Quit";

	cout << "\nEnter your choice:";
	int ch;
	cin >> ch;

	switch (ch)
	{
	case 1:
		characterSelection();
		break;
	case 2:
		howToPlay();
		break;
	case 3:
		exit(0);
	}
}

void characterSelection()
{
	//1,3 are in one team, 2,4 are in other team
	for (int i = 1;i <= 4;i++)
	{
		system("cls");
		//Names
		cout << "Player " << i << " choose your character:";
		cout << "\n1. Tank"
			<< "\n2. Fighter"
			<< "\n3. Shooter"
			<< "\n4. Worker";
		int ch;
		cin >> ch;

		players[i - 1].set(ch - 1, rand() % 641, rand() % 481);
	}

	game();
}

void howToPlay()
{
	system("cls");
	cout << "\t\tHow to play\n";
	cout << "\nGameplay:\n";
	cout << "\nThis is a 2v2 turn based ship battle game. The first team to lose both the ships lose. If no team has lost after 10 turns, the team with highest percentage health at the end wins."
		<< "\nIn each turn, the players choose to either move or shoot. Once all players enter their choice, the move choices are executed followed by shoot choices."
		<< "\nMoving regains some of the health of the ship. More movement leads to more health increase."
		<< "\nShooting checks which enemy is closest and tries to shoot it. Farther a ship is, lesser the chance of hitting and even if it hits, damage is less."
		<< "\nIn case all ships are destroyed in the same turn, it is a tie.";

	//Names
	cout << "\n\nClasses:";
	cout << "\n1. Tank: High health, low damage, accuracy."
		<< "\n2. Fighter: Medium health, high damage, accuracy at low distances but low damage, accuracy at high distances."
		<< "\n3. Shooter: Low health, high damage, accuracy"
		<< "\n4. Worker: Medium health, low damage, accuracy. Gains high amounts of health by moving.\n\n";

	system("pause");
	startingScreen();
}

void game()
{
	for (int turns = 0;turns < MAX_TURNS;turns++)
	{
		system("cls");
		for (int i = 0;i < 4;i++)
		{
			if (players[i].alive)
			{
				cout << "Ship " << i + 1 << ":"
					<< "\nHealth:" << players[i]._health
					<< "\nX-coordinate:" << players[i]._x
					<< "\nY-coordinate:" << players[i]._y;
				cout << "\n\n";
			}
			else
			{
				cout << "Ship " << i + 1 << ":Destroyed";
				cout << "\n\n";
			}
		}

		cout << "Enter your move:";
		cout << "\n1. Shoot"
			<< "\n2. Move";

		int ch[4];
		int x[4], y[4];

		for (int i = 0;i < 4;i++)
			x[i] = y[i] = -1;

		for (int i = 0;i < 4;i++)
		{
			if (players[i].alive)
			{
				cout << "\nPlayer " << i + 1 << ":";
				cin >> ch[i];
				if (ch[i] == 2)
				{
					cout << "Enter the coordinates to move to (between (0,0) and (640,480)):";
					cin >> x[i] >> y[i];
					assert(x[i] <= 640 && x[i] >= 0);
					assert(y[i] <= 480 && y[i] >= 0);
				}
			}
			else
				ch[i] = -1;
		}

		for (int i = 0;i < 4;i++)
			if (ch[i] == 2)
				players[i].move_to(x[i], y[i]);


		for (int i = 0;i < 4;i++)
			if (ch[i] == 1)
				players[i].shoot(players[i % 2 + 1], players[(i % 2 + 3) % 4]);


		if (!players[0].alive && !players[2].alive && (players[1].alive || players[3].alive))
			win(2, 4);
		else if (!players[1].alive && !players[3].alive && (players[0].alive || players[2].alive))
			win(1, 3);
		else if (!players[1].alive && !players[3].alive && !(players[0].alive || players[2].alive))
		{
			system("cls");
			cout << "It is a tie.\n";
			system("pause");
			startingScreen();
		}
	}

	double h[4];
	for (int i = 0;i < 4;i++)
		h[i] = players[i]._health / players[i].MAX_HEALTH;

	if ((h[0] + h[2])>(h[1] + h[3]))
		win(1, 3);
	else if ((h[0] + h[2]) < (h[1] + h[3]))
		win(2, 4);
	else
	{
		system("cls");
		cout << "It is a tie.\n";
		system("pause");
		startingScreen();
	}
}

void win(int a, int b)
{
	system("cls");
	cout << "Players " << a << " and " << b << " have won.\n";
	system("pause");
	startingScreen();
}