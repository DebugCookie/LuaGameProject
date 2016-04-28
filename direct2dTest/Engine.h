#pragma once
#include <SFML\Graphics.hpp>
#include "Object.h"
#include "lua.hpp"
#include "Player.h"

class Engine : public sf::Drawable
{
private:
	std::vector<Object*> objects;

	lua_State* lua;
	float timeCount;
	sf::RenderWindow* window;


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void runLuaFunction(char* functionName);//only works on void functions
public:
	Engine(sf::RenderWindow* window);
	~Engine();


	void addObject(Object* obj, std::string name = "default.png");
	lua_State* getLua() {
		return this->lua;}

	void update(float dt);
	void keyboard();
	bool collision(Object* obj1, Object* obj2);
	bool collision(Object* obj, float x, float y);
	sf::Vector2i getMousePos() {return sf::Mouse::getPosition(*this->window);}
	int getNrOfObj() { return this->objects.size(); }
	void removeObj(int index) {
		this->objects.erase(this->objects.begin() + index);
	}

};
