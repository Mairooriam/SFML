#ifndef GAME_HPP
#define GAME_HPP

#include "ResourceManager.hpp"
#include "GameStateManager.hpp"
#include "node.hpp"
#include "operatorUtils.hpp"
#include <memory> // Include the memory header for std::shared_ptr
#include "AStar.hpp"

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
    void drawMapText();
    void drawPathStep(Node* step);
    void drawPathAnimation();
    void drawPathFull(std::vector<Node*>& path);
    sf::RenderWindow& getRenderWindow();
    std::vector<std::vector<Node>>& getMap();
    int tempDebugthingy = 0;
    // Add public getter methods for worldScale, offsetX, and offsetY
    float getWorldScale() const { return *worldScale; }
    float getOffsetX() const { return *mapOffsetX; }
    float getOffsetY() const { return *mapOffsetY; }
    
    // A STAR STUFF
    Node* startNode = nullptr;
    Node* endNode = nullptr;
private:
    sf::Time accumulatedTime;
    sf::Vector2i mousePosWindow;
    sf::Vector2i mousePosWorld;
    std::shared_ptr<int> worldScale; // Use shared_ptr for worldScale
    bool mouseOneDown = false;
    sf::Vector2f mousePosTemp;
    void handleMouseEvent(sf::Event& event);
    void handleKeyEvent(sf::Event &event);

    void update(sf::Time deltaTime);
    void updateMousePos(int x, int y);
    void updateCurrentlyWallNodes();
    void updateMapScale();
    void updateMapOffset();

    void resetMap();

    void addNodeToCurrentlyWallNodesMap(Node* node);
    std::unordered_map<sf::Vector2f, Node*, std::hash<sf::Vector2f>> currentlyWallNodesMap;
   
    void render();

    sf::RenderWindow window;
    sf::View view; // Add a view for panning and zooming
    Node& getNodeAtPosition();
    ResourceManager& resourceManager = ResourceManager::getInstance();
    
    void initMap(size_t mapSize);
    void updateMapOffset(float offsetX, float offsetY);
    std::vector<std::vector<Node>> map;
    std::shared_ptr<float> mapOffsetX = std::make_shared<float>(0);
    std::shared_ptr<float> mapOffsetY = std::make_shared<float>(0);
    
    

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
    
    // A START STUFF
    AStar pathfinder;
    std::vector<Node*> path;
    int pathAnimationCounter = 0;
    bool animationON;
};

#endif // GAME_HPP