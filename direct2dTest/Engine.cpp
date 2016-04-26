#include "Engine.h"

int none(lua_State* lua) { return 0; }//used as default function global

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

	if (error && lua_tostring(lua, -1) == "attempt to call a nil value")//setting default lua function //funkar ej
	{
		lua_pushcfunction(lua, none);
		lua_setglobal(lua, functionName);
	}
	if (error)
	{

		std::cout << "[C++][ERROR] function " << functionName << std::endl;
		std::cout << "\t[lua][ERROR]" << lua_tostring(lua, -1) << std::endl;
		lua_pop(lua, -1);
	}
}

void RegisterObject(lua_State* lua);


Engine::Engine(sf::RenderWindow* window)
{
	this->window = window;
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

	lua_pushnumber(lua, dt);
	lua_setglobal(lua, "dt");

	this->runLuaFunction("update");

	for (int i = 0; i < this->objects.size(); i++)
	{
		this->objects[i]->animate(dt, this->frameCount, 500);
	}

	this->frameCount++;
}


void Engine::keyboard()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))//left
	{
		this->runLuaFunction("MouseLeftPressed");
	}
	else {
		this->runLuaFunction("MouseLeftReleased");
	}


	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//left
	{
		this->runLuaFunction("LeftPressed");
	}
	else {
		this->runLuaFunction("LeftReleased");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))//right
	{
		this->runLuaFunction("RightPressed");
	}
	else {
		this->runLuaFunction("RightReleased");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//up
	{
		this->runLuaFunction("UpPressed");
	}
	else {
		this->runLuaFunction("UpReleased");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))//dwon
	{
		this->runLuaFunction("DownPressed");
	}
	else {
		this->runLuaFunction("DownReleased");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))//esc
	{
		this->runLuaFunction("EscPressed");
	}
	else {
		this->runLuaFunction("EscReleased");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))//a
	{
		this->runLuaFunction("APressed");
	}
	else {
		this->runLuaFunction("AReleased");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))//d
	{
		this->runLuaFunction("DPressed");
	}
	else {
		this->runLuaFunction("DReleased");
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))//w
	{
		this->runLuaFunction("WPressed");
	}
	else {
		this->runLuaFunction("WReleased");
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))//s
	{
		this->runLuaFunction("SPressed");
	}
	else {
		this->runLuaFunction("SReleased");
	}
}

bool Engine::collision(Object * obj1, Object * obj2)
{
	if (((obj1->getPos().x > obj2->getPos().x &&
		obj1->getPos().x < obj2->getPos().x + obj2->getSize().x) ||
		(obj1->getPos().x + obj1->getSize().x > obj2->getPos().x &&
			obj1->getPos().x + obj1->getSize().x < obj2->getPos().x + obj2->getSize().x))
		&&
		((obj1->getPos().y > obj2->getPos().y &&
			obj1->getPos().y < obj2->getPos().y + obj2->getSize().y) ||
			(obj1->getPos().y + obj1->getSize().y > obj2->getPos().y &&
				obj1->getPos().y + obj1->getSize().y < obj2->getPos().y + obj2->getSize().y)))
	{
		return true;
	}else if (((obj2->getPos().x > obj1->getPos().x &&
		obj2->getPos().x < obj1->getPos().x + obj1->getSize().x) ||
		(obj2->getPos().x + obj2->getSize().x > obj1->getPos().x &&
			obj2->getPos().x + obj2->getSize().x < obj1->getPos().x + obj1->getSize().x))
		&&
		((obj2->getPos().y > obj1->getPos().y &&
			obj2->getPos().y < obj1->getPos().y + obj1->getSize().y) ||
			(obj2->getPos().y + obj2->getSize().y > obj1->getPos().y &&
				obj2->getPos().y + obj2->getSize().y < obj1->getPos().y + obj1->getSize().y)))
	{
		return true;
	}

	return false;
}

