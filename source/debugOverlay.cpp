#include "debugOverlay.h"

DebugOverlay::DebugOverlay() : yOffset(0.0f) {
    if (!font.loadFromFile("resources/arial.ttf")) {
        // Handle error
    }
}

void DebugOverlay::addTextField(const std::string label, const std::string& value) {
    TextField textField;
    textField.label = label;
    textField.value = value;
    textField.text.setFont(font);
    textField.text.setString(label + ": " + value);
    textField.text.setPosition(10.0f, yOffset);
    textField.text.setCharacterSize(14);
    textField.text.setFillColor(sf::Color::White);
    textFields.push_back(textField);
    yOffset += 20.0f; // Adjust the offset for the next text field
}

void DebugOverlay::updateTextField(const std::string label, const std::string& value) {
    for (auto& textField : textFields) {
        if (textField.label == label) {
            textField.value = value;
            textField.text.setString(label + ": " + value);
            break;
        }
    }
}

void DebugOverlay::draw(sf::RenderWindow& window) {
    for (const auto& textField : textFields) {
        window.draw(textField.text);
    }
}