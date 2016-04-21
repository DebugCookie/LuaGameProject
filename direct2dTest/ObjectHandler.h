#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Object.h"


class ObjectHandler : public sf::Drawable
{
private:
	std::vector<Object*> objects;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	ObjectHandler();
	~ObjectHandler();

	bool collision(int index1, int index2);

	void addObject(Object* object);

};