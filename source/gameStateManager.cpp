#include "gameStateManager.hpp"
#include "game.hpp" // Include the header file for the Game class

#include "resourceManager.hpp" // Include the resource manager header
// Initialize the debug flag
bool GameStateManager::debugEnabled = false;

// Constructor accepting a pointer to Game
GameStateManager::GameStateManager(Game& game, sf::RenderWindow& window) : game(game), window(window) {}

// GameStateManager Methods
void GameStateManager::pushState(std::unique_ptr<GameState> state) {
    states.push(std::move(state));
    debugPrint("State pushed. Current state count: " + std::to_string(states.size()));
}

void GameStateManager::popState() {
    if (!states.empty()) {
        states.pop();
        debugPrint("State popped. Current state count: " + std::to_string(states.size()));
    }
}

void GameStateManager::changeState(std::unique_ptr<GameState> state) {
    if (!states.empty()) {
        states.pop();
    }
    states.push(std::move(state));
    debugPrint("State changed. Current state count: " + std::to_string(states.size()));
}

GameState* GameStateManager::getCurrentState() {
    if (states.empty()) {
        return nullptr;
    }
    return states.top().get();
}

void GameStateManager::handleEvent(sf::Event& event) {
    if (!states.empty()) {
        states.top()->handleEvent(event);
    }
}
void GameStateManager::handleMouseEvent(sf::Event& event) {
    enableDebug();
    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("PlayState: Left Mouse Button Pressed");
            // Handle left mouse button press
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("PlayState: Right Mouse Button Pressed");
            // Handle right mouse button press
        }
    } else if (event.type == sf::Event::MouseButtonReleased) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            debugPrint("PlayState: Left Mouse Button Released");
            // Handle left mouse button release
        } else if (event.mouseButton.button == sf::Mouse::Right) {
            debugPrint("PlayState: Right Mouse Button Released");
            // Handle right mouse button release
        }
    disableDebug();
    } else if (event.type == sf::Event::MouseMoved) {
        
        debugPrint("PlayState: Mouse Moved to (" + std::to_string(event.mouseMove.x/16) + ", " + std::to_string(event.mouseMove.y/16) + ")");
        // Handle mouse move
    }
}
void GameStateManager::update(sf::Time deltaTime) {
    if (!states.empty()) {
        states.top()->update(deltaTime);
    }
}

void GameStateManager::render(sf::RenderWindow& window) {
    if (!states.empty()) {
        states.top()->render(window);
    }
}

