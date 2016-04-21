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

	int frameCount;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
	void runLuaFunction(char* functionName);//only works on void functions
public:
	Engine();
	~Engine();


	void addObject(Object * object) {
		this->objects.push_back(object);
	}
	lua_State* getLua() {
		return this->lua;}

	void update(float dt);
	void keyboard();
	bool collision(Object* obj1, Object* obj2);

};
