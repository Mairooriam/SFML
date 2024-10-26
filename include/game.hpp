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
    sf::RenderWindow& getRenderWindow();
    std::vector<std::vector<Node>>& getMap();
private:
    Node& checkMouseCollisions();
    void update();
    void render();
    void initMap(size_t mapSize, sf::Vector2f nodeSize, float offset);
    std::vector<std::vector<Node>> map;
    ResourceManager& resourceManager = ResourceManager::getInstance();
    GameStateManager gameStateManager;
    
    sf::RenderWindow window;

    // Debug print method
    static void debugPrint(const std::string& message) {
        if (debugEnabled) {
            std::cout << message << std::endl;
        }
    }
};

#endif // GAME_HPP