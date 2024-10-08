#include <SFML/Graphics/Color.hpp>
#include <string>
#ifndef ENUMS_H
#define ENUMS_H
enum NodeType{
    NODE_EMPTY = 0,
    NODE_PLAYER,
    NODE_ENEMY,
    NODE_WALL,
    NODE_HOVER
};

enum button_states{
    BTN_IDLE = 0,
    BTN_ACTIVE,
    BTN_HOVER
    
};
sf::Color nodeTypeToColor(NodeType type);
std::string nodeTypeToString(NodeType type);
#endif // ENUMS_H