#pragma once
#include <iostream>

class Player
{
public:
	std::string _name;
	int _x;
	int _y;

	Player(const std::string name = "defaultName")
	{
		_name = name;
	}

	void attack()
	{
		std::cout << "BOOM!!\n";
	}

	void SetPosition(int x, int y)
	{
		_x = x;
		_y = y;

	}
};

void RegisterPlayer(lua_State * ls);
