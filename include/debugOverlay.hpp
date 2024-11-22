#ifndef DEBUG_OVERLAY_HPP
#define DEBUG_OVERLAY_HPP

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "ResourceManager.hpp"
class DebugOverlay {
public:
    struct Cell {
        sf::Text text;
        sf::RectangleShape background;
        bool isButton;
        bool isEditable;
    };

    struct GridConfig {
        unsigned int rows;
        unsigned int cols;
        float cellWidth;
        float cellHeight;
    };

public:
    // Constructor with window size and grid configuration
    DebugOverlay(const GridConfig& config);
    
    // Core functionality
    void draw(sf::RenderWindow& window);
    void handleClick(const sf::Vector2i& mousePos);
    void handleKeyPress(const sf::Event::KeyEvent& keyEvent);
    
    // Content management
    void setText(unsigned int row, unsigned int col, const std::string& text);
    void setButton(unsigned int row, unsigned int col, const std::string& label);
    void setEditable(unsigned int row, unsigned int col, bool editable);

private:
    sf::RenderTexture overlayTexture;
    sf::Font font;
    GridConfig gridConfig;
    std::vector<std::vector<Cell>> cells;
    
    float calculateFontSize() const;
    sf::Vector2f getCellPosition(unsigned int row, unsigned int col) const;
    Cell* getCellAtPosition(const sf::Vector2i& position);
    void initializeGrid();
    ResourceManager& resourceManager = ResourceManager::getInstance();
};

#endif // DEBUG_OVERLAY_HPP