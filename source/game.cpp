#include "Game.h"

#include <iostream>
#include "vectorOperators.h"
Game::Game()
    : window(sf::VideoMode(800, 600), "SFML Window with Shape"),
      view(sf::FloatRect(0, 0, 800, 600)) {
    const sf::Vector3f initialVelocity(1.0f, 0.0f, 0.0f);
    sf::Vector3f position(0.0f, 0.0f,0.0f);

    for (size_t offset = 0; offset < 1; offset++) {
        balls.emplace_back(5, position, initialVelocity);
    }

    
    // Instead of setting the size, use zoom to zoom out
    view.zoom(1.0f); // Zoom out by a factor of 2 (0.5 means zoom out)
    window.setView(view);
}

void Game::run() {
    sf::Clock clock;
    sf::Time timeSinceLastUpdate = sf::Time::Zero;
    const sf::Time TimePerFrame = sf::seconds(1.0f / 60.0f);
    //const sf::Time TimePerFrame = sf::seconds(1.0f);
    while (window.isOpen()) {
        sf::Time deltaTime = clock.restart();
        timeSinceLastUpdate += deltaTime;
        totalElapsedTime += deltaTime;
        while (timeSinceLastUpdate > TimePerFrame) {
            timeSinceLastUpdate -= TimePerFrame;
            processEvents();
            update(totalElapsedTime);
        }

        render();
    }
}

void Game::processEvents() {
    sf::Event event;
    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            window.close();
        if (event.type == sf::Event::MouseButtonReleased){
            sf::Vector2 position = sf::Mouse::getPosition();
            //std::cout << "clieck at X:" << position.x << "Y:" << position.y << "\n";
            sf::Vector2f mousepos(position.x,position.y);
            std::cout << "mosuepos:" << mousepos<< "\n";
            sf::FloatRect textrect = text.getGlobalBounds();
            // if (text.getGlobalBounds().contains(mousepos)){
            //      std::printf("MOUSE HIT TEXT");
            // }
        }
    }
}

void Game::update(sf::Time totalElapsedTime) {
    for (auto& ball : balls) {
        if(!ball.update(totalElapsedTime.asSeconds())){
            totalElapsedTime = sf::seconds(0);
        };
    }
}

void Game::render() {
    window.clear();
     // Declare and load a font
    sf::Font font;
    font.loadFromFile("resources/arial.ttf");
    text.setFont(font);
    text.setString("HELOOOOO");
    // Create a text
    
    text.setCharacterSize(100);
    text.setStyle(sf::Text::Bold);
    text.setFillColor(sf::Color::Red);
    //sf::Rect textrect = text.getGlobalBounds();

    //std::cout << "left: " << textrect.left << "top: "<< textrect.top  << "textect sode X:" << textrect.getSize().x <<"textect sode Y:" << textrect.getSize().y <<"\n";
    window.draw(text);
    

    
    for (auto& ball : balls) {
        ball.draw(window);
    }
    window.display();
}