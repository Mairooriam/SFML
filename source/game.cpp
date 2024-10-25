#include "game.hpp"
Game::Game() : window(sf::VideoMode(800, 600), "SFML Game"), stateManager(*this) {
    // TODO: add calc into initmap to size/16 to get multiplier to scale sprite accordingly
    this->initMap(2,sf::Vector2f(16,16),0.0f);
}

void Game::run(){
    this->stateManager.pushState(std::make_unique<GameStateManager::MenuState>(stateManager));
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            stateManager.handleEvent(event);
        }

        stateManager.update(sf::seconds(1.f / 60.f));

        window.clear();
        stateManager.render(window);
        window.display();
    }
}

void Game::initMap(size_t mapSize, sf::Vector2f nodeSize, float offset){
    ResourceManager& resourceManager = ResourceManager::getInstance();
    offset += nodeSize.x;
    for (size_t i = 0; i < mapSize; ++i) {
        std::vector<Node> row;
        for (size_t j = 0; j < mapSize; ++j) {
            row.emplace_back(sf::Vector2f(j * offset, i * offset), resourceManager.getFont("arial"),resourceManager.createSprite16x16("wall_textures",WALL_HORIZONTAL));
        }
    map.push_back(row);
    }
}

void Game::drawMap() {
    for (size_t i = 0; i < map.size(); ++i) { // Use size() to get the number of rows
        for (size_t j = 0; j < map[i].size(); ++j) { // Use size() to get the number of columns
            // Assuming Node has a draw method that takes a window reference
            map[i][j].draw(window);
        }
    }

    
    //std::cout << "DRAWING MAP\n" << "map size: " << map.size() << "\n" ;
}

void Game::printMap() {
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            // Assuming Node has a method to get its position or relevant information
            map[i][j].printNodeInfo();
        }
    }
}