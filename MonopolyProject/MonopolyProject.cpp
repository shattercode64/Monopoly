#include <conio.h>
#include "GameFunctions.h"

int main()
{
	system("MODE CON COLS=162 LINES=51");

	// Start page.
	startPage();
	int ky = _getch();
	if (ky == 224) ky = _getch();
	system("CLS");

	// Setups.
	setup();

	// Players' initialization.
	const int colours[] =
	{
		PLAYER_ONE_COLOUR, PLAYER_TWO_COLOUR,
		PLAYER_THREE_COLOUR, PLAYER_FOUR_COLOUR
	};

	for (int i = 0; i < 4; i++)
	{
		gamePlayers[i].cash = STARTING_CASH;
		gamePlayers[i].propertyData.clear();
		gamePlayers[i].propertyLevels.clear();
		gamePlayers[i].colour = colours[i];
		gamePlayers[i].number = i;
		gamePlayers[i].currentLoc_no = 0;
		gamePlayers[i].currentLoc.Y = 8;
	};

	gamePlayers[0].currentLoc.X = 46;
	gamePlayers[0].dataLoc.X = 2;
	gamePlayers[0].dataLoc.Y = 3;

	gamePlayers[1].currentLoc.X = 49;
	gamePlayers[1].dataLoc.X = 22;
	gamePlayers[1].dataLoc.Y = 3;

	gamePlayers[2].currentLoc.X = 53;
	gamePlayers[2].dataLoc.X = 2;
	gamePlayers[2].dataLoc.Y = 12;

	gamePlayers[3].currentLoc.X = 56;
	gamePlayers[3].dataLoc.X = 22;
	gamePlayers[3].dataLoc.Y = 12;
	// Players' initialization ends here.

	// Blocks' initialization.
	COORD xy{ 45, 5 };
	for (int i = 0; i < 8; i++)
	{
		blocks[i].location = i;
		blocks[i].location_xy = xy;
		// if (i != 0) blocks[i].printProperty();
		xy.X += BLOCK_WIDTH;
	}
	xy.X -= BLOCK_WIDTH;
	for (int i = 8; i < 15; i++)
	{
		xy.Y += BLOCK_HEIGHT;
		blocks[i].location = i;
		blocks[i].location_xy = xy;
		// blocks[i].printProperty();
	}
	for (int i = 15; i < 22; i++)
	{
		xy.X -= BLOCK_WIDTH;
		blocks[i].location = i;
		blocks[i].location_xy = xy;
		// blocks[i].printProperty();
	}
	for (int i = 22; i < 28; i++)
	{
		xy.Y -= BLOCK_HEIGHT;
		blocks[i].location = i;
		blocks[i].location_xy = xy;
		// blocks[i].printProperty();
	}
	// Blocks' initialization ends here.
	loadGame(_RESET_FILE_4, gamePlayers, gameBank, gameStocks, blocks, &player_n, &turnsLeft, &mapName, &currentPlayer);
	goto startgame;

initgame:
	for (int i = 0; i < 28; i++) blocks[i].printProperty();
	for (int i = 0; i < 4; i++) playing[i] = current[i] = false;
	for (int i = 0; i < 4; i++) placedRoadBlock[i] = usedRobotDice[i] = true;
	for (int i = 0; i < player_n; i++)
	{
		playing[i] = current[i] = true;
		placedRoadBlock[i] = usedRobotDice[i] = false;
		gamePlayers[i].printPlayer();
		printPlayerWealth(gamePlayers[i], gameBank, gameStocks);
	}
	gameStocks.printStocks();
	// End of setups.

startgame:
	while (!win)
	{
		clearAnnouncement_LO();
		clearAnnouncement_LT();
		COORD loc = { ANNOUNCEMENT_LOC_X, ANNOUNCEMENT_LOC_Y - 1};
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), ANNOUNCEMENT_TEXT_COLOUR);
		std::cout << "                                    ";
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
		std::cout << "Player " << currentPlayer + 1 << "'s turn!";

		Sleep(1000);

		bool upgraded = false;
		int newBlock = -1;
		int opt;
		while (newBlock == -1)
		{
			opt = getOption(upgraded, usedRobotDice[currentPlayer], placedRoadBlock[currentPlayer]);
			if (opt == -3) goto initgame;
			switch (opt)
			{
			case 0:
				if (borrowMoney(gameBank, gamePlayers[currentPlayer])) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
				break;

			case 1:
				if (returnMoney(gameBank, gamePlayers[currentPlayer])) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
				break;

			case 2:
				if (withdrawMoney(gameBank, gamePlayers[currentPlayer])) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
				break;

			case 3:
				if (saveMoney(gameBank, gamePlayers[currentPlayer])) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
				break;

			case 4:
				if (buyStock(gameStocks, gamePlayers[currentPlayer])) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
				break;

			case 5:
				if (sellStock(gameStocks, gamePlayers[currentPlayer])) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
				break;

			case 6:
				if (upgradeProperty(gamePlayers[currentPlayer], blocks))
				{
					printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
					upgraded = true;
				}
				break;

			case 7:
				newBlock = movePlayer(gamePlayers[currentPlayer], blocks);
				break;

			case 8:
				usedRobotDice[currentPlayer] = true;
				newBlock = movePlayer(gamePlayers[currentPlayer], blocks, robotDice());
				break;

			case 9:
				placedRoadBlock[currentPlayer] = roadBlock();
				break;
			}

			Sleep(1500);
		}

		if (blocks[newBlock].type == 1)
		{
			if (blocks[newBlock].owner == -1)
			{
				if (buyProperty(gamePlayers[currentPlayer], blocks[newBlock], gameBank, gameStocks)) printPlayerWealth(gamePlayers[currentPlayer], gameBank, gameStocks);
			}
			else
			{
				for (int i = 0; i < 4; i++) if (blocks[newBlock].owner == gamePlayers[i].number && i != currentPlayer)
				{
					playing[currentPlayer] = payToll(gamePlayers[i], gamePlayers[currentPlayer], gameBank, gameStocks, blocks[newBlock]);
					break;
				}
				
			}
				
		}
		else if (blocks[newBlock].type == 0) gamePlayers[currentPlayer].cash += ALLOWANCE_CASH;
		else
		{
			int card = takeCard(gamePlayers[currentPlayer], gameBank, gameStocks);
			Sleep(1500);
			if (card == -1) current[currentPlayer] = false;
			else if (card == 0)
			{
				playing[currentPlayer] = false;
			}
			
		}

		do
		{
			if (currentPlayer == player_n - 1)
			{
				currentPlayer = 0;
				turnsLeft--;
			}
			else currentPlayer++;
		} while (!playing[currentPlayer]);

		while (!current[currentPlayer])
		{
			current[currentPlayer] = true;

			if (currentPlayer == player_n - 1)
			{
				currentPlayer = 0;
				turnsLeft--;
			}
			else currentPlayer++;
		}

		win = checkWin(gamePlayers, gameBank, gameStocks, playing, turnsLeft);
		gameStocks.alterStocks();
		Sleep(1500);
	}

	clearAnnouncement_LO();
	announce_LO("Player " + std::to_string(win) + " wins!");

	Sleep(5000);
	return 0;
}