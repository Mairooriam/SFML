#include "node.hpp"
#include "resourceManager.hpp"

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

// GET METHODS   
sf::Vector2f Node::getPosition() const {
    return this->position; // Function definition
}
sf::Vector2f Node::getPositionWithScale(int scale) const {
    return sf::Vector2f(this->position.x/scale, this->position.y/scale); // Function definition
}
NodeType Node::getNodeType()
{
    return this->nodeType;
}
sf::FloatRect Node::getGlobalBounds() const
{
    return this->Sprite.getGlobalBounds();
}
int Node::getNeighbourBitSet()
{
    return this->neighbourBitSet.to_ulong();
}
Node* Node::getNodePointer() {
    return this; // Return a pointer to this Node
}
// UTIL
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

// UPDATE METHODS
void Node::updateNeighbours(Node* topNeighbour, Node* leftNeighbour, Node* rightNeighbour, Node* bottomNeighbour)
{
    // this->neighbours[0] = topNeighbour;
    // this->neighbours[1] = leftNeighbour;
    // this->neighbours[2] = rightNeighbour;
    // this->neighbours[3] = bottomNeighbour;

    this->neighbours[0] = leftNeighbour;
    this->neighbours[1] = topNeighbour;
    this->neighbours[2] = bottomNeighbour;
    this->neighbours[3] = rightNeighbour;
}
void Node::updateWallTextureAccordingToNeighbours()
{
    int wallCheckResult = this->getNeighbourBitSet();
    std::cout << "Node at position: [" << this->position.x/16 << ", " << this->position.y/16 << "] updated wall into wallCheckResult: " << wallCheckResult << std::endl;
    switch (wallCheckResult)
    {
    // SINGLE WALL ON ANY SIDE
    case 1:
        // WALL AT TOP
        this->updateTexture(WALL_VERTICAL);
        break;
    case 8:
        // WALL AT BOTTOM
        this->updateTexture(WALL_VERTICAL);
        break;
    case 12:
        // WALL AT BOTTOM RIGHT
        this->updateTexture(WALL_CORNER_TOP_LEFT);
        break;
    case 10:
        // WALL AT LEFT BOTTOM
        this->updateTexture(WALL_CORNER_TOP_RIGHT);
        break;
    case 3:
        // WALL AT BOTTOM
        this->updateTexture(WALL_CORNER_BOTTOM_RIGHT);
        break;
    case 5:
        // WALL AT LEFT AND TOP
        this->updateTexture(WALL_CORNER_BOTTOM_LEFT);
        break;
    
    case 2:
        // WALL AT TOP
        this->updateTexture(WALL_HORIZONTAL);
        break;

    case 4:
        // WALL AT LEFT
        this->updateTexture(WALL_HORIZONTAL);
        break;
    
    case 9:
        // WALL AT RIGHT
        this->updateTexture(WALL_VERTICAL);
        break;


    
    case 11:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_JUNCTION_TOP_LEFT_BOTTOM);
        break;    
      
    case 13:
        // WALL LEFT TOP RIGHT
        this->updateTexture(WALL_JUNCTION_TOP_RIGHT_BOTTOM);
        break;
    case 14:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_JUNCTION_LEFT_BOTTOM_RIGHT);
        break; 
    case 7:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_JUNCTION_LEFT_TOP_RIGHT);
    break;
    case 6:
        // WALL TOP RIGHT BOTTOM
        this->updateTexture(WALL_HORIZONTAL);
    break;        
    case 15:
        // WALL AT EACH SIDE
        this->updateTexture(WALL_JUNCTION);
        break;
    default:
        break;
    }
}
void Node::updateTexture(int textureIndex)
{
    this->Sprite.setTextureRect(resourceManager.getTextureRect(textureIndex,16,8,8)); 
}
void Node::updateNeighbourBitSet(){
    for (size_t i = 0; i < 4; ++i) {
        if (this->neighbours[i] != nullptr) {
            if (this->neighbours[i]->isOfNodeType(NODE_WALL)) {
                this->neighbourBitSet.set(i);
            } else {
                this->neighbourBitSet.reset(i);
            }
        } else {
            this->neighbourBitSet.reset(i);
        }
    }
}
// PRINT METHODS
void Node::printNeighbours() const
{
    std::cout << "Node neighbour top position: [(" << neighbours[0]->position.x/16 << "),("<< neighbours[0]->position.y/16 << ")]" << "Nodetype: " << neighbours[0]->nodeType << "\n";
    std::cout << "Node neighbour left position: [(" << neighbours[1]->position.x/16 << "),("<< neighbours[1]->position.y/16 << ")]" << "Nodetype: " << neighbours[1]->nodeType << "\n";
    std::cout << "Node neighbour right position: [(" << neighbours[2]->position.x/16 << "),("<< neighbours[1]->position.y/16 << ")]" << "Nodetype: " << neighbours[2]->nodeType << "\n";
    std::cout << "Node neighbour bottom position: [(" << neighbours[3]->position.x/16 << "),("<< neighbours[3]->position.y/16 << ")]" << "Nodetype: " << neighbours[3]->nodeType << "\n";
}
void Node::printNeighbourBitSet()
{
    this->printNodeInfo();
    std::cout <<"Bitset INT: "<< this->getNeighbourBitSet() << " Binary from [0][1][2][4] [top][left][right][bottom]: "<< neighbourBitSet[0]<< neighbourBitSet[1] << neighbourBitSet[2] << neighbourBitSet[3] <<"\n"; 
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

// SET METHODS
void Node::setNodeWall()
{
    this->setTextureRect(resourceManager.getTextureRect(WALL_LONELY,16,8,8));
    this->nodeType = NODE_WALL;
}
void Node::setTextureRect(sf::IntRect rect)
{
    this->Sprite.setTextureRect(rect);
}
void Node::setSprite(sf::Sprite sprite)
{
    this->Sprite = sprite;
    //this->Sprite.setScale(10,10);
    this->Sprite.setPosition(position.x,position.y);
}
