#include "node.hpp"
#include "resourceManager.hpp"
ResourceManager& resourceManager = ResourceManager::getInstance();

Node::Node(sf::Vector2f position, sf::Font font, sf::Sprite sprite) 
    : position(position), 
    font(font){ // Use initializer list
    setSprite(sprite);
    // Additional initialization if needed
}
    
sf::Vector2f Node::getPosition() const {
    return this->position; // Function definition
}

void Node::printNodeInfo()
{
    std::cout << "Node at position: [" << this->position.x << "," << this->position.y << "]"
              //<< "\nNode font: " << this->font.getInfo().family
              << "\nNode sprite global bounds: ["
              << "left: " << this->Sprite.getGlobalBounds().left << ", "
              << "top: " << this->Sprite.getGlobalBounds().top << ", "
              << "width: " << this->Sprite.getGlobalBounds().width << ", "
              << "height: " << this->Sprite.getGlobalBounds().height << "]"
              << std::endl;
}

sf::FloatRect Node::getGlobalBounds() const
{
    return this->Sprite.getGlobalBounds();
}

void Node::cycleTextures()
{
    if (debugTextureIndex > 12)
    {
        debugTextureIndex = 0;
    }
    
    this->updateTexture(debugTextureIndex);
    debugTextureIndex++; 
}

void Node::updateTexture(int textureIndex)
{
    this->Sprite.setTextureRect(resourceManager.getTextureRect(textureIndex,16,8,8));
    if (textureIndex > 0 & textureIndex < 12);
    {
         
    }
    
}

void Node::setSprite(sf::Sprite sprite)
{
    this->Sprite = sprite;
    //this->Sprite.setScale(10,10);
    this->Sprite.setPosition(position.x,position.y);
}

void Node::draw(sf::RenderWindow &window)
{
    window.draw(this->Sprite);
}
