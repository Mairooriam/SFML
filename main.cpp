//#include "Game.h"
#include <SFML/Graphics/Font.hpp>
#include <vector>
#include <bitset>
//#include "enums.h"
#include "resourceManager.hpp"
#include "gameStateManager.hpp"



int main() {

    sf::RenderWindow window(sf::VideoMode(800, 600), "Game");
    GameStateManager stateManager;
    // Initialize ResourceManager
    ResourceManager& resourceManager = ResourceManager::getInstance();
    // Enable debug printing
    GameStateManager::enableDebug();

    stateManager.pushState(std::make_unique<GameStateManager::MenuState>(stateManager));

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

 
    // Game game;
    // game.run();
    return 0;


    // std::bitset<4> bitsetExample("0010");

    // // Print the entire bitset
    // std::cout << bitsetExample << "\n";

    // // Print each bit individually
    // for (size_t i = 0; i < bitsetExample.size(); ++i) {
    //     std::cout << bitsetExample[i] << "\n";
    // }
    // std::cout << "bitset in int: " << bitsetExample.to_ulong() << "\n";
    // if (bitsetExample.to_ulong() == 1){
    //     // WALL AT TOP
    // }
     // if (bitsetExample.to_ulong() == 2){
    //     // WALL AT BOTTOM
    // }
      // if (bitsetExample.to_ulong() == 4){
    //     // WALL AT LEFT
    // }
     // if (bitsetExample.to_ulong() == 8){
    //     // WALL AT RIGHT
    // }
   

    // return 0;

   
}

