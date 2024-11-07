#include "node.hpp"
#include "resourceManager.hpp"
#include "game.hpp" // Include the header file for the Game class
#include <sstream>
#include <iomanip>
ResourceManager& resourceManager = ResourceManager::getInstance();
bool Node::debugEnabled = false; // Define the static member

// Function to convert a float to a string with a specified number of decimal places
std::string floatToStringWithPrecision(float value, int precision) {
    std::ostringstream out;
    out << std::fixed << std::setprecision(precision) << value;
    return out.str();
}

Node::Node(sf::Vector2f position, sf::Font& font, sf::Sprite sprite, Game* game)
    : position(position),
    font(font),
    game(game)

    { // Use initializer list

    setSprite(sprite);
    updateSpriteScale(game->getWorldScale());
    gCost = INFINITY;
    hCost = INFINITY;

    debugPrint("NODE INIT DONE: worldscale:" + std::to_string(game->getWorldScale()) + std::to_string(position.x));



    text.setFont(font);
    text.setCharacterSize(32); // Set character size
    text.setOutlineColor(sf::Color::Black);
    text.setOutlineThickness(0.5);
    text.setFillColor(sf::Color::White); // Set text color
     // Set text position
    text.setString("("+std::to_string(int(position.x)) + ", " + std::to_string(int(position.y))+ ")");

    fCostText.setFont(font);
    fCostText.setCharacterSize(32); // Set character size
    fCostText.setOutlineColor(sf::Color::Black);
    fCostText.setOutlineThickness(0.5);
    fCostText.setFillColor(sf::Color::White); // Set text color


    hCostText.setFont(font);
    hCostText.setCharacterSize(32); // Set character size
    hCostText.setOutlineColor(sf::Color::Black);
    hCostText.setOutlineThickness(0.5);
    hCostText.setFillColor(sf::Color::White); // Set text color

    gCostText.setFont(font);
    gCostText.setCharacterSize(32); // Set character size
    gCostText.setOutlineColor(sf::Color::Black);
    gCostText.setOutlineThickness(0.5);
    gCostText.setFillColor(sf::Color::White); // Set text color
    updateTextAccordingToSpriteSize();

    // Additional initialization if needed
}

// GET METHODS
sf::Vector2f Node::getPosition() const {
    return this->position; // Function definition
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

std::pair<float, float> Node::getScreenSpacePosition()
{
    float spriteSize = game->getWorldScale();
    float newX = position.x * spriteSize + game->getOffsetX();
    float newY = position.y * spriteSize + game->getOffsetY();
    return std::make_pair(newX, newY);
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
    disableDebug();
    float worldScale = game->getWorldScale();
    float rowHeight = worldScale / 3.0f; // Divide the sprite height into 3 rows


    // Set character size to be a fraction of the row height
    text.setCharacterSize(rowHeight / 2.0f);
    gCostText.setCharacterSize(rowHeight / 2.0f);
    hCostText.setCharacterSize(rowHeight / 2.0f);
    fCostText.setCharacterSize(rowHeight / 2.0f);

    std::pair<float, float> worldPos = getScreenSpacePosition();
    float spriteCenterX = worldPos.first + (worldScale / 2.0f);

    // Calculate the offset for centering the text
    sf::FloatRect textBounds = text.getLocalBounds();
    float textOffsetX = textBounds.width / 2.0f;
    float textOffsetY = textBounds.height / 2.0f;

    // Calculate the Y positions for each row
    float topRowY = worldPos.second + (rowHeight / 2.0f);
    float middleRowY = worldPos.second + (rowHeight * 1.5f);
    float bottomRowY = worldPos.second + (rowHeight * 2.5f);

    // Calculate the X position for the second column in the top row
    float columnOffsetX = worldScale / 4.0f; // Adjust this value as needed

    // Set the position of the text to be centered within each row
    text.setPosition(spriteCenterX - textOffsetX, bottomRowY - textOffsetY);
    gCostText.setPosition(spriteCenterX - columnOffsetX - textOffsetX, topRowY - textOffsetY);
    hCostText.setPosition(spriteCenterX + columnOffsetX - textOffsetX, topRowY - textOffsetY);
    fCostText.setPosition(spriteCenterX - textOffsetX, middleRowY - textOffsetY);

    debugPrint("Node::updateTextAccordingToSpriteSize: Text position updated to: (" + std::to_string(text.getPosition().x) + ", " + std::to_string(text.getPosition().y) + ")");
}
void Node::updateSpritePositionAccordingToWorldscale()
{
    enableDebug();
    std::pair posWorld = getScreenSpacePosition();
    Sprite.setPosition(posWorld.first,posWorld.second);
    updateTextAccordingToSpriteSize();
    debugPrint("Node::updateSpritePositionAccordingToWorldscale: " + std::to_string(game->getOffsetX()) + std::to_string(game->getOffsetY()));
    disableDebug();
}
void Node::updateSpritePositionAccordingToOffset()
{
    std::pair posWorld = getScreenSpacePosition();
    Sprite.setPosition(posWorld.first,posWorld.second);
    updateTextAccordingToSpriteSize();
}
sf::Text Node::fIntoText(float val)
{
    sf::Text text;
    text.setString(floatToStringWithPrecision(val,0));

    text.setFont(this->font); // Assuming 'font' is a member of Node
    return text;
}
void Node::draw(sf::RenderWindow &window)
{
    window.draw(this->Sprite);

}
void Node::drawText(sf::RenderWindow &window)
{
    window.draw(this->text);
    window.draw(this->gCostText);
    window.draw(this->hCostText);
    window.draw(this->fCostText);
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

std::string Node::toString() const
{
    return "Node: (" + std::to_string(position.x) + ", " + std::to_string(position.y) + ")";
}



// UPDATE METHODS
void Node::updateNeighbours(Node* top, Node* left, Node* right, Node* bottom,
                            Node* topLeft, Node* topRight, Node* bottomLeft, Node* bottomRight)
{
    // ROW 1
    this->neighbours[0] = topLeft;
    this->neighbours[1] = top;
    this->neighbours[2] = topRight;

    //ROW 2
    this->neighbours[3] = left;
    this->neighbours[4] = right;

    // ROW 3
    this->neighbours[5] = bottomLeft;
    this->neighbours[6] = bottom;
    this->neighbours[7] = bottomRight;
}


void Node::updateAStarValues()
{
    // Cost from start to current node GCOST
    // Heuristic cost from current node to goal HCOST
    this->gCost = static_cast<int>(Utils::getDistanceVector2F(this->position, game->startNode->position)*10);
    this->hCost = static_cast<int>(Utils::getDistanceVector2F(this->position, game->endNode->position)*10);
    fCost();
    gCostText.setString(floatToStringWithPrecision(gCost,0));
    hCostText.setString(floatToStringWithPrecision(hCost,0));
    fCostText.setString(floatToStringWithPrecision(fCost(),0));
}
void Node::updateWallTextureAccordingToNeighbours()
{
    int wallCheckResult = this->getNeighbourBitSet();
    debugPrint("Node::updateWallTextureAccordingToNeighbours Node at position: [" + std::to_string(this->position.x) + ", " + std::to_string(this->position.y) + "] updated wall into wallCheckResult: " + std::to_string(wallCheckResult));
    switch (wallCheckResult)
    {
    // SINGLE WALL ON ANY SIDE
    case 1:
        // WALL AT TOP
        this->updateTexture(WALL_VERTICAL);
        break;
    }
}
void Node::updateTexture(int textureIndex)
{
    this->Sprite.setTextureRect(resourceManager.getTextureRect(textureIndex,16,8,8));
}
void Node::updateNeighbourBitSet(){
    neighbourSize = 0;
    for (size_t i = 0; i < 8; ++i) {
        if (this->neighbours[i] != nullptr) {
            if (this->neighbours[i]->isOfNodeType(NODE_WALL)) {
                this->neighbourBitSet.set(i);
                neighbourSize += 1;
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
    for (int i = 0; i < 8; ++i) {
        if (neighbours[i] != nullptr) {
            debugPrint("Node neighbour " + std::to_string(i) + " position: [(" + std::to_string(neighbours[i]->position.x) + "),(" + std::to_string(neighbours[i]->position.y) + ")]" + " Nodetype: " + std::to_string(neighbours[i]->nodeType));
        } else {
            debugPrint("Node neighbour " + std::to_string(i) + " is nullptr");
        }
    }
}
void Node::printNeighbourBitSet()
{
    this->printNodeInfo();
    std::cout <<"Bitset INT: "<< this->getNeighbourBitSet() << " Binary from [0][1][2][4] [top][left][right][bottom]: "
    << neighbourBitSet[0]
    << neighbourBitSet[1]
    << neighbourBitSet[2]
    << neighbourBitSet[3]
    << neighbourBitSet[4]
    << neighbourBitSet[5]
    << neighbourBitSet[6]
    << neighbourBitSet[7]
    <<"\n";
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
void Node::setNodeDefault()
{
    this->setTextureRect(resourceManager.getTextureRect(FLOOR_GREEN,16,8,8));
    this->nodeType = NODE_EMPTY;
    this->Sprite.setColor(sf::Color::White);
}
void Node::updateSpriteScale(float scale)
{
    float multiplier = scale / 16;
    Sprite.setScale(multiplier, multiplier);

    // Update the position according to the new scale
    // float newX = position.x * multiplier;
    // float newY = position.y * multiplier;
    // Sprite.setPosition(newX, newY);

    // Update the text position as well
    //text.setPosition(newX, newY);
    this->updateSpritePositionAccordingToOffset();
    this->updateTextAccordingToSpriteSize();
}
void Node::setColor(sf::Color color)
{
    Sprite.setColor(color);
}
void Node::setNodePath()
{
    this->setColor(sf::Color::Black);
}
void Node::setSprite(sf::Sprite sprite)
{
    this->Sprite = sprite;

}

// OPERATORS
std::ostream& operator<<(std::ostream& os, const Node& node) {
    os << "Node(position: (" << node.position.x << ", " << node.position.y << "), fCost: " << node.fCost() << ")";
    return os;
}
