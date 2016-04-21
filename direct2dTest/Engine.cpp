#include "Engine.h"


void Engine::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		target.draw(*this->objects[i], states);
	}
}

void Engine::runLuaFunction(char* functionName)
{
	lua_getglobal(this->lua, functionName);
	int error = lua_pcall(this->lua, 0, 0, 0);
	if (error)
	{
		std::cout << "[C++][ERROR] function " << functionName << std::endl;
		std::cout << "\t[lua][ERROR]" << lua_tostring(lua, -1) << std::endl;
		lua_pop(lua, -1);
	}
}

void RegisterObject(lua_State* lua);


Engine::Engine()
{
	this->lua = luaL_newstate();
	luaL_openlibs(lua);
	RegisterObject(lua);
	this->frameCount = 0;

}

Engine::~Engine()
{

}

void Engine::update(float dt)
{
	this->keyboard();
	lua_pushnumber(lua, this->frameCount);
	lua_setglobal(lua, "frameCount");


	this->runLuaFunction("update");

	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->animate(dt, this->frameCount, 500);
	}

	this->frameCount++;
}

void Engine::keyboard()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//left
	{
		this->runLuaFunction("LeftPressed");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//right
	{
		this->runLuaFunction("RightPressed");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//up
	{
		this->runLuaFunction("UpPressed");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//dwon
	{
		this->runLuaFunction("DownPressed");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//esc
	{
		this->runLuaFunction("EscPressed");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//a
	{
		this->runLuaFunction("APressed");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//d
	{
		this->runLuaFunction("DPressed");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//w
	{
		this->runLuaFunction("WPressed");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//s
	{
		this->runLuaFunction("SPressed");
	}
}

bool Engine::collision(Object * obj1, Object * obj2)
{
	if (obj1->getPos().x > obj2->getPos().x &&
		obj1->getPos().x < obj2->getPos().x + obj2->getSize().x &&
		obj1->getPos().y > obj2->getPos().y &&
		obj1->getPos().y < obj2->getPos().y + obj2->getSize().y)
	{
		return true;
	}

	return false;
}

