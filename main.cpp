#include "Game.h"
#include <SFML/Graphics/Font.hpp>
    #include <vector>

int main() {
   


    Game game;
    game.run();
    return 0;





   

    // sf::Texture texture;
    // if (!texture.loadFromFile("resources/sfml_logo.png")) {
    //     // error out here
    //     std::cout << "Error loading texture!" << std::endl;
    // }

    // std::vector<sf::Sprite> sprites;
    // sprites.emplace_back(texture);
    // sprites.emplace_back(texture);
    // sprites.emplace_back(texture);

    // sf::RenderWindow window(sf::VideoMode(800, 600), "SFML works!");

    // while (window.isOpen())
    // {
    //     sf::Event event;
    //     while (window.pollEvent(event))
    //     {
    //         if (event.type == sf::Event::Closed)
    //             window.close();
    //     }

    //     window.clear();
    //     for (int x = 0; x < sprites.size(); x++) {
    //         sprites[x].setPosition(x*10.0f,x*10.0f);
    //         window.draw(sprites[x]);
    //     }
    //     window.display();
    // }

    // return 0;

}

