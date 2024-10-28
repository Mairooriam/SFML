#include "game.hpp"

bool Game::debugEnabled = false; // Define the static member

Game::Game() : window(sf::VideoMode(800, 600), "SFML Game") {
    // TODO: add calc into initmap to size/16 to get multiplier to scale sprite accordingly
    this->initMap(10,sf::Vector2f(16,16),0.0f);
    this->populateNodeNeighbours();
}

void Game::run() {
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleMouseEvent(event);
        }
       
        // Update game logic here
        // For example, you can call a method to update the game state
        update(sf::seconds(1.f / 60.f));

        window.clear();
        // Render the game here
        drawMap();
        window.display();
    }
}
void Game::handleMouseEvent(sf::Event &event)
{
    
    enableDebug();
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("Game::handleMouseEvent: Left Mouse Button Pressed [(" + std::to_string(mousePosWindow.x) + ", " + std::to_string(mousePosWindow.y) + "),("  + std::to_string(mousePosWorld.x) + ", " + std::to_string(mousePosWorld.y) + ")]");
            map[mousePosWorld.x][mousePosWorld.y].printNeighbours();
            map[mousePosWorld.x][mousePosWorld.y].setNodeWall();
            map[mousePosWorld.x][mousePosWorld.y].printNeighbourBitSet();
            // Handle left mouse button press
            
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("Game::handleMouseEvent: Right Mouse Button Pressed");
            // Handle right mouse button press
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("Game::handleMouseEvent: Left Mouse Button Released");
            
            // Handle left mouse button release1
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("Game::handleMouseEvent: Right Mouse Button Released");
            // Handle right mouse button release
        }
    disableDebug();
    } else if (event.type == sf::Event::MouseMoved) {
        updateMousePos(event.mouseMove.x,event.mouseMove.y);
        //map[mousePosWorld.x][mousePosWorld.y].cycleTextures();
        
        //debugPrint("Game::handleMouseEvent: Mouse Moved to [(" + std::to_string(mousePosWindow.x) + ", " + std::to_string(mousePosWindow.y) + "),("  + std::to_string(mousePosWorld.x) + ", " + std::to_string(mousePosWorld.y) + ")]");
        // Handle mouse move
    }
}
void Game::updateMousePos(int x, int y)
{
    this->mousePosWindow.x = x;
    this->mousePosWindow.y = y;

    
    this->mousePosWorld.x = x/worldScale;
    this->mousePosWorld.y = y/worldScale;
}
void Game::update(sf::Time deltaTime) {
    // Update game state here
    // For example, you can update the positions of game objects
}
Node &Game::getNodeAtPosition()
{
    // TODO: insert return statement here
}
void Game::initMap(size_t mapSize, sf::Vector2f nodeSize, float offset){
    ResourceManager& resourceManager = ResourceManager::getInstance();
    offset += nodeSize.x;
    for (size_t i = 0; i < mapSize; ++i) {
        std::vector<Node> row;
        for (size_t j = 0; j < mapSize; ++j) {
            row.emplace_back(sf::Vector2f(i * offset, j * offset), resourceManager.getFont("arial"),resourceManager.createSprite16x16("wall_textures",FLOOR_GREEN));
        }
    map.push_back(row);
    }
}
void Game::populateNodeNeighbours(){
    for (size_t i = 0; i < map.size(); ++i) { 
        for (size_t j = 0; j < map[i].size(); ++j) {
            Node* topNeighbour = (i > 0) ? &map[i - 1][j] : nullptr;
            Node* leftNeighbour = (j > 0) ? &map[i][j - 1] : nullptr;
            Node* rightNeighbour = (j < map[i].size() - 1) ? &map[i][j + 1] : nullptr;
            Node* bottomNeighbour = (i < map.size() - 1) ? &map[i + 1][j] : nullptr;
            map[i][j].updateNeighbours(topNeighbour, leftNeighbour, rightNeighbour, bottomNeighbour);
        }
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

sf::RenderWindow &Game::getRenderWindow()
{
    return this->window;
}

std::vector<std::vector<Node>> &Game::getMap()
{
    return this->map;
}

void Game::printMap() {
    for (size_t i = 0; i < map.size(); ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            // Assuming Node has a method to get its position or relevant information
            map[i][j].printNodeInfo();
        }
    }
}