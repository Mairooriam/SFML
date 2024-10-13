#include "uiElements.h"


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

    node.setTexture(this->texture);
    node.setTextureRect(sf::IntRect(textureIndex*16,0,16,16));
    node.setScale(6.4f,6.4f);
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
        else if(nodeState != NODE_ENEMY && nodeState != NODE_PLAYER && nodeState != NODE_WALL_1 && nodeState != NODE_WALL_2 && nodeState != NODE_WALL_3&& nodeState != NODE_WALL_4){
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
    case NODE_WALL_1:
        //this->node.setColor(nodeTypeToColor(NODE_WALL));
        //this->updateTexture(TEXTURE_WALL,WALL_JUNCTION);
        updateTexture(WALL_CORNER_BOTTOM_LEFT);
        return NODE_WALL_1;
        break;
    case NODE_WALL_2:
        //this->node.setColor(nodeTypeToColor(NODE_WALL));
        //this->updateTexture(TEXTURE_WALL,WALL_JUNCTION);
        updateTexture(WALL_CORNER_BOTTOM_RIGHT);
        return NODE_WALL_2;
        break;
    case NODE_WALL_3:
        //this->node.setColor(nodeTypeToColor(NODE_WALL));
        //this->updateTexture(TEXTURE_WALL,WALL_JUNCTION);
        updateTexture(WALL_JUNCTION);
        return NODE_WALL_3;
        break;
    case NODE_WALL_4:
        //this->node.setColor(nodeTypeToColor(NODE_WALL));
        //this->updateTexture(TEXTURE_WALL,WALL_JUNCTION);
        updateTexture(WALL_HORIZONTAL);
        return NODE_WALL_4;
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




void Node::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(this->node);
    target.draw(this->nodeText);
}

bool Node::isPressed() const
{
    // if(this->nodeState == NODE_WALL){
    //     return true;
    // }
    // return false;
}




