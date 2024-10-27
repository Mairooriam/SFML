#include "uiElements.h"
#include <bitset>


Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string text, 
    sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor) 
    {
    this->buttonState = BTN_IDLE;
    this->font = font;

    this->button.setPosition(x,y);
    this->button.setSize(sf::Vector2f(width,height));
    
    float fontsize = 32.0f;
    this->buttonText.setFont(*this->font);
    this->buttonText.setString(text);
    this->buttonText.setFillColor(sf::Color::White);
    this->buttonText.setCharacterSize(fontsize);
    std::cout << " boidningdsa" << buttonText.getLocalBounds().width << "\n";
    this->buttonText.setPosition(
        this->button.getPosition().x + (this->button.getSize().x / 2.0f) - (this->buttonText.getGlobalBounds().width / 2.0f) - fontsize/4,
        this->button.getPosition().y + (this->button.getSize().y / 2.0f) - (this->buttonText.getGlobalBounds().height / 2.0f) - fontsize/4
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->button.setFillColor(this->idleColor);
    // Set other properties like font, color, etc.
}

void Button::handleEvent(const sf::Event& event) {

}

int Button::update(const sf::Vector2i& mousePos) {
    
    //IDLE
    this->buttonState = BTN_IDLE;
    
    // HOVER
    if (this->button.getGlobalBounds().contains(mousePos.x,mousePos.y)){
        this->buttonState = BTN_HOVER;

        // PRESSED
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState = BTN_ACTIVE;
            std::cout << "Pressed: " << buttonText.getString().toAnsiString() << "\n";
        }
    }

    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->button.setFillColor(this->idleColor);
        return BTN_IDLE;
        break;
    case BTN_HOVER:
        this->button.setFillColor(this->hoverColor);
        return BTN_HOVER;
        break;
    case BTN_ACTIVE:
        this->button.setFillColor(this->activeColor);
        return BTN_ACTIVE;
        break;
    default:
        this->button.setFillColor(sf::Color::Red); // should not happendm only in error
        return -1;
        break;
    }
    return -1;
    
}

void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    target.draw(this->button);
    target.draw(this->buttonText);
}

bool Button::isPressed() const
{
    if(this->buttonState == BTN_ACTIVE){
        return true;
    }
    return false;
}


Node::Node(float x, float y, sf::Vector2f nodeSize, sf::Font* font, const std::string text, sf::Texture initialTexture, std::vector<sf::Texture>* textures) {
    this->nodeState = NODE_EMPTY;
    this->font = font;
    this->position.x = x;
    this->position.y = y;
    this->texture = initialTexture;

    // Check if the initial texture is valid
    if (initialTexture.getSize().x > 0 && initialTexture.getSize().y > 0) {
        this->node.setTexture(initialTexture, true);
        std::cout << "Texture set successfully.\n";
    } else {
    // Handle the case where the texture is not valid
    std::cout << "Error: Invalid initial texture provided.\n";
    // You can set a default texture or handle the error as needed
    }

    this->node.setPosition(x, y);
    this->node.setTexture(initialTexture, true); // Use pointer to sf::Texture
    this->node.setTextureRect(sf::IntRect(0,0,16,16));
    this->node.setScale(1.0f,1.0f);
    float fontsize = 32.0f;
    this->nodeText.setFont(*this->font);
    this->nodeText.setString(text);
    this->nodeText.setFillColor(sf::Color::White);
    this->nodeText.setCharacterSize(fontsize);

    //this->nodeText.setPosition(
        //this->node.getPosition().x + (this->node.getSize().x / 2.0f) - (this->nodeText.getGlobalBounds().width / 2.0f) - fontsize / 4,
        //this->node.getPosition().y + (this->node.getSize().y / 2.0f) - (this->nodeText.getGlobalBounds().height / 2.0f) - fontsize / 4
    //);

    //this->node.setFillColor(nodeTypeToColor(NODE_EMPTY));
    // Set other properties like font, color, etc.
}


void Node::handleEvent(const sf::Event& event) {

}

void Node::updateTexture(TextureEnum textureIndex) {
    
    // int y = textureIndex % 8;
    // node.setTexture(this->texture);
    // node.setTextureRect(sf::IntRect(textureIndex*16,y,16,16));
    // node.setScale(6.4f,6.4f);
    int x = textureIndex % 8; // Column index
    int y = textureIndex / 8; // Row index

    node.setTexture(this->texture);
    node.setTextureRect(sf::IntRect(x * 16, y * 16, 16, 16));
    node.setScale(6.4f, 6.4f);
}



int Node::update(const sf::Vector2i& mousePos, NodeType hotbarSelection) {
   
   
   
   updateTexture(FLOOR_GREEN);
    //IDLE
    if (nodeState == NODE_HOVER){
    this->nodeState = NODE_EMPTY;
    }
    
    // HOVER
    if (this->node.getGlobalBounds().contains(mousePos.x,mousePos.y)){
        // if empty selected still show hower
        if (hotbarSelection == NODE_EMPTY){
            this->nodeState = NODE_HOVER;  
        }
        // add isvalid function or something
        else if(nodeState != NODE_ENEMY && nodeState != NODE_PLAYER && nodeState != NODE_WALL){
            this->nodeState = NODE_HOVER;    
        }
        // PRESSED
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->nodeState = hotbarSelection;
            std::cout << "Pressed: " << nodeText.getString().toAnsiString() << "\n";
        }
    }

    switch (this->nodeState)
    {
    case NODE_EMPTY:
        this->node.setColor(nodeTypeToColor(NODE_EMPTY));
        return NODE_EMPTY;
        break;
    case NODE_PLAYER:
        this->node.setColor(nodeTypeToColor(NODE_PLAYER));
        return NODE_PLAYER;
        break;
    case NODE_ENEMY:
        this->node.setColor(nodeTypeToColor(NODE_ENEMY));
        return NODE_ENEMY;
        break;
    case NODE_WALL:
        //this->node.setColor(nodeTypeToColor(NODE_WALL));
        //this->updateTexture(TEXTURE_WALL,WALL_JUNCTION);
        updateTexture(WALL_LONELY);
        return NODE_WALL;
        break;
    case NODE_HOVER:
        this->node.setColor(nodeTypeToColor(NODE_HOVER));
        return NODE_HOVER;
        break;
    default:
        //this->node.setFillColor(sf::Color::Red); // should not happendm only in error
        return -1;
        break;
    }

    return -1;
   
}

void Node::updateWallTextureAccordingToNeighbours(int wallCheckResult)
{
    
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

void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    
    target.draw(this->node);
    target.draw(this->nodeText);
}

void Node::printNeighbours() {
    std::cout << "Neighbours of : " <<position.x << "," << position.y << "\n";
    // for (const auto& neighbour : this->neighbors) {
    //     if (neighbour != nullptr){
    //         std::cout << "(" << neighbour->position.x << ", " << neighbour->position.y << ") \n";
    //     }else{
    //         std::cout << "(" << position.x << ", " << position.y << ") HAS NO NEIGHBOUR HERE. \n";
    //     }
        
    // }
    
    //TOP
    if(this->neighbors[0] != nullptr)
        std::cout << "TOP   (" << this->neighbors[0]->position.x << ", " << this->neighbors[0]->position.y << ") \n"; 
    else
        std::cout << "TOP   (nullptr) \n";

    if(this->neighbors[1] != nullptr)
        std::cout << "BOT   (" << this->neighbors[1]->position.x << ", " << this->neighbors[1]->position.y << ") \n";
    else
        std::cout << "BOT   (nullptr) \n";

    if(this->neighbors[2] != nullptr)
        std::cout << "LEFT  (" << this->neighbors[2]->position.x << ", " << this->neighbors[2]->position.y << ") \n"; 
    else
        std::cout << "LEFT  (nullptr) \n";

    if(this->neighbors[3] != nullptr)
        std::cout << "RIGHT (" << this->neighbors[3]->position.x << ", " << this->neighbors[3]->position.y << ") \n";
    else
        std::cout << "RIGHT (nullptr) \n";
}

int Node::areNeighboursWall()
{
    std::bitset<4> bitsetExample("0000");

    for (size_t i = 0; i < 4; ++i) {
        if (this->neighbors[i] != nullptr)
            if (this->neighbors[i]->isWall) {
                bitsetExample.set(i);
            }
    }
    //std::cout <<"im in NODE. Bitset printed: "<< bitsetExample << "\n";
    return bitsetExample.to_ulong();
}
// IS FUCNTIONS
bool Node::isPressed() const
{
    // if(this->nodeState == NODE_WALL){
    //     return true;
    // }
    // return false;
}
bool Node::isWall() const{
    if (this->nodeState == NODE_WALL){
        //std::cout << this->position.x << " " << this->position.y << " is wall"<< "\n";
        return true;
    }else{
        //std::cout << this->position.x << " " << this->position.y << " is not wall"<< "\n";
        return false;
    }
    
}



