#ifndef GAME_HPP
#define GAME_HPP

#include "ResourceManager.hpp"
#include "GameStateManager.hpp"
#include "node.hpp"
class Game {
public:
static Game& getInstance() {
        static Game instance;
        return instance;
    }
    Game();
   // ~Game();
    void printMap();
    void run();
    void drawMap();
    std::vector<std::vector<Node>> map;
private:
    void processEvents();
    void update();
    void render();
    void initMap(size_t mapSize, sf::Vector2f nodeSize, float offset);
    
    ResourceManager& resourceManager = ResourceManager::getInstance();
    GameStateManager stateManager;
    
    sf::RenderWindow window;
};

#endif // GAME_HPP