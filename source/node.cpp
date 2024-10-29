#include "node.hpp"
#include "resourceManager.hpp"

ResourceManager& resourceManager = ResourceManager::getInstance();
bool Node::debugEnabled = false; // Define the static member

Node::Node(sf::Vector2f position, sf::Font& font, sf::Sprite sprite, std::shared_ptr<int> worldScale) 
    : position(position), 
    font(font),
    worldScale(worldScale)
    { // Use initializer list
    setSprite(sprite);
    this->Sprite.setPosition(position);
    text.setFont(font);
    text.setCharacterSize(32); // Set character size
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(0.5);
    text.setFillColor(sf::Color::White); // Set text color
    text.setPosition(position); // Set text position
    text.setString("("+std::to_string(int(position.x/16)) + ", " + std::to_string(int(position.y/16))+ ")");
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
void Node::updateTextAccordingToSpriteSize()
{
    text.setCharacterSize(*worldScale/4); // Set character size

    // Calculate the center of the sprite
    float spriteCenterX = position.x + (*worldScale / 2.0f);
    float spriteCenterY = position.y + (*worldScale / 2.0f);

    // Calculate the offset for centering the text
    sf::FloatRect textBounds = text.getLocalBounds();
    float textOffsetX = textBounds.width / 2.0f;
    float textOffsetY = textBounds.height / 2.0f;

    // Set the position of the text to be centered within the sprite
    text.setPosition(spriteCenterX - textOffsetX, spriteCenterY - textOffsetY);
    

}
void Node::updateSpritePosition()
{   
    enableDebug();
    int size = Sprite.getGlobalBounds().width;
    sf::Vector2f oldpos = Sprite.getPosition();
    debugPrint("Node old pos: (" + std::to_string(oldpos.x) + ", " + std::to_string(oldpos.y) + "), size: " + std::to_string(size));
    this->Sprite.setPosition(sf::Vector2f(size - *worldScale, size - *worldScale));
    sf::Vector2f newpos = Sprite.getPosition();
    debugPrint("Node new pos: (" + std::to_string(newpos.x) + ", " + std::to_string(newpos.y) + "), size: " + std::to_string(size));
    disableDebug();
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
    for (int i = 0; i < 4; ++i) {
        if (neighbours[i] != nullptr) {
            std::cout << "Node neighbour " << i << " position: [(" << neighbours[i]->position.x/16 << "),(" << neighbours[i]->position.y/16 << ")]" << " Nodetype: " << neighbours[i]->nodeType << "\n";
        } else {
            std::cout << "Node neighbour " << i << " is nullptr\n";
        }
    }
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
void Node::setSpriteScale(float scale)
{
    float multiplier = scale / 16;
    Sprite.setScale(multiplier, multiplier);

    // Update the position according to the new scale
    // float newX = position.x * multiplier;
    // float newY = position.y * multiplier;
    // Sprite.setPosition(newX, newY);

    // Update the text position as well
    //text.setPosition(newX, newY);
}
void Node::setSprite(sf::Sprite sprite)
{
    this->Sprite = sprite;

}


