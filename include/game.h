#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"

class Game {
public:
    Game();
    void run();

private:
    void processEvents();
    void update(sf::Time totalElapsedTime);
    void render();

    sf::RenderWindow window;
    std::vector<Ball> balls;
    sf::Time totalElapsedTime;
    sf::View view;
};

#endif // GAME_H