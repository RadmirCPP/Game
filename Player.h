#pragma once
#include "SFML/Graphics.hpp"
#include "iostream"
#include "MapMaker.h"
class Player
{
public:
	Player(const std::string& texturePath, sf::Vector2f position);
	void update(const sf::RenderWindow& window);
	void draw(sf::RenderWindow& window);

	void tryMove(float speed, TileMap& Map);
	sf::Vector2f offset(float deltatime);
	sf::Texture texture{{ (unsigned int)64, 64}};
	sf::Sprite sprite{texture};
	sf::FloatRect getNextBounds(float deltaTime) ;
	float getCurrentSpeed() const ;
	bool canWalkX = true;
	bool canWalkY = true;
	bool canWalkXneg = true;
	bool canWalkYneg = true;
	bool boost = false;
	float speed=350;
private:
	float Move = 350;
	float FastMove = 520;
	
};

