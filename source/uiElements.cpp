#include "uiElements.h"


Button::Button(float x, float y, float width, float height, sf::Font* font, const std::string text, 
    sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor) 
    {
    this->buttonState = BTN_IDLE;

    this->button.setPosition(x,y);
    this->button.setSize(sf::Vector2f(width,height));
    
    this->font = font;
    this->buttonText.setFont(*this->font);
    this->buttonText.setString(text);
    this->buttonText.setFillColor(sf::Color::White);
    this->buttonText.setCharacterSize(12);
    this->buttonText.setPosition(
        this->button.getPosition().x / 2.0f - this->buttonText.getGlobalBounds().width / 2.0f,
        this->button.getPosition().y / 2.0f - this->buttonText.getGlobalBounds().height / 2.0f
    );

    this->idleColor = idleColor;
    this->hoverColor = hoverColor;
    this->activeColor = activeColor;

    this->button.setFillColor(this->idleColor);
    // Set other properties like font, color, etc.
}

void Button::handleEvent(const sf::Event& event) {
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

    // if (event.type == sf::Event::MouseButtonPressed) {
    //     if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
    //         std::cout << "mouse pressed!!!" << "\n";
            
            
    //     }
    // } else if (event.type == sf::Event::MouseButtonReleased) {
    //     if (button.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
            
    //         std::cout << "mouse pressed!!!" << "\n";
    //         std::cout << button.getGlobalBounds().left << "\n";
    //     }
    // }
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

void Label::handleEvent(const sf::Event& event) {
    // Labels typically don't handle events, but you can implement if needed
}

// void Label::update(float dt) {
//     // Update label state if necessary
// }

void Label::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    target.draw(labelText, states);
}