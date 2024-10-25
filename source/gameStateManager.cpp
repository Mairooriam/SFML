#include "gameStateManager.hpp"

// Initialize the debug flag
bool GameStateManager::debugEnabled = false;

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

// MenuState Methods
void GameStateManager::MenuState::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        debugPrint("MenuState: Key Pressed");
        if (event.key.code == sf::Keyboard::Escape) {
            debugPrint("MenuState: Switching to PlayState");
            manager.changeState(std::make_unique<GameStateManager::PlayState>(manager));
        }
    }
}

void GameStateManager::MenuState::update(sf::Time deltaTime) {
    // Update logic here
}

void GameStateManager::MenuState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Blue);
    // Add rendering code here
}

// PlayState Methods
void GameStateManager::PlayState::handleEvent(sf::Event& event) {
    if (event.type == sf::Event::KeyPressed) {
        debugPrint("PlayState: Key Pressed");
        if (event.key.code == sf::Keyboard::Escape) {
            debugPrint("PlayState: Switching to MenuState");
            manager.changeState(std::make_unique<GameStateManager::MenuState>(manager));
        }
    }
}

void GameStateManager::PlayState::update(sf::Time deltaTime) {
    // Update logic here
}

#include "resourceManager.hpp" // Include the resource manager header

void GameStateManager::PlayState::render(sf::RenderWindow& window) {
    window.clear(sf::Color::Green);
    
    // Example usage of ResourceManager to load and draw a texture
    // Example usage of ResourceManager to load and draw a texture
    ResourceManager& resourceManager = ResourceManager::getInstance();
    sf::Sprite sprite = resourceManager.createSprite16x16("wall_textures", WALL_CORNER_BOTTOM_RIGHT);
    sprite.setScale(10,10);
    window.draw(sprite);
    
    // Add more rendering code here
}
