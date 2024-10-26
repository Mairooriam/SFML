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
    static bool debugEnabled;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosWorld;
    int worldScale = 16;
    void handleMouseEvent(sf::Event& event);
    void update(sf::Time deltaTime);
    void updateMousePos(int x, int y);
    void render();
    void initMap(size_t mapSize, sf::Vector2f nodeSize, float offset);
    std::vector<std::vector<Node>> map;
    ResourceManager& resourceManager = ResourceManager::getInstance();
    Node& getNodeAtPosition();
    
    sf::RenderWindow window;
    // Methods to enable/disable debug printing
    static void enableDebug() { debugEnabled = true; }
    static void disableDebug() { debugEnabled = false; }
    
    // Debug print method
    static void debugPrint(const std::string& message) {
        if (debugEnabled) {
            std::cout << message << std::endl;
        }
    }
};

#endif // GAME_HPP