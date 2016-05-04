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
	sf::RectangleShape visualBoundingbox;
	int spriteCount;
	std::string textureSource;
	std::vector<std::vector<sf::Texture*>> sprites;

	VectorFloat2 textureOffset;
	bool hitboxVisable;
	int currentSpriteState;
	bool b_animate;
	int myIndex;
	bool stretchTexture;
	float animateCount;

	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;
public:
	Object(int index, std::string texture = "default.png");
	~Object();

	void animate(float dt);
	int addSpriteState();
	bool addSpriteToSpriteState(int x, int y, int width, int height, int index);
	void removeSpritetate(int index = 0);

	//setters
	void setPos(float x, float y);
	void setSize(float width, float height);
	void setSpriteState(int state) { this->currentSpriteState = state; }

	void setTextureOffset(int x, int y) {
		this->textureOffset.y = y;
		this->textureOffset.x = x;
		this->sprite.setPosition(this->pos.x + x, this->pos.y + y);
	}
	void setVisableBoundingBox(bool visable) { this->hitboxVisable = visable; }

	void toggleVisableBoundingBox() {
		if (this->hitboxVisable)
			this->hitboxVisable = false;
		else
			this->hitboxVisable = true;
	}
	void setAnimated(bool a) { this->b_animate = a; }
	void setMyIndex(int index) { this->myIndex = index; }
	void setAutoScale(bool s) { this->stretchTexture = s; }

	//getters
	sf::Sprite getSprite()const;
	VectorFloat2 getPos()const;
	VectorFloat2 getSize()const;
	sf::Texture* getTexture() { return &this->texture; }
	int getMyIndex() { return this->myIndex; }
};