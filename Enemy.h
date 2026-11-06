#pragma once
#include "iostream"
#include <cmath>
#include <SFML/Graphics.hpp>

class Enemy
{
public:
	Enemy( sf::Vector2f position, const std::string& path);
	~Enemy();
	sf::Texture texture{ { (unsigned int)64, 64} };
	sf::Sprite sprite{ texture };
	sf::Vector2f position;
	bool canGoX = true;
	bool canGoY = true;
	sf::CircleShape SeeBox;
	std::vector<int> collision;
	sf::Vector2f inBounds(sf::FloatRect playerPos) const;
	sf::Vector2f dummAI(sf::Vector2f dir,float &TickSpeed);
	void draw(sf::RenderWindow& window);
	void setMovement(sf::Vector2f& Pos);
	sf::FloatRect getNextBounds(const sf::Vector2f& move)const;
	
private:

};



