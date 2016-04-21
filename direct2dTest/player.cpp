#pragma once

#include "Engine.h"
#include "Player.h"
#include <iostream>



int createPlayer(lua_State* lua)
{
	const char* name = lua_tolstring(lua, 1, nullptr);

	if (name != nullptr)
	{
		Player** player = reinterpret_cast<Player**>(lua_newuserdata(lua, sizeof(Player*)));
		*player = new Player(name);

		luaL_getmetatable(lua, "MetaPlayer");
		lua_setmetatable(lua, -2);

		std::cout << "[C++] Created player - " << name << std::endl;
	}
	else
	{
		std::cout << "[C++][ERROR] player not created" << std::endl;

	}

	return 1;

}

Player* l_CheckPlayer(lua_State* lua, int nr)
{
	Player* player = nullptr;
	void* ptr = luaL_testudata(lua, nr, "MetaPlayer");

	if (ptr != nullptr)
	{
		player = *(Player**)ptr;
	}
	return player;
}


int player_destroy(lua_State* lua)
{
	Player* player = l_CheckPlayer(lua, 1);
	delete player;
	return 0;
}

int player_getName(lua_State* lua)
{
	
	Player* p = l_CheckPlayer(lua, 1);
	lua_pushstring(lua, p->_name.c_str());

	return 1;

}

int player_setPos(lua_State* lua)
{
	Player* p = l_CheckPlayer(lua, 1);
	float x = lua_tonumber(lua, 2);
	float y = lua_tonumber(lua, 3);
	p->SetPosition(x, y);
	return 0;
}

void RegisterPlayer(lua_State* ls)
{
	// Create a luaL metatable. This metatable is not 
	// exposed to Lua. The "luaL_Foo" label is used by luaL
	// internally to identity things.
	luaL_newmetatable(ls, "MetaPlayer");
	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "MetaMonster"   |-1


	luaL_Reg sMonsterRegs[] =
	{
		{ "New",			createPlayer },
		{ "getName",		player_getName },
		{ "setPos",			player_setPos },
		{ "__gc",			player_destroy },
		{ NULL, NULL }
	};

	// Register the C functions _into_ the metatable we just created.
	luaL_setfuncs(ls, sMonsterRegs, 0);

	lua_pushvalue(ls, -1);

	// The Lua stack at this point looks like this:
	//     
	//     2| metatable "MetaMonster"   |-1
	//     1| metatable "MetaMonster"   |-2

	// Set the "__index" field of the metatable to point to itself
	// This pops the stack
	lua_setfield(ls, -1, "__index");

	// The Lua stack at this point looks like this:
	//     
	//     1| metatable "MetaMonster"   |-1

	// The luaL_Foo metatable now has the following fields
	//     - __gc
	//     - __index
	//     - add
	//     - print
	//     - new

	// Now we use setglobal to officially expose the luaL_Foo metatable 
	// to Lua. And we use the name "Monster".
	//
	// This allows Lua scripts to _override_ the metatable of Monster.
	// For high security code this may not be called for but 
	// we'll do this to get greater flexibility.
	lua_setglobal(ls, "Player");
}