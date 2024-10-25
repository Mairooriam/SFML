#ifndef DEBUGOVERLAY_H
#define DEBUGOVERLAY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>

class DebugOverlay {
public:
    DebugOverlay();
    void addTextField(const std::string label, const std::string& value);
    void updateTextField(const std::string label, const std::string& value);
    void drawBackground(sf::RenderWindow& window);
    void draw(sf::RenderWindow& window);

private:
    struct TextField {
        std::string label;
        std::string value;
        sf::Text text;
    };

    std::vector<TextField> textFields;
    sf::Font font;
    float yOffset;
};

#endif // DEBUGOVERLAY_H