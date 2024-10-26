#ifndef GAME_STATE_MANAGER_HPP
#define GAME_STATE_MANAGER_HPP

#include <SFML/Graphics.hpp>
#include <memory>
#include <stack>
#include <iostream>
#include "node.hpp"
// Forward declaration of the Game class
class Game;

class GameState {
public:
    virtual ~GameState() = default;
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void handleMouseEvent(sf::Event& event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
};

class GameStateManager {
public:
    GameStateManager(Game& game, sf::RenderWindow& window); // Constructor accepting a pointer to Game
    /**
     * @class GameStateManager
     * @brief Manages the stack of game states, allowing for pushing, popping, and changing states.
     */

    /**
     * @brief Pushes a new state onto the stack.
     * @param state A unique pointer to the new game state to be pushed.
     */
    void pushState(std::unique_ptr<GameState> state);

    /**
     * @brief Pops the current state from the stack.
     */
    void popState();

    /**
     * @brief Changes the current state by replacing it with a new state.
     * @param state A unique pointer to the new game state to replace the current state.
     */
    void changeState(std::unique_ptr<GameState> state);

    /**
     * @brief Retrieves the current state from the stack.
     * @return A pointer to the current game state.
     */
    GameState* getCurrentState();

    /**
     * @brief Handles an event by passing it to the current state.
     * @param event The event to be handled.
     */
    void handleEvent(sf::Event& event);
     /**
     * @brief Handles an event by passing it to the current state.
     * @param event The event to be handled.
     */
    void handleMouseEvent(sf::Event& event);
    /**
     * @brief Updates the current state with the given delta time.
     * @param deltaTime The time elapsed since the last update.
     */
    void update(sf::Time deltaTime);

    /**
     * @brief Renders the current state to the given window.
     * @param window The window to render the current state to.
     */
    void render(sf::RenderWindow& window);

    // Methods to enable/disable debug printing
    static void enableDebug() { debugEnabled = true; }
    static void disableDebug() { debugEnabled = false; }
    // Debug print method
    static void debugPrint(const std::string& message) {
        if (debugEnabled) {
            std::cout << message << std::endl;
        }
    }
private:
    Game& game;
    sf::RenderWindow& window;
    std::stack<std::unique_ptr<GameState>> states;
    static bool debugEnabled;
};

#endif // GAME_STATE_MANAGER_HPP