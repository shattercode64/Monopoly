#ifndef PROPERTY_H
#define PROPERTY_H

#include <Windows.h>
#include <iostream>
#include <string>

#define PROPERTY_LEVEL_ZERO 15
#define PROPERTY_LEVEL_ONE 79
#define PROPERTY_LEVEL_TWO 128
#define PROPERTY_LEVEL_THREE 96
#define TEXT_COLOUR_HIGHLIGHT 112

class property_t
{
public:
	property_t();
	void printProperty();
	void resetProperty();

	std::string name;
	unsigned long long initialPrice, toll[4];
	COORD location_xy; // Top-left corner of block
	int type, location, level;
	int owner;
	bool roadBlock_exist;

};

#endif // !PROPERTY_H