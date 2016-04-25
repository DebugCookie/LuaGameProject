#include <SFML/Graphics.hpp>
#include "Engine.h"

Engine* engine = nullptr;


int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	sf::RenderWindow window(sf::VideoMode(600, 400), "Lua game");
	engine = new Engine();
	int error = luaL_loadfile(engine->getLua(), "main.lua") || lua_pcall(engine->getLua(), 0, 0, 0);

	sf::Clock clock;
	float dt = 0;


	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}


		dt = clock.restart().asSeconds();

		

		engine->update(dt);


		window.clear();
		window.draw(*engine);
		window.display();
	}

	lua_close(engine->getLua());
	delete engine;
	return 0;
}

int object_create(lua_State* lua)
{
	const char* name = lua_tolstring(lua, 1, nullptr);
	Object** object = reinterpret_cast<Object**>(lua_newuserdata(lua, sizeof(Object*)));


	if (name != nullptr)
	{
		*object = new Object(name);

		engine->addObject(*object);


		luaL_getmetatable(lua, "MetaObject");
		lua_setmetatable(lua, -2);



		std::cout << "[C++] Created object - " << name << std::endl;
	}
	else
	{

		*object = new Object();

		engine->addObject(*object);

		luaL_getmetatable(lua, "MetaObject");
		lua_setmetatable(lua, -2);


		std::cout << "[C++] Default object created" << std::endl;

	}

	(*object)->setSize((*object)->getTexture()->getSize().x, (*object)->getTexture()->getSize().y);

	return 1;

}

Object* l_CheckObject(lua_State* lua, int nr)
{
	Object* object = nullptr;
	void* ptr = luaL_testudata(lua, nr, "MetaObject");

	if (ptr != nullptr)
	{
		object = *(Object**)ptr;
	}
	return object;
}

int object_destroy(lua_State* lua)
{
	Object* object = l_CheckObject(lua, 1);
	delete object;
	return 0;
}

int object_setPos(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);
	float x = lua_tonumber(lua, 2);
	float y = lua_tonumber(lua, 3);
	o->setPos(x, y);
	return 0;
}

int object_getPos(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);

	lua_pushnumber(lua, o->getPos().x);
	lua_pushnumber(lua, o->getPos().y);
	return 2;
}

int object_getPosX(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);

	lua_pushnumber(lua, o->getPos().x);
	return 1;
}

int object_getPosY(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);

	lua_pushnumber(lua, o->getPos().y);
	return 1;
}

int object_collision(lua_State* lua)
{
	Object* o1 = l_CheckObject(lua, 1);
	Object* o2 = l_CheckObject(lua, 2);


	lua_pushboolean(lua, engine->collision(o1, o2));

	return 1;
}

int object_setSize(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);
	float x = lua_tonumber(lua, 2);
	float y = lua_tonumber(lua, 3);
	o->setSize(x, y);
	return 0;
}

int object_addSpriteState(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);

	lua_pushnumber(lua, o->addSpriteState());

	return 1;
}

int object_addToSpriteState(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);

	lua_pushboolean(lua,
		o->addSpriteToSpriteState(lua_tonumber(lua, 2), lua_tonumber(lua, 3),
			lua_tonumber(lua, 4), lua_tonumber(lua, 5), lua_tonumber(lua, 6)));

	return 1;
}

int object_setSpriteState(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);
	o->setSpriteState(lua_tonumber(lua, 2));

	return 0;
}

int object_setTextureOffset(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);
	o->setTextureOffset(lua_tonumber(lua, 2),
		lua_tonumber(lua, 3));

	return 0;
}

int object_setVisableBB(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);
	o->setVisableBoundingBox(lua_tonumber(lua, 2));

	return 0;
}

int object_ToggleVisableBB(lua_State* lua)
{
	Object* o = l_CheckObject(lua, 1);
	o->toggleVisableBoundingBox();

	return 0;
}


void RegisterObject(lua_State* lua)
{
	luaL_newmetatable(lua, "MetaObject");


	luaL_Reg sMonsterRegs[] =
	{
		{ "New",			object_create },

		//seters
		{ "setPos",			object_setPos },
		{ "setSize",		object_setSize },
		{ "setSpriteState",	object_setSpriteState },
		{ "setTextureOffset",	object_setTextureOffset },
		{ "setVisableBB",	object_setVisableBB },

		//getters
		{ "getPos",			object_getPos },
		{ "getPosX",		object_getPosX },
		{ "getPosY",		object_getPosY },

		{ "addSpriteState",	object_addSpriteState },
		{ "addToSpriteState",	object_addToSpriteState },
		{ "toggleVisableBB",	object_ToggleVisableBB },

		{ "collision",		object_collision },
		{ "__gc",			object_destroy },
		{ NULL, NULL }
	};

	luaL_setfuncs(lua, sMonsterRegs, 0);

	lua_pushvalue(lua, -1);

	lua_setfield(lua, -1, "__index");

	lua_setglobal(lua, "Object");
}

