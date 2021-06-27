#ifndef PLAYER_H
#define PLAYER_H

#include <Windows.h>
#include <iostream>
#include <vector>

#include "Property.h"

// #define DICE_RES_LOCATION
// #define TEXT_COLOUR_PLAYER

class Player
{
public:
	// Constructor.
	Player();
	Player(const COORD currentLoc, const COORD dataLoc, const int currentLoc_no, const int colour, const int number);

	// Member functions
	void receiveMoney(const long long unsigned sum); // Cash increases
	void giveMoney(const long long unsigned sum); // Cash decreases
	void getProperty(const int property, const int level); // property = property location number
	void moveTo(COORD newLocation, const int currentLoc_no);
	void printPlayer();


	// Data members.
	unsigned long long cash;
	std::vector<int> propertyData;
	std::vector<int> propertyLevels;
	COORD currentLoc, dataLoc;
	int colour, number, currentLoc_no;
};

#endif // !PLAYER_H