#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

int main() {
    // Create a window
    sf::RenderWindow window(sf::VideoMode(800, 600), "SFML Music Example");

    // Load a music file
    sf::Music music;
    if (!music.openFromFile("resources/doodle_pop.ogg")) {
        std::cerr << "Error loading music file" << std::endl;
        return -1;
    }

    // Play the music
    music.play();

    // Main loop
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.display();
    }

    return 0;
}