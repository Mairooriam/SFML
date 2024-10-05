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

int Button::handleEvent(const sf::Event& event) {
    //std::cout << "EVENT: " << "x:" << event.mouseButton.x << "y: " <<  event.mouseButton.y << "\n";

    std::cout << " IDLEING buton" << "\n"; 
    //IDLE
    this->buttonState = BTN_IDLE;
    
    // HOVER
    if (this->button.getGlobalBounds().contains(event.mouseMove.x,event.mouseMove.y)){
        this->buttonState = BTN_HOVER;
        std::cout << " HOVERING" << "\n";
        // PRESSED
        if(event.type == sf::Event::MouseButtonPressed){
            this->buttonState = BTN_ACTIVE;
            
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
        break;
    }
    return -1;
}

void Button::update(const sf::Vector2i& mousePos) {
    
    //IDLE
    this->buttonState = BTN_IDLE;
    
    // HOVER
    if (this->button.getGlobalBounds().contains(mousePos.x,mousePos.y)){
        this->buttonState = BTN_HOVER;

        // PRESSED
        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            this->buttonState = BTN_ACTIVE;
        }
    }

    switch (this->buttonState)
    {
    case BTN_IDLE:
        this->button.setFillColor(this->idleColor);
        break;
    case BTN_HOVER:
        this->button.setFillColor(this->hoverColor);
        break;
    case BTN_ACTIVE:
        this->button.setFillColor(this->activeColor);
        break;
    default:
        this->button.setFillColor(sf::Color::Red); // should not happendm only in error
        break;
    }
    
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



Label::Label(const std::string& text) {
    labelText.setString(text);
    // Set other properties like font, color, etc.
}

// void Label::handleEvent(const sf::Event& event) {
//     // Labels typically don't handle events, but you can implement if needed
// }

// void Label::update(float dt) {
//     // Update label state if necessary
// }

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(labelText, states);
}