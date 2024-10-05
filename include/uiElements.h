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

// class DraggableBox : public UIElement {
// public:
//     DraggableBox(const sf::Vector2f& size);
//     void handleEvent(const sf::Event& event) override;
//     void update(float dt) override;
//     void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

// private:
//     sf::RectangleShape box;
//     bool isDragging;
//     sf::Vector2f dragOffset;
// };

// class CheckBox : public UIElement {
// public:
//     CheckBox(float size);
//     void handleEvent(const sf::Event& event) override;
//     void update(float dt) override;
//     void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//     bool isChecked() const;

// private:
//     sf::RectangleShape box;
//     bool checked;
// };
enum button_states{
    BTN_IDLE = 0,
    BTN_ACTIVE,
    BTN_HOVER
    
};
class Button : public UIElement {
public:
    Button(float x, float y, float width, float height, sf::Font* font, const std::string text, 
    sf::Color idleColor,sf::Color hoverColor,sf::Color activeColor);
    
    int handleEvent(const sf::Event& event);
    void update(const sf::Vector2i& mousePos);
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

class Label : public UIElement {
public:
    Label(const std::string& text);
    //void handleEvent(const sf::Event& event) override;
    //void update(float dt) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

private:
    sf::Text labelText;
};

// class Slider : public UIElement {
// public:
//     Slider(float length, float minValue, float maxValue);
//     void handleEvent(const sf::Event& event) override;
//     void update(float dt) override;
//     void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
//     float getValue() const;

// private:
//     sf::RectangleShape track;
//     sf::RectangleShape thumb;
//     float minValue;
//     float maxValue;
//     float value;
//     bool isDragging;
// };

#endif // OVERLAY_H