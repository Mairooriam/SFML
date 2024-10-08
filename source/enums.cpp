#include "enums.h"
#include <string>
#include <SFML/Graphics/Color.hpp>
sf::Color nodeTypeToColor(NodeType type){
    switch (type) {
        case NodeType::NODE_EMPTY: return sf::Color::Magenta;
        case NodeType::NODE_PLAYER: return sf::Color::Green;
        case NodeType::NODE_ENEMY: return sf::Color::Red;
        case NodeType::NODE_WALL: return sf::Color::Blue;
        case NodeType::NODE_HOVER: return sf::Color::Yellow;
        default: return sf::Color::Black;
    }
}



std::string nodeTypeToString(NodeType type) {
    switch (type) {
        case NODE_EMPTY: return "Empty";
        case NODE_PLAYER: return "Player";
        case NODE_ENEMY: return "Enemy";
        case NODE_WALL: return "Wall";
        case NODE_HOVER: return "Hover";
        default: return "Unknown";
    }
}
