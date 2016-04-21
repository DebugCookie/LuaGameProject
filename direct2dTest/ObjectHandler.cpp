#include "ObjectHandler.h"

ObjectHandler::ObjectHandler()
{

}

ObjectHandler::~ObjectHandler()
{
	for (int i = 0; i < objects.size(); i++)
	{
		delete objects[i];
	}
}

bool ObjectHandler::collision(int index1, int index2)
{
	if (this->objects[index1]->getPos().x > this->objects[index2]->getPos().x && 
		this->objects[index1]->getPos().x < this->objects[index2]->getPos().x + this->objects[index2]->getSize().x &&
		this->objects[index1]->getPos().y > this->objects[index2]->getPos().y &&
		this->objects[index1]->getPos().y < this->objects[index2]->getPos().y + this->objects[index2]->getSize().y)
	{
		return true;
	}

	return false;
}

void ObjectHandler::addObject(Object * object)
{
	this->objects.push_back(object);
}

void ObjectHandler::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	for (int i = 0; i < this->objects.size(); i++)
	{
		target.draw(*this->objects[i], states);
	}
}


