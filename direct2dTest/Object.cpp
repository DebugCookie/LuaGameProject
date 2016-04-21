#include "Object.h"
#include <iostream>
#include "global.h"

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	target.draw(this->boundingbox);
}

Object::Object(std::string texture)
{
	
	this->texture.loadFromFile(texture);
	//this->texture.loadFromFile("sprites/magnemite.png", sf::IntRect(0, 0, 32, 32));
	this->sprite.setTexture(this->texture);
	this->spriteSquares.push_back(sf::IntRect(0, 0, 32, 32));
	this->spriteSquares.push_back(sf::IntRect(32, 0, 32, 32));
	this->spriteSquares.push_back(sf::IntRect(64, 0, 32, 32));
	this->spriteCount = 0;
	this->textureSource = texture;


	this->boundingbox.setSize(sf::Vector2f(this->size.x, this->size.y));
	this->boundingbox.setFillColor(sf::Color(150, 50, 250));
	this->boundingbox.setOutlineThickness(10);
	this->boundingbox.setOutlineColor(sf::Color(250, 150, 100));
}

Object::~Object()
{
	
}

void Object::animate(float dt, int frameCount, int frameSpace)
{
	
	if (frameCount % frameSpace * dt == 0)
	{
		this->texture.loadFromFile(this->textureSource, this->spriteSquares[this->spriteCount]);
		this->spriteCount++;
		this->spriteCount = this->spriteCount % this->spriteSquares.size();
	}
}

sf::Sprite Object::getSprite() const
{
	return this->sprite;
}

VectorFloat2 Object::getPos() const
{
	return this->pos;
}

VectorFloat2 Object::getSize() const
{
	return this->size;
}

void Object::setPos(float x, float y)
{

	this->pos.x = x;
	this->pos.y = y;

	this->sprite.setPosition(x, y);
}

void Object::setSize(float width, float height)
{
	this->size.x = width;
	this->size.y = height;
}

