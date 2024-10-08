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

Node::Node(float x, float y, sf::Vector2f nodeSize, sf::Font* font, const std::string text) 
    {
    this->nodeState = NODE_EMPTY;
    this->font = font;

    this->node.setPosition(x,y);
    this->node.setSize(nodeSize);
    
    float fontsize = 32.0f;
    this->nodeText.setFont(*this->font);
    this->nodeText.setString(text);
    this->nodeText.setFillColor(sf::Color::White);
    this->nodeText.setCharacterSize(fontsize);
    
    this->nodeText.setPosition(
        this->node.getPosition().x + (this->node.getSize().x / 2.0f) - (this->nodeText.getGlobalBounds().width / 2.0f) - fontsize/4,
        this->node.getPosition().y + (this->node.getSize().y / 2.0f) - (this->nodeText.getGlobalBounds().height / 2.0f) - fontsize/4
    );




    this->node.setFillColor(getColor(NODE_EMPTY));
    // Set other properties like font, color, etc.
}

void Node::handleEvent(const sf::Event& event) {

}

int Node::update(const sf::Vector2i& mousePos) {
    
    //IDLE
    this->nodeState = BTN_IDLE;
    
    // HOVER
    if (this->node.getGlobalBounds().contains(mousePos.x,mousePos.y)){
        this->nodeState = NODE_PLAYER;

        // PRESSED
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->nodeState = NODE_WALL;
            std::cout << "Pressed: " << nodeText.getString().toAnsiString() << "\n";
        }
    }

    switch (this->nodeState)
    {
    case NODE_EMPTY:
        this->node.setFillColor(getColor(NODE_EMPTY));
        return NODE_EMPTY;
        break;
    case NODE_PLAYER:
        this->node.setFillColor(getColor(NODE_PLAYER));
        return NODE_PLAYER;
        break;
    case NODE_ENEMY:
        this->node.setFillColor(getColor(NODE_ENEMY));
        return NODE_ENEMY;
        break;
    case NODE_WALL:
        this->node.setFillColor(getColor(NODE_WALL));
        return NODE_WALL;
        break;
    default:
        this->node.setFillColor(sf::Color::Red); // should not happendm only in error
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
    if(this->nodeState == NODE_WALL){
        return true;
    }
    return false;
}

sf::Color Node::getColor(NodeType type){
    switch (type) {
        case NodeType::NODE_EMPTY: return sf::Color::Magenta;
        case NodeType::NODE_PLAYER: return sf::Color::Green;
        case NodeType::NODE_ENEMY: return sf::Color::Red;
        case NodeType::NODE_WALL: return sf::Color::Blue;
        default: return sf::Color::Black;
    }
}

