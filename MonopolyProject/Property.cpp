#include "Property.h"

property_t::property_t()
{
	name = "";
	initialPrice = 1000;
	for (int i = 0; i < 4; i++) toll[i] = 0;
	location_xy.X = location_xy.Y = 0;
	type = location = level = 0;
	owner = -1;
	roadBlock_exist = false;
}

void property_t::printProperty()
{
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), location_xy);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PROPERTY_LEVEL_ZERO);
	std::cout << " ";

	switch (level)
	{
	case 0:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PROPERTY_LEVEL_ZERO);
		break;

	case 1:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PROPERTY_LEVEL_ONE);
		break;

	case 2:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PROPERTY_LEVEL_TWO);
		break;

	case 3:
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PROPERTY_LEVEL_THREE);
		break;
	}

	if (location < 10) std::cout << "0";
	std::cout << location << "." << name;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), PROPERTY_LEVEL_ZERO);

	if (owner != -1)
	{
		COORD xy_owner = { location_xy.X + 6, location_xy.Y + 3 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_owner);
		std::cout << owner + 1;
	}

	if (roadBlock_exist)
	{
		COORD xy_roadBlock = { location_xy.X + 6, location_xy.Y + 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_roadBlock);
		std::cout << "|";
	}
	else
	{
		COORD xy_roadBlock = { location_xy.X + 6, location_xy.Y + 2 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy_roadBlock);
		std::cout << " ";
	}
	

}

void property_t::resetProperty()
{
	name = "";
	initialPrice = level = 0;
	toll[0] = toll[1] = toll[2] = toll[3] = 0;
	owner = -1;
	roadBlock_exist = false;
}