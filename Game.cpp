
#include "Game.h"

int main()
{
    
    TileMap Map; // MapMaker
    Enemy TestEnemy({ 850.f,850.f }, "assets/Enemy.png");
    Player player("assets/player.png", { Map.Map_Width*16, Map.Map_Height*16 });
    
    WindowHelpLogic Win_help;
    sf::Clock deltaClock;
    unsigned int width = 620;
    unsigned int height = 360;
    auto window = std::make_unique<sf::RenderWindow>(sf::VideoMode({ width, height }), "asd");
    window->setVerticalSyncEnabled(1);
    
    bool canPlayerWalk = true;
    while (window->isOpen()) {
        float deltaTime = deltaClock.restart().asSeconds();
       
        while (const std::optional event = window->pollEvent()) {

            if (event->is<sf::Event::KeyPressed>()) {


                if (auto keyEvent = event->getIf<sf::Event::KeyPressed>()) {
                    Map.handlePressKey(keyEvent->code);
                }
            }
            if (event->is<sf::Event::Closed>()) {
                window->close();



            }
          //  if (event->is<sf::Event::Resized>()) { Win_help.ViewAdjust(*window); }
        }
        sf::Vector2u window_Size = window->getSize();


        Map.handleClick(*window);
        //Kool sheat
        window->clear();
       
       
        sf::View view;
        float changer = 1.89f;
        view.setSize({620* changer,360* changer });     //fucking
        view.setCenter(player.sprite.getPosition());    //poggies
        window->setView(view);                          //lines
            

        
        Map.drawAll(*window, view);//has to be first, otherwise it will cover everything
       
        player.draw(*window);
        TestEnemy.draw(*window);
           
        sf::Vector2f dirToPlayer = TestEnemy.inBounds(player.sprite.getGlobalBounds());
        
        sf::Vector2f desiredMove = TestEnemy.dummAI(dirToPlayer,deltaTime);
       
        sf::FloatRect nextBounds = TestEnemy.getNextBounds(desiredMove);
        bool canEnemyWalk = Map.isWalkable(nextBounds);
        if (canEnemyWalk) {
        
            TestEnemy.setMovement(desiredMove);
			
        }
        else {
            sf::Vector2f ifMove = Map.CanMove(TestEnemy.sprite, desiredMove);
            std::cout << ifMove.x << " x and y " << ifMove.y << "\n";
            TestEnemy.setMovement(ifMove);
			
        }
                
                player.tryMove(deltaTime, Map);
                player.boost = Map.isRoad;
        window->display(); 
    }

}

