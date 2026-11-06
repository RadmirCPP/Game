#include "Player.h"
Player::Player(const std::string& texturePath, sf::Vector2f position) : Move(350.f), FastMove(520.f)

{
    
    
    if (!texture.loadFromFile(texturePath)) {
        std::cerr << "Failed to load texture from: " << texturePath << "\n";
    }

    sprite.setTexture(texture, true);
    sprite.setPosition(position);
    sprite.setOrigin({texture.getSize().x / 2.f, texture.getSize().y / 2.f});
  
    
}
 
sf::Vector2f Player::offset(float deltatime) {
	float speed = getCurrentSpeed();

    float speedPerDelta = speed * deltatime;
    sf::Vector2f direction{0,0};
    sf::Vector2f position = sprite.getPosition();
    
    if (canWalkXneg) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            direction.x -= speedPerDelta;
        }
    }
    if (canWalkX){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            direction.x += speedPerDelta;
        }
    }

    if (canWalkYneg) {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
            direction.y -= speedPerDelta;
        }
    }
    if(canWalkY){
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::S)) {
            direction.y += speedPerDelta;
        }
    }
    
  
   
    return direction;

}
// OFFSET HERE ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
sf::FloatRect Player::getNextBounds(float deltaTime)  {

    sf::Vector2f move = offset(deltaTime);
    sf::FloatRect bounds = sprite.getGlobalBounds();
    float left = bounds.position.x;
    float top = bounds.position.y;
    float width = bounds.size.x;
    float height = bounds.size.y;
    
    bounds.position.x += move.x;
    bounds.position.y += move.y;
    sf::Vector2f change = bounds.position;
    return bounds;
}
void Player::tryMove(float deltaTime, TileMap& Map) {
    sf::Vector2f moveDir = offset(deltaTime);
    sf::FloatRect hitbox = sprite.getGlobalBounds();
  
    

    // --- шаг 1: движение по X ---
    sprite.move({ moveDir.x, 0.f });
    if (!Map.isWalkable(sprite.getGlobalBounds())) {
        sprite.move({-moveDir.x, 0.f}); // откат
    }

    // --- шаг 2: движение по Y ---
    sprite.move({ 0.f, moveDir.y });
    if (!Map.isWalkable(sprite.getGlobalBounds())) {
        sprite.move({ 0.f, -moveDir.y }); // откат
    }

    

}

    
void Player::update(const sf::RenderWindow& window) {

}
void Player::draw(sf::RenderWindow& window) {
    window.draw(sprite);
}

float Player::getCurrentSpeed() const {
    return boost ? FastMove : Move;
    
}

