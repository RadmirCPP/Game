#include "Enemy.h"

Enemy::Enemy(sf::Vector2f position, const std::string& path) {

	if (!texture.loadFromFile(path)) {
		std::cerr << "Failed to load texture from: " << path << "\n";
	}
	sprite.setTexture(texture, true);
	sprite.setPosition(position);

	SeeBox.setRadius(200);
	float SeeBoxRadius = SeeBox.getRadius();

	SeeBox.setOutlineThickness(3);
	SeeBox.setFillColor(sf::Color::Transparent);
	SeeBox.setOutlineColor(sf::Color::Red);
	sf::Vector2f SpritePosition = sprite.getPosition();
	SeeBox.setOrigin({ SeeBoxRadius, SeeBoxRadius, });
	
	sf::Vector2f SpriteSize = sprite.getGlobalBounds().size;

	SeeBox.setPosition({ SpritePosition.x + SpriteSize.x/2, SpritePosition.y + SpriteSize.y / 2 });
	
}
void Enemy::draw(sf::RenderWindow& window) {
	window.draw(sprite);
	window.draw(SeeBox);
}
sf::Vector2f Enemy::inBounds(sf::FloatRect PlayerPosition) const {
	sf::Vector2f circleCenter = SeeBox.getPosition(); // если origin = radius,radius
	float PlayerCenterX = PlayerPosition.size.x/ 2;
	float PlayerCenterY = PlayerPosition.size.y / 2;
	float nearestX = std::max(PlayerPosition.position.x+ PlayerCenterX,
		std::min(circleCenter.x, PlayerPosition.position.x+ PlayerCenterX));
	float nearestY = std::max(PlayerPosition.position.y+ PlayerCenterY,
		std::min(circleCenter.y, PlayerPosition.position.y+ PlayerCenterY));
	


	float dx = circleCenter.x - nearestX;
	float dy = circleCenter.y - nearestY;
	
	
	float triggerRadius = SeeBox.getRadius();
	

	
	if (dx * dx + dy * dy <= triggerRadius * triggerRadius) {
		return{dx,dy};
	}
	

	return {};
}
sf::Vector2f Enemy::dummAI(sf::Vector2f dir, float& TickSpeed) {

	if (dir.x == 0 && dir.y == 0) {
		return {0,0};
	}
	float speed = 200;
	
	sf::Vector2f spritePos = sprite.getPosition();
	float length = sqrt(dir.x * dir.x + dir.y * dir.y);

	if (length != 0) {
		dir.x /= length;
		dir.y /= length;
	}

	return { -dir.x * speed * TickSpeed, -dir.y * speed * TickSpeed };

	
	
}

void Enemy::setMovement(sf::Vector2f& pos) {
	sprite.move(pos);
	SeeBox.move(pos);
}

sf::FloatRect Enemy::getNextBounds(const sf::Vector2f& move) const {


	sf::FloatRect bounds = sprite.getGlobalBounds();
	

	bounds.position.x += move.x;
	bounds.position.y += move.y;
	sf::Vector2f change = bounds.position;
	return bounds;
}

Enemy::~Enemy()
{
}