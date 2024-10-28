#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>
#include <bitset>
enum NodeType{
    NODE_EMPTY = 0,
    NODE_PLAYER,
    NODE_ENEMY,
    NODE_WALL,
    NODE_HOVER
};

class Node {
public:
    Node(sf::Vector2f position, sf::Font& font, sf::Sprite initialSprite);
    
    void setSprite(sf::Sprite sprite);
     void setNodeWall();
    void setTextureRect(sf::IntRect rect);


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

    sf::Sprite Sprite;
    sf::Font& font;
    sf::Text text;
    };

#endif // NODE_HPP