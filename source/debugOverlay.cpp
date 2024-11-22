#include "debugOverlay.hpp"
#include <iostream>

DebugOverlay::DebugOverlay(const GridConfig& config)
    : gridConfig(config) {
    font = resourceManager.getFont("arial");

    // Initialize the render texture
    overlayTexture.create(config.cellWidth * config.cols, config.cellHeight * config.rows);

    // Initialize the grid
    initializeGrid();
}

void DebugOverlay::initializeGrid() {
    cells.resize(gridConfig.rows, std::vector<Cell>(gridConfig.cols));

    for (unsigned int row = 0; row < gridConfig.rows; ++row) {
        for (unsigned int col = 0; col < gridConfig.cols; ++col) {
            Cell& cell = cells[row][col];
            cell.background.setSize(sf::Vector2f(gridConfig.cellWidth, gridConfig.cellHeight));
            cell.background.setPosition(getCellPosition(row, col));
            cell.background.setFillColor(sf::Color(255, 0, 0, 255)); // Solid background
            cell.background.setOutlineColor(sf::Color::Black);
            cell.background.setOutlineThickness(1.0f);

           
            cell.text.setFont(font);
            cell.text.setCharacterSize(static_cast<unsigned int>(calculateFontSize()));
            cell.text.setFillColor(sf::Color::White);
            cell.text.setPosition(cell.background.getPosition());
            cell.isButton = false;
            cell.isEditable = false;
        }
    }
}

float DebugOverlay::calculateFontSize() const {
    return gridConfig.cellHeight * 0.5f; // Example: 50% of cell height
}

sf::Vector2f DebugOverlay::getCellPosition(unsigned int row, unsigned int col) const {
    return sf::Vector2f(col * gridConfig.cellWidth, row * gridConfig.cellHeight);
}

void DebugOverlay::draw(sf::RenderWindow& window) {
    overlayTexture.clear(sf::Color::Transparent);

    for (const auto& row : cells) {
        for (const auto& cell : row) {
            overlayTexture.draw(cell.background);
            overlayTexture.draw(cell.text);
        }
    }

    overlayTexture.display();

    sf::Sprite sprite(overlayTexture.getTexture());
    window.draw(sprite);
}

void DebugOverlay::handleClick(const sf::Vector2i& mousePos) {
    for (unsigned int row = 0; row < gridConfig.rows; ++row) {
        for (unsigned int col = 0; col < gridConfig.cols; ++col) {
            Cell& cell = cells[row][col];
            if (cell.background.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos))) {
                if (cell.isButton) {
                    std::cout << "DebugOverlay::handleClick: Button clicked at (" << row << ", " << col << ")" << std::endl;
                    // Handle button click
                }
                if (cell.isEditable) {
                    std::cout << "DebugOverlay::handleClick: Editable cell clicked at (" << row << ", " << col << ")" << std::endl;
                    // Handle editable cell click
                }
            }
        }
    }
}

void DebugOverlay::handleKeyPress(const sf::Event::KeyEvent& keyEvent) {
    // Handle key press events for editable cells
    // This is a placeholder implementation
    std::cout << "DebugOverlay::handleClick: Key pressed: " << keyEvent.code << std::endl;
}

void DebugOverlay::setText(unsigned int row, unsigned int col, const std::string& text) {
    if (row < gridConfig.rows && col < gridConfig.cols) {
        cells[row][col].text.setString(text);
    }
}

void DebugOverlay::setButton(unsigned int row, unsigned int col, const std::string& label) {
    if (row < gridConfig.rows && col < gridConfig.cols) {
        cells[row][col].text.setString(label);
        cells[row][col].isButton = true;
    }
}

void DebugOverlay::setEditable(unsigned int row, unsigned int col, bool editable) {
    if (row < gridConfig.rows && col < gridConfig.cols) {
        cells[row][col].isEditable = editable;
    }
}