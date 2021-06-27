#ifndef STOCKS_H
#define STOCKS_H

#include <Windows.h>
#include <cstdlib>
#include <time.h>
#include <string>
#include <iostream>

#define STOCK_LOCATION_X 13
#define STOCK_LOCATION_Y 21
#define STOCK_COLOUR_NEUTRAL 15
#define STOCK_COLOUR_UP 10
#define STOCK_COLOUR_DOWN 12
#define TEXT_COLOUR_STOCK 15

#define MAX_STOCK 800
#define MAX_BUYABLE 750
#define MIN_STOCK 200
#define MIN_BUYABLE 250
#define MAX_CHANGE 8 // rand() % 9

#define N_STOCKS 5

class Stocks
{
public:
	Stocks();
	void alterStocks();
	void printStocks();
	void resetStocks();

	void playerBought(const int player, const int stock, const int n_ofStock);
	void playerSold(const int player, const int stock, const int n_ofStock);
	unsigned long long playerTotalStock(const int player);

	int ownershipDatabase[5][N_STOCKS]; // 4 owners and N_STOCKS stocks.
	int stockPrices[N_STOCKS];
	int buyable[N_STOCKS];
	int stockColours[N_STOCKS];
};

#endif // !STOCKS_H