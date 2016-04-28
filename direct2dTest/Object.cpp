#include "Object.h"
#include <iostream>
#include "global.h"

void Object::draw(sf::RenderTarget & target, sf::RenderStates states) const
{
	target.draw(this->sprite);
	if (this->hitboxVisable)
	{
		target.draw(this->visualBoundingbox);
	}
	
}

Object::Object(int index, std::string texture)
{
	this->myIndex = index;
	this->texture.loadFromFile(texture);
	this->sprite.setTexture(this->texture);
	this->spriteCount = 0;
	this->textureSource = texture;
	this->currentSpriteState = 0;
	this->animateCount = 1;

	this->size.x = 1;
	this->size.y = 1;

	this->hitboxVisable = true;
	this->b_animate = false;
	this->stretchTexture = true;

	this->visualBoundingbox.setSize(sf::Vector2f(this->size.x, this->size.y));
	this->visualBoundingbox.setFillColor(sf::Color(0, 0, 0, 0));
	this->visualBoundingbox.setOutlineThickness(-1);
	this->visualBoundingbox.setOutlineColor(sf::Color(255, 0, 0));


}

Object::~Object()
{
	for (int i = 0; i < this->sprites.size(); i++)
	{
		for (int j = 0; j < this->sprites[i].size(); j++)
		{
			delete this->sprites[i][j];
		}
	}
}

void Object::animate(float dt)
{
	this->animateCount += dt;
	if (this->animateCount >= 0.2f && this->sprites[this->spriteCount].size() > 0 && this->b_animate)
	{
		this->sprite.setTexture(*this->sprites[this->currentSpriteState][this->spriteCount]);
		this->spriteCount++;
		if (this->spriteCount >= this->sprites[this->currentSpriteState].size())
		{
			this->spriteCount = 0;
		}
		this->animateCount = 0;
	}
}

int Object::addSpriteState()
{
	int index = this->sprites.size();
	this->sprites.push_back(std::vector<sf::Texture*>());


	return index;
}

bool Object::addSpriteToSpriteState(int x, int y, int width, int height, int index)
{
	if (this->sprites.size() >= index)//does the index exist
	{
		sf::Texture* insert = new sf::Texture();
		insert->loadFromFile(this->textureSource, sf::IntRect(x, y, height, width));
		this->sprites[index].push_back(insert);


		return true;
	}

	return false;
}

void Object::removeSpritetate(int index)
{
	for (int i = 0; i < this->sprites[index].size(); i++)
	{
		delete this->sprites[index][i];
	}
	this->sprites.erase(this->sprites.begin() + index);
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

	this->sprite.setPosition(x + this->textureOffset.x, y + this->textureOffset.y);
	this->visualBoundingbox.setPosition(x, y);
}

void Object::setSize(float width, float height)
{
	this->size.x = width;
	this->size.y = height;
	this->visualBoundingbox.setSize(sf::Vector2f(this->size.x, this->size.y));
	if (this->stretchTexture)
	{
		this->sprite.setScale((float)this->size.x / (float)this->texture.getSize().x,
			(float)this->size.y / (float)this->texture.getSize().y);
	}
}

