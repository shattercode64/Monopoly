#ifndef GAMEFUNCTIONS_H
#define GAMEFUNCTIONS_H

#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <stdlib.h>

#include "Bank.h"
#include "Player.h"
#include "Stocks.h"

#define STARTING_CASH 12000
#define ALLOWANCE_CASH 2000
#define UPGRADE_TOLL 150

#define MAX_ROUND_COUNT 20

#define PLAYER_ONE_COLOUR 64
#define PLAYER_TWO_COLOUR 16
#define PLAYER_THREE_COLOUR 32
#define PLAYER_FOUR_COLOUR 224

#define ANNOUNCEMENT_LOC_X 3
#define ANNOUNCEMENT_LOC_Y 36
#define ANNOUNCEMENT_TEXT_COLOUR 15

#define MENU_LOC_X 3
#define MENU_LOC_Y 38
#define MENU_WIDTH 10
#define MENU_HEIGHT 10

#define FIRSTBLOCK_MID_X 51
#define FIRSTBLOCK_MID_Y 6
#define BLOCK_WIDTH 14
#define BLOCK_HEIGHT 5

#define _RESET_FILE_1 "memory/_MAIN_FILE_RESET_1.txt"
#define _RESET_FILE_2 "memory/_MAIN_FILE_RESET_2.txt"
#define _RESET_FILE_3 "memory/_MAIN_FILE_RESET_3.txt"
#define _RESET_FILE_4 "memory/_MAIN_FILE_RESET_4.txt"
#define _MEM_FILE "memory/mem.txt"

#define _SOUND_PLAYERMOVE "sound/mario_hop_short.wav"
#define _SOUND_PAYCOINS "sound/coin_dropping.wav"
#define _SOUND_DICEROLL "sound/dice_roll.wav"

int x, y, i, j;
COORD position;

Bank gameBank;
Stocks gameStocks;
property_t blocks[28];
Player gamePlayers[4];

int player_n = 4, turnsLeft = MAX_ROUND_COUNT, currentPlayer = 0;
int win = 0;
bool playing[4] = { true, true, true, true };
bool current[4] = { true, true, true, true };
bool placedRoadBlock[4] = { false, false, false, false };
bool usedRobotDice[4] = { false, false, false, false };
std::string mapName;

// Prototype(s).
int getMenu();
int getPlayerNumber();

// Announcement functions (Bottom left box).
void clearAnnouncement_LO()
{
	COORD loc = { ANNOUNCEMENT_LOC_X, ANNOUNCEMENT_LOC_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	std::cout << "                                    ";
}

void clearAnnouncement_LT()
{
	COORD loc = { ANNOUNCEMENT_LOC_X, ANNOUNCEMENT_LOC_Y + 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	std::cout << "                                    ";
}

void announce_LO(std::string announcement)
{
	COORD loc = { ANNOUNCEMENT_LOC_X, ANNOUNCEMENT_LOC_Y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	std::cout << announcement;
}

void announce_LT(std::string announcement)
{
	COORD loc = { ANNOUNCEMENT_LOC_X, ANNOUNCEMENT_LOC_Y + 1};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	std::cout << announcement;
}

void clearMenu()
{
	COORD xy_loc = { MENU_LOC_X, MENU_LOC_Y };
	for (int y = MENU_LOC_Y; y <= MENU_LOC_Y + MENU_HEIGHT; y++)
	{
		xy_loc.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cout << "                                    ";
	}
}

void clearAllAnnounced()
{
	clearAnnouncement_LO();
	clearAnnouncement_LT();
	clearMenu();
}
//Announcement functions end here.


// Dice drawing functions.
void drawOne()
{
	using namespace std;
	for (i = 100; i <= 101; i++)
	{
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 116);
		position.X = i;
		position.Y = 31;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(219);
	}
}

void drawTwo()
{
	using namespace std;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 116);
	for (i = 95; i <= 96; i++)
	{
		position.X = i;
		position.Y = 29;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(219);
	}
	for (i = 105; i <= 106; i++)
	{
		position.X = i;
		position.Y = 33;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(219);
	}
}

void drawFour()
{
	using namespace std;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 116);
	drawTwo();
	for (i = 105; i <= 106; i++)
	{
		position.X = i;
		position.Y = 29;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(219);
	}
	for (i = 95; i <= 96; i++)
	{
		position.X = i;
		position.Y = 33;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(219);
	}
}

void drawSix()
{
	using namespace std;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 116);
	for (i = 95; i <= 96; i++)
	{
		for (j = 28; j <= 34; j += 3)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << char(219);
		}
	}
	for (i = 105; i <= 106; i++)
	{
		for (j = 28; j <= 34; j += 3)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << char(219);
		}
	}
}

void diceOutput(int dice)
{
	using namespace std;
	//output dice area
	for (i = 90; i <= 111; i++)
	{
		for (j = 27; j <= 35; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
			cout << " ";
		}
	}
	//output dice
	switch (dice)
	{
	case 1:
		drawOne();
		break;
	case 2:
		drawTwo();
		break;
	case 3:
		drawOne();
		drawTwo();
		break;
	case 4:
		drawFour();
		break;
	case 5:
		drawFour();
		drawOne();
		break;
	case 6:
		drawSix();
		break;
	}
}
// Dice drawing functions end here.

// User Interface (UI) drawing functions.
void gotoxy(short col, short row)
{
	COORD position = { col,row };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
}

void drawBroke(int i)
{
	using namespace std;
	position.X = 55;
	position.Y = i;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	if (i == 3)
		cout << "$$$$$$$\\                      $$\\                           ";
	if (i == 4)
		cout << "$$  __$$\\                     $$ |                  ";
	if (i == 5)
		cout << "$$ |  $$ | $$$$$$\\   $$$$$$\\  $$ |  $$\\  $$$$$$\\        ";
	if (i == 6)
		cout << "$$$$$$$\\ |$$  __$$\\ $$  __$$\\ $$ | $$  |$$  __$$\\      ";
	if (i == 7)
		cout << "$$  __$$\\ $$ |  \\__|$$ /  $$ |$$$$$$  / $$$$$$$$ |    ";
	if (i == 8)
		cout << "$$ |  $$ |$$ |      $$ |  $$ |$$  _$$<  $$   ____|        ";
	if (i == 9)
		cout << "$$$$$$$  |$$ |      \\$$$$$$  |$$ | \\$$\\ \\$$$$$$$\\               ";
	if (i == 10)
		cout << "\\_______/ \\__|       \\______/ \\__|  \\__| \\_______|       ";
}

void drawMonopoly(int i)
{
	using namespace std;
	position.X = 40;
	position.Y = i;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	if (i == 13)
		cout << "|$$\\      $$\\  $$$$$$\\  $$\\   $$\\  $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$\\   $$\\     $$\\ ";
	if (i == 14)
		cout << "|$$$\\    $$$ |$$  __$$\\ $$$\\  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |  \\$$\\   $$  |";
	if (i == 15)
		cout << "|$$$$\\  $$$$ |$$ /  $$ |$$$$\\ $$ |$$ /  $$ |$$ |  $$ |$$ /  $$ |$$ |   \\$$\\ $$  /";
	if (i == 16)
		cout << "|$$\\$$\\$$ $$ |$$ |  $$ |$$ $$\\$$ |$$ |  $$ |$$$$$$$  |$$ |  $$ |$$ |    \\$$$$  /";
	if (i == 17)
		cout << "|$$ \\$$$  $$ |$$ |  $$ |$$ \\$$$$ |$$ |  $$ |$$  ____/ $$ |  $$ |$$ |     \\$$  /";
	if (i == 18)
		cout << "|$$ |\\$  /$$ |$$ |  $$ |$$ |\\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |      $$ | ";
	if (i == 19)
		cout << "|$$ | \\_/ $$ | $$$$$$  |$$ | \\$$ | $$$$$$  |$$ |       $$$$$$  |$$$$$$$$\\ $$ |";
	if (i == 20)
		cout << " \\__|     \\__| \\______/ \\__|  \\__| \\______/ \\__|       \\______/ \\________|\\__|  ";
}

void startPage()
{
	using namespace std;
	//border
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
	for (i = 0; i <= 49; i++)
	{
		for (j = 0; j <= 160; j++)
		{
			if (i == 0 || i == 49)
			{
				position.X = j;
				position.Y = i;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
				cout << char(177);
			}
		}
		position.X = 0;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(177);
		position.X = 160;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(177);
	}

	//draw name of game
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	i = 3;
	j = 20;
	while (i <= 10 && j >= 13)
	{
		drawBroke(i);
		drawMonopoly(j);
		i++;
		j--;
		Sleep(100);
	}

	//Start
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	position.X = 70;
	position.Y = 22;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "Press Anything To Start...";

	for (i = 27; i <= 40; i++)
	{
		position.X = 68;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (i == 27)
			cout << "@        @@@@@@@@@@&        @";
		if (i == 28)
			cout << "@@(  #@@@@@@@@@@@@@@@@@*  (@@";
		if (i == 29)
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		if (i == 30)
			cout << " @@@@@@@@@@@@@@@@@@@@@@@@@@@ ";
		if (i == 31)
			cout << " @@@@@@@,   @@@@@   ,@@@@@@@  ";
		if (i == 32)
			cout << "@@@@@@@   *@@@@@@@/   @@@@@@@";
		if (i == 33)
			cout << "@@@@@@@.  &@@@@@@@%  *@@@@@@@";
		if (i == 34 || i == 35)
			cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@";
		if (i == 36)
			cout << "@@@@                     @@@@";
		if (i == 37)
			cout << " @@@@                   @@@@ ";
		if (i == 38)
			cout << "  @@@@#               #@@@@  ";
		if (i == 39)
			cout << "   @@@@@@.         *@@@@@%   ";
		if (i == 40)
			cout << "     #@@@@@@@@@@@@@@@@@*  ";
	}
}

void setup()
{
	using namespace std;
	system("MODE CON COLS=162 LINES=51");

	//top line cover
	x = 0;
	while (x <= 160)
	{
		position.X = x;
		position.Y = 0;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (x == 40)
			cout << char(203);
		else if (x < 160)
			cout << char(205);
		else
			cout << char(187);
		x++;
	}

	//three boxes= player money status, player status, player options bar
	x = 0;
	while (x < 40)
	{
		position.X = x;
		position.Y = 18;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(205);
		x++;
	}

	x = 0;
	while (x < 40)
	{
		position.X = x;
		position.Y = 33;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(205);
		x++;
	}

	x = 0;
	while (x < 160)
	{
		position.X = x;
		position.Y = 49;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << char(205);
		x++;
	}

	y = 1;
	while (y <= 49)
	{
		position.X = 40;
		position.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (y < 49)
			cout << char(186);
		else
			cout << char(202);
		y++;
	}

	y = 1;
	while (y <= 49)
	{
		position.X = 160;
		position.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (y < 49)
			cout << char(186);
		else
			cout << char(188);
		y++;
	}

	//small squares for player's money
	x = 0;
	while (x < 40)
	{
		position.X = x;
		position.Y = 9;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (x != 20)
			cout << char(205);
		else
			cout << char(206);
		x++;
	}

	y = 0;
	while (y <= 18)
	{
		position.X = 20;
		position.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (y < 1)
			cout << (char)203;
		else if (y < 18)
			cout << char(186);
		else
			cout << char(202);
		y++;
	}

	x = 0;
	while (x < 40)
	{
		position.X = x;
		position.Y = 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (x != 20)
			cout << char(240);
		x++;

	}

	x = 0;
	while (x < 40)
	{
		position.X = x;
		position.Y = 11;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (x != 20)
			cout << char(240);
		x++;
	}

	//output players 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 64);
	position.X = 6;
	position.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "Player  1";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 16);
	position.X = 26;
	position.Y = 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "Player  2";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 32);
	position.X = 6;
	position.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "Player  3";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 224);
	position.X = 26;
	position.Y = 10;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "Player  4";

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	//output monopoly board
	//outer border
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 132);
	for (i = 41; i <= 44; i++)
	{
		for (j = 1; j <= 48; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)178;
		}
	}
	for (i = 156; i < 160; i++)
	{
		for (j = 1; j <= 48; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)178;
		}
	}
	for (i = 1; i < 4; i++)
	{
		for (j = 45; j <= 155; j++)
		{
			position.X = j;
			position.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)178;
		}
	}
	for (i = 45; i <= 48; i++)
	{
		for (j = 45; j <= 155; j++)
		{
			position.X = j;
			position.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)178;
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	for (i = 45; i <= 155; i++)
	{
		position.X = i;
		position.Y = 44;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << (char)240;
		position.X = i;
		position.Y = 4;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << (char)240;
	}
	//inner board
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
	for (i = 5; i < 44; i++)
	{
		position.X = 58;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << (char)179;
	}
	for (i = 5; i < 44; i++)
	{
		position.X = 142;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << (char)179;
	}
	for (i = 45; i <= 155; i++)
	{
		position.X = i;
		position.Y = 9;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << (char)196;
		if (i == 47 || i == 50 || i == 52 || i == 55)
		{
			position.Y = 8;
			position.X = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)186;
		}
	}
	for (i = 45; i <= 155; i++)
	{
		position.X = i;
		position.Y = 39;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << (char)196;
		if (i == 47 || i == 50 || i == 52 || i == 55)
		{
			position.Y = 43;
			position.X = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)186;
		}
	}
	for (i = 14; i <= 39; i += 5)
	{
		for (j = 45; j < 59; j++)
		{
			position.X = j;
			position.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			if (j == 58)
				cout << (char)180;
			else
				cout << (char)196;
			if (j == 47 || j == 50 || j == 52 || j == 55)
			{
				position.Y = i - 1;
				position.X = j;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
				cout << (char)186;
			}
		}
	}
	for (i = 14; i <= 39; i += 5)
	{
		for (j = 142; j <= 155; j++)
		{
			position.X = j;
			position.Y = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			if (j == 142)
				cout << (char)195;
			else
				cout << (char)196;
			if (j == 145 || j == 148 || j == 150 || j == 153)
			{
				position.Y = i - 1;
				position.X = j;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
				cout << (char)186;
				position.Y = 8;
				position.X = j;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
				cout << (char)186;
				position.Y = 43;
				position.X = j;
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
				cout << (char)186;
			}
		}
	}
	for (i = 72; i <= 128; i += 14)
	{
		for (j = 5; j < 10; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			if (j == 9)
				cout << (char)193;
			else
				cout << (char)179;
		}
	}
	for (i = 72; i <= 128; i += 14)
	{
		for (j = 39; j < 44; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			if (j == 39)
				cout << (char)194;
			else
				cout << (char)179;
		}
	}
	position.X = 58;
	position.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << (char)197;

	position.X = 142;
	position.Y = 9;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << (char)197;

	position.X = 58;
	position.Y = 39;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << (char)197;

	position.X = 142;
	position.Y = 39;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << (char)197;

	for (j = 8; j <= 43; j += 35)
	{
		for (i = 58; i <= 142; i++)
		{
			position.Y = j;
			i += 3;
			position.X = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)186;
			i += 3;
			position.X = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)186;
			i += 2;
			position.X = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)186;
			i += 3;
			position.X = i;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			cout << (char)186;
			i += 2;
		}
	}

	//output "MONOPOLY"
	for (i = 12; i <= 19; i++)
	{
		if (i == 12)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4);
		if (i == 13)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
		if (i == 14)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14);
		if (i == 15)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
		if (i == 16)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9);
		if (i == 17)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5);
		if (i == 18)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13);
		if (i == 19)
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3);
		position.X = 60;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (i == 12)
			cout << "|$$\\      $$\\  $$$$$$\\  $$\\   $$\\  $$$$$$\\  $$$$$$$\\   $$$$$$\\  $$\\   $$\\     $$\\ ";
		if (i == 13)
			cout << "|$$$\\    $$$ |$$  __$$\\ $$$\\  $$ |$$  __$$\\ $$  __$$\\ $$  __$$\\ $$ |  \\$$\\   $$  |";
		if (i == 14)
			cout << "|$$$$\\  $$$$ |$$ /  $$ |$$$$\\ $$ |$$ /  $$ |$$ |  $$ |$$ /  $$ |$$ |   \\$$\\ $$  /";
		if (i == 15)
			cout << "|$$\\$$\\$$ $$ |$$ |  $$ |$$ $$\\$$ |$$ |  $$ |$$$$$$$  |$$ |  $$ |$$ |    \\$$$$  /";
		if (i == 16)
			cout << "|$$ \\$$$  $$ |$$ |  $$ |$$ \\$$$$ |$$ |  $$ |$$  ____/ $$ |  $$ |$$ |     \\$$  /";
		if (i == 17)
			cout << "|$$ |\\$  /$$ |$$ |  $$ |$$ |\\$$$ |$$ |  $$ |$$ |      $$ |  $$ |$$ |      $$ | ";
		if (i == 18)
			cout << "|$$ | \\_/ $$ | $$$$$$  |$$ | \\$$ | $$$$$$  |$$ |       $$$$$$  |$$$$$$$$\\ $$ |";
		if (i == 19)
			cout << " \\__|     \\__| \\______/ \\__|  \\__| \\______/ \\__|       \\______/ \\________|\\__|  ";
		Sleep(50);
	}
	/*
	//output dice area
	for (i = 90; i <= 110; i++)
	{
		for (j = 25; j <= 34; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
			cout << " ";
		}
	}*/

	//output place names
	for (i = 48; i <= 156; i += 14)
	{
		position.X = i;
		position.Y = 5;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		if (i == 48)
			cout << "START->";
	}
	//temporary
	// cin >> x >> y;
	// gotoxy(x, y);

	// Dice
	for (i = 90; i <= 111; i++)
	{
		for (j = 27; j <= 35; j++)
		{
			position.X = i;
			position.Y = j;
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
			SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 112);
			cout << " ";
		}
	}
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8);
	position.X = 112;
	position.Y = 27;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "\\";
	for (i = 28; i <= 35; i++)
	{
		position.X = 113;
		position.Y = i;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
		cout << "|";
	}
	position.X = 90;
	position.Y = 36;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), position);
	cout << "\\_____________________\\|";
	diceOutput(1 + (rand() % 6));
}
// UI drawing functions end here.

// Game functions.
// Starts below.

// Passed by reference so that it mimics the behavior of the const keyword.
void printPlayerWealth(Player subject, Bank monopolyBank, Stocks monopolyStocks)
{
	COORD begin{ subject.dataLoc };
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "                 ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "Cash : $" << subject.cash;
	begin.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "                 ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "Dep. : $" << monopolyBank.debits[subject.number];
	begin.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "                 ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "Debt : $" << monopolyBank.credits[subject.number];
	begin.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "                 ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "Stock: $" << monopolyStocks.playerTotalStock(subject.number);
	begin.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "  --------------";
	begin.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "                 ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), begin);
	std::cout << "Total: $" << subject.cash + monopolyBank.debits[subject.number] - monopolyBank.credits[subject.number] + monopolyStocks.playerTotalStock(subject.number);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), subject.currentLoc);
}

// Menu -> New/Load Game problem (solved, unreviewed).
int getOption(const bool upgraded, const bool usedRD, const bool usedRB)
{
	clearAllAnnounced();

	int cmd = 0;
	const std::string options[] = // ADD ROBOT DICE AND ROAD BLOCKS + their functions.
	{
		"  Borrow Money  ", "  Return money  ",
		" Withdraw Money ", "   Save Money   ",
		"   Buy Stocks   ", "   Sell Stock   ",
		"Upgrade Property", "   Roll Dice!   ",
		"   Robot Dice   ", "   Road Block   "

	};
	const COORD after = 
	{
		ANNOUNCEMENT_LOC_X + 17, ANNOUNCEMENT_LOC_Y 
	};

	announce_LO("Choose an action:");
	announce_LT("<= " + options[cmd] + " =>");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);
	
	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();
		
		if (key == 77) // Arrow right
		{
			if (cmd == 9) cmd = 0;
			else cmd++;
			if (upgraded && cmd == 6) cmd++;
			if (usedRD && cmd == 8) cmd++;
			if (usedRB && cmd == 9) cmd = 0;

		}
		else if (key == 75) // Arrow left
		{
			if (cmd == 0) cmd = 9;
			else cmd--;
			if (usedRB && cmd == 9) cmd--;
			if (usedRD && cmd == 8) cmd--;
			if (upgraded && cmd == 6) cmd--;
		}
		else if (key == 27) // Esc key
		{
			int opt = getMenu();
			if (opt == -3) return opt;
			clearMenu();
		}

		announce_LT("<= " + options[cmd] + " =>");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);
		key = _getch();
	}

	return cmd;
}

int getReducedOption()
{
	clearAllAnnounced();

	int cmd = 0;
	const std::string options[] =
	{
		"  Borrow Money  ", " Withdraw Money ", "   Sell Stock   ", "     Cancel     "
	};
	const COORD after = 
	{ 
		ANNOUNCEMENT_LOC_X + 17, ANNOUNCEMENT_LOC_Y 
	};

	announce_LO("Choose an action:");
	announce_LT("<= " + options[cmd] + " =>");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);

	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		if (key == 77) // Arrow right
		{
			if (cmd == 3) cmd = 0;
			else cmd++;

		}
		else if (key == 75) // Arrow left
		{
			if (cmd == 0) cmd = 3;
			else cmd--;
		}
		else if (key == 27) // Esc key
		{
			getMenu();
			clearMenu();
		}

		announce_LT("<= " + options[cmd] + " =>");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);
		key = _getch();
	}

	return cmd;
}

int borrowMoney(Bank& monopolyBank, Player& borrower)
{
	clearAllAnnounced();

	long long unsigned sum;

	announce_LO("Enter the sum of money:");
	announce_LT("");
	std::cin >> sum; // Adjust field?

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (sum > monopolyBank.getMaxDebt() - monopolyBank.credits[borrower.number])
	{
		announce_LO("Cancelled due to insufficient money.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), borrower.currentLoc);
		return 0;
	}
	else
	{
		borrower.receiveMoney(sum);
		monopolyBank.giveMoney(sum, borrower.number, 1);

		announce_LO("Money borrowed successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), borrower.currentLoc);

		return 1;
	}
}

int returnMoney(Bank& monopolyBank, Player& borrower)
{
	clearAllAnnounced();

	long long unsigned sum;

	announce_LO("Enter the sum of money:");
	announce_LT("");
	std::cin >> sum; // Adjust field?

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (borrower.cash < sum)
	{
		announce_LO("Cancelled due to insufficient money.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), borrower.currentLoc);
		return 0;
	}
	else
	{
		monopolyBank.receiveMoney(sum, borrower.number, 1);
		borrower.giveMoney(sum);

		announce_LO("Money returned successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), borrower.currentLoc);

		return 1;
	}	
}

int withdrawMoney(Bank& monopolyBank, Player& client)
{
	clearAllAnnounced();

	long long unsigned sum;

	announce_LO("Enter the sum of money:");
	announce_LT("");
	std::cin >> sum; // Adjust field?

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (sum > monopolyBank.debits[client.number])
	{
		announce_LO("Cancelled due to insufficient money.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else
	{
		monopolyBank.giveMoney(sum, client.number, 0);
		client.receiveMoney(sum);

		announce_LO("Money withdrawed successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 1;
	}
}

int saveMoney(Bank& monopolyBank, Player& client)
{
	clearAllAnnounced();

	long long unsigned sum;

	announce_LO("Enter the sum of money:");
	announce_LT("");
	std::cin >> sum; // Adjust field?

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (client.cash < sum)
	{
		announce_LO("Cancelled due to insufficient money.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else
	{
		monopolyBank.receiveMoney(sum, client.number, 0);
		client.giveMoney(sum);

		announce_LO("Money saved successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 1;
	}
}

int buyStock(Stocks& monopolyStocks, Player& client)
{
	clearAllAnnounced();

	int stockNumber = -1;
	int n_stock;
	std::string stockName;
	const std::string stockNames[] =
	{
		"AGOQ", "SHIP", "WRHM", "IHFR", "WWGR"
	};

	announce_LO("Enter stock name:");
	announce_LT("");
	std::cin >> stockName; // Adjust field?

	for (int i = 0; i < 5; i++) if (stockName == stockNames[i])
	{
		stockNumber = i;
		break;
	}

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (stockNumber == -1)
	{
		announce_LO("Stock not found.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else
	{
		announce_LO("Enter the number of stock desired:");
		announce_LT("");
		std::cin >> n_stock; // Adjust field?
	}

	clearAnnouncement_LO();
	clearAnnouncement_LT();
	
	if (!monopolyStocks.buyable[stockNumber])
	{
		announce_LO("Stock is not buyable at the moment.");
		announce_LT("Transaction cancelled.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else if (client.cash < n_stock * monopolyStocks.stockPrices[stockNumber])
	{
		announce_LO("Insufficient money.");
		announce_LT("Transaction cancelled.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else
	{
		client.giveMoney(n_stock * monopolyStocks.stockPrices[stockNumber]);
		monopolyStocks.ownershipDatabase[client.number][stockNumber] += n_stock;

		announce_LO("Stock bought successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 1;
	}
}

int sellStock(Stocks& monopolyStocks, Player& client)
{
	clearAllAnnounced();

	int stockNumber = -1;
	int n_stock;
	std::string stockName;
	const std::string stockNames[] =
	{
		"AGOQ", "SHIP", "WRHM", "IHFR", "WWGR"
	};

	announce_LO("Enter stock name:");
	announce_LT("");
	std::cin >> stockName; // Adjust field?

	for (int i = 0; i < 5; i++) if (stockName == stockNames[i])
	{
		stockNumber = i;
		break;
	}

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (stockNumber == -1)
	{
		announce_LO("Stock not found");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else
	{							
		announce_LO("Enter the number of stock desired:");
		announce_LT("");
		std::cin >> n_stock; // Adjust field?
	}

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (!monopolyStocks.buyable[stockNumber])
	{
		announce_LO("Stock is not sellable at the moment.");
		announce_LT("Transaction cancelled.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	if (monopolyStocks.ownershipDatabase[client.number][stockNumber] < n_stock)
	{
		announce_LO("Insufficient money.");
		announce_LT("Transaction cancelled.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 0;
	}
	else
	{
		client.receiveMoney(n_stock * monopolyStocks.stockPrices[stockNumber]);
		monopolyStocks.ownershipDatabase[client.number][stockNumber] -= n_stock;

		announce_LO("Stock sold successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), client.currentLoc);
		return 1;
	}
}

int upgradeProperty(Player& owner, property_t blocks[28])
{
	clearAllAnnounced();

	announce_LO("Choose the property to be upgraded!");

	int x = FIRSTBLOCK_MID_X, y = FIRSTBLOCK_MID_Y, propNo = 0; // maxPropNo = 27;
	COORD curLoc = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curLoc);
	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		switch (key)
		{
		case 72: // Arrow up
			if (x == FIRSTBLOCK_MID_X || x == FIRSTBLOCK_MID_X + BLOCK_WIDTH * 7)
			{
				y -= BLOCK_HEIGHT;
				if (y < FIRSTBLOCK_MID_Y) y += BLOCK_HEIGHT;
				else
				{
					if (x == FIRSTBLOCK_MID_X) propNo++;
					else propNo--;
				}
			}
			break;

		case 75: //Arrow left
			if (y == FIRSTBLOCK_MID_Y || y == FIRSTBLOCK_MID_Y + BLOCK_HEIGHT * 7)
			{
				x -= BLOCK_WIDTH;
				if (x < FIRSTBLOCK_MID_X) x += BLOCK_WIDTH;
				else
				{
					if (y == FIRSTBLOCK_MID_Y) propNo--;
					else propNo++;
				}
			}
			break;

		case 77: // Arrow right
			if (y == FIRSTBLOCK_MID_Y || y == FIRSTBLOCK_MID_Y + BLOCK_HEIGHT * 7)
			{
				x += BLOCK_WIDTH;
				if (x > FIRSTBLOCK_MID_X + BLOCK_WIDTH * 7) x -= BLOCK_WIDTH;
				else
				{
					if (y == FIRSTBLOCK_MID_Y) propNo++;
					else propNo--;
				}
			}
			break;

		case 80: // Arrow down
			if (x == FIRSTBLOCK_MID_X || x == FIRSTBLOCK_MID_X + BLOCK_WIDTH * 7)
			{
				y += BLOCK_HEIGHT;
				if (y > FIRSTBLOCK_MID_Y + BLOCK_HEIGHT * 7) y -= BLOCK_HEIGHT;
				else
				{
					if (x == FIRSTBLOCK_MID_X) propNo--;
					else propNo++;
				}
			}
			break;
		}
		
		if (propNo < 0) propNo = 27;
		if (propNo > 27) propNo = 0;

		curLoc.X = x;
		curLoc.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curLoc);

		key = _getch();
	}

	clearAnnouncement_LO();

	for (int i = 0; i < owner.propertyData.size(); i++) if (owner.propertyData[i] == blocks[propNo].location)
	{
		if (owner.propertyLevels[i] == 3)
		{
			announce_LO("This property has reached max level.");
			announce_LT("Transaction cancelled.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), owner.currentLoc);
			return 0;
		}
		else
		{
			announce_LO("Pay " + std::to_string(UPGRADE_TOLL) + " to upgrade property? (Y/N)");

			int key = _getch();
			while (key != 121 && key != 89 && key != 78 && key != 110) key = _getch();

			clearAnnouncement_LO();
			clearAnnouncement_LT();

			if (key == 110 || key == 78)
			{
				announce_LO("Transaction cancelled.");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), owner.currentLoc);
				return 0;
			}
		}

		if (owner.cash < UPGRADE_TOLL)
		{
			announce_LO("Insufficient cash.");
			announce_LT("Transaction cancelled.");
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), owner.currentLoc);
			return 0;

		}

		owner.giveMoney(UPGRADE_TOLL);
		owner.propertyLevels[i] += 1;
		blocks[propNo].level += 1;
		blocks[propNo].printProperty();

		announce_LO("Property upgraded successfully!");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), owner.currentLoc);
		return 1;
	}

	announce_LO("This property's ownership lies");
	announce_LT("elsewhere.");
	Sleep(1500);
	clearAnnouncement_LO();
	clearAnnouncement_LT();
	announce_LO("Transaction cancelled.");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), owner.currentLoc);
	return 0;
}

int buyProperty(Player& buyer, property_t& product, Bank& monopolyBank, Stocks& monopolyStocks)
{
	clearAllAnnounced();

	if (buyer.cash < product.initialPrice)
	{
		announce_LO("Insufficient money.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), buyer.currentLoc);
		return 0;
	}

	announce_LO("Pay " + std::to_string(product.initialPrice) + " to buy");
	announce_LT("property? (Y/N)");

	int key = _getch();
	while (key != 121 && key != 89 && key != 78 && key != 110) key = _getch();

	clearAnnouncement_LO();
	clearAnnouncement_LT();

	if (key == 110 || key == 78)
	{
		announce_LO("Transaction cancelled.");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), buyer.currentLoc);
		return 0;
	}
	else
	{
		buyer.giveMoney(product.initialPrice);
		buyer.getProperty(product.location, 0);
		product.owner = buyer.number;

		product.printProperty();

		announce_LO("Transaction is successfull!");
		printPlayerWealth(buyer, gameBank, gameStocks);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), buyer.currentLoc);

		return 1;
	}
}

int payToll(Player& owner, Player& visitor, Bank& monopolyBank, Stocks& monopolyStocks, property_t block)
{
	clearAllAnnounced();

	if (visitor.cash + monopolyBank.debits[visitor.number] + monopolyBank.getMaxDebt() - monopolyBank.credits[visitor.number] + monopolyStocks.playerTotalStock(visitor.number) < block.toll[block.level])
	{
		owner.receiveMoney(block.toll[block.level]);

		announce_LO("Bankrupt! ~");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), visitor.currentLoc);
		return 0;
	}
	else
	{
		if (visitor.cash < block.toll[block.level])
		{
			while (visitor.cash < block.toll[block.level])
			{
				announce_LO("Insufficient cash.");
				announce_LT("Please provide enough cash to pay.");
				Sleep(1500);
				clearAnnouncement_LO();
				clearAnnouncement_LT();

				switch (getReducedOption())
				{
				case 0:
					if (borrowMoney(monopolyBank, visitor)) printPlayerWealth(visitor, monopolyBank, monopolyStocks);
					break;

				case 1:
					if (withdrawMoney(monopolyBank, visitor)) printPlayerWealth(visitor, monopolyBank, monopolyStocks);
					break;

				case 2:
					if (sellStock(monopolyStocks, visitor)) printPlayerWealth(visitor, monopolyBank, monopolyStocks);
					break;

				case 3:
					clearAllAnnounced();
					announce_LO("You will be bankrupt.");
					announce_LT("Are you sure? (Y/N)");

					int key = _getch();
					while (key != 121 && key != 89 && key != 78 && key != 110) key = _getch();
					clearAnnouncement_LO();
					clearAnnouncement_LT();
					if (key == 110 || key == 78)
					{
						owner.receiveMoney(block.toll[block.level]);

						announce_LO("Bankrupt! ~");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), visitor.currentLoc);
						return 0;
					}
					break;
				}
			}
		}

		visitor.giveMoney(block.toll[block.level]);
		owner.receiveMoney(block.toll[block.level]);
		printPlayerWealth(visitor, gameBank, gameStocks);
		printPlayerWealth(owner, gameBank, gameStocks);

		clearAnnouncement_LO();
		clearAnnouncement_LT();
		announce_LO("Paid " + std::to_string(block.toll[block.level]) + "!");
		PlaySound(TEXT(_SOUND_PAYCOINS), NULL, SND_FILENAME);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), visitor.currentLoc);
		return 1;
	}
}

int movePlayer(Player& moving, property_t blocks[28]) // returns new block no
{
	clearAllAnnounced();

	int i, dice = 1 + (rand() % 6);
	PlaySound(TEXT(_SOUND_DICEROLL), NULL, SND_FILENAME);
	diceOutput(dice);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), moving.currentLoc);
	Sleep(1500);
	announce_LO("Player rolled " + std::to_string(dice) + "!");
	Sleep(1500);

	COORD prevLoc = moving.currentLoc;
	int prevLoc_no = moving.currentLoc_no;

	moving.currentLoc = blocks[(prevLoc_no + dice) % 28].location_xy;
	moving.currentLoc_no = blocks[(prevLoc_no + dice) % 28].location;
	moving.currentLoc.Y += 3;

	bool hitRB = false;
	for (i = prevLoc_no; i < moving.currentLoc_no; i++)
	{
		if (blocks[i].roadBlock_exist)
		{
			blocks[i].roadBlock_exist = false;
			moving.currentLoc = blocks[i].location_xy;
			moving.currentLoc_no = blocks[i].location;
			moving.currentLoc.Y += 3;
			hitRB = true;
			break;
		}
	}

	switch (moving.number)
	{
	case 0:
		moving.currentLoc.X += 1;
		break;

	case 1:
		moving.currentLoc.X += 4;
		break;

	case 2:
		moving.currentLoc.X += 8;
		break;

	case 3:
		moving.currentLoc.X += 11;
		break;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prevLoc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	std::cout << " \b";

	PlaySound(TEXT(_SOUND_PLAYERMOVE), NULL, SND_FILENAME);
	Sleep(500);

	if (hitRB)
	{
		blocks[i].printProperty();
		announce_LT("Road block!");
		moving.printPlayer();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), moving.currentLoc);
		return blocks[i].location;
	}

	moving.printPlayer();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), moving.currentLoc);
	return blocks[(prevLoc_no + dice) % 28].location;
}

int movePlayer(Player& moving, property_t blocks[28], const int dice) // returns new block no
{
	clearAllAnnounced();

	int i;
	PlaySound(TEXT(_SOUND_DICEROLL), NULL, SND_FILENAME);
	diceOutput(dice);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), moving.currentLoc);
	Sleep(1500);
	announce_LO("Player rolled " + std::to_string(dice) + "!");
	Sleep(1500);

	COORD prevLoc = moving.currentLoc;
	int prevLoc_no = moving.currentLoc_no;

	moving.currentLoc = blocks[(prevLoc_no + dice) % 28].location_xy;
	moving.currentLoc_no = blocks[(prevLoc_no + dice) % 28].location;
	moving.currentLoc.Y += 3;

	bool hitRB = false;
	for (i = prevLoc_no; i < moving.currentLoc_no; i++)
	{
		if (blocks[i].roadBlock_exist)
		{
			blocks[i].roadBlock_exist = false;
			moving.currentLoc = blocks[i].location_xy;
			moving.currentLoc_no = blocks[i].location;
			moving.currentLoc.Y += 3;
			hitRB = true;
			break;
		}
	}

	switch (moving.number)
	{
	case 0:
		moving.currentLoc.X += 1;
		break;

	case 1:
		moving.currentLoc.X += 4;
		break;

	case 2:
		moving.currentLoc.X += 8;
		break;

	case 3:
		moving.currentLoc.X += 11;
		break;
	}

	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), prevLoc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	std::cout << " \b";

	PlaySound(TEXT(_SOUND_PLAYERMOVE), NULL, SND_FILENAME);
	Sleep(500);

	if (hitRB)
	{
		blocks[i].printProperty();
		announce_LT("Road block!");
		moving.printPlayer();
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), moving.currentLoc);
		return blocks[i].location;
	}
	moving.printPlayer();
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), moving.currentLoc);
	return blocks[(prevLoc_no + dice) % 28].location;
}

int takeCard(Player& playing, Bank& monopolyBank, Stocks& monopolyStocks)
{
	clearAllAnnounced();

	int card = rand() % 3;
	const std::string cards[] =
	{
		"You fell ill. Rest for one turn!", "Oh! You found $100!", "Went travelling, spent $300!"
	};

	announce_LO(cards[card]);

	switch (card)
	{
	case 0:
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), playing.currentLoc);
		return -1;
		break;

	case 1:
		playing.cash += 100;
		printPlayerWealth(playing, monopolyBank, monopolyStocks);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), playing.currentLoc);
		return 1;
		break;

	case 2:
		if (playing.cash >= 300)
		{
			playing.giveMoney(300);
			printPlayerWealth(playing, monopolyBank, monopolyStocks);
			SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), playing.currentLoc);
			return 1;
		}
		else
		{
			while (playing.cash < 300)
			{
				clearAnnouncement_LO();
				clearAnnouncement_LT();

				announce_LO("Insufficient cash.");
				announce_LT("Please provide enough cash to pay.");
				Sleep(1500);
				clearAnnouncement_LO();
				clearAnnouncement_LT();

				switch (getReducedOption())
				{
				case 0:
					if (borrowMoney(monopolyBank, playing)) printPlayerWealth(playing, monopolyBank, monopolyStocks);
					break;

				case 1:
					if (withdrawMoney(monopolyBank, playing)) printPlayerWealth(playing, monopolyBank, monopolyStocks);
					break;

				case 2:
					if (sellStock(monopolyStocks, playing)) printPlayerWealth(playing, monopolyBank, monopolyStocks);
					break;

				case 3:
					clearAllAnnounced();
					announce_LO("You will be bankrupt.");
					announce_LT("Are you sure? (Y/N)");

					int key = _getch();
					while (key != 121 && key != 89 && key != 78 && key != 110) key = _getch();
					clearAnnouncement_LO();
					clearAnnouncement_LT();
					if (key == 110 || key == 78)
					{
						announce_LO("Bankrupt! ~");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), playing.currentLoc);
						return 0;
					}
					break;
				}
			}
		}
		break;
	}

	playing.giveMoney(300);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), playing.currentLoc);

	return 1;
}

int saveFile(const std::string fileName, const Player players[5], Bank monopolyBank, Stocks monopolyStocks, const property_t blocks[28], int players_n, int turnsLeft, std::string mapName, int currentPlayer)
{
	clearAllAnnounced();

	std::ofstream outputStream;
	outputStream.open(fileName, std::ios::out);
	if (!outputStream.is_open()) return 0;

	outputStream << mapName << " " << turnsLeft << " " << players_n << "\n";
	for (int i = 0; i < 28; i++)
	{
		if (blocks[i].location < 10) outputStream << "0";
		outputStream << blocks[i].location << " ";

		outputStream << blocks[i].name << " " << blocks[i].type;
		if (blocks[i].type != 1)
		{
			outputStream << "\n";
			continue;
		}
		else
		{
			outputStream << " " << blocks[i].initialPrice;
			for (int j = 0; j < 4; j++) outputStream << " " << blocks[i].toll[j];
			outputStream << "\n";
		}
	}

	outputStream << "playerstate " << currentPlayer << "\n";

	for (int i = 0; i < players_n; i++)
	{
		outputStream << i + 1 << " ";
		if (players[i].currentLoc_no < 10) outputStream << "0";
		outputStream << players[i].currentLoc_no << " ";
		
		outputStream << players[i].cash + monopolyBank.debits[players[i].number] - monopolyBank.credits[players[i].number] + monopolyStocks.playerTotalStock(players[i].number);

		for (int j = 0; j < players[i].propertyData.size(); j++)
		{
			if (players[i].propertyData[j] < 10) outputStream << " 0" << players[i].propertyData[j];
			else outputStream << " " << players[i].propertyData[j];
			outputStream << " " << players[i].propertyLevels[j];
		}
		outputStream << "\n";
	}
	outputStream.close();
	return 1;
}

std::string findFile()
{
	clearAllAnnounced();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	COORD xy_loc;
	COORD after = { MENU_LOC_X + 15, MENU_LOC_Y };
	int cmd = 0;

	// Gets file names.
	std::vector<std::string>fileList;
	fileList.clear();

	std::string temp;
	std::ifstream inputStream;
	inputStream.open(_MEM_FILE, std::ios::in);
	if (!inputStream.is_open()) return 0;

	while (inputStream >> temp) fileList.push_back(temp);	
	// Gets file names ends here.

	xy_loc.X = MENU_LOC_X;
	xy_loc.Y = MENU_LOC_Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
	if (fileList.size() == 0)
	{
		std::cout << "There are no games saved.";
		return 0;
	}
	else
	{
		std::cout << "Existing files:                   ";
	}
	
	xy_loc.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
	std::cout << "<= " << fileList[cmd] << " =>          ";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);

	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		if (key == 77) // Arrow right
		{
			if (cmd == fileList.size() - 1) cmd = 0;
			else cmd++;

		}
		else if (key == 75) // Arrow left
		{
			if (cmd == 0) cmd = fileList.size() - 1;
			else cmd--;
		}

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cout << "<= " << fileList[cmd] << " =>          ";
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);
		key = _getch();
	}
	inputStream.close();

	return "memory/" + fileList[cmd] + ".txt";
}

std::string promptFile()
{
	clearAllAnnounced();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	COORD xy_loc;
	COORD after = { MENU_LOC_X + 15, MENU_LOC_Y };
	int cmd = 0;

	// Gets file names.
	std::vector<std::string>fileList;
	fileList.clear();

	std::string temp, fileNameSelected;
	std::ifstream inputStream;
	std::ofstream outputStream;
	inputStream.open(_MEM_FILE, std::ios::in);
	outputStream.open(_MEM_FILE, std::ios_base::app);
	if (!inputStream.is_open()) return 0;

	while (inputStream >> temp) fileList.push_back(temp);
	// Gets file names ends here.

	xy_loc.X = MENU_LOC_X;
	xy_loc.Y = MENU_LOC_Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
	std::cout << "Save as an existing file? (Y/N)";

	int key = _getch();
	while (key != 121 && key != 89 && key != 78 && key != 110) key = _getch();
	if (key == 110 || key == 78) // No
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cout << "Enter file name (8 chars max): "; // file names could be the same?
		xy_loc.Y += 1;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cin >> fileNameSelected;

		outputStream << " " << fileNameSelected << " ";

		inputStream.close();
		outputStream.close();
		return "memory/" + fileNameSelected + ".txt";
	}

	inputStream.close();
	outputStream.close();
	return "" + findFile() + "";
}

int loadGame(std::string fileName, Player players[5], Bank& monopolyBank, Stocks& monopolyStocks, property_t blocks[28], int* players_n, int* turnsLeft, std::string* mapName , int* currentPlayer)
{
	clearAllAnnounced();

	monopolyBank.resetBank();
	monopolyStocks.resetStocks();

	for (int i = 0; i < 4; i++) playing[i] = current[i] = false;
	for (int i = 0; i < 4; i++) placedRoadBlock[i] = usedRobotDice[i] = true;

	for (int i = 0; i < 28; i++) blocks[i].resetProperty();

	std::ifstream inputStream;
	inputStream.open(fileName, std::ios::in);
	if (!inputStream.is_open()) return 0;

	std::string temp;
	std::vector<std::string> tokens;

	inputStream >> *mapName >> *turnsLeft >> *players_n;

	for (int i = 0; i < 28; i++)
	{
		inputStream >> temp;
		blocks[i].location = std::stoi(temp);

		inputStream >> blocks[i].name;

		inputStream >> temp;
		blocks[i].type = std::stoi(temp);

		if (blocks[i].type != 1) continue;
		else inputStream >> blocks[i].initialPrice >> blocks[i].toll[0] >> blocks[i].toll[1] >> blocks[i].toll[2] >> blocks[i].toll[3];
	}

	inputStream >> temp >> *currentPlayer;

	for (int i = 0; i < *players_n; i++)
	{
		tokens.clear();
		players[i].propertyData.clear();
		players[i].propertyLevels.clear();

		inputStream >> players[i].number;
		players[i].number -= 1;

		inputStream >> players[i].currentLoc_no;
		players[i].currentLoc = blocks[players[i].currentLoc_no].location_xy;
		players[i].currentLoc.Y += 3;
		switch (i)
		{
		case 0:
			players[i].currentLoc.X += 1;
			break;

		case 1:
			players[i].currentLoc.X += 4;
			break;

		case 2:
			players[i].currentLoc.X += 8;
			break;

		case 3:
			players[i].currentLoc.X += 11;
			break;
		}

		inputStream >> players[i].cash;

		if (getline(inputStream, temp))
		{
			std::istringstream iss(temp);
			copy(std::istream_iterator<std::string>(iss),
				std::istream_iterator<std::string>(),
				back_inserter(tokens));

			for (int j = 0; j < tokens.size(); j += 2)
			{
				players[i].propertyData.push_back(std::stoi(tokens[j]));
				blocks[std::stoi(tokens[j])].owner = players[i].number;
				players[i].propertyLevels.push_back(std::stoi(tokens[j + 1]));
				blocks[std::stoi(tokens[j])].level = std::stoi(tokens[j + 1]);
			}
		}
	}

	for (int i = 0; i < 28; i++) blocks[i].printProperty();
	for (int i = 0; i < *players_n; i++)
	{
		playing[i] = current[i] = true;
		placedRoadBlock[i] = usedRobotDice[i] = false;
		players[i].printPlayer();
		printPlayerWealth(players[i], monopolyBank, monopolyStocks);
	}
	monopolyStocks.printStocks();

	inputStream.close();
	return 1;
}

int getMenu()
{
	clearAllAnnounced();

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
	COORD xy_loc;
	COORD menuLoc = { MENU_LOC_X + 10, MENU_LOC_Y };

	xy_loc.X = MENU_LOC_X;
	xy_loc.Y = MENU_LOC_Y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
	std::cout << "M  E  N  U";

	const std::string menu[] =
	{
		"New game", "Save game", "Load game", "Exit game"
	};

	xy_loc.X += 2;
	for (int i = 0; i < 4; i++)
	{
		xy_loc.Y += 2;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cout << menu[i];
	}
	xy_loc.X -= 2;

	int userChoice = 0;
	xy_loc.Y = MENU_LOC_Y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
	std::cout << ">";
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), menuLoc);

	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		xy_loc.Y = MENU_LOC_Y + ((userChoice + 1) * 2);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cout << " ";
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), menuLoc);

		if (key == 72) // Arrow up
		{
			if (userChoice == 0) userChoice = 3;
			else userChoice--;
		}
		else if (key == 80) // Arrow down
		{
			if (userChoice == 3) userChoice = 0;
			else userChoice++;
		}
		else if (key == 27)
		{
			clearMenu();
			clearAnnouncement_LO();
			announce_LO("Choose an action:");
			return 2;
		}

		xy_loc.Y = MENU_LOC_Y + ((userChoice + 1) * 2);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_loc);
		std::cout << ">";
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), menuLoc);

		key = _getch();
	}

	if (userChoice == 0) // New game
	{
		switch (getPlayerNumber())
		{
		case 1:
			loadGame(_RESET_FILE_1, gamePlayers, gameBank, gameStocks, blocks, &player_n, &turnsLeft, &mapName, &currentPlayer);
			break;

		case 2:
			loadGame(_RESET_FILE_2, gamePlayers, gameBank, gameStocks, blocks, &player_n, &turnsLeft, &mapName, &currentPlayer);
			break;

		case 3:
			loadGame(_RESET_FILE_3, gamePlayers, gameBank, gameStocks, blocks, &player_n, &turnsLeft, &mapName, &currentPlayer);
			break;

		case 4:
			loadGame(_RESET_FILE_4, gamePlayers, gameBank, gameStocks, blocks, &player_n, &turnsLeft, &mapName, &currentPlayer);
			break;
		}

		system("CLS");
		setup();
		return -3;
	}
	else if (userChoice == 1) // Save game
	{
		std::string filename_forSave = promptFile();
		if (saveFile(filename_forSave, gamePlayers, gameBank, gameStocks, blocks, player_n, turnsLeft, mapName, currentPlayer))
		{
			announce_LO("File saved!");
		}
		else
		{
			announce_LO("File save failed.");
		}
		
		Sleep(1500);
		clearAnnouncement_LO();
		announce_LO("Choose an action:");
		return 0;
	}
	else if (userChoice == 2) // Load game
	{
		std::string filename_forLoad = findFile();
		loadGame(filename_forLoad, gamePlayers, gameBank, gameStocks, blocks, &player_n, &turnsLeft, &mapName, &currentPlayer);
		system("CLS");
		setup();
		return -3;
	}
	else if (userChoice == 3)
	{
		exit(0);
		return 0;
	}

}

int checkWin(Player players[4], Bank monopolyBank, Stocks monopolyStocks, const bool playing[5], const int turnsLeft) // returns player number.
{
	int playing_n = 0;
	for (int i = 0; i < 4; i++) if (playing[i]) playing_n++;
	if (playing_n == 1) for (int i = 0; i < 4; i++) if (playing[i]) return i + 1;
	else if (!turnsLeft)
	{
		int i;
		int winner, winner_cash;

		for (i = 0; i < 4; i++) if (playing[i])
		{
			winner = i;
			winner_cash = players[i].cash + monopolyBank.debits[players[i].number] - monopolyBank.credits[players[i].number] + monopolyStocks.playerTotalStock(players[i].number);
			break;
		}

		for (i = 0; i < 4; i++)
		{
			if (!playing[i]) continue;
			long long cash = players[i].cash + monopolyBank.debits[players[i].number] - monopolyBank.credits[players[i].number] + monopolyStocks.playerTotalStock(players[i].number);
			if (cash > winner_cash)
			{
				winner = i;
				winner_cash = cash;
			}
		}

		return winner + 1;
	}

	return 0;
}

int robotDice()
{
	clearAllAnnounced();

	int dc = 1;
	const COORD after =
	{
		ANNOUNCEMENT_LOC_X + 20, ANNOUNCEMENT_LOC_Y
	};

	announce_LO("Choose a dice value:");
	announce_LT("<= " + std::to_string(dc) + " =>");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);

	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		if (key == 77) // Arrow right
		{
			if (dc == 6) dc = 1;
			else dc++;

		}
		else if (key == 75) // Arrow left
		{
			if (dc == 1) dc = 6;
			else dc--;
		}

		announce_LT("<= " + std::to_string(dc) + " =>");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);
		key = _getch();
	}
	return dc;

}

int getPlayerNumber()
{
	clearAllAnnounced();

	int dc = 1;
	const COORD after =
	{
		ANNOUNCEMENT_LOC_X + 29, ANNOUNCEMENT_LOC_Y
	};

	announce_LO("Choose the number of players:");
	announce_LT("<= " + std::to_string(dc) + " =>");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);

	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		if (key == 77) // Arrow right
		{
			if (dc == 4) dc = 1;
			else dc++;

		}
		else if (key == 75) // Arrow left
		{
			if (dc == 1) dc = 4;
			else dc--;
		}

		announce_LT("<= " + std::to_string(dc) + " =>");
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), after);
		key = _getch();
	}

	return dc;

}

int roadBlock()
{
	clearAllAnnounced();

	announce_LO("Where to put the road block?");

	int x = FIRSTBLOCK_MID_X, y = FIRSTBLOCK_MID_Y, propNo = 0; // maxPropNo = 27;
	COORD curLoc = { x, y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curLoc);
	int key = _getch();
	while (key != 13)
	{
		if (key == 224) key = _getch();

		switch (key)
		{
		case 72: // Arrow up
			if (x == FIRSTBLOCK_MID_X || x == FIRSTBLOCK_MID_X + BLOCK_WIDTH * 7)
			{
				y -= BLOCK_HEIGHT;
				if (y < FIRSTBLOCK_MID_Y) y += BLOCK_HEIGHT;
				else
				{
					if (x == FIRSTBLOCK_MID_X) propNo++;
					else propNo--;
				}
			}
			break;

		case 75: //Arrow left
			if (y == FIRSTBLOCK_MID_Y || y == FIRSTBLOCK_MID_Y + BLOCK_HEIGHT * 7)
			{
				x -= BLOCK_WIDTH;
				if (x < FIRSTBLOCK_MID_X) x += BLOCK_WIDTH;
				else
				{
					if (y == FIRSTBLOCK_MID_Y) propNo--;
					else propNo++;
				}
			}
			break;

		case 77: // Arrow right
			if (y == FIRSTBLOCK_MID_Y || y == FIRSTBLOCK_MID_Y + BLOCK_HEIGHT * 7)
			{
				x += BLOCK_WIDTH;
				if (x > FIRSTBLOCK_MID_X + BLOCK_WIDTH * 7) x -= BLOCK_WIDTH;
				else
				{
					if (y == FIRSTBLOCK_MID_Y) propNo++;
					else propNo--;
				}
			}
			break;

		case 80: // Arrow down
			if (x == FIRSTBLOCK_MID_X || x == FIRSTBLOCK_MID_X + BLOCK_WIDTH * 7)
			{
				y += BLOCK_HEIGHT;
				if (y > FIRSTBLOCK_MID_Y + BLOCK_HEIGHT * 7) y -= BLOCK_HEIGHT;
				else
				{
					if (x == FIRSTBLOCK_MID_X) propNo--;
					else propNo++;
				}
			}
			break;
		}

		if (propNo < 0) propNo = 27;
		if (propNo > 27) propNo = 0;

		curLoc.X = x;
		curLoc.Y = y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), curLoc);

		key = _getch();
	}

	clearAnnouncement_LO();

	if (blocks[propNo].roadBlock_exist)
	{
		announce_LO("This place already has a road block.");
		return 0;
	}
	else
	{
		blocks[propNo].roadBlock_exist = true;
		blocks[propNo].printProperty();
		announce_LO("Road block placed!");
		return 1;
	}
}
#endif // !GAMEFUNCTIONS_H
