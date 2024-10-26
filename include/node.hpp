#ifndef NODE_HPP
#define NODE_HPP

#include <SFML/Graphics.hpp>
#include <array>
#include <iostream>

enum NodeType{
    NODE_EMPTY = 0,
    NODE_PLAYER,
    NODE_ENEMY,
    NODE_WALL,
    NODE_HOVER
};

class Node {
public:
    Node(sf::Vector2f position, sf::Font font, sf::Sprite initialSprite);
    void setSprite(sf::Sprite sprite);
    sf::Vector2f getPosition() const; // Function declaration
    void printNodeInfo();

    void update();
    sf::FloatRect getGlobalBounds() const;
    void cycleTextures();
    void updateTexture(int textureIndex);
    void updateNeighbours(Node* topNeighbour, Node* leftNeighbour, Node* rightNeighbour, Node* bottomNeighbour);
    
    int updateWallTextureAccordingToNeighbours();
    void draw(sf::RenderWindow& window);
    bool isOfNodeType(NodeType input) const;
    void printNeighbours() const;
    int getNeighboursNodeType() const;

private:
    sf::Vector2f position;
    //std::array<int, 4> neighbours;
    //NodeType nodeState;
    //sf::Text nodeText;
    //sf::Color nodeColor;
    int debugTextureIndex = 0;
    Node* neighbours[4];
    sf::Sprite Sprite;
    sf::Font& font;
};

#endif // NODE_HPP