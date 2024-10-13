#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include "enums.h"
#include <vector>
#include <memory>
#include <iostream>
class UIElement : public sf::Drawable, public sf::Transformable {
public:
    //virtual void handleEvent(const sf::Event& event) = 0;
    //virtual void update(float dt) = 0;
};

class Button : public UIElement {
public:
    Button(float x, float y, float width, float height, sf::Font* font, const std::string text, 
    sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor);
    
    void handleEvent(const sf::Event& event);
    int update(const sf::Vector2i& mousePos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isPressed() const;

    sf::RectangleShape button;
    short unsigned buttonState;
private:
    

    sf::Font* font;
    sf::Text buttonText;
    

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
};

class Node : public UIElement {
public:
    Node(float x, float y, sf::Vector2f nodeSize, sf::Font* font, const std::string text, sf::Texture* Initialtexture, std::vector<sf::Texture>* textures);
    
    void handleEvent(const sf::Event& event);
    int update(const sf::Vector2i& mousePos, NodeType hotbarSelection);
    
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isPressed() const;
    bool isNodeIgnored(NodeType type);
    void updateTexture(TextureFileNames texturename, TextureEnum texture);
    sf::Texture selectTextureFromFile(sf::Texture & texture, TextureEnum textureName);
    std::string nodeTypeToString(NodeType);
    sf::Vector2f position;
    sf::RectangleShape node;
    NodeType nodeState;
    std::vector<sf::Texture>* textures;
private:
    
    sf::Font* font;
    sf::Text nodeText;
    sf::Color nodeColor;
};;

#endif // OVERLAY_H