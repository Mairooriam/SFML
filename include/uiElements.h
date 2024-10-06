#ifndef OVERLAY_H
#define OVERLAY_H

#include <SFML/Graphics.hpp>
#include <vector>
#include <memory>
#include <iostream>
class UIElement : public sf::Drawable, public sf::Transformable {
public:
    //virtual void handleEvent(const sf::Event& event) = 0;
    //virtual void update(float dt) = 0;
};


enum button_states{
    BTN_IDLE = 0,
    BTN_ACTIVE,
    BTN_HOVER
    
};
class Button : public UIElement {
public:
    Button(float x, float y, float width, float height, sf::Font* font, const std::string text, 
    sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor);
    
    void handleEvent(const sf::Event& event);
    int update(const sf::Vector2i& mousePos);
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    bool isPressed() const;

    sf::RectangleShape button;
    short unsigned buttonState;
private:
    

    sf::Font* font;
    sf::Text buttonText;
    

    sf::Color idleColor;
    sf::Color hoverColor;
    sf::Color activeColor;
};



#endif // OVERLAY_H