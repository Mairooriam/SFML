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


Node::Node(float x, float y, sf::Vector2f nodeSize, sf::Font* font, const std::string text, sf::Texture* initialTexture, std::vector<sf::Texture>* textures) {
    this->nodeState = NODE_EMPTY;
    this->font = font;
    this->position.x = x;
    this->position.y = y;
    this->textures = textures;

    this->node.setPosition(x, y);
    this->node.setSize(nodeSize);
    this->node.setTexture(initialTexture); // Use pointer to sf::Texture
    float fontsize = 32.0f;
    this->nodeText.setFont(*this->font);
    this->nodeText.setString(text);
    this->nodeText.setFillColor(sf::Color::White);
    this->nodeText.setCharacterSize(fontsize);

    this->nodeText.setPosition(
        this->node.getPosition().x + (this->node.getSize().x / 2.0f) - (this->nodeText.getGlobalBounds().width / 2.0f) - fontsize / 4,
        this->node.getPosition().y + (this->node.getSize().y / 2.0f) - (this->nodeText.getGlobalBounds().height / 2.0f) - fontsize / 4
    );

    this->node.setFillColor(nodeTypeToColor(NODE_EMPTY));
    // Set other properties like font, color, etc.
}


void Node::handleEvent(const sf::Event& event) {

}

void Node::updateTexture(TextureFileNames textureName, TextureEnum texture) {
    // Assuming 'textureName' is an index or identifier to access the correct texture
    if (textureName < this->textures->size()) {
        sf::Texture& chosenTexture = this->textures->at(textureName); // Access the texture from the vector
        sf::Texture subTexture = this->selectTextureFromFile(chosenTexture, texture); // Get the sub-texture
        this->node.setTexture(&chosenTexture); // Set the texture to the node
    } else {
        // Handle the case where the texture index is out of bounds
        std::cerr << "Error: Texture index out of bounds\n";
    }
}

int Node::update(const sf::Vector2i& mousePos, NodeType hotbarSelection) {
    
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
        else if(nodeState != NODE_ENEMY && nodeState != NODE_PLAYER && nodeState != NODE_WALL ){
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
        this->node.setFillColor(nodeTypeToColor(NODE_EMPTY));
        return NODE_EMPTY;
        break;
    case NODE_PLAYER:
        this->node.setFillColor(nodeTypeToColor(NODE_PLAYER));
        return NODE_PLAYER;
        break;
    case NODE_ENEMY:
        this->node.setFillColor(nodeTypeToColor(NODE_ENEMY));
        return NODE_ENEMY;
        break;
    case NODE_WALL:
        this->node.setFillColor(nodeTypeToColor(NODE_WALL));
        this->updateTexture(TEXTURE_WALL,WALL_JUNCTION);
        return NODE_WALL;
        break;
    case NODE_HOVER:
        this->node.setFillColor(nodeTypeToColor(NODE_HOVER));
        return NODE_HOVER;
        break;
    default:
        this->node.setFillColor(sf::Color::Red); // should not happendm only in error
        return -1;
        break;
    }
    return -1;
}

sf::Texture Node::selectTextureFromFile(sf::Texture & texture, TextureEnum textureName)
{
    sf::Texture subTexture;
    sf::IntRect rect;

    // Calculate the position of the sub-texture
    int textureSize = 16;
    int texturesPerRow = 128 / textureSize;
    int x = (textureName % texturesPerRow) * textureSize;
    int y = (textureName / texturesPerRow) * textureSize;
    std::cout << "TEXTURE X:" << x << "TEXTURE Y:" << y << "\n";
    rect.left = x;
    rect.top = y;
    rect.width = textureSize;
    rect.height = textureSize;

    // Load the sub-texture
    if (subTexture.loadFromImage(texture.copyToImage(), rect)) {
        return subTexture;
    } else {
        // Handle error (return an empty texture or throw an exception)
        return sf::Texture();
    }
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




