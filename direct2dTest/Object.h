#pragma once
#include <SFML\Graphics.hpp>
#include "structs.h"
#include "lua.hpp"

class Object : public sf::Drawable 
{
private:
	VectorFloat2 pos;
	VectorFloat2 size;
	sf::Texture texture;
	sf::Sprite sprite;
	sf::RectangleShape boundingbox;
	std::vector<sf::IntRect> spriteSquares;
	int spriteCount;
	std::string textureSource;


	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Object(std::string texture = "default.png");
	~Object();

	void animate(float dt, int frameCount, int frameSpace = 0);

	//setters
	void setPos(float x ,float y);
	void setSize(float width, float height);

	//getters
	sf::Sprite getSprite()const;
	VectorFloat2 getPos()const;
	VectorFloat2 getSize()const;
	sf::Texture* getTexture() {
		return &this->texture;}
};