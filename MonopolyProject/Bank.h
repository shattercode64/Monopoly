#ifndef  BANK_H
#define BANK_H

#include <Windows.h>
#include <iostream>

// #define TEXT_COLOUR_BANK
#define MAX_DEBT 12000

class Bank
{
public:
	Bank();

	void receiveMoney(const unsigned long long sum, const int player, const int isDebt);
	void giveMoney(const unsigned long long sum, const int player, const int isDebt);

	unsigned long long getMaxDebt();

	void resetBank();

	long long debits[5]; // operation 0: deposit/withdraw
	long long credits[5]; // operation 1: return/borrow
};

#endif // ! BANK_H