#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Ball.h"
#include <SFML/Window/Mouse.hpp>
#include "debugOverlay.h"
#include "uiElements.h"
#include "enums.h"
class Game {
public:
    Game();
    void run();
    sf::RenderWindow window;
    sf::Vector2i mousePos;
    sf::Text text;
    DebugOverlay debugOverlay;
    std::vector<Button> buttons;
    std::vector<std::vector<Node>> map;
private:
    void processEvents();
    void processKeyPressed(sf::Event *event);
    void update(sf::Time totalElapsedTime);
    void updateWalls();
    void render();

    // init stuff
    void initButtons();
    void initMap(size_t mapSize, sf::Vector2f nodeSize, float offset);
    int initFonts();
    int initTextures();
    int initDebugWindow();
    std::vector<sf::Texture> textures;
    NodeType selectedHotkey = NODE_EMPTY;
    std::vector<Ball> balls;
    sf::Time totalElapsedTime;
    sf::View view;
    sf::Font font;
};

#endif // GAME_H