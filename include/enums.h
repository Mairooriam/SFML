#include <SFML/Graphics/Color.hpp>
#include <string>
#ifndef ENUMS_H
#define ENUMS_H
enum NodeType{
    NODE_EMPTY = 0,
    NODE_PLAYER,
    NODE_ENEMY,
    NODE_WALL_1,
    NODE_WALL_2,
    NODE_WALL_3,
    NODE_WALL_4,
    NODE_HOVER
};

enum button_states{
    BTN_IDLE = 0,
    BTN_ACTIVE,
    BTN_HOVER
    
};

enum TextureEnum{
    WALL_VERTICAL = 0,
    WALL_HORIZONTAL,
    WALL_JUNCTION,
    WALL_CORNER_BOTTOM_LEFT,
    WALL_CORNER_BOTTOM_RIGHT,
    WALL_CORNER_TOP_LEFT,
    WALL_CORNER_TOP_RIGHT,
    FLOOR_GREEN
};
enum TextureFileNames{
    TEXTURE_KISSA = 0,
    TEXTURE_WALL
};
sf::Color nodeTypeToColor(NodeType type);
std::string nodeTypeToString(NodeType type);
#endif // ENUMS_H