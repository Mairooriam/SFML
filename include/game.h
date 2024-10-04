#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include <SFML/Window/Mouse.hpp>
class Game {
public:
    Game();
    void run();
    sf::RenderWindow window;
    sf::Mouse mouse;
    sf::Text text;
    
private:
    void processEvents();
    void update(sf::Time totalElapsedTime);
    void render();

    
    std::vector<Ball> balls;
    sf::Time totalElapsedTime;
    sf::View view;
};

#endif // GAME_H