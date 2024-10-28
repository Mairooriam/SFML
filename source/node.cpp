#include "node.hpp"
#include "resourceManager.hpp"
#include <bitset>
ResourceManager& resourceManager = ResourceManager::getInstance();

Node::Node(sf::Vector2f position, sf::Font& font, sf::Sprite sprite) 
    : position(position), 
    font(font){ // Use initializer list
    setSprite(sprite);
    text.setFont(font);
    text.setCharacterSize(5); // Set character size
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(0.5);
    text.setFillColor(sf::Color::White); // Set text color
    text.setPosition(position); // Set text position
    text.setString(std::to_string(int(position.x/16)) + ", " + std::to_string(int(position.y/16)));
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

NodeType Node::getNodeType()
{
    return this->nodeType;
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
    this->nodeType = NODE_WALL;
    debugTextureIndex++; 
}

void Node::updateTexture(int textureIndex)
{
    this->Sprite.setTextureRect(resourceManager.getTextureRect(textureIndex,16,8,8));

    
}

int Node::getNeighbourBitSet()
{
    std::bitset<4> bitsetExample("0000");

    for (size_t i = 0; i < 3; ++i) {
        if (this->neighbours[i] != nullptr)
            if (this->neighbours[i]->isOfNodeType(NODE_WALL)) {
                bitsetExample.set(i);
            }
    }
    //std::cout <<"im in NODE. Bitset printed: "<< bitsetExample << "\n";
    return bitsetExample.to_ulong();
}

void Node::updateNeighbours(Node* topNeighbour, Node* leftNeighbour, Node* rightNeighbour, Node* bottomNeighbour)
{
    this->neighbours[0] = topNeighbour;
    this->neighbours[1] = leftNeighbour;
    this->neighbours[2] = rightNeighbour;
    this->neighbours[3] = bottomNeighbour;
}
void Node::setNodeWall()
{
    this->setTextureRect(resourceManager.getTextureRect(WALL_HORIZONTAL,16,8,8));
    this->nodeType = NODE_WALL;
}

void Node::setTextureRect(sf::IntRect rect)
{
    this->Sprite.setTextureRect(rect);
}

void Node::printNeighbourBitSet()
{
    this->printNodeInfo();
    std::cout << this->getNeighbourBitSet() << "\n"; 
}

void Node::updateWallTextureAccordingToNeighbours()
{
    int wallCheckResult = this->getNeighbourBitSet();
    switch (wallCheckResult)
    {
    // SINGLE WALL ON ANY SIDE
    case 1:
        // WALL AT TOP
        this->updateTexture(WALL_VERTICAL);
        break;
    case 2:
        // WALL AT BOTTOM
        this->updateTexture(WALL_VERTICAL);
        break;
    case 3:
        // WALL AT BOTTOM
        this->updateTexture(WALL_VERTICAL);
        break;
    case 4:
        // WALL AT LEFT
        this->updateTexture(WALL_HORIZONTAL);
        break;
    case 8:
        // WALL AT RIGHT
        this->updateTexture(WALL_HORIZONTAL);
        break;
    case 9:
        // WALL AT RIGHT
        this->updateTexture(WALL_CORNER_BOTTOM_LEFT);
        break;
    
    case 10:
        // WALL AT RIGHT AND BOTTOM
        this->updateTexture(WALL_CORNER_TOP_LEFT);
        break;
    case 5:
        // WALL AT LEFT AND TOP
        this->updateTexture(WALL_CORNER_BOTTOM_RIGHT);
        break;
    case 11:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_JUNCTION_TOP_RIGHT_BOTTOM);
        break;    
     case 12:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_HORIZONTAL);
        break;   
    case 13:
        // WALL LEFT TOP RIGHT
        this->updateTexture(WALL_JUNCTION_LEFT_TOP_RIGHT);
        break;
    case 14:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_JUNCTION_LEFT_BOTTOM_RIGHT);
        break; 
    case 7:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_JUNCTION_TOP_LEFT_BOTTOM);
    break;
    case 6:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_CORNER_TOP_RIGHT);
    break;        
    case 15:
        // WALL AT EACH SIDE
        this->updateTexture(WALL_JUNCTION);
        break;
    default:
        break;
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
    window.draw(this->text);
}

bool Node::isOfNodeType(NodeType input) const
{
    if(this->nodeType == input){
        return true;
    }
    else{
         return false;
    }
   
}

void Node::printNeighbours() const
{
    std::cout << "Node neighbour top position: [(" << neighbours[0]->position.x/16 << "),("<< neighbours[0]->position.y/16 << ")]" << "Nodetype: " << neighbours[0]->nodeType << "\n";
    std::cout << "Node neighbour left position: [(" << neighbours[1]->position.x/16 << "),("<< neighbours[1]->position.y/16 << ")]" << "Nodetype: " << neighbours[1]->nodeType << "\n";
    std::cout << "Node neighbour right position: [(" << neighbours[2]->position.x/16 << "),("<< neighbours[1]->position.y/16 << ")]" << "Nodetype: " << neighbours[2]->nodeType << "\n";
    std::cout << "Node neighbour bottom position: [(" << neighbours[3]->position.x/16 << "),("<< neighbours[3]->position.y/16 << ")]" << "Nodetype: " << neighbours[3]->nodeType << "\n";
}
