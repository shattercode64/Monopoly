#include "Player.h"

Player::Player()
{
	this->currentLoc.X = 0;
	this->currentLoc.Y = 0;

	this->dataLoc.X = 0;
	this->dataLoc.Y = 0;

	this->colour = 15;

	this->number = -1;

	this->currentLoc_no =-1;

	cash = 0;

	propertyData.clear();
	propertyLevels.clear();
}

Player::Player(const COORD currentLoc, const COORD dataLoc, const int currentLoc_no, const int colour, const int number)
{
	this->currentLoc.X = currentLoc.X;
	this->currentLoc.Y = currentLoc.Y;

	this->dataLoc.X = dataLoc.X;
	this->dataLoc.Y = dataLoc.Y;

	this->colour = colour;
	
	this->number = number;

	this->currentLoc_no = currentLoc_no;

	cash = 0;

	printPlayer();

	propertyData.clear();
	propertyLevels.clear();
}

void Player::receiveMoney(const long long unsigned sum) { cash += sum; }

void Player::giveMoney(const long long unsigned sum) { cash -= sum; }

void Player::getProperty(const int property, const int level)
{
	propertyData.push_back(property);
	propertyLevels.push_back(level);
}

void Player::moveTo(COORD newLocation, const int currentLoc_no)
{
	currentLoc.X = newLocation.X;
	currentLoc.Y = newLocation.Y;

	this->currentLoc_no = currentLoc_no;

	printPlayer();
}

void Player::printPlayer()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), currentLoc);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), colour);
	std::cout << number + 1;
}