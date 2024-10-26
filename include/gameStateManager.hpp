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
    
    virtual void handleEvent(sf::Event& event) = 0;
    virtual void handleMouseEvent(sf::Event& event) = 0;
    virtual void update(sf::Time deltaTime) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual ~GameState() = default;
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

    class MenuState : public GameState {
    public:
        MenuState(GameStateManager& manager) : manager(manager) {}
        void handleEvent(sf::Event& event) override;
        void handleMouseEvent(sf::Event& event) override;
        void update(sf::Time deltaTime) override;
        void render(sf::RenderWindow& window) override;
    private:
        GameStateManager& manager;
        Game& getGame() { return manager.getGame(); }
        sf::RenderWindow& getRenderWindow() { return manager.getRenderWindow(); }
    };

    class PlayState : public GameState {
    public:
        PlayState(GameStateManager& manager) : manager(manager) {}
        void handleEvent(sf::Event& event) override;
        void handleMouseEvent(sf::Event& event) override;
        void update(sf::Time deltaTime) override;
        void render(sf::RenderWindow& window) override;
    private:
        GameStateManager& manager;
        Game& getGame() { return manager.getGame(); }
        sf::RenderWindow& getRenderWindow() { return manager.getRenderWindow(); }
    };
    Game& getGame() { return game; }
    sf::RenderWindow& getRenderWindow() { return window; }
private:
    Game& game; // Pointer to the Game class
    sf::RenderWindow& window;
    /**
     * @brief A stack of unique pointers to game states.
     */
    std::stack<std::unique_ptr<GameState>> states;
    static bool debugEnabled; // Debug flag

        // Debug print method
    static void debugPrint(const std::string& message) {
        if (debugEnabled) {
            std::cout << message << std::endl;
        }
    }
};

#endif // GAME_STATE_MANAGER_HPP