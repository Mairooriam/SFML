#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <bitset>
#include <memory> // Include the memory header for std::shared_ptr
enum NodeType{
    NODE_EMPTY = 0,
    NODE_PLAYER,
    NODE_ENEMY,
    NODE_WALL,
    NODE_HOVER
};

class Node {
public:
    Node(sf::Vector2f position, sf::Font& font, sf::Sprite initialSprite, std::shared_ptr<int> worldScale);
    
    void setSprite(sf::Sprite sprite);
    void setNodeWall();
    void setTextureRect(sf::IntRect rect);
    void setSpriteScale(float scale);

    sf::Vector2f getPosition() const; // Function declaration
    sf::Vector2f getPositionWithScale(int scale) const;
    NodeType getNodeType();
    int getNeighbourBitSet();
    sf::FloatRect getGlobalBounds() const;
    Node* getNodePointer();
    
    void printNodeInfo();
    void printNeighbourBitSet();
    void printNeighbours() const;

    void update();
    void updateWallTextureAccordingToNeighbours();
    void updateTexture(int textureIndex);
    void updateNeighbours(Node* topNeighbour, Node* leftNeighbour, Node* rightNeighbour, Node* bottomNeighbour);
    void updateNeighbourBitSet();
    void updateTextAccordingToSpriteSize();
    void updateSpritePosition();
    
    void cycleTextures();
    
    
    
    void draw(sf::RenderWindow& window);
    bool isOfNodeType(NodeType input) const;
    int getNeighboursNodeType() const;
    NodeType nodeType;
private:
    sf::Vector2f position;
    int debugTextureIndex = 0;
    
    Node* neighbours[4];
    std::bitset<4> neighbourBitSet{0};
    std::shared_ptr<int> worldScale;
    sf::Sprite Sprite;
    sf::Font& font;
    sf::Text text;

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