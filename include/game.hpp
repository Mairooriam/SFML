#ifndef GAME_HPP
#define GAME_HPP

#include "ResourceManager.hpp"
#include "GameStateManager.hpp"
#include "node.hpp"
#include "operatorUtils.hpp"
#include <memory> // Include the memory header for std::shared_ptr
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
    
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosWorld;
    std::shared_ptr<int> worldScale; // Use shared_ptr for worldScale


    void handleMouseEvent(sf::Event& event);
    void handleKeyEvent(sf::Event &event);

    void update(sf::Time deltaTime);
    void updateMousePos(int x, int y);
    void updateCurrentlyWallNodes();
    void updateMapScale();
    
    void addNodeToCurrentlyWallNodesMap(Node* node);
    std::unordered_map<sf::Vector2f, Node*, std::hash<sf::Vector2f>> currentlyWallNodesMap;
   
    void render();
    sf::RenderWindow window;

    Node& getNodeAtPosition();
    ResourceManager& resourceManager = ResourceManager::getInstance();
    
    void initMap(size_t mapSize);
    std::vector<std::vector<Node>> map;
    
    // Methods to enable/disable debug printing
    void populateNodeNeighbours();
    void setWorldScale(int newScale);
    void printCurrentlyWallNodesMap() const;
    // Debug print method
    static void debugPrint(const std::string& message) {
        if (debugEnabled) {
            std::cout << message << std::endl;
        }
    }
    static void enableDebug() { debugEnabled = true; }
    static void disableDebug() { debugEnabled = false; }
    static bool debugEnabled;
};

#endif // GAME_HPP