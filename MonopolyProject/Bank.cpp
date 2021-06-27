#include "Bank.h"

Bank::Bank()
{
	for (int i = 0; i < 5; i++)
	{
		debits[i] = 0;
		credits[i] = 0;
	}
}

void Bank::receiveMoney(const unsigned long long sum, const int player, const int isDebt)
{
	if (isDebt) credits[player] -= sum;
	else debits[player] += sum;

	if (credits[player] < 0)
	{
		debits[player] -= credits[player];
		credits[player] = 0;
	}
}

void Bank::giveMoney(const unsigned long long sum, const int player, const int isDebt)
{
	if (isDebt) credits[player] += sum;
	else debits[player] -= sum;

	if (debits[player] < 0)
	{
		credits[player] -= debits[player];
		debits[player] = 0;
	}
}

unsigned long long Bank::getMaxDebt() { return MAX_DEBT; }

void Bank::resetBank() { for (int i = 0; i < 5; i++) debits[i] = credits[i] = 0; }