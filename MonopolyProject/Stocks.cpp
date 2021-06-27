#include "Stocks.h"

Stocks::Stocks()
{
	srand(time(NULL));

	for (int i = 0; i < N_STOCKS; i++)
	{
		stockColours[i] = STOCK_COLOUR_NEUTRAL;
		stockPrices[i] = MIN_STOCK + (rand() % (MAX_STOCK - MIN_STOCK + 1));
		if (stockPrices[i] < MIN_BUYABLE || stockPrices[i] > MAX_BUYABLE) buyable[i] = false;
		else buyable[i] = true;
	}

	for (int i = 0; i < 5; i++) for (int j = 0; j < N_STOCKS; j++) ownershipDatabase[i][j] = 0;

}

void Stocks::alterStocks()
{
	for (int i = 0; i < N_STOCKS; i++)
	{
		int change = (rand() % (MAX_CHANGE + 1));
		if (!change) stockColours[i] = STOCK_COLOUR_NEUTRAL;
		else if (rand() % 2 == 1)
		{
			stockPrices[i] += change;
			stockColours[i] = STOCK_COLOUR_UP;
		}
		else
		{
			stockPrices[i] -= change;
			stockColours[i] = STOCK_COLOUR_DOWN;
		}

		if (stockPrices[i] < MIN_BUYABLE || stockPrices[i] > MAX_BUYABLE) buyable[i] = false;
		else buyable[i] = true;
	}

	printStocks();
}

void Stocks::printStocks()
{
	const std::string stockNames[] =
	{
		"AGOQ", "SHIP", "WRHM", "IHFR", "WWGR"
	};

	COORD loc = { STOCK_LOCATION_X - 4, STOCK_LOCATION_Y - 2 };
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TEXT_COLOUR_STOCK);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	std::cout << "S T O C K   P R I C E S";

	loc.X = STOCK_LOCATION_X;
	loc.Y = STOCK_LOCATION_Y;
	for (int i = 0; i < N_STOCKS; i++)
	{
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TEXT_COLOUR_STOCK);
		std::cout << stockNames[i] << "\t";
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), stockColours[i]);
		std::cout << stockPrices[i];

		loc.Y += 2;
	}

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), TEXT_COLOUR_STOCK);
	loc.X -= 3;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	std::cout << "Lowest buyable : " << MIN_BUYABLE;
	loc.Y += 1;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), loc);
	std::cout << "Highest buyable: " << MAX_BUYABLE;
}

void Stocks::playerBought(const int player, const int stock, const int n_ofStock) { ownershipDatabase[player][stock] += n_ofStock; }

void Stocks::playerSold(const int player, const int stock, const int n_ofStock) { ownershipDatabase[player][stock] -= n_ofStock; }

unsigned long long Stocks::playerTotalStock(const int player)
{
	unsigned long long total = 0;
	for (int i = 0; i < N_STOCKS; i++) total += stockPrices[i] * ownershipDatabase[player][i];
	return total;
}

void Stocks::resetStocks()
{
	srand(time(NULL));

	for (int i = 0; i < N_STOCKS; i++)
	{
		stockColours[i] = STOCK_COLOUR_NEUTRAL;
		stockPrices[i] = MIN_STOCK + (rand() % (MAX_STOCK - MIN_STOCK + 1));
		if (stockPrices[i] < MIN_BUYABLE || stockPrices[i] > MAX_BUYABLE) buyable[i] = false;
		else buyable[i] = true;
	}

	for (int i = 0; i < 5; i++) for (int j = 0; j < N_STOCKS; j++) ownershipDatabase[i][j] = 0;
}