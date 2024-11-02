#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <bitset>
#include <memory>
#include <utility> // Include this for std::pair // Include the memory header for std::shared_ptr
#include "AStar.hpp"
class Game;

enum NodeType{
    NODE_EMPTY = 0,
    NODE_PLAYER,
    NODE_ENEMY,
    NODE_WALL,
    NODE_HOVER
};

class Node {
public:
    Node(sf::Vector2f position, sf::Font& font, sf::Sprite initialSprite, Game* game);
    
    void setSprite(sf::Sprite sprite);
    void setNodeWall();
    void setTextureRect(sf::IntRect rect);
    void updateSpriteScale(float scale);

    sf::Vector2f getPosition() const; // Function declaration

    NodeType getNodeType();
    int getNeighbourBitSet();
    sf::FloatRect getGlobalBounds() const;
    Node* getNodePointer();

    std::pair<float, float> getScreenSpacePosition();

    void printNodeInfo();
    void printNeighbourBitSet();
    void printNeighbours() const;

    void update();
    void updateAStarValues();
    void updateWallTextureAccordingToNeighbours();
    void updateTexture(int textureIndex);
    void updateNeighbours(Node* topNeighbour, Node* leftNeighbour, Node* rightNeighbour, Node* bottomNeighbour);
    void updateNeighbourBitSet();
    void updateTextAccordingToSpriteSize();
    void updateSpritePositionAccordingToWorldscale();
    void updateSpritePositionAccordingToOffset();
    void cycleTextures();
    
    
    sf::Text fIntoText(float val);
    void draw(sf::RenderWindow& window);
    bool isOfNodeType(NodeType input) const;
    int getNeighboursNodeType() const;
    NodeType nodeType;
    std::string toString() const;

    // A* related members
    float gCost = 10; // Cost from start to current node
    float hCost = 20; // Heuristic cost from current node to goal
    float fCost() const { return gCost + hCost; } // Total cost
    std::shared_ptr<Node> parent; // Parent node in the path
    sf::Text gCostText = fIntoText(static_cast<int>(gCost));
    sf::Text hCostText = fIntoText(static_cast<int>(hCost)); // Corrected from gCost to hCost
    sf::Text fCostText = fIntoText(static_cast<int>(fCost()));

private:
    sf::Vector2f position;

    int debugTextureIndex = 0;
    
    Node* neighbours[4];
    std::bitset<4> neighbourBitSet{0};

    sf::Sprite Sprite;
    sf::Font& font;
    sf::Text text;

    Game* game;
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

#endif // NODE_HPP